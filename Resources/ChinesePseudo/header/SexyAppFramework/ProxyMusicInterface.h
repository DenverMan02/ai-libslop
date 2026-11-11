#ifndef __PROXYMUSICINTERFACE_H__
#define __PROXYMUSICINTERFACE_H__

#include "Common.h"
#include "MusicInterface.h"

namespace Sexy
{


	/**
	 * The ProxyMusicInterface wraps another music interface in such a way that makes it
	 * safe to extend the music interface class without needing to know what the base class is.
	 * Some games have used this to add some features, but they typically have to extend a platform
	 * specific implementation in order to do that.
	 */

	class ProxyMusicInterface : public MusicInterface
	{
	public:
		ProxyMusicInterface(MusicInterface* theTargetInterface, bool deleteTarget);
		virtual ~ProxyMusicInterface();

		virtual bool			LoadMusic(int theSongId, const std::string& theFileName);
		virtual void			PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false, uint64 theStartPos=0);		
		virtual void			StopMusic(int theSongId);
		virtual void			PauseMusic(int theSongId);
		virtual void			ResumeMusic(int theSongId);
		virtual void			StopAllMusic();		

		virtual void			UnloadMusic(int theSongId);
		virtual void			UnloadAllMusic();
		virtual void			PauseAllMusic();
		virtual void			ResumeAllMusic();
		
		virtual void			FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
		virtual void			FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
		virtual void			FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
		virtual void			SetSongVolume(int theSongId, double theVolume);
		virtual void			SetSongMaxVolume(int theSongId, double theMaxVolume);
		virtual bool			IsPlaying(int theSongId);
		
		virtual void			SetVolume(double theVolume);
		virtual void			SetMusicAmplify(int theSongId, double theAmp);
		virtual void			Update();
	private:
		MusicInterface* mTargetInterface;
		bool mDeleteTarget;
	};

};

#endif //__MUSICINTERFACE_H__
