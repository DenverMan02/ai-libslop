
#pragma once
#include "MusicInterface.h"
#include <AudioToolbox/AudioToolbox.h>

namespace Sexy
{

	struct CoreAudioMusicStream;
	
	class CoreAudioMusicInterface : public MusicInterface
	{
	public:
		CoreAudioMusicInterface();
		virtual ~CoreAudioMusicInterface();
		
		virtual void			Enable( bool enable );
		
		virtual bool			LoadMusic( int theSongId, const std::string& theFileName );
		virtual void			UnloadMusic( int theSongId );
		virtual void			UnloadAllMusic();
		
        virtual void			PlayMusic(int theSongId, int theOffset, bool noLoop, uint64 theStartPos);
        virtual void			StopMusic(int theSongId);

        virtual void			PauseMusic(int theSongId); 
        virtual void			ResumeMusic(int theSongId);
         virtual void			PauseAllMusic();
        virtual void			ResumeAllMusic();
        virtual void			StopAllMusic();		
		
        virtual void			FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
        virtual void			FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
        virtual void			FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
        virtual void			SetSongVolume(int theSongId, double theVolume);
        virtual void			SetSongMaxVolume(int theSongId, double theMaxVolume);
        
		virtual bool			IsPlaying( int theSongId );
		virtual void			SetVolume( double theVolume );
        
        virtual void			SetMusicAmplify(int theSongId, double theAmp);

		virtual void			Update();

	protected:
		
		typedef std::map< int, CoreAudioMusicStream* > Songs;
		virtual void			PlayMusic( int theSongId, int offset, float fadeOutSpeed, float fadeInSpeed, bool loop );
		virtual void			StopMusic( float fadeOutSpeed );
        
		virtual void			PauseMusic();
		virtual void			ResumeMusic();

		void					CreateQueue();
		void					DisposeQueue();
		void					FadeIn( CoreAudioMusicStream* song, float fadeInSpeed, bool loop );
		void					FadeOut( float fadeOutSpeed );
		void					Start( CoreAudioMusicStream* song, bool loop );
		void					Stop();
		void					SetQueueVolume( double volume );
		void					SetVolumeTarget( double volumeTarget, double rampTimeSpeed );
		
		static void AudioQueueCallbackStub( void* aqData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer );
		void PropertyChanged( AudioQueueRef inAQ, AudioQueuePropertyID inID );

		static void AudioQueuePropertyListenerStub( void* inUserData, AudioQueueRef inAQ, AudioQueuePropertyID inID );
		void FeedAudioQueue( AudioQueueRef inAQ, AudioQueueBufferRef inBuffer );

		bool						mEnabled;
		AudioStreamBasicDescription	mFormat;
		AudioQueueRef				mQueue;
		UInt32						mQueueIsRunning;
		
		Songs						mSongs;
		CoreAudioMusicStream*		mNowPlaying;
		CoreAudioMusicStream*		mNextSong;
		bool						mNextSongLoop;
		float						mNextSongFadeInSpeed;
		int							mRequestedSongId;
		bool						mRequestedSongLoop;
		float						mRequestedSongFadeInSpeed;
		
		double						mVolumeSetting;
		double						mVolumeActive;
		double						mVolumeAdd;
		double						mVolumeTarget;
        
        
        float                       mDefaultFadeInSpeed;
        float                       mDefaultFadeOutSpeed;
        
	};
	
}
