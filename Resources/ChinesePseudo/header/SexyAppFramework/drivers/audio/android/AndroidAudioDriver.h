#pragma once
#ifndef ANDROIDAUDIODRIVER_H_INCLUDED
#define ANDROIDAUDIODRIVER_H_INCLUDED

#include <IAudioDriver.h>

namespace Sexy
{
	class SexyAppBase;
	class SoundManager;
	class MusicInterface;

	class AndroidAudioDriver : public IAudioDriver
	{
		public:
			AndroidAudioDriver(SexyAppBase*);
			virtual ~AndroidAudioDriver();
			
			bool InitAudioDriver();
			
			virtual SoundManager*	CreateSoundManager();
			virtual MusicInterface* CreateMusicInterface();
			
		private:
			SexyAppBase* mApp;
	};


};

#endif // ANDROIDAUDIODRIVER_H_INCLUDED

