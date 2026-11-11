#pragma once
#ifndef __XAUDIODRIVER__
#define __XAUDIODRIVER__

#include "IAudioDriver.h"

#include <xaudio2.h>

namespace Sexy 
{
	class SexyAppBase;

	class XAudioDriver : public IAudioDriver
	{
	public:
		XAudioDriver(SexyAppBase*);
		virtual ~XAudioDriver();

		bool InitAudioDriver();

		virtual SoundManager*	CreateSoundManager();
		virtual MusicInterface* CreateMusicInterface();

//		IXAudio2* GetXAudio2(){ return mXAudio2; };

	private:
		SexyAppBase *mApp;		
		IXAudio2	*m_pMusicEngine;
		IXAudio2	*m_pSfxEngine;
		IXAudio2MasteringVoice *m_pMusicMasteringVoice;
		IXAudio2MasteringVoice *m_pSfxMasteringVoice;
	};

};

#endif
