/////////////////////////////////////////////////////////////////////////////
// eathread_atomicstruct.h
//
// Copyright (c) 2008, Electronic Arts Inc. All rights reserved.
//
// STATUS: BETA
// A version of this code has shipped on PS3. The implementation on other
// platforms involves significant new code, which has not been tested as
// extensively. 
// 
// Created by Stuart Riffle, Black Box
/////////////////////////////////////////////////////////////////////////////

//
//  Hardware support for atomic operations is limited to single words. These 
//  templates provide a portable way to atomically modify structures of any size. 
//  
//  -   The most efficient implementation is automatically chosen. On machines 
//      with LLR support (like PS3), we can use native operations for structures 
//      up to 8 bytes. On CAS architectures (like PC), we can support up to 4
//      bytes natively (64-bit compare and swap only allows for 4 bytes of 
//      payload, because the other 4 bytes are used for a version counter to 
//      avoid the ABA problem).
//  -   When a client reads the structure, he sees an internally consistent
//      snapshot of the fields.
//  -   When a client modifies the structure, all fields are committed at
//      once, and the entire transaction either succeeds or fails atomically.
//  -   This is done without locking; in fact, the higher level lock-free
//      containers are based on atomic structures. 
//  
//  To modify a structure atomically, you declare it like so:
//   
//      struct QueueInfo
//      {
//          Node*   mHead;
//          Node*   mTail;
//      };
//   
//      AtomicStruct< QueueInfo > mInfo;
//   
//  
//  And then edit it with the magic macros:
//   
//      ATOMIC_UPDATE_BEGIN( QueueInfo, &mInfo, info )
//          tailPrev    = info->mTail;
//          info->mTail = last;
//          info->mHead = info->mHead? info->mHead : first;
//      ATOMIC_UPDATE_END()
//   
//  
//  Or you can do it manually... the macros expand as shown below. The user code 
//  is re-executed until the transaction successfully commits.
//   
//      AtomicTransaction< QueueInfo > trans( &mInfo );
//       
//      for( ;; )
//      {
//          QueueInfo* info = trans.Begin();
//       
//          tailPrev    = info->mTail;
//          info->mTail = last;
//          info->mHead = info->mHead? info->mHead : first;
//       
//          if( trans.Commit() )
//              break;
//      }
//

#ifndef EATHREAD_EATHREAD_ATOMICSTRUCT_H
#define EATHREAD_EATHREAD_ATOMICSTRUCT_H


#include <EABase/eabase.h>
#include <eathread/eathread.h>
#include <eathread/eathread_sync.h>
#include <eathread/eathread_atomic.h>

#ifdef _MSC_VER
    #pragma once
    #pragma warning(push)
    #pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#endif

#if defined(EA_PRAGMA_ONCE_SUPPORTED)
    #pragma once // Some compilers (e.g. VC++) benefit significantly from using this. We've measured 3-4% build speed improvements in apps as a result.
#endif


#if defined(EA_PLATFORM_MICROSOFT) || defined( EA_PLATFORM_PS3 ) || defined( EA_PLATFORM_PS3_SPU ) || defined( EA_PLATFORM_OSX )
    #define EATHREAD_ATOMICSTRUCTS_AVAILABLE (1)
#endif


#if EATHREAD_ATOMICSTRUCTS_AVAILABLE

namespace EA 
{ 
    namespace Thread 
    {
        template< typename T >  struct  AtomicStructSelect;

        //-------------------------------------------------------------------------------------------
        /// Atomic structure
        /// 
        /// \author     Stuart Riffle (Black Box)
        /// \date       1/23/2008
        ///
        /// This is just a shell class. The templates will choose an implementation based on the 
        /// size of the structure. 
        /// 
        template< typename T >
        struct AtomicStruct : public AtomicStructSelect< T >::StructType
        {
            typedef typename AtomicStructSelect< T >::StructType TSTRUCT;

            //---------------------------------------------------------------------------------------
            /// Take a snapshot of the structure
            ///
            /// \param  dest    Where to store the snapshot
            /// 
            /// This function fills the destination with an internally consistent snapshot of the
            /// current value of the atomic structure. This is used for read-only access to the
            /// structure. Changing the data is done using an AtomicTransaction<>.
            /// 
            EA_FORCE_INLINE void ReadCurrentValue( T* dest ) { TSTRUCT::ReadCurrentValue( dest ); }
        };

