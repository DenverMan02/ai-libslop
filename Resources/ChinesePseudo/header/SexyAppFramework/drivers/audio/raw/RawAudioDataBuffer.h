
#ifndef _RAWAUDIODATABUFFER_H_
#define _RAWAUDIODATABUFFER_H_

#include <SexyAppBase.h>

//#include <string>


namespace Sexy
{

struct RawAudioDataBuffer
{
	byte * mpData;
	uint32 mTotalFrames;
	uint32 mNumBytes;
	
	int mNumChannels;

	int mBitsPerSample;
	int mBytesPerFrame;

	bool mbOwnsData;

	RawAudioDataBuffer()
		: mpData(NULL)
		, mNumBytes(0)
		
		, mNumChannels(2)
		, mBitsPerSample(16)
		, mBytesPerFrame( mNumChannels * mBitsPerSample/8 )
		, mbOwnsData(false)
	{}
		
	~RawAudioDataBuffer()
	{
		Release();
	}

	void SetFormat( ushort InChannelCount, ushort InBitCount )
	{
		mNumChannels = InChannelCount;
		mBitsPerSample = InBitCount;

		mBytesPerFrame = InChannelCount * ( InBitCount / 8 );
	}


	inline bool IsValid() const 
	{
		return mpData != NULL;
	}

	virtual void Release()
	{
		if ( mbOwnsData )
		{
			delete [] mpData;
		}
		
		mpData = NULL;
	}

	virtual void AllocateWithFrameCount( uint32 iFrameCount )
	{
		DBG_ASSERT( mpData == NULL );

		mTotalFrames = iFrameCount;

		mNumBytes = iFrameCount * mBytesPerFrame;
		mpData = new byte[ mNumBytes ];
		mbOwnsData = true;
	}

	byte * GetDataPtr() const
	{
		return mpData;
	}
	
	unsigned int GetDataSize() const
	{
		return mNumBytes;
	}

};

} // namespace Sexy

#endif // _RAWAUDIODATABUFFER_H_


