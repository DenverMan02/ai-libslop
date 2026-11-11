#ifndef _RAWAUDIOOUTPUTBUFFER_H_
#define _RAWAUDIOOUTPUTBUFFER_H_

#include "RawAudioDataBuffer.h"

#include <CritSect.h>

namespace Sexy
{

struct RawAudioOutputFrame
{
	int LeftChannel;
	int RightChannel;
};

struct RawAudioOutputBuffer : public RawAudioDataBuffer
{
	class RawAudioSoundManager * mpManager;
	uint64 mSampleRate;

	uint32 mReadFrameAccumulator;

	RawAudioOutputFrame * mpLockedPtr;
	uint32 mNumLockedFrames;

	CritSect  mWriteCS;

	uint64 mStartTimeUS;			// Time-t at byte-0 in the buffer
	uint64 mLastReadTimeUS;		// Time-t where the last read ended in the buffer

	uint64 mResetBufferThreshold;

public:
	RawAudioOutputBuffer( class RawAudioSoundManager * pInManager )
		: mpManager(pInManager)
		, mSampleRate(0)
		, mReadFrameAccumulator(0)
		, mpLockedPtr(NULL)
		, mNumLockedFrames(0)
		, mStartTimeUS(0)
		, mLastReadTimeUS(0)
		, mResetBufferThreshold( 100000ULL )		// 1/10th of a second in microseconds
	{}


	void Initialize( uint32 InBufferSampleCount, uint64 InResetBufferThreshold );
	void SetFormat( ulong InSampleRate, ushort InChannelCount, ushort InBitCount );
	virtual void AllocateWithFrameCount(uint32 iFrameCount);
	
	RawAudioOutputFrame * LockForWrite( uint64 nowTimeUS, uint32 * outAvailableFrames );
	void UnlockForWrite();

	inline RawAudioOutputFrame * GetLockedWritePtr( uint32 * outAvailableFrames ) const
	{
		(*outAvailableFrames) = mNumLockedFrames;
		return mpLockedPtr;
	}

	inline uint64 GetLastReadTime() const { return mLastReadTimeUS; }

	RawAudioOutputFrame * GetDataReadPtr( uint32 * outAvailableFrames ) const
	{
		*outAvailableFrames = mTotalFrames - mReadFrameAccumulator;
		
		return reinterpret_cast<RawAudioOutputFrame*>(mpData) + mReadFrameAccumulator;
	}

	void AdvanceReadPtr( uint32 InNumFrames );

};

} // namespace Sexy

#endif // _RAWAUDIOOUTPUTBUFFER_H_

