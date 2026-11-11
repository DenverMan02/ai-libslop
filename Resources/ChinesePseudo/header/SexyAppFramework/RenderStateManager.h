#pragma once
#ifndef __RENDERSTATEMANAGER_H__
#define __RENDERSTATEMANAGER_H__
//****************************************************************************
//**
//**  File     :  RENDERSTATEMANAGER.H
//**  Summary  :  Header - State manager used by RenderDevice/RenderDevice3D
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
//============================================================================
//    HEADERS
//============================================================================
#include "Common.h"
#include "MemPools.h"
#include <assert.h>
#include "SexyMath.h"
namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
/*
	RenderStateManager

	Abstract base state manager class, maintaining common things like
	a dirty list of states, and the current context for journaling etc.

	The actual set of states used is determined by derived classes,
	due to it being rather platform-specific.
*/
class RenderStateManager
{
public:
	/*
		RenderStateManager::StateValue

		Simple variant value of a state, holding a data type and up to 16 bytes
		of data (for 4-float vector values).
	*/
	class StateValue
	{
	public:
		enum EStateValueType
		{
			SV_Dword=0,
			SV_Float,
			SV_Ptr,
			SV_Vector
		};

        union Data
		{
			uint32_t mDword;
			float mFloat;
			void* mPtr;
			struct
			{
				float mX, mY, mZ, mW;
			};
		};
        
        EStateValueType mType;
        Data mData;
        
		inline void clear()
		{
			*((uint32_t*)&mData.mX) = 0;
			*((uint32_t*)&mData.mY) = 0;
			*((uint32_t*)&mData.mZ) = 0;
			*((uint32_t*)&mData.mW) = 0;
		}
        
        StateValue(uint32_t inDword = 0) : mType(SV_Dword) { clear(); mData.mDword = inDword; }
		StateValue(float inFloat) : mType(SV_Float) { clear(); mData.mFloat = inFloat; }
		StateValue(void* inPtr) : mType(SV_Ptr) { clear(); mData.mPtr = inPtr; }
#if USE_FIXED_POINT
		inline StateValue(const MATH_FIXED_POINT_TYPE& inX, const MATH_FIXED_POINT_TYPE& inY, const MATH_FIXED_POINT_TYPE& inZ, const MATH_FIXED_POINT_TYPE& inW) : mType(SV_Vector)
		{
			// this is a hack solution. Store MATH_FIXED_POINT_TYPE in float since MATH_FIXED_POINT_TYPE is not supported in union.
			*((MATH_FIXED_POINT_TYPE *)&mX) = inX;
			*((MATH_FIXED_POINT_TYPE *)&mY) = inY;
			*((MATH_FIXED_POINT_TYPE *)&mZ) = inZ;
			*((MATH_FIXED_POINT_TYPE *)&mW) = inW;
		}
#else //#if USE_FIXED_POINT
		inline StateValue(float inX, float inY, float inZ, float inW) : mType(SV_Vector) { mData.mX = inX; mData.mY = inY; mData.mZ = inZ; mData.mW = inW; }
#endif //#if USE_FIXED_POINT

		inline StateValue(const StateValue& inValue)
		: mType(inValue.mType)
		{
			// copy as dwords rather than floats so that NaNs don't silently change and screw up dword values
			*((uint32_t*)&mData.mX) = *((uint32_t*)&inValue.mData.mX);
			*((uint32_t*)&mData.mY) = *((uint32_t*)&inValue.mData.mY);
			*((uint32_t*)&mData.mZ) = *((uint32_t*)&inValue.mData.mZ);
			*((uint32_t*)&mData.mW) = *((uint32_t*)&inValue.mData.mW);
		}

