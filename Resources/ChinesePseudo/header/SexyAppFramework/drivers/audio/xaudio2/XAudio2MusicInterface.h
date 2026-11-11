#ifndef __XAUDIOMUSICINTERFACE_H__
#define __XAUDIOMUSICINTERFACE_H__ 

#include "Common.h"
#include "MusicInterface.h"

struct IXAudio2;
struct IXAudio2MasteringVoice;

namespace Sexy
{

class SexyAppBase;

class XAudioMusicInfo
{
public:
	XAudioMusicInfo();

//	FMOD_SOUND*				mStream;
//	FMOD_CHANNEL*			mChannel;

	float					mVolume;
	float					mVolumeAdd;
	float					mVolumeCap;
	bool					mStopOnFade;
	bool					mRepeats;
};

typedef std::map<int, XAudioMusicInfo> XAudioMusicMap;

class XAudioMusicInterface : public MusicInterface
{
public:
	XAudioMusicInterface(IXAudio2 *pEngine, IXAudio2MasteringVoice *pMasteringVoice); 
	virtual ~XAudioMusicInterface();
		
	virtual bool			LoadMusic(int theSongId, const std::string& theFileName);
//	virtual bool			LoadSample(int theSongId, const std::string& theFileName, bool repeat);
//	virtual bool			LoadSample(int theSongId, const std::string& theIntroFileName, const std::string& theRepeatFileName, bool repeat);
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

	XAudioMusicInfo*			GetMusic(int theSongId);

	// functions for dealing with MODs
    
    // tempo is multiplier of base (1.0 is original speed)
	virtual int				GetMusicTempo(int theSongId);
	virtual void 			SetMusicTempo(int theSongId, int theTempo );

	virtual int				GetMusicOrder(int theSongId);
	virtual void			SetMusicOrder(int theSongId, int theOrder);

	virtual int				GetMusicRow(int theSongId);

	virtual int				GetMusicChannelVolume(int theSongId, int theChannelId);
	virtual void			SetMusicChannelVolume(int theSongId, int theChannelId, int theVolume );

public:
//	FMOD_SOUND*				LoadFMODSample(const std::string& theFileName);

public:	
	IXAudio2 				*m_pEngine;
	IXAudio2MasteringVoice 	*m_pMasteringVoice;

//	FMOD_SYSTEM*			mFMod;
//	FMOD_CHANNELGROUP*		mMusicGroup;

	XAudioMusicMap			mMusicMap;
	float					mMasterVolume;
	float					mMaxMusicVolume;
	float					mMaxSampleVolume;
};

}

#endif //__XAudioMusicINTERFACE_H__
