/////////////////////////////////////////////////////////////////////////////
// eathread_fiber.h
//
// Copyright (c) 2007, Electronic Arts Inc. All rights reserved.
//
// Created by Stuart Riffle, Black Box
/////////////////////////////////////////////////////////////////////////////


#ifndef EATHREAD_EATHREAD_FIBER_H
#define EATHREAD_EATHREAD_FIBER_H


#include <EABase/eabase.h>
#include <eathread/eathread.h>

#if defined(EA_PRAGMA_ONCE_SUPPORTED)
    #pragma once // Some compilers (e.g. VC++) benefit significantly from using this. We've measured 3-4% build speed improvements in apps as a result.
#endif



#if defined( EA_PLATFORM_WIN32 ) && EA_WINAPI_FAMILY_PARTITION(EA_WINAPI_PARTITION_DESKTOP)

    #pragma warning( push )
    #pragma warning( disable: 4311 )    // 'variable' : pointer truncation from 'type' to 'type'
    #pragma warning( disable: 4312 )    // 'operation' : conversion from 'type1' to 'type2' of greater size
    #pragma warning( disable: 4611 )    // interaction between '_setjmp' and C++ object destruction is non-portable
    #pragma warning( disable: 4702 )    // unreachable code

    #define EATHREAD_FIBERS_AVAILABLE   (1)
    #define EXPECTED( _cond )           (_cond)
    #define NOT_EXPECTED( _cond )       (_cond)
    #define FIELD_ALIGN 

    EATHREADLIB_API void CallWithStack( void (*func)( void* ), void* info, void* stackBase, int stackSize );

#elif defined( EA_PLATFORM_PS3_SPU )

    #define EATHREAD_FIBERS_AVAILABLE   (1)
    #define EXPECTED( _cond )           __builtin_expect( (_cond), 1 )
    #define NOT_EXPECTED( _cond )       __builtin_expect( (_cond), 0 )
    #define FIELD_ALIGN                 __attribute(( aligned( 16 ) ))

    extern "C" void CallWithStack( void (*func)( void* ), void* info, void* stackBase, int stackSize );

#endif



#if defined( EATHREAD_FIBERS_AVAILABLE )

#include <eathread/eathread_sync.h>
#include <setjmp.h>

// Allow user to activate asserts, otherwise ignore them
#if !defined( EAFIBER_ASSERT )
#define EAFIBER_ASSERT( _cond )
#endif


//-------------------------------------------------------------------------------------------
/// Minimal single ended queue implemented as a circular array
/// 
template< typename TELEM, int CAPACITY >
class Pow2Queue
{
public:
    enum { CAPACITY_MASK = CAPACITY - 1 };

    Pow2Queue() : mCount( 0 ), mStartIdx( 0 ) {}

    inline int      GetCount() const    { return( mCount ); }
    inline bool     IsEmpty() const     { return( mCount == 0 ); }
    inline void     Clear()             { mCount = 0; }

    inline void PushFront( const TELEM& elem )
    {
        EAFIBER_ASSERT( mCount < CAPACITY );
        mStartIdx = (mStartIdx - 1) & CAPACITY_MASK;
        mElem[mStartIdx] = elem;
        mCount++;
    }

    inline TELEM PopBack()
    {
        EAFIBER_ASSERT( mCount > 0 );
        mCount--;
        int slotIdx = (mStartIdx + mCount) & CAPACITY_MASK;
        return( mElem[slotIdx] );
    }

private:
    TELEM   mElem[CAPACITY] FIELD_ALIGN;
    int     mCount          FIELD_ALIGN;
    int     mStartIdx       FIELD_ALIGN;
};


namespace EA { 
    namespace Thread {

        //-------------------------------------------------------------------------------------------
        /// Fiber system
        /// 
        /// \author     Stuart Riffle (Black Box)
        /// \date       5/13/2007
        ///
        /// The fiber system allows cooperative multitasking by keeping track of multiple execution
        /// contexts, each with its own callstack. All fibers in a fiber system execute within a
        /// single thread. Control is switched between the fibers manually. Fibers are not pre-empted, 
        /// so it's possible for a fiber that never blocks and never yields to just run to completion 
        /// like a normal function call.
        ///
        /// This class can be extended to provide automatic fiber switching for specialized purposes.
        /// For example, there's an SPU fiber system that switches fibers when they block on DMA
        /// transfers. 
        /// 
        class FiberSys
        {
        public:

            typedef void (*FiberProc)( FiberSys*, uintptr_t );              ///< Fiber entry point signature

            enum 
            {
                SUSPEND_YIELD           = 0,                                ///< Context suspended because it yielded 
                SUSPEND_JOIN_ALL,                                           ///< Context suspended until all fibers have completed
                SUSPEND_FOR_FIBER_SLOT,                                     ///< Context suspended because it wants to spawn a fiber, but no slots are available
                SUSPEND_REASON_CUSTOM,                                      ///< Derived classes can add new codes starting here