		inline uint32_t GetDword() const { assert(mType == SV_Dword); return mData.mDword; }
		inline float GetFloat() const { assert(mType == SV_Float); return mData.mFloat; }
		inline void* GetPtr() const { assert(mType == SV_Ptr); return mData.mPtr; }
#if USE_FIXED_POINT
		inline void GetVector(MATH_FIXED_POINT_TYPE& outX, MATH_FIXED_POINT_TYPE& outY, MATH_FIXED_POINT_TYPE& outZ, MATH_FIXED_POINT_TYPE& outW) const
		{
			assert(mType == SV_Vector);
			outX = *((MATH_FIXED_POINT_TYPE *)&mX); outY = *((MATH_FIXED_POINT_TYPE *)&mY); outZ = *((MATH_FIXED_POINT_TYPE *)&mZ); outW = *((MATH_FIXED_POINT_TYPE *)&mW);
		}
#else //#if USE_FIXED_POINT
		inline void GetVector(float& outX, float& outY, float& outZ, float& outW) const { assert(mType == SV_Vector); outX = mData.mX; outY = mData.mY; outZ = mData.mZ; outW = mData.mW; }
#endif //#if USE_FIXED_POINT

		bool operator == (const StateValue& inValue) const
		{
            return	*((uint32_t*)&mData.mX) == *((uint32_t*)&inValue.mData.mX) &&
            *((uint32_t*)&mData.mW) == *((uint32_t*)&inValue.mData.mW) &&
            *((uint32_t*)&mData.mY) == *((uint32_t*)&inValue.mData.mY) &&
            *((uint32_t*)&mData.mZ) == *((uint32_t*)&inValue.mData.mZ);
		}
	};

	/*
		RenderStateManager::State

		Represents a single piece of hardware state information, containing current
		and default StateValues for the state.
		
		A RenderStateManager (or more specifically one of its derived classes, for a given
		platform) holds a potentially large number of these, along with a dirty list
		which dirty states are linked into.  These states remain dirty until the state
		is actually "committed" to the hardware.
	*/
	class State
	{
	public:
		// commit function for a state.  Is responsible for clearing dirty on the states it commits (since it may commit several).
		typedef bool (*FCommitFunc)(State* inState);

		RenderStateManager* mManager; // state manager containing this state
		uint32_t mContext[4]; // context data for use on a state-specific basis, mostly for commit funcs
		State* mDirtyPrev, *mDirtyNext; // prev/next CLL links for the dirty list.  If the state is not self-linked, then it's dirty (so no separate "mDirty" bool required).
		StateValue mValue; // current value of the state
		StateValue mHardwareDefaultValue; // default value the hardware is initialized to
		StateValue mContextDefaultValue; // default value assumed by state contexts; may be different from hardware default
		StateValue mLastCommittedValue; // value last committed to the hardware
		State* mContextDefPrev, *mContextDefNext; // prev/next CLL links for context default initialization list (self-linked if same as hardware default).
		FCommitFunc mCommitFunc; // function used to commit the state to the hardware and clear dirtiness; null means an effectively unused state
		std::string mName; // text name for debugging purposes
#ifndef RELEASEFINAL
		const char* mValueEnumName; // enum type name for values, used only for debugging with reflection enabled
#endif

		// state constructor; sets the manager and the state-specific context data (for use by commit funcs etc)
		State(RenderStateManager* inManager = NULL, uint32_t inContext0 = 0, uint32_t inContext1 = 0, uint32_t inContext2 = 0, uint32_t inContext3 = 0)
		: mManager(inManager)
		, mCommitFunc(NULL)
#ifndef RELEASEFINAL
		, mValueEnumName(NULL)
#endif
		{
			mDirtyPrev = mDirtyNext = this;
			mContextDefPrev = mContextDefNext = this;

			mContext[0] = inContext0;
			mContext[1] = inContext1;
			mContext[2] = inContext2;
			mContext[3] = inContext3;
		}
		State(const State& inState)
		: mManager(inState.mManager)
		, mValue(inState.mValue)
		, mHardwareDefaultValue(inState.mHardwareDefaultValue)
		, mContextDefaultValue(inState.mContextDefaultValue)
		, mLastCommittedValue(inState.mLastCommittedValue)
		, mCommitFunc(inState.mCommitFunc)
#ifndef RELEASEFINAL
		, mValueEnumName(inState.mValueEnumName)
#endif
		{
			mDirtyPrev = mDirtyNext = this;
			mContextDefPrev = mContextDefNext = this;

			for (int i=0; i<4; ++i)
				mContext[i] = inState.mContext[i];
		}

