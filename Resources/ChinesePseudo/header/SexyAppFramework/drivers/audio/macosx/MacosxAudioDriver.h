#pragma once
#ifndef MACOSXAUDIODRIVER_H_INCLUDED
#define MACOSXAUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"


namespace Sexy
{
	class SexyAppBase;
	
	class MacosxAudioDriver : public IAudioDriver
	{
	public:
		MacosxAudioDriver(SexyAppBase*);
		virtual ~MacosxAudioDriver();
		
		bool InitAudioDriver();
		
		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();
		
	private:
		SexyAppBase* mApp;
//		FMOD_SYSTEM* mSystem;
	};
	
};

#endif

