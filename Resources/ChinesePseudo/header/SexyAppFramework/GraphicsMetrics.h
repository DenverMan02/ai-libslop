#pragma once
#ifndef __GRAPHICSMETRICS_H__
#define __GRAPHICSMETRICS_H__
//****************************************************************************
//**
//**  File     :  GRAPHICSMETRICS.H
//**  Summary  :  Header - Graphics Device usage metrics (counters etc)
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
	D3DMetrics
*/
class GraphicsMetrics
{
public:
	typedef int64 DCount;

	enum ECounterType
	{
		// drawprim
		CT_TriListCalls,
		CT_TriListPrims,
		CT_TriStripCalls,
		CT_TriStripPrims,
		CT_TriFanCalls,
		CT_TriFanPrims,
		CT_LineStripCalls,
		CT_LineStripPrims,

		// rendertarget
		CT_SetRenderTargetCalls,
		CT_SetRenderTargetCallsRedundant,

		// shaders
		CT_SetVertexShaderCalls,
		CT_SetPixelShaderCalls,
		
		// textures
		CT_SetTextureCalls,
		
		// clears (color and z)
		CT_ClearCalls,
		
		// timings (these are more than just graphics, but the metrics object is quite useful)
		CT_TimeSpentInUpdate,
		CT_TimeSpentInDraw,
		CT_TimeSpentInPresent,
		CT_TimeSpentInFrame,
		// This may not mean much on some platforms that do fast inline submissions to command buffers (Xbox/PS3)
		// but on others, this can give a good idea of how much draw time is in our setup vs the API's
		CT_TimeSpentInGraphicsAPI, 

		CT_COUNT
	};

	class CCounter
	{
	protected:
		int mFramesPerSlice; // number of frames for each slice; set at initialization
		int mSliceFramesRemaining; // number of frames remaining in the current slice
		DCount mCurFrameCount; // current count for this frame
		DCount mPrevFrameCount; // current count for this frame
		DCount mSliceTotalCount; // total count over the current slice
		DCount mAvgCount; // average count from the last slice, for display purposes

	public:
		static const int kDefaultFramesPerSlice = 30;

		CCounter(int inFramesPerSlice = kDefaultFramesPerSlice)
		: mFramesPerSlice(inFramesPerSlice)
		, mSliceFramesRemaining(inFramesPerSlice)
		, mCurFrameCount(0)
		, mSliceTotalCount(0)
		, mAvgCount(0)
		{}
		CCounter(const CCounter& inCounter)
		: mFramesPerSlice(inCounter.mFramesPerSlice)
		, mSliceFramesRemaining(inCounter.mSliceFramesRemaining)
		, mCurFrameCount(inCounter.mCurFrameCount)
		, mSliceTotalCount(inCounter.mSliceTotalCount)
		, mAvgCount(inCounter.mAvgCount)
		{}

		inline CCounter& operator ++ (void) { Add(1); return *this; }
		inline CCounter& operator ++ (int) { Add(1); return *this; }
		inline CCounter& operator += (DCount inValue) { Add(inValue); return *this; }

		inline DCount GetAverage() const { return mAvgCount; }
		inline DCount GetPrevFrameVal() const { return mPrevFrameCount; }

		inline void Add(DCount inValue)
		{
			mCurFrameCount += inValue;
		}
		void NextFrame()
		{
			mPrevFrameCount = mCurFrameCount;
			mSliceTotalCount += mCurFrameCount;
			mCurFrameCount = 0;

			if (mSliceFramesRemaining)
			{
				--mSliceFramesRemaining;
			}
			else
			{
				mAvgCount = mSliceTotalCount / mFramesPerSlice;
				mSliceTotalCount = 0;
				mSliceFramesRemaining = mFramesPerSlice;
			}
		}
	};

protected:
	class CContext
	{
	protected:
		CCounter mCounters[CT_COUNT];

	public:
		inline CCounter& operator [] (ECounterType inCounter) { return mCounters[inCounter]; }
		inline const CCounter& operator [] (ECounterType inCounter) const { return mCounters[inCounter]; }

		void NextFrame()
		{
			for (int i=0; i<CT_COUNT; ++i)
				mCounters[i].NextFrame();
		}
	};

	CContext mCtxActive;

public:
	inline CCounter& operator [] (ECounterType inCounter) { return mCtxActive[inCounter]; }
	
	inline CCounter& GetCounter(ECounterType inCounter) { return mCtxActive[inCounter]; }

	void NextFrame()
	{
		mCtxActive.NextFrame();
	}
	void ResetCounter(ECounterType inCounter, int inFramesPerSlice = CCounter::kDefaultFramesPerSlice)
	{
		mCtxActive[inCounter] = CCounter(inFramesPerSlice);
	}
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
//**    END HEADER GraphicsMETRICS.H
//**
//****************************************************************************
#endif // __GRAPHICSMETRICS_H__