		// initialize the state to its default value; also sets appropriate commit function as provided by the state manager
		void Init(const StateValue& inDefaultValue, const std::string& inName, const char* inValueEnumName=0);
		
		// same as above, but supplying two different default values, one being the actual default for the hardware, and the
		// other being the default that we assume in our state contexts (we'll set up the hardware to match these assumptions
		// through a separate method).  This prevents us from having to record generally common state in the journal of every
		// single context.
		void Init(const StateValue& inHardwareDefaultValue, const StateValue& inContextDefaultValue, const std::string& inName, const char* inValueEnumName=0);

		// indicate that the state has been reset to its hardware default value
		void Reset();

		// check whether state uses a context default different from the hardware default
		inline bool HasContextDefault() const { return mContextDefPrev != this; }

		// check/set/clear dirtiness
		inline bool IsDirty() const { return mDirtyPrev != this; }
		void SetDirty();
		void ClearDirty(bool inActAsCommit = false); // if act-as-commit is true, behave like state was committed for hardware purposes

		// set the state's current value and mark dirty; changes are recorded by the journal in the state manager's current context
		void SetValue(const StateValue& inValue);
		inline void SetValue(uint32_t inDword) { SetValue(StateValue(inDword)); }
		inline void SetValue(float inFloat) { SetValue(StateValue(inFloat)); }
		inline void SetValue(void* inPtr) { SetValue(StateValue(inPtr)); }
#if USE_FIXED_POINT
		inline void SetValue(const MATH_FIXED_POINT_TYPE& inX, const MATH_FIXED_POINT_TYPE& inY, const MATH_FIXED_POINT_TYPE& inZ, const MATH_FIXED_POINT_TYPE& inW) { SetValue(StateValue(inX, inY, inZ, inW)); }
#else //#if USE_FIXED_POINT
		inline void SetValue(float inX, float inY, float inZ, float inW) { SetValue(StateValue(inX, inY, inZ, inW)); }
#endif //#if USE_FIXED_POINT

		// get the state's current value
		inline uint32_t GetDword() const { return mValue.GetDword(); }
		inline float GetFloat() const { return mValue.GetFloat(); }
		inline void* GetPtr() const { return mValue.GetPtr(); }
#if USE_FIXED_POINT
		inline void GetVector(MATH_FIXED_POINT_TYPE& outX, MATH_FIXED_POINT_TYPE& outY, MATH_FIXED_POINT_TYPE& outZ, MATH_FIXED_POINT_TYPE& outW) const { return mValue.GetVector(outX, outY, outZ, outW); }
#else //#if USE_FIXED_POINT
		inline void GetVector(float& outX, float& outY, float& outZ, float& outW) const { return mValue.GetVector(outX, outY, outZ, outW); }
#endif //#if USE_FIXED_POINT
	};

	/*
		RenderStateManager::Context

		Single context for the state manager.  Holds a journal of state changes,
		which is used for PushState/PopState functionality.

		It is important to note that contexts DO NOT hold an entire set of hardware
		state, as doing so would be far too expensive.  Instead, contexts only care
		about state changes, as walking those changes in reverse is sufficient to
		undo all these changes.  Changing context then only involves walking the
		changes of the old context in reverse, and then walking the changes
		of the new context forward.  These changes go through the dirty-list system
		and are thus not committed to hardware during the walk, making the operation
		relatively efficient depending only on the number of states that are actually
		being changed (which is usually relatively low at any one time).
	*/
	class Context
	{
	public:
		class JournalEntry
		{
		public:
			State* mState; // state that changed
			StateValue mOldValue; // old previous value of the state
			StateValue mNewValue; // new value of the state

			JournalEntry()
			: mState(NULL)
			{}
			JournalEntry(State* inState, const StateValue& inOldValue, const StateValue& inNewValue)
			: mState(inState)
			, mOldValue(inOldValue)
			, mNewValue(inNewValue)
			{}
		};

		SimplePooledVector<JournalEntry>::Type mJournal; // stack of journal entries
		uint32_t mJournalFloor; // current floor of journal, used by revert/push/pop state
		SimplePooledVector<uint32_t>::Type mFloorStack; // stack of floors which effectively define push/pop state depth
		mutable Context* mParentContext; // parent context in a copy-ctor'ed parent-child relationship
		mutable SimplePooledVector<Context*>::Type mChildContexts; // child contexts in a copy-ctor'ed parent-child relationship

		Context();
		Context(const Context& inContext);
		~Context();

		// revert the state back to the most recent floor (either the most recent PushState point, or the default state if no PushState is applicable)
		void RevertState();

		// push the state; very lightweight, just pushes the current floor on the internal floor stack and sets a new floor
		void PushState();
		// pop the state; does a revert back to the current floor, then pops the previous floor off the floor stack
		void PopState();

		// unacquire the context on the hardware state; undoes all the changes made within the context
		void Unacquire(bool inIgnoreParent = false);
		// reacquire the context on the hardware state; redoes all the changes
		void Reacquire(bool inIgnoreParent = false);
		// split off any children as independent contexts
		void SplitChildren();
		
		
	private:
		static SimpleMemPool	msJournalEntryPool;
		static SimpleMemPool	msFloorPool;
		static SimpleMemPool	msChildPool;
	};

protected:
	friend class State;
	
	State mDirtyDummyHead; // dummy head for the dirty state list.  Yes it sounds like an insult from a preschooler.
	State mContextDefDummyHead; // dummy head for the context-default state list
	Context* mCurrentContext; // current context that state changes are journaled into
	Context mDefaultContext; // default context created along with the manager; always available
	bool mWouldCommitStateDirty; // true if the WouldCommitState result is dirty and needs to be recalculated
	bool mWouldCommitStateResult; // last result of WouldCommitState

	virtual State::FCommitFunc GetCommitFunc(State* inState) = 0; // get commit function to use for a given state; used by state during initialization

public:
	RenderStateManager()
	: mDirtyDummyHead()
	, mContextDefDummyHead()
	, mWouldCommitStateDirty(false)
	, mWouldCommitStateResult(false)
	{
		mCurrentContext = &mDefaultContext;
	}
	virtual ~RenderStateManager()
	{
	}

	// initialize the states contained within the state manager; called immediately after construction
	virtual void Init() = 0;

	// reset the states to their default hardware state; called upon device reset
	virtual void Reset() = 0;

	virtual void Cleanup() // clean up manager prior to destruction
	{
		assert(mCurrentContext != NULL);
		mCurrentContext->Unacquire(); // this can't be done in the dtor as the states may already be gone
	}

	inline bool IsDirty() const { return (mDirtyDummyHead.mDirtyNext != &mDirtyDummyHead); }
	
	void ApplyContextDefaults();

	bool WouldCommitState();
	bool CommitState();
	virtual void Flush();

	inline Context* GetContext() const { return mCurrentContext; }
	void SetContext(Context* inContext);

	inline void RevertState() { assert(mCurrentContext != NULL); mCurrentContext->RevertState(); }
	inline void PushState() { assert(mCurrentContext != NULL); mCurrentContext->PushState(); }
	inline void PopState() { assert(mCurrentContext != NULL); mCurrentContext->PopState(); }

	virtual void LostFocus()	{ return; }
	virtual void GotFocus()	{ return; }

};

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace Sexy
//****************************************************************************
//**
//**    END HEADER RENDERSTATEMANAGER.H
//**
//****************************************************************************
#endif // __RENDERSTATEMANAGER_H__
