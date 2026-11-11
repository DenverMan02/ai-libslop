#ifndef VITAAUDIODRIVER_H_INCLUDED
#define VITAAUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"

namespace Sexy
{
	class SexyAppBase;

	class VitaAudioDriver : public IAudioDriver
	{
	public:
		VitaAudioDriver(SexyAppBase*);
		virtual ~VitaAudioDriver();

		bool InitAudioDriver();

		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();

	private:
		SexyAppBase* mApp;		
	};

};

#endif