        //-------------------------------------------------------------------------------------------
        /// Atomic transaction
        /// 
        /// \author     Stuart Riffle (Black Box)
        /// \date       1/23/2008
        ///
        /// This is just a shell class. The templates will choose an implementation based on the 
        /// size of the structure.
        /// 
        template< typename T >
        struct AtomicTransaction : public AtomicStructSelect< T >::TransactionType 
        {
            typedef typename AtomicStructSelect< T >::TransactionType   TTRANS;
            typedef typename AtomicStructSelect< T >::StructType        TSTRUCT;

            //---------------------------------------------------------------------------------------
            /// Atomic transaction constructor
            ///
            /// \param  atomicStruct    Structure to be modified
            /// 
            /// For large structures, attempting a transaction requires reserving a slot in the
            /// structure to store an updated copy of the data. This only needs to be done once,
            /// for the lifetime of the transaction, not every time an update is attempted. So if
            /// you need to do multiple updates, it is a bit more efficient to reuse the same
            /// transaction.
            ///
            /// However, since the slot is reserved for the lifetime of the transaction, and there
            /// are a limited number of slots available, this object must be temporary. Declare
            /// it on the stack, not at global scope. 
            /// 
            EA_FORCE_INLINE AtomicTransaction( TSTRUCT* atomicStruct ) : TTRANS( atomicStruct ) {}

            //---------------------------------------------------------------------------------------
            /// Begin an atomic transaction
            /// 
            /// \return     A snapshot of the data to be edited.
            ///
            /// This call marks the start of a transaction. Modify the structure as needed, then
            /// call Commit() to make the changes visible. 
            /// 
            EA_FORCE_INLINE T* Begin()      { return( TTRANS::Begin() ); }

            //---------------------------------------------------------------------------------------
            /// End an atomic transaction
            /// 
            /// \return     true if the transaction succeeded
            ///
            /// This call marks the end of a transaction. If Commit() returns false, the transaction
            /// failed, and you must once again call Begin() and make your changes. The macros
            /// ATOMIC_UPDATE_BEGIN and ATOMIC_UPDATE_END will do the looping for you if you like.
            /// 
            EA_FORCE_INLINE bool Commit()   { return( TTRANS::Commit() ); }
        };


        // The data we want to update atomically is probably pretty small. But we want to make sure
        // that individual items are in different cache lines, to avoid performance problems. 

        #if defined( EA_PLATFORM_XENON ) || defined( EA_PLATFORM_PS3 ) || defined( EA_PLATFORM_PS3_SPU )
            #define EA_ATOMIC_ALIGNMENT         (128)
            #define EA_PREFIX_ALIGN_ATOMIC      EA_PREFIX_ALIGN( 128 )
            #define EA_POSTFIX_ALIGN_ATOMIC     EA_POSTFIX_ALIGN( 128 )
        #else
            #define EA_ATOMIC_ALIGNMENT         (64)
            #define EA_PREFIX_ALIGN_ATOMIC      EA_PREFIX_ALIGN( 64 )
            #define EA_POSTFIX_ALIGN_ATOMIC     EA_POSTFIX_ALIGN( 64 )
        #endif


        // The following declarations choose the most efficient implementation for the
        // atomic structure, based on the machine type and struct size. 

        enum
        {
            ATOMICSTRUCT_SIZERANGE_32 = 1,
            ATOMICSTRUCT_SIZERANGE_64,
            ATOMICSTRUCT_SIZERANGE_LARGE,
        };

        template< typename T, int SIZERANGE > 
        struct AtomicStructImpl {};

        template< typename T >
        struct AtomicStructSelect
        {
            enum
            {
                SIZEDETECT_32       = (sizeof( T ) <= 4)?                           ATOMICSTRUCT_SIZERANGE_32 : 0,
                SIZEDETECT_64       = ((sizeof( T ) > 4) && (sizeof( T ) <= 8))?    ATOMICSTRUCT_SIZERANGE_64 : 0,
                SIZEDETECT_LARGE    = (sizeof( T ) > 8)?                            ATOMICSTRUCT_SIZERANGE_LARGE : 0,
                SIZERANGE           = SIZEDETECT_32 + SIZEDETECT_64 + SIZEDETECT_LARGE,
            };

