#pragma once
#ifndef IPHONEOSAUDIODRIVER_H_INCLUDED
#define IPHONEOSAUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"


namespace Sexy
{
	class SexyAppBase;
	
	class iPhoneOSAudioDriver : public IAudioDriver
	{
	public:
		iPhoneOSAudioDriver(SexyAppBase*);
		virtual ~iPhoneOSAudioDriver();
		
		bool InitAudioDriver();
		
		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();
		
	private:
		SexyAppBase* mApp;
	};
	
};

#endif

