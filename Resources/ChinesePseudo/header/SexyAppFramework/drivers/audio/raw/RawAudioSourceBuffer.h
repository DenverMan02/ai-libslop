
#ifndef _RAWAUDIOSOURCEBUFFER_H_
#define _RAWAUDIOSOURCEBUFFER_H_

#include <SexyAppBase.h>

#include "RawAudioDataBuffer.h"


namespace Sexy
{

struct RawAudioSourceBuffer : public RawAudioDataBuffer
{
	int mSampleRate;

	int mBasePan;
	float mBaseVolume;

	std::string mFilename;

	RawAudioSourceBuffer()
		: mBasePan(0)
		, mBaseVolume(1.0)
		
		, mSampleRate(44100)
	{}
		
	virtual ~RawAudioSourceBuffer()
	{
		Release();
	}

	bool SetBaseVolume( double InBaseVolume )
	{
		mBaseVolume = (float)InBaseVolume;
	}
	
	bool SetBasePan( int InBasePan )
	{
		mBasePan = InBasePan;
	}
	
	void SetFormat( ulong InSampleRate, ushort InChannelCount, ushort InBitCount )
	{
		RawAudioDataBuffer::SetFormat( InChannelCount, InBitCount );

		mSampleRate = InSampleRate;
	}

	void Release()
	{
		RawAudioDataBuffer::Release();
		mFilename.clear();
	}

};

} // namespace Sexy

#endif // _RAWAUDIOSOURCEBUFFER_H_

