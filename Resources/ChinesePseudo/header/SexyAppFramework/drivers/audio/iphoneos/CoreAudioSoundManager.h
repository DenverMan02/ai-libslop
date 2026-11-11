#ifndef __COREAUDIOSOUNDMANAGER_H__
#define __COREAUDIOSOUNDMANAGER_H__

#include "Common.h"
#include "SoundManager.h"
#include "CoreAudioUtility.h"
#include <libkern/OSAtomic.h>

namespace Sexy
{
class CoreAudioSoundInstance;

class CoreAudioSoundManager
	: public SoundManager
{
public:
	CoreAudioSoundManager();
	~CoreAudioSoundManager();

	void			Enable( bool enable );
	bool			Initialized();

	bool			LoadSound(unsigned int theSfxID, const std::string& theFilename);
	int				LoadSound(const std::string& theFilename);
	void			ReleaseSound(unsigned int theSfxID);

	void			SetVolume(double theVolume);
	void			SetVolume(int theVolIdx, double theVolume);
	bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume);
	bool			SetBasePan(unsigned int theSfxID, int theBasePan);	

	SoundInstance*	GetSoundInstance(unsigned int theSfxID);

	void			ReleaseSounds();
	void			ReleaseChannels();

	double			GetMasterVolume();
	void			SetMasterVolume(double theVolume);

	void			Flush();
	void			StopAllSounds();
	int				GetFreeSoundId();
	int				GetNumSounds();

	void			Update();
	
	AudioConverterRef GetConverter( const AudioStreamBasicDescription& format );
	void FreeConverter( AudioConverterRef converter, const AudioStreamBasicDescription& format );
	void EmptyConverterPool();
	
private:

	void CreateAudioUnits();
	void ReleaseAudioUnits();
	
	static OSStatus RenderNotificationProc( void* inRefCon, AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp, UInt32 inBusNumber, UInt32 inNumFrames, AudioBufferList* ioData );
	OSStatus RenderNotification( AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp, UInt32 inBusNumber, UInt32 inNumFrames, AudioBufferList* ioData );

	int	FindFreeChannel();

	bool LoadCoreAudioFile(unsigned int theSfxID, const std::string& theFilename);
	bool LoadCoreAudioFileFromMemory(unsigned int theSfxID, const std::string& theFilename, uint8* theBuffer, uint32 theSize);

	bool mEnabled;
	AudioUnit mOutputUnit;
	AudioUnit mMixerUnit;
	AudioStreamBasicDescription mBusFormat;

	CoreAudioSoundBuffer mSourceSounds[ MAX_SOURCE_SOUNDS ];
	CoreAudioSoundInstance* mPlayingSounds[ MAX_CHANNELS ];

	typedef std::multimap< AudioStreamBasicDescription, AudioConverterRef > ConverterMap;
	ConverterMap mConverterPool;

	double mMasterVolume[ MAX_NUM_VOLUMES ];
	
	OSSpinLock mChannelLocks[ MAX_CHANNELS ];
	
	bool TryLockChannel( int index )
	{
		return ::OSSpinLockTry( &mChannelLocks[ index ] );
	}
	
	void LockChannel( int index )
	{
		return ::OSSpinLockLock( &mChannelLocks[ index ] );
	}
	
	void UnlockChannel( int index )
	{
		::OSSpinLockUnlock( &mChannelLocks[ index ] );
	}
	
};

}

#endif //__COREAUDIOSOUNDMANAGER_H__