                MAX_FIBER_SLOTS         = 32,                               ///< Maximum number of concurrent fiber contexts (arbitrary)
            };

            FiberSys() : mStackMem( NULL ), mStackSize( 0 ) {}

            virtual ~FiberSys()
            {
                this->Shutdown();
            }

            //---------------------------------------------------------------------------------------
            /// Initialize the fiber system
            ///
            /// \param  stackMem    Block of memory for fiber stack array
            /// \param  stackCount  Number of fiber stacks
            /// \param  stackSize   Size of each fiber stack
            /// 
            void Init( uint8_t* stackMem, int stackCount, int stackSize )
            {
                mStackMem   = stackMem;
                mStackSize  = stackSize;
                mFiberLimit = stackCount;

                for( int onFrame = 0; onFrame < stackCount; onFrame++ )
                    mStacksAvail.PushFront( (uint8_t*) mStackMem + (onFrame * mStackSize) );
            }

            //---------------------------------------------------------------------------------------
            /// Shut down the fiber system
            /// 
            /// If any fibers are still running, this method will stall until they exit.
            /// 
            void Shutdown()
            {
                this->JoinAll();

                mStackMem   = NULL;
                mStackSize  = 0;
                mFiberLimit = 0;
                mStacksAvail.Clear();
                mRunQueue.Clear();
            }

            //---------------------------------------------------------------------------------------
            /// Start executing a new fiber
            ///
            /// \param  func    Fiber entry point
            /// \param  param   User parameter, arbitrary
            ///
            /// This method creates a new fiber context and starts it running. If the system is
            /// already at the maximum number of fibers, the calling fiber will be suspended until
            /// a slot opens up.
            ///
            void Spawn( FiberProc func, uintptr_t param = 0 )
            {
                if( !this->CanSpawnFiber() )
                    this->Suspend( SUSPEND_FOR_FIBER_SLOT );

                this->CreateFiberContext( func, param );
            }

            //---------------------------------------------------------------------------------------
            /// Set limit on the number of spawned fibers
            ///
            /// \param  limit   Max number of spawned fibers
            ///
            /// This is for debugging. If more fibers than this already exist, they will not be
            /// terminated. This limit only prevents new fibers from being spawned.
            ///
            void SetFiberLimit( int limit )
            {
                mFiberLimit = limit;
            }

            //---------------------------------------------------------------------------------------
            /// Suspend the caller and switch to the next fiber that's ready to run
            ///
            void YieldFiber()
            {
                this->Suspend( SUSPEND_YIELD );
            }

            //---------------------------------------------------------------------------------------
            /// Block until all fibers have finished running
            /// 
            /// This should only be called from the main context, not a spawned fiber. Otherwise,
            /// you risk deadlock. TODO: enforce that.
            ///
            void JoinAll()
            {
                this->Suspend( SUSPEND_JOIN_ALL );
            }

        protected:

            //---------------------------------------------------------------------------------------
            /// Saved execution context for a fiber
            ///
            struct Context
            {
                jmp_buf         mState          FIELD_ALIGN;    ///< Saved setjmp/longjmp state
                int             mSuspendReason  FIELD_ALIGN;    ///< Why this context was suspended
                int             mData           FIELD_ALIGN;    ///< Extra data about why this context was suspended
            };

            //---------------------------------------------------------------------------------------
            /// Startup parameters for a fiber
            /// 
            /// These are copied onto the newly created fiber stack by EntryPoint(), because they 
            /// will disappear from the parent's stack after the first context switch.
            ///
            struct SpawnInfo
            {
                FiberSys*       mSys            FIELD_ALIGN;    ///< Fiber system that created the fiber
                FiberProc       mFunc           FIELD_ALIGN;    ///< User function
                uintptr_t       mParam          FIELD_ALIGN;    ///< User function data
                void*           mStackBase      FIELD_ALIGN;    ///< Stack address (so that we can give it back)
            };

            //---------------------------------------------------------------------------------------
            /// Check to see if a fiber is runnable
            /// 
            /// \param  fiberCon    Fiber context
            /// \return             true if the fiber is ready to run
            /// 
            /// Override in your derived class to handle any new reasons for suspending fibers.
            /// 
            virtual bool CanRunFiber( Context * )
            {
                return( true );
            }

            //---------------------------------------------------------------------------------------
            /// Check to see if it's possible to spawn a new fiber
            /// 
            /// \return true if a fiber can be spawned
            /// 
            bool CanSpawnFiber()
            {
                return( (mStacksAvail.GetCount() > 0) && (mRunQueue.GetCount() < mFiberLimit) );
            }

