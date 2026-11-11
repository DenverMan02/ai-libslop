#ifndef _RAWAUDIOSOUNDMANAGER_H_
#define _RAWAUDIOSOUNDMANAGER_H_

#include <SoundManager.h>

#include "RawAudioSourceBuffer.h"
#include "RawAudioSoundInstance.h"
#include "RawAudioOutputBuffer.h"

#define MAX_ACTIVE_CHANNELS 6

namespace Sexy
{
	
class RawAudioSoundManager : public SoundManager
{
//protected:
public:
	class RawAudioSourceBuffer      mSourceSounds[ MAX_SOURCE_SOUNDS ];
	class RawAudioSoundInstance *   mSoundInstances[ MAX_CHANNELS ];
	class RawAudioSoundInstance *    mActiveSounds[ MAX_ACTIVE_CHANNELS ];

	// TODO: Hard RawAudioSoundInstance array with a pointer array (mActiveSounds) into it for mixer processing
	
	int mNumActiveSounds;

	float                         mMasterVolume[ MAX_NUM_VOLUMES ];


	typedef std::map< std::string const, unsigned int > NameMapType;
	NameMapType                  mNameMap;

	RawAudioOutputBuffer	mOutputBuffer;

	uint32 mOutputSampleRate;
	uint32 mOutputNumChannels;
	uint32 mOutputBitsPerSample;
	uint32 mOutputBufferLength;

	// the number of frames allocated in the ring buffer
	uint32 mOutputFrameCount;

	// Size of a single output audio frame in bytes
	uint32 mOutputFrameSize;
		
	class RawAudioMixer *     mpAudioMixer;

public:
	
	static const int INVALID_SFX_ID = -1;
	static const int INVALID_CHANNEL_ID = -1;

	RawAudioSoundManager();
	virtual ~RawAudioSoundManager() {}

	virtual void			Enable();
	virtual void			Disable();

	virtual bool			Initialized();

	virtual bool			LoadSound(unsigned int theSfxID, const std::string& theFilename)  =0;
	virtual int				LoadSound(const std::string& theFilename);
	virtual void			ReleaseSound(unsigned int theSfxID);

    virtual double			GetVolume(int theVolIdx);
	virtual void			SetVolume(double theVolume);
	virtual void			SetVolume(int theVolIdx, double theVolume);
	virtual bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume);
	virtual bool			SetBasePan(unsigned int theSfxID, int theBasePan);	

	virtual SoundInstance*	GetSoundInstance(unsigned int theSfxID);
//    inline SoundInstance*   GetSoundInstance(SoundResource* theSound) { return theSound ? GetSoundInstance(theSound->mSfxID) : NULL; }

	virtual void			ReleaseSounds();
	virtual void			ReleaseChannels();

	virtual double			GetMasterVolume();
	virtual void			SetMasterVolume(double theVolume);

	virtual void			Flush()  {}
	
	virtual void			StopAllSounds();

	virtual int				GetFreeSoundId();
	virtual int				GetNumSounds();

	virtual void			Update();
	virtual void			Update( uint64 nowTimeUS );

//	virtual void			Update( float fDeltaTime );

//    virtual int             GetDefaultVolumeIdx() const { return 0; };
//    virtual void            SetDefaultVolumeIdx( int i_val ) { };

public:

	virtual void SetAudioOutputConfig( uint32 InSampleRate, uint32 InNumChannels, uint32 InBitsPerSample, uint32 InSizeOfBuffer );

	bool PlayInstance( RawAudioSoundInstance * pInstanceToPlay );
	void StopInstance( RawAudioSoundInstance * pInstanceToStop );

	void ReleaseChannel( RawAudioSoundInstance * pInInstance );

	void ResetAudioPlayback() { Flush(); }

	uint32 GetOutputSampleRate() const { return mOutputSampleRate; }

private:
	int GetFreeChannelId() const;

	int FindSoundBufferByName( std::string const& InName ) const;

	void RemoveActiveUnordered( int iActiveIdx );
	int FindActiveSoundByInstance( RawAudioSoundInstance * pInstanceToFind ) const;

};

} // namespace Sexy

#endif // _RAWAUDIOSOUNDMANAGER_H_

