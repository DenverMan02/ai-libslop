#pragma once
#ifndef WIIAUDIODRIVER_H_INCLUDED
#define WIIAUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"

namespace Sexy
{
	class SexyAppBase;

	class WiiAudioDriver : public IAudioDriver
	{
	public:
		WiiAudioDriver(SexyAppBase*);
		virtual ~WiiAudioDriver();

		bool InitAudioDriver();

		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();

	private:
		SexyAppBase* mApp;		
	};

};

#endif
