#pragma once
#ifndef __RTUTILS_H__
#define __RTUTILS_H__
//****************************************************************************
//**
//**  File     :  RTUTILS.H
//**  Summary  :  Header - Rt - Miscellaneous Utilities
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

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
/*
	CDH FIXME$$ this really should go in a general framework data structures
	place, but we don't have one of those for the framework at the moment,
	so it's going here (once we get some of the core layer stuff split out
	a bit, this should be revisited).
*/
/*
	RtRingItem

	Templated circular-linked-list (ring) item class, following Jim Coplien's
	"Curiously Recurring Template" pattern (where a concrete implementation
	class derives from this template, passing its class name as the template
	parameter).

	By deriving from this template, the concrete class is given circular links
	to neighbors in a linked list, and can be linked or unlinked at will.
	The ring item is self-linked whenever it's not connected to other items,
	so at no time should the links ever be null.

	A traversable list of these items is controlled by a dummy head, from which
	you can iterate starting with dummy.RingGetNext(), repeating this until
	RingGetNext returns &dummy.  Reverse iteration is the same, but using
	RingGetPrev instead.  Alternatively, a scoped convenience iterator class
	is provided which can make this process more readable, for example:

	class CMyItem : public RtRingItem<CMyItem>() { void SomeMethod(); ...etc... };
	
	CMyItem myRing; // dummy head item
	// ... link a bunch of stuff to myRing, then when you want to iterate, ...
	for (CMyItem::Iterator it(&myRing); it; ++it)
	    it->SomeMethod();
*/
template <class T> class RtRingItem
{
protected:
	RtRingItem<T>* mPrev;
	RtRingItem<T>* mNext;

public:
	// ctor/dtor
	inline RtRingItem() { mPrev = mNext = this; }
	inline ~RtRingItem() { RingUnlink(); }

	// prev/next get accessors
	inline T* RingGetPrev() const { return (T*)mPrev; }
	inline T* RingGetNext() const { return (T*)mNext; }

	// prev/next direct set accessors (use with caution)
	inline void RingSetPrevDirect(T* inPrev) { mPrev = inPrev; }
	inline void RingSetNextDirect(T* inNext) { mNext = inNext; }

	// unlink from existing ring (if any)
	inline void RingUnlink()
	{
		mNext->mPrev = mPrev;
		mPrev->mNext = mNext;
		mNext = mPrev = this;
	}

	// link before/after another ring item
	inline void RingLinkBefore(T* inRingItem)
	{
		RingUnlink();
		mNext = inRingItem;
		mPrev = inRingItem->mPrev;
		mNext->mPrev = mPrev->mNext = this;
	}
	inline void RingLinkAfter(T* inRingItem)
	{
		RingUnlink();
		mPrev = inRingItem;
		mNext = inRingItem->mNext;
		mNext->mPrev = mPrev->mNext = this;
	}

	// convenience iterator class
	class Iterator
	{
	protected:
		T* mHead; // dummy head item for the ring
		T* mCurrent; // current item being pointed at by the iterator
		T* mPending; // pending item to iterate to (held separately so that the current item can be safely unlinked mid-iteration)
		T* (T::*mGetNextMethod)() const; // traversal method (get next or get prev)

		inline void UpdatePending() { mPending = (mCurrent->*mGetNextMethod)(); }
		inline void Advance() { mCurrent = mPending; UpdatePending(); }

	public:
		void Reset(T* inDummyHeadItem, bool inIterReverse=false)
		{
			mCurrent = mHead = inDummyHeadItem;
			mGetNextMethod = inIterReverse ? &T::RingGetPrev : &T::RingGetNext;
			UpdatePending();
			Advance();
		}

		// ctor
		inline Iterator(T* inDummyHeadItem, bool inIterReverse=false) { Reset(inDummyHeadItem, inIterReverse); }
		inline Iterator(const Iterator& inIter) : mHead(inIter.mHead), mCurrent(inIter.mCurrent), mPending(inIter.mPending), mGetNextMethod(inIter.mGetNextMethod) {}

		// operators
		inline T* operator * () const { return mCurrent; }
		inline T* operator -> () const { return mCurrent; }
		inline Iterator& operator ++ (void) { Advance(); return *this; }
		inline Iterator& operator ++ (int) { Iterator temp(*this); Advance(); return temp; }
		inline operator bool () const { return mCurrent != mHead; }
	};
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
//**    END HEADER RTUTILS.H
//**
//****************************************************************************
#endif // __RTUTILS_H__
