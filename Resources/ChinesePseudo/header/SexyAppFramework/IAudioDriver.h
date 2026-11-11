#pragma once
#ifndef IAUDIODRIVER_H_INCLUDED
#define IAUDIODRIVER_H_INCLUDED


namespace Sexy
{
	class SexyAppBase;
	class SoundManager;
	class MusicInterface;

	class IAudioDriver 
	{
	public:
		static IAudioDriver* CreateAudioDriver(SexyAppBase*);
		virtual ~IAudioDriver() {};

		virtual bool InitAudioDriver() = 0;
		virtual SoundManager*	CreateSoundManager() = 0;
		virtual MusicInterface* CreateMusicInterface() = 0;
	};


};
#endif