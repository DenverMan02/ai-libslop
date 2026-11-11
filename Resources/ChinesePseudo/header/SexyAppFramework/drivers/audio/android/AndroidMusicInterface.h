
#ifndef _ANDROIDMUSICINTERFACE_H_
#define _ANDROIDMUSICINTERFACE_H_


#include <map>
#include <string>
#include "MusicInterface.h"


namespace Sexy
{

typedef std::map<int, class AndroidMusicStream*> AndroidMusicMap;

class AndroidMusicInterface : public MusicInterface
{
private:

 	bool mbEnabled;
	AndroidMusicMap mMusicMap;

	AndroidMusicStream* mpNowPlaying;

	
	AndroidMusicStream* mpNextSong;
	bool mNextSongLoop;
	float mNextSongFadeInSpeed;
	int mRequestedSongId;
	bool mRequestedSongLoop;
	float mRequestedSongFadeInSpeed;
	
	double mDefaultFadeInSpeed;
	double mDefaultFadeOutSpeed;

	
	double mVolumeSetting;			// The current player volume setting - moves while fading

	double mMaxMusicVolume;		// Global cap on the volume
	double mMasterVolume;			// Conceptually the user's volume setting

	double mFadeVolumeActive;			// The Volume for the currently-active song
	double mFadeVolumeAdd;				// Delta volume when fading in and out
	double mFadeVolumeTarget;			// The target active volume when fading

	bool mbStopOnFade;

	bool mbRehupVolume;

public:
	AndroidMusicInterface();
	virtual ~AndroidMusicInterface();

	void Enable();
	void Disable();

	virtual bool			LoadMusic( int InSongId, const std::string& InFileName );
	virtual void			PlayMusic( int InSongId, int theOffset = 0, bool bNoLoop = false, uint64 InStartPos=0 );
	virtual void			StopMusic( int InSongId );
	virtual void			PauseMusic( int InSongId );
	virtual void			ResumeMusic( int InSongId );
	virtual void			StopAllMusic();		

	virtual void			UnloadMusic( int InSongId );
	virtual void			UnloadAllMusic();
	virtual void			PauseAllMusic();
	virtual void			ResumeAllMusic();
	
	virtual void			FadeIn( int InSongId, int InOffset = -1, double InSpeed = 0.002, bool bNoLoop = false );
	virtual void			FadeOut( int InSongId, bool bStopSong = true, double InSpeed = 0.004 );
	virtual void			FadeOutAll( bool bStopSong = true, double InSpeed = 0.004 );
	virtual void			SetSongVolume( int InSongId, double InVolume );
	virtual void			SetSongMaxVolume( int InSongId, double InMaxVolume );
	virtual bool			IsPlaying( int InSongId );
	
	virtual void			SetVolume( double InVolume );
	virtual void			SetMusicAmplify( int InSongId, double InAmp );
	virtual void			Update();



private:
	
	bool Util_FindMusicFile( std::string const & sRootPath, std::string & sOutPath );
	AndroidMusicStream * Util_GetMusicById( int InSongId );

	void Util_SetVolumeTarget( double InVolumeTarget, double InRampTimeSpeed );
	void Util_ClearVolumeTarget();

	void Util_UpdateDeviceVolume();
	void Util_StopCurrent();
	void Util_FadeOutCurrent( bool bStopSong, double InFadeSpeed );

};

}

#endif // _ANDROIDMUSICINTERFACE_H_

