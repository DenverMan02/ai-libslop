#ifndef _RAWAUDIOMIXER_H_
#define _RAWAUDIOMIXER_H_

namespace Sexy
{

class RawAudioMixer
{
	float mfOneOverOutputSampleRate;
	uint32 mOutputSampleRate;
	uint32 mOutputFrameSizeInBytes;
	uint32 mBufferFrameSizeInBytes;

public:
	
	RawAudioMixer();
	
	bool Initialize( uint32 InSampleRate, uint32 InFrameSizeInBytes );

	uint32 MixAudioToOutputBuffer( uint64 nowTimeUS, struct RawAudioOutputBuffer & outBuffer, class RawAudioSoundInstance ** activeInstances, int numActiveInstances );

};

} // namespace Sexy

#endif // _RAWAUDIOMIXER_H_
