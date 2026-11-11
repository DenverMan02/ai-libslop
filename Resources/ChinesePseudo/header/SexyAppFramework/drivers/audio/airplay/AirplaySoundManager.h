#ifndef __AIRPLAYSOUNDMANAGER_H__
#define __AIRPLAYSOUNDMANAGER_H__

#include "SoundManager.h"

namespace Sexy
{

class AirplaySoundInstance;

class AirplaySoundManager : public SoundManager
{
  public:

    struct SSOUND
    {
      uint64 mSoundFileDataSize;
      uint64 mSoundDataOffset;

      int32 mFreq;

      void* mSoundFileData;
    };

  private:

    int32 mMasterVolume;

	  SSOUND*	mSourceSounds[MAX_SOURCE_SOUNDS];

	  friend class AirplaySoundInstance;
	  typedef std::vector<AirplaySoundInstance*> AirplaySoundInstanceVector;
	  AirplaySoundInstanceVector mAutoReleaseInstances;

  public:

	  AirplaySoundManager();
	  virtual ~AirplaySoundManager();

	  virtual bool			Initialized();

	  virtual bool			LoadSound(unsigned int theSfxID, const std::string& theFilename);
	  virtual int				LoadSound(const std::string& theFilename);
	  virtual void			ReleaseSound(unsigned int theSfxID);
	  virtual void			Release( SoundInstance *s );

	  virtual void			SetVolume(double theVolume);
	  virtual void			SetVolume(int theVolIdx, double theVolume);
	  virtual bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume){return false;};
	  virtual bool			SetBasePan(unsigned int theSfxID, int theBasePan){return false;};

	  virtual SoundInstance*	GetSoundInstance(unsigned int theSfxID);
	  virtual SoundInstance*	GetSoundInstanceUnsafe(unsigned int theSfxID){ return NULL; };

	  virtual double			GetMasterVolume();
	  virtual void			SetMasterVolume(double theVolume);

	  virtual void			ReleaseSounds();
	  virtual void			ReleaseChannels();

	  virtual void			Update();
	  virtual void			Flush();
	  virtual void			StopAllSounds(){};
	  virtual int				GetFreeSoundId();
	  virtual int				GetNumSounds();

  private:

    void parseWAVFile(SSOUND* pSound);
};

}

#endif //__AIRPLAYSOUNDMANAGER_H__
