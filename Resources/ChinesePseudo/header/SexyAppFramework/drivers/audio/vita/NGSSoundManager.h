#ifndef NGSSOUNDMANAGER_H_INCLUDED
#define NGSSOUNDMANAGER_H_INCLUDED

#include "Common.h"
#include "SoundManager.h"
#include "ngs_common.h"

namespace Sexy
{
class NGSSoundInstance;

class NGSSoundManager
	: public SoundManager
{
public:
	NGSSoundManager();
	~NGSSoundManager();

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
protected:
	bool			InitManager();


	int				InitNGS();
	int				CreateRacks( int nChannels );
	int				InitPlayer( SceNgsHVoice hVoice, SceUInt32 nModuleId, SoundInfo *pSound );
	int				ConnectRacks( SceNgsHVoice hVoiceSource, SceNgsHVoice hVoiceDest );
	void			PrintParamError( SceNgsHVoice hVoice, SceUInt32 nModuleId );
	static	int		_AudioUpdateThread(SceSize args, void *argc);
	int				StartAudioUpdateThread();
private:
	static const int NGS_MAX_CHANNELS = 30;

	int	FindFreeChannel();

	bool LoadWAVSound(unsigned int theSfxID, const std::string& theFilename);
	bool LoadVAGSound(unsigned int theSfxID, const std::string& theFilename);
	bool LoadOGGSound(unsigned int theSfxID, const std::string& theFilename);


	bool mEnabled;

	NGSSoundInstance* mPlayingSounds[ NGS_MAX_CHANNELS ];
	
	SoundInfo mSourceSounds[ MAX_SOURCE_SOUNDS ];

	double mMasterVolume[ MAX_NUM_VOLUMES ];
	
	

	void*			mSysMem;
	SceNgsHSynSystem mSysHandle;

	void*			mRackMemPlayer;
	SceNgsHRack		mRackPlayer;
	void*			mRackMemMaster;
	SceNgsHRack		mRackMaster;

	SceNgsHVoice     mVoiceMaster;

	SceNgsHVoice	mVoiceChannels[NGS_MAX_CHANNELS];

	bool   mRun;
	int    mTickCount;
	SceUID mThreadIdAudioUpdate;


};

}

#endif //__NGSSoundManager_H__
