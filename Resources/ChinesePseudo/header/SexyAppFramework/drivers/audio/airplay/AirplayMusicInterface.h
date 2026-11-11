#ifndef __AIRPLAYMUSICINTERFACE_H__
#define __AIRPLAYMUSICINTERFACE_H__

#include "MusicInterface.h"

namespace Sexy
{

class SexyAppBase;

struct AirplayMusicInfo
{
  uint8* mSoundFileData;

  uint64 mSoundFileDataSize;

	float					mVolume;
	float					mVolumeAdd;		
	float					mVolumeCap;		
	bool					mStopOnFade;
	bool					mRepeats;
};

typedef std::map<int, AirplayMusicInfo*> AirplayMusicMap;

class AirplayMusicInterface : public MusicInterface
{
public:
	AirplayMusicInterface();
	virtual ~AirplayMusicInterface();
		
	virtual bool			LoadMusic(int theSongId, const std::string& theFileName);
	virtual void			PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false, uint64 theStartPos=0);		
	virtual void			StopMusic(int theSongId);
	virtual void			PauseMusic(int theSongId);
	virtual void			ResumeMusic(int theSongId);
	virtual void			StopAllMusic();		
	virtual void			FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
	virtual void			FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
	virtual void			FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
	virtual void			SetSongVolume(int theSongId, double theVolume);
	virtual bool			IsPlaying(int theSongId);

	virtual void			SetVolume(double theVolume);
	virtual void			Update();

public:	

  AirplayMusicMap	mMusicMap;

  int mCurrentSongId;

  float					mMasterVolume;
	float					mMaxMusicVolume;
	float					mMaxSampleVolume;
};

}

#endif //__AIRPLAYMUSICINTERFACE_H__
