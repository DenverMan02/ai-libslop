/*
*****************************************************************************
*   SCC:Perforce SCM
*
*   $File:$                      
*
*   $Revision:$
*
*   $DateTime:$
*
*   $Author:$
*
*   $Id:$
*
*****************************************************************************
*
* Description: WinRT - XAudio2 Sound Effects - Driver for a single voice
*
*****************************************************************************
*
* The following text and routines are proprietary and protected by the
* following copyright:
*
* PopCap Games
* 2401 4th Ave, Suite 300
* Seattle, WA 98121
*
*****************************************************************************
*
* History-
*
* 07.10.12 	_SCL_	Initial Version
*
*****************************************************************************
*/

#ifndef __XAUDIOSFXINSTANCE_H__
#define __XAUDIOSFXINSTANCE_H__

#include <xaudio2.h>
#include "SoundInstance.h"

namespace Sexy
{
	class XAudioSfxManager;
	class XAudioSourceSound;
	class XAudioSoundCallback;

	class XAudioSfxInstance : public SoundInstance
	{
	public:
		virtual ~XAudioSfxInstance(); 
			
		virtual void			SetVolume(double fVolume); 
		virtual void			SetMasterVolumeIdx(int nVolumeIdx);
		virtual void			SetPan(int thePosition); //-db to +db = left to right

		virtual bool			Play(bool bLooping, bool bAutoRelease);
		virtual void			Stop();
		virtual bool			IsPlaying();
		virtual bool			IsReleased();

		virtual void			SetBaseVolume(double fBaseVolume); 
		virtual void			SetBasePan(int fBasePan);
		virtual void			SetBaseRate(double fBaseRate);

		virtual void			AdjustPitch(double nNumSteps);
		virtual double			GetVolume();
        void                    RehupVolume();

	protected:
		friend class XAudioSfxManager;

		XAudioSfxInstance( XAudioSfxManager *pMgr );
		void Prepare( XAudioSourceSound *pSound );
		virtual void Release();

	private:
		XAudioSfxManager *m_pMgr;

		bool 	m_bAutoRelease;
		bool 	m_bPrepared;
		bool 	m_bIsPlaying;
		bool 	m_bReleased;
		double 	m_fBaseRate;
		double 	m_fVolume;
        int 	m_nMasterVolumeIdx;

		IXAudio2SourceVoice *m_pSourceVoice;
		XAudioSourceSound 	*m_pSound;
		XAudioSoundCallback	*m_pSoundCallback;
	};
}

//*************************************************************************** End of Incluce *

#endif