            typedef typename AtomicStructImpl< T, SIZERANGE >::StructType       StructType;
            typedef typename AtomicStructImpl< T, SIZERANGE >::TransactionType  TransactionType;
        };

        namespace Detail
        {
            template< typename T, int NUM_SLOTS = 8 >   class   AtomicStructLarge;
            template< typename T, typename TSTRUCT >    class   AtomicTransactionLarge;
            template< typename T >                      class   AtomicStructSmall_CAS;
            template< typename T, typename TSTRUCT >    class   AtomicTransactionSmall_CAS;
            template< typename T, typename TWORD >      class   AtomicStructSmall_LLR;
            template< typename T, typename TSTRUCT >    class   AtomicTransactionSmall_LLR;
        }

        #if defined(EA_THREAD_ATOMIC_LLR_SUPPORTED) && EA_THREAD_ATOMIC_LLR_SUPPORTED

            template< typename T > 
            struct AtomicStructImpl< T, ATOMICSTRUCT_SIZERANGE_32 > 
            { 
                typedef Detail::AtomicStructSmall_LLR< T, uint32_t >        StructType; 
                typedef Detail::AtomicTransactionSmall_LLR< T, StructType > TransactionType; 
            };

            template< typename T > 
            struct AtomicStructImpl< T, ATOMICSTRUCT_SIZERANGE_64 > 
            { 
                typedef Detail::AtomicStructSmall_LLR< T, uint64_t >        StructType; 
                typedef Detail::AtomicTransactionSmall_LLR< T, StructType > TransactionType; 
            };

            template< typename T > 
            struct AtomicStructImpl< T, ATOMICSTRUCT_SIZERANGE_LARGE > 
            { 
                typedef Detail::AtomicStructLarge< T >                      StructType; 
                typedef Detail::AtomicTransactionLarge< T, StructType >     TransactionType; 
            };

        #else

            template< typename T > 
            struct AtomicStructImpl< T, ATOMICSTRUCT_SIZERANGE_32 > 
            { 
                typedef Detail::AtomicStructSmall_CAS< T >                  StructType; 
                typedef Detail::AtomicTransactionSmall_CAS< T, StructType > TransactionType; 
            };

            template< typename T > 
            struct AtomicStructImpl< T, ATOMICSTRUCT_SIZERANGE_64 > 
            { 
                typedef Detail::AtomicStructLarge< T >                      StructType; 
                typedef Detail::AtomicTransactionLarge< T, StructType >     TransactionType; 
            };

            template< typename T > 
            struct AtomicStructImpl< T, ATOMICSTRUCT_SIZERANGE_LARGE > 
            { 
                typedef Detail::AtomicStructLarge< T >                      StructType; 
                typedef Detail::AtomicTransactionLarge< T, StructType >     TransactionType; 
            };

        #endif


        // Helper macros for doing atomic updates. Used like this:
        //
        //      ATOMIC_UPDATE_BEGIN( StackInfo, &mInfo, info )
        //      {
        //          WriteSync32( &node->mNext, (uint32_t) info->mHead );
        //          info->mHead = node;
        //      }
        //      ATOMIC_UPDATE_END()

        #define ATOMIC_UPDATE_BEGIN( _TYPE, _PTR, _VARNAME ) \
            { \
                AtomicTransaction< _TYPE > trans( _PTR ); \
                \
                for( ;; ) \
                { \
                    _TYPE* _VARNAME = trans.Begin();

        #define ATOMIC_UPDATE_END() \
                    if( trans.Commit() ) \
                        break; \
                }\
            }


        // Utility functions for PS3

        #if defined( EA_PLATFORM_PS3_SPU )
        inline uint32_t FindOpenDmaChannel()
        {
            uint32_t firstFree  = si_to_uint( (vector signed char) spu_cntlz( (vector unsigned int) si_from_uint( cellDmaWaitTagStatusImmediate( ~0 ) ) ) );
            uint32_t channelIdx = (31 - firstFree) & 0x1F;

            return( channelIdx );
        }
        #endif


