#pragma once
#ifndef AIRPLAYAUDIODRIVER_H_INCLUDED
#define AIRPLAYAUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"


namespace Sexy
{
	class SexyAppBase;
	
	class AirplayAudioDriver : public IAudioDriver
	{
	public:
		AirplayAudioDriver(SexyAppBase*);
		virtual ~AirplayAudioDriver();
		
		bool InitAudioDriver();
		
		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();
		
	private:
		SexyAppBase* mApp;
	};
	
};

#endif