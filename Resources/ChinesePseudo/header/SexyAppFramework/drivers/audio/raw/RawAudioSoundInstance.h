#ifndef _RAWAUDIOSOUNDINSTANCEA_H_
#define _RAWAUDIOSOUNDINSTANCEA_H_

#include "SoundInstance.h"

namespace Sexy
{
struct RawAudioFrame_Stereo16
{
	int16 LeftChannel;
	int16 RightChannel;
};

struct RawAudioFrame_Mono16
{
	int16 MonoChannel;
};

struct RawAudioFrame_Stereo8
{
	int8 LeftChannel;
	int8 RightChannel;
};

struct RawAudioFrame_Mono8
{
	int8 MonoChannel;
};

// TODO: Figure this out for all platforms ?
//#define THISCALL __thiscall
#define THISCALL

class RawAudioSoundInstance;

//typedef void (THISCALL RawAudioSoundInstance::*SampleStreamFunc)( float fSrcFrameIdx, struct RawAudioFrame_Stereo16 * outFrame ) const;
typedef bool (THISCALL RawAudioSoundInstance::*PlaybackFunc)( uint64 nowTimeUS, struct RawAudioOutputBuffer & outputBuffer );

class RawAudioSoundInstance : public SoundInstance
{
	static uint64 const RAWAUDIO_START_IMMEDIATELY = ULLONG_MAX;

private:
	class RawAudioSoundManager * mpSoundManager;

	int mChannelId;

	uint32 mSampleRate;

	float mfBaseRate;
	
	float mfBasePan;
	float mfPan;

	float mfBaseVolume;
	float mfVolume;
	
	float mfVolumeL;
	float mfVolumeR;

	int iMasterVolumeIdx;

	bool mbLooping;
	bool mbAutoRelease;
	bool mbPlaying;

	PlaybackFunc PlaybackCB;


	void RecalcVolumePan();

	void AdvancePlayback( uint32 numFramesToAdvance );
	bool HandleEndOfSource( uint64 nowTimeUS );

public:
	struct RawAudioSourceBuffer const & mSourceBuffer;
	
	uint64 mPlaybackBaseTimeUS;
	uint32 mPlaybackBaseFrame;
	uint32 mPlaybackFrame;

public:
	RawAudioSoundInstance( RawAudioSoundManager * pInSoundManager, int InChannelId, RawAudioSourceBuffer const & InSourceBuffer  );

	virtual ~RawAudioSoundInstance()
	{}
	
	virtual void			Release();
		
	virtual void			SetBaseVolume(double theBaseVolume); 
	virtual void			SetBasePan(int theBasePan);
	virtual void			SetBaseRate(double theBaseRate);

	virtual void			AdjustPitch(double theNumSteps);

	virtual void			SetVolume(double theVolume); 
	virtual void			SetMasterVolumeIdx(int theVolumeIdx);
	virtual void			SetPan(int thePosition); //-hundredth db to +hundredth db = left to right

	virtual bool			Play(bool looping, bool autoRelease);	
	virtual void			Stop();
	virtual bool			IsPlaying();
	virtual bool			IsReleased();
	virtual double			GetVolume();


// *************************************

	void SetCallbacks();

	inline uint32 GetActualSampleRate() const { return mSampleRate; }
	inline void SetBaseRate( float InBaseRate );
	inline float GetBaseRate() const { return mfBaseRate; }
	inline uint GetChannelId() const { return mChannelId; }

	inline bool IsCompleted() const { return !mbLooping && ( mPlaybackFrame >= mSourceBuffer.mTotalFrames); }

	bool PostUpdate( uint64 InEndTimeUS );
	uint64 GetPlaybackStartTime( struct RawAudioOutputBuffer const & outputBuffer ) const;

	// TODO: Fix up this argument passing - it's not very good
	inline void Playback( uint64 nowTimeUS, struct RawAudioOutputBuffer & outputBuffer )
	{
		// If the instance is just starting, then set the start time to right now
		if ( mPlaybackBaseTimeUS == RAWAUDIO_START_IMMEDIATELY )
		{
//			mPlaybackBaseTimeUS = nowTimeUS;
			// Cheat new sounds into the past to they'll play with less latency
			mPlaybackBaseTimeUS = GetPlaybackStartTime( outputBuffer );
		}

		bool bShouldTryAgain = false;
		do
		{
			bShouldTryAgain = (this->*PlaybackCB)( nowTimeUS, outputBuffer );
		}
		while ( mbLooping && bShouldTryAgain );
	}


	// No resampling
	bool Playback_Stereo16Fast( uint64 nowTimeUS, struct RawAudioOutputBuffer & outputBuffer );
	bool Playback_Mono16Fast( uint64 nowTimeUS, struct RawAudioOutputBuffer & outputBuffer );

	// Resampling
	bool Playback_Stereo16( uint64 nowTimeUS, struct RawAudioOutputBuffer & outputBuffer );
	bool Playback_Mono16( uint64 nowTimeUS, struct RawAudioOutputBuffer & outputBuffer );

};

} // namespace Sexy

#endif // _RAWAUDIOSOUNDINSTANCEA_H_

