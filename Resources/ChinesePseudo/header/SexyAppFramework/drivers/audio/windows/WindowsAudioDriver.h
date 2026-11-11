#pragma once
#ifndef WINDOWSAUDIODRIVER_H_INCLUDED
#define WINDOWSAUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"


namespace Sexy
{
	class SexyAppBase;

	class WindowsAudioDriver : public IAudioDriver
	{
	public:
		WindowsAudioDriver(SexyAppBase*);
		virtual ~WindowsAudioDriver();

		bool InitAudioDriver();

		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();

	private:
		SexyAppBase* mApp;
		//FMOD_SYSTEM* mSystem;
	};

};

#endif