        template< typename T >
        inline void WriteSyncUintptr( T ptr, uintptr_t value ) 
        {
        #if defined( EA_PLATFORM_PS3_SPU )
            cellDmaPutUint32( value, (uint64_t) ptr, FindOpenDmaChannel(), 0, 0 );
        #else
            *((volatile uintptr_t*) ptr) = value;
            (void)ptr; // The PS3 SN compiler still yields a 'parameter "ptr" was set but never used' warning.
            EAWriteBarrier();
        #endif
        }
        #define WriteSync32 WriteSyncUintptr // Temporary backward compatibility.


        template< typename T >
        inline uintptr_t ReadSyncUintptr( T ptr ) 
        {
        #if defined( EA_PLATFORM_PS3_SPU )
            return( cellDmaGetUint32( (uint64_t) ptr, FindOpenDmaChannel(), 0, 0 ) );
        #else
            EAReadBarrier();
            return( *((volatile uintptr_t*) ptr) );
        #endif
        }
        #define ReadSync32 ReadSyncUintptr // Temporary backward compatibility.


        // Implementations

        namespace Detail
        {
            //-------------------------------------------------------------------------------------------
            /// Large atomic structure
            /// 
            /// An array of structures is maintained, controlled by a lock-free slot allocator. The
            /// "active" slot is tracked atomically.
            ///
            template< typename T, int NUM_SLOTS >
            class AtomicStructLarge
            {
                template< typename TELEMENT, typename TSTRUCT > friend class AtomicTransactionLarge;

                struct ControlData
                {
                    ControlData() : mWord(0) {}
                    void IncrementVersionAndSetSlot(int slot) { mWord = (GetVersion() + 0x100) | static_cast<uint64_t>(slot & 0xFF); }
                    uint64_t GetSlot() const { return mWord & 0xFF; }
                    uint64_t GetVersion() const { return mWord & ~static_cast<uint64_t>(0xFF); }
                    uint64_t GetData() const { return mWord; }
                    void SetData(uint64_t data) { mWord = data; }

                private:
                    uint64_t mWord;
                };

                enum
                {
                    ELEMENT_SIZE_PADDED = (sizeof( T ) + EA_ATOMIC_ALIGNMENT - 1) & ~(EA_ATOMIC_ALIGNMENT - 1)
                };

                EA_PREFIX_ALIGN_ATOMIC  AtomicInt< uint64_t >   mControlWord                                EA_POSTFIX_ALIGN_ATOMIC;
                EA_PREFIX_ALIGN_ATOMIC  AtomicInt< uint64_t >   mSlotUsedMap                                EA_POSTFIX_ALIGN_ATOMIC;
                EA_PREFIX_ALIGN_ATOMIC  uint8_t                 mSlotMem[ELEMENT_SIZE_PADDED * NUM_SLOTS]   EA_POSTFIX_ALIGN_ATOMIC;

                ControlData ReadControlData()
                {
                    ControlData data;
                    data.SetData(mControlWord.GetValue());

                    return( data );
                }

                ControlData ReadControlDataAndValue( T* dest )
                {
                    ControlData control = this->ReadControlData();

                    for( ;; )
                    {
                        ControlData previous = control;

                        this->ReadSlot( static_cast<int>(control.GetSlot()), dest );
                        control = this->ReadControlData();

                        if (control.GetVersion() == previous.GetVersion())   // Same as: if( control.mVersion == previous.mVersion )
                            break;

                        EAProcessorPause();
                    }

                    return( control );
                }

                bool WriteControlData( ControlData newData, ControlData prevData )
                {
                    return( mControlWord.SetValueConditional( newData.GetData(), prevData.GetData() ) );
                }

                int AllocSlot()
                {
                    int bitToClaim;

                    for( ;; )
                    {
                        uint64_t slotBits = mSlotUsedMap.GetValue();

                        bitToClaim = 0;

                        for( uint64_t testBits = slotBits; testBits & 1; testBits >>= 1 )
                            bitToClaim++;

                        if( bitToClaim < NUM_SLOTS )
                            if( mSlotUsedMap.SetValueConditional( slotBits | (((uint64_t) 1) << bitToClaim), slotBits ) )
                                break;

                        EAProcessorPause();

                        #if !defined( EA_PLATFORM_PS3_SPU )
                            if( bitToClaim == NUM_SLOTS )
                                ThreadSleep();
                        #endif
                    }

                    return( bitToClaim );
                }

                void FreeSlot( int slotIdx )
                {
                    uint64_t slotMask = ~(((uint64_t) 1) << slotIdx);

                    for( ;; )
                    {
                        uint64_t slotBits = mSlotUsedMap.GetValue();

                        if( mSlotUsedMap.SetValueConditional( slotBits & slotMask, slotBits ) )
                            break;

                        EAProcessorPause();
                    }
                }

                inline T* CalcSlotAddr( int slotIdx )
                {
                    return( (T*) (mSlotMem + slotIdx * ELEMENT_SIZE_PADDED) );
                }

                void ReadSlot( int slotIdx, T* dest )
                {
                    T* slot = this->CalcSlotAddr( slotIdx );

                #if defined( EA_PLATFORM_PS3_SPU )
                    volatile EA_PREFIX_ALIGN_ATOMIC uint8_t local[ELEMENT_SIZE_PADDED] EA_POSTFIX_ALIGN_ATOMIC;
                    uint32_t channel = FindOpenDmaChannel();
                    cellDmaGet( local, (uint64_t) slot, (sizeof( T ) + 0xF) & ~0xF, channel, 0, 0 );
                    cellDmaWaitTagStatusAll( 1 << channel );
                    slot = (T*) local;
                #endif

                    EAReadBarrier();
                    *dest = *slot;
                }

                void WriteSlot( int slotIdx, T* src )
                {
                    T* slot = this->CalcSlotAddr( slotIdx );

                #if defined( EA_PLATFORM_PS3_SPU )
                    EA_PREFIX_ALIGN_ATOMIC T local EA_POSTFIX_ALIGN_ATOMIC = *src;
                    uint32_t channel = FindOpenDmaChannel();
                    spu_dsync();
                    cellDmaPut( local, (uint64_t) slot, (sizeof( T ) + 0xF) & ~0xF, channel, 0, 0 );
                    cellDmaWaitTagStatusAll( 1 << channel );
                #else
                    *slot = *src;
                    EAWriteBarrier();
                #endif
                }

            public:

                AtomicStructLarge()
                {
                    mControlWord.SetValue( 0 );
                    mSlotUsedMap.SetValue( 1 );
                }

                void ReadCurrentValue( T* dest )
                {
                    this->ReadControlDataAndValue( dest );
                }
            };

            //-------------------------------------------------------------------------------------------
            /// Large atomic transaction
            /// 
            template< typename T, typename TSTRUCT >
            class AtomicTransactionLarge
            {
            public:
                typedef typename TSTRUCT::ControlData   TCONTROL;

                enum { SLOT_UNUSED = -1 };

                AtomicTransactionLarge( TSTRUCT* atomicStruct ) : mStruct( atomicStruct ), mOutputSlot( SLOT_UNUSED )
                {
                }

                virtual ~AtomicTransactionLarge()
                {
                    if( mOutputSlot != SLOT_UNUSED )
                        mStruct->FreeSlot( mOutputSlot );
                }

                T* Begin()
                {
                    // Lazy alloc an output slot

                    if( mOutputSlot == SLOT_UNUSED )
                        mOutputSlot = mStruct->AllocSlot();

                    // Initialize the struct

                    mControl = mStruct->ReadControlDataAndValue( &mData );
                    return( &mData );
                }

                bool Commit()
                {
                    mStruct->WriteSlot( mOutputSlot, &mData );

                    TCONTROL previous = mControl;

                    mControl.IncrementVersionAndSetSlot(mOutputSlot);
                    if( mStruct->WriteControlData( mControl, previous ) )
                    {
                        mOutputSlot = SLOT_UNUSED;
                        mStruct->FreeSlot( static_cast<int>(previous.GetSlot()) );
                        return( true );
                    }

                    return( false );
                }

            private:

                TSTRUCT*            mStruct;
                T                   mData;
                TCONTROL            mControl;
                int                 mOutputSlot;
            };