            //---------------------------------------------------------------------------------------
            /// Create an execution context for a new fiber and run it
            ///
            /// \param  func    Fiber entry point
            /// \param  param   User data (arbitrary)
            ///
            /// This method suspends the calling thread, creates a new stack for the fiber, and 
            /// calls the fiber entry point.
            ///
            void CreateFiberContext( FiberProc func, uintptr_t param )
            {
                EAFIBER_ASSERT( mStacksAvail.GetCount() > 0 );

                Context fiberCon;

                if( setjmp( fiberCon.mState ) == 0 )
                {
                    fiberCon.mSuspendReason = SUSPEND_YIELD;
                    fiberCon.mData          = 0;

                    mRunQueue.PushFront( &fiberCon );

                    SpawnInfo info;

                    info.mSys       = this;
                    info.mFunc      = func;
                    info.mParam     = param;
                    info.mStackBase = mStacksAvail.PopBack();

                    EACompilerMemoryBarrier();

                    CallWithStack( FiberSys::EntryPoint, &info, info.mStackBase, mStackSize );
                }
            }

            //---------------------------------------------------------------------------------------
            /// Generic fiber entry point
            /// 
            /// \param  data    Pointer to SpawnInfo structure for fiber 
            /// 
            /// At this point, we're using the fiber's new stack. But the SpawnInfo structure is 
            /// sitting on the stack of the fiber which created us, so we need to make a local
            /// copy before giving control to the user code.
            /// 
            /// Once the fiber is done, the context is terminated.
            ///
            static void EntryPoint( void* data )
            {
                SpawnInfo info;
                info = *((SpawnInfo*) data);

                EACompilerMemoryBarrier();

                info.mFunc( info.mSys, info.mParam );
                info.mSys->Terminate( info.mStackBase );
            }

            //---------------------------------------------------------------------------------------
            /// Suspend the current context, and switch to a different one
            ///
            /// \param  reason  Reason for suspension, one of the SUSPEND_* enum values
            /// \param  data    Optional extra info, the meaning depends on the suspension type
            ///
            void Suspend( int reason, int data = 0 )
            {
                Context fiberCon;

                if( EXPECTED( setjmp( fiberCon.mState ) == 0 ) )
                {
                    fiberCon.mSuspendReason = reason;
                    fiberCon.mData          = data;

                    mRunQueue.PushFront( &fiberCon );
                    this->Switch();
                }
            }

            //---------------------------------------------------------------------------------------
            /// Kill a fiber context
            ///
            /// \param  stackBase   Fiber stack
            ///
            /// This is a little wierd. The way we kill a fiber is by switching away without saving
            /// the current context first. After we do this, control will never return, because our
            /// context will no longer be in the run queue. 
            ///
            void Terminate( void* stackBase )
            {
                mStacksAvail.PushFront( stackBase );
                this->Switch();

                // Control will never get here!
                
                for( ;; ) EAFIBER_ASSERT( 0 );
            }

            //---------------------------------------------------------------------------------------
            /// Switch to the next fiber that can be run
            ///
            /// Fibers are processed in round-robin fashion. If a fiber is not yet ready to run, it
            /// will be skipped. There is no priority system, and no scheduling is attempted.
            ///
            void Switch()
            {
                for( ;; )
                {
                    Context* next     = mRunQueue.PopBack();
                    bool     runnable = true;

                    switch( next->mSuspendReason )
                    {
                        case SUSPEND_YIELD:
                            break;

                        case SUSPEND_JOIN_ALL:
                            runnable = mRunQueue.IsEmpty();
                            break;

                        case SUSPEND_FOR_FIBER_SLOT:
                            runnable = this->CanSpawnFiber();
                            break;

                        default:
                            runnable = this->CanRunFiber( next );
                            break;
                    }

                    if( runnable )
                        longjmp( next->mState, 1 );

                    mRunQueue.PushFront( next );
                }
            }

            Pow2Queue< Context*, MAX_FIBER_SLOTS >  mRunQueue       FIELD_ALIGN;    ///< Active fibers
            Pow2Queue< void*,    MAX_FIBER_SLOTS >  mStacksAvail    FIELD_ALIGN;    ///< Available stacks for new fibers
            void*                                   mStackMem       FIELD_ALIGN;    ///< Block of memory that contains all the fiber stacks
            int                                     mStackSize      FIELD_ALIGN;    ///< Size of each fiber stack
            int                                     mFiberLimit     FIELD_ALIGN;    ///< Maximum number of fibers that can be spawned at once
        };

    } // namespace Thread
} // namespace EA


#undef EXPECTED
#undef NOT_EXPECTED
#undef FIELD_ALIGN 


#endif // EATHREAD_FIBERS_AVAILABLE


#if defined( EA_PLATFORM_WIN32 ) && EA_WINAPI_FAMILY_PARTITION(EA_WINAPI_PARTITION_DESKTOP)
    #pragma warning( pop )
#endif





#endif // EATHREAD_EATHREAD_FIBER_H

