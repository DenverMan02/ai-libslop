#ifndef __FMODSOUNDMANAGER_H__
#define __FMODSOUNDMANAGER_H__

#include "SoundManager.h"
#include "FModSoundInstance.h"

#include <fmod.h>
#include <fmod_errors.h>

namespace Sexy
{

class FModSoundManager : public SoundManager
{
private:
	FMOD_SYSTEM*			mFMod;
	FMOD_SOUND*				mSourceSounds[MAX_SOURCE_SOUNDS];
	FMOD_SOUNDGROUP*		mSoundGroupAll;
    FMOD_SOUNDGROUP*        mMasterVolumeSoundGroups[MAX_NUM_VOLUMES];
    
    friend class FModSoundInstance;
	typedef std::vector<FModSoundInstance *> FModSoundInstanceVector;
	FModSoundInstanceVector mAutoReleaseInstances;

    int                     mDefaultVolumeIdx;

public:
	FModSoundManager(FMOD_SYSTEM* FMod);
	virtual ~FModSoundManager();

	virtual bool			Initialized();

	virtual bool			LoadSound(unsigned int theSfxID, const std::string& theFilename);
	virtual int				LoadSound(const std::string& theFilename);
	virtual void			ReleaseSound(unsigned int theSfxID);
	virtual void			Release( SoundInstance *s );

    virtual double			GetVolume(int theVolIdx);
	virtual void			SetVolume(double theVolume);
	virtual void			SetVolume(int theVolIdx, double theVolume);
	virtual bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume){return false;};
	virtual bool			SetBasePan(unsigned int theSfxID, int theBasePan){return false;};

	virtual SoundInstance*	GetSoundInstance(unsigned int theSfxID);
	virtual SoundInstance*	GetSoundInstanceUnsafe(unsigned int theSfxID){ return NULL; };

    FMOD_SOUNDGROUP*        GetMasterVolumeSoundGroup( int theIdx ) const;

	virtual double			GetMasterVolume();
	virtual void			SetMasterVolume(double theVolume);

	virtual void			ReleaseSounds();
	virtual void			ReleaseChannels();

	virtual void			Update();
	virtual void			Flush();
	//virtual void			SetCooperativeWindow(HWND theHWnd, bool isWindowed);
	virtual void			StopAllSounds(){};
	virtual int				GetFreeSoundId();
	virtual int				GetNumSounds();

    int GetDefaultVolumeIdx() const 		{ return mDefaultVolumeIdx; }
    void SetDefaultVolumeIdx( int i_val ) 		{ mDefaultVolumeIdx = i_val; }
};

}

#endif //__FMODSOUNDMANAGER_H__