            //-------------------------------------------------------------------------------------------
            /// Small atomic structure for CAS architecture
            /// 
            /// Up to four bytes is supported
            ///
            template< typename T >
            class AtomicStructSmall_CAS
            {
                template< typename T2, typename TSTRUCT > friend class AtomicTransactionSmall_CAS;

                union ControlData
                {
                    uint64_t        mWord;

                    struct
                    {
                        uint32_t    mVersion;
                        T           mValue;
                    };
                };

                ControlData ReadControlData()
                {
                    ControlData data;
                    data.mWord = mControlWord.GetValue();

                    return( data );
                }

                ControlData ReadControlDataAndValue( T* dest )
                {
                    ControlData control;
                    control.mWord = mControlWord.GetValue();

                    *dest = control.mValue;
                    return( control );
                }

                bool WriteControlData( ControlData newData, ControlData prevData )
                {
                    return( mControlWord.SetValueConditional( newData.mWord, prevData.mWord ) );
                }

                AtomicInt< uint64_t > mControlWord;

            public:

                AtomicStructSmall_CAS() 
                {
                    mControlWord.SetValue( 0 );
                }

                void ReadCurrentValue( T* dest )
                {
                    this->ReadControlDataAndValue( dest );
                }
            };

            //-------------------------------------------------------------------------------------------
            /// Small atomic transaction for CAS architecture
            /// 
            template< typename T, typename TSTRUCT >
            class AtomicTransactionSmall_CAS
            {
            public:
                typedef typename TSTRUCT::ControlData TCONTROL;

                AtomicTransactionSmall_CAS( TSTRUCT* atomicStruct ) : mStruct( atomicStruct ) {}

                T* Begin()
                {
                    mControl = mStruct->ReadControlDataAndValue( &mData );
                    return( &mData );
                }

                bool Commit()
                {
                    TCONTROL previous = mControl;

                    mControl.mVersion++;
                    mControl.mValue = mData;

                    if( mStruct->WriteControlData( mControl, previous ) )
                        return( true );

                    return( false );
                }
            private:

                TSTRUCT*            mStruct;
                T                   mData;
                TCONTROL            mControl;
            };


            //-------------------------------------------------------------------------------------------
            /// Small atomic structure for LLR architecture
            /// 
            /// Up to eight bytes is supported
            ///
            template< typename T, typename TWORD >
            class AtomicStructSmall_LLR
            {
                template< typename T2, typename TSTRUCT > friend class AtomicTransactionSmall_LLR;

                union ControlData
                {
                    TWORD   mWord;
                    T       mValue;
                };

                AtomicInt< TWORD > mControlWord;

            public:

                inline void ReadCurrentValue( T* dest ) const
                {
                    ControlData control;
                    control.mWord = mControlWord.GetValue();
                    *dest = control.mValue;
                }
            };

            //-------------------------------------------------------------------------------------------
            /// Small atomic transaction for CAS architecture
            /// 
            template< typename T, typename TSTRUCT >
            class AtomicTransactionSmall_LLR
            {
                typedef typename TSTRUCT::ControlData TCONTROL;

            public:
                AtomicTransactionSmall_LLR( TSTRUCT* atomicStruct ) : mStruct( atomicStruct ) {}

                inline T* Begin()
                {
                    mLocal.mWord = mStruct->mControlWord.Reserve( this->GetScratchBuffer() );
                    return( &mLocal.mValue );
                }

                inline bool Commit()
                {
                    return( mStruct->mControlWord.StoreConditionalReserved( mLocal.mWord, this->GetScratchBuffer() ) );
                }

            private:

            #if defined( EA_PLATFORM_PS3_SPU )
                uint8_t     mScratch[128] __attribute__(( aligned( 128 ) ));
            #endif
                TSTRUCT*    mStruct;
                TCONTROL    mLocal;

                inline uint8_t* GetScratchBuffer()
                {
            #if defined( EA_PLATFORM_PS3_SPU )
                    return( mScratch );
            #else
                    return( NULL );
            #endif
                }
            };

        } // namespace Detail
    } // namespace Thread
} // namespace EA

#endif // EATHREAD_ATOMICSTRUCTS_AVAILABLE

#ifdef _MSC_VER
    #pragma warning(pop)
#endif

#endif // Header include guard

