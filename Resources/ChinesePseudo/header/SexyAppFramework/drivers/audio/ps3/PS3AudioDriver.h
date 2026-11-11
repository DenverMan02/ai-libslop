#ifndef PS3AUDIODRIVER_H_INCLUDED
#define PS3AUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"

#include <fmod.h>
#include <fmod_errors.h>
#include <fmodps3.h>

namespace Sexy
{
	class SexyAppBase;

	class PS3AudioDriver : public IAudioDriver
	{
	public:
		PS3AudioDriver(SexyAppBase*);
		virtual ~PS3AudioDriver();

		bool InitAudioDriver();

		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();

		FMOD_SYSTEM *GetFmodSystem(){ return mSystem; };
	private:
		bool mDisabled;

		SexyAppBase* mApp;
		FMOD_SYSTEM* mSystem;

		FMOD_PS3_EXTRADRIVERDATA mInitData;
	};
};

#endif
