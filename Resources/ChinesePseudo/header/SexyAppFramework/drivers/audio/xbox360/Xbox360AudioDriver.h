#pragma once
#ifndef XBOX360AUDIODRIVER_H_INCLUDED
#define XBOX360AUDIODRIVER_H_INCLUDED

#include "IAudioDriver.h"

#include <xtl.h>
#include <xaudio2.h>

#include <fmod.h>
#include <fmod_errors.h>
#include <fmodxbox360.h>

namespace Sexy
{
	class SexyAppBase;

	class Xbox360AudioDriver : public IAudioDriver
	{
	public:
		Xbox360AudioDriver(SexyAppBase*);
		virtual ~Xbox360AudioDriver();

		bool InitAudioDriver();

		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();

		FMOD_SYSTEM* GetFmodSystem(){ return mSystem; };
		IXAudio2* GetXAudio2(){ return mXAudio2; };

	private:
		SexyAppBase* mApp;
		FMOD_SYSTEM* mSystem;
		IXAudio2* mXAudio2;
		IXAudio2MasteringVoice* mMasterVoice;

		FMOD_360_EXTRADRIVERDATA mInitData;
	};
};

#endif
