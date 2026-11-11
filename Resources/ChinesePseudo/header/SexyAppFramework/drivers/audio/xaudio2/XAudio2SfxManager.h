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
* Description: WinRT - XAudio2 Sound Effects Interface
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

#ifndef __XAUDIOSFXMANAGER_H__
#define __XAUDIOSFXMANAGER_H__

#include <xaudio2.h>
#include "SoundManager.h"
#include "XAudio2SfxInstance.h"
#include "PakLib/PakInterface.h"

namespace Sexy
{

class XAudioSourceSound
{
public:
	XAudioSourceSound()
	{
		m_pDataPtr = NULL;
		m_nDataLen = 0;      
		m_fBaseVolume = 0.0f;   
		m_nBasePan = 0;
	}

	WAVEFORMATEX	  		m_aWaveFormat;
	uint8					*m_pDataPtr;
	uint32					m_nDataLen;
	double					m_fBaseVolume;
	int						m_nBasePan;
};

class XAudioSfxManager : public SoundManager
{
private:
	IXAudio2 				*m_pEngine;
	IXAudio2MasteringVoice 	*m_pMasteringVoice;

	XAudioSourceSound		*m_pSourceSounds[MAX_SOURCE_SOUNDS];

	double					mMasterVolume[MAX_NUM_VOLUMES];

    friend class XAudioSfxInstance;
	typedef std::vector<XAudioSfxInstance *> XAudioSfxInstanceVector;
	XAudioSfxInstanceVector mAutoReleaseInstances;

	int                     mDefaultVolumeIdx;

public:
	XAudioSfxManager(IXAudio2 *pEngine, IXAudio2MasteringVoice *pMasteringVoice);
	virtual ~XAudioSfxManager();

	virtual bool			Initialized();

	virtual bool			LoadSound(unsigned int theSfxID, const std::string& theFilename);
	virtual int    			LoadSound(const std::string& theFilename);
	virtual void			ReleaseSound(unsigned int theSfxID);
	virtual void			Release( SoundInstance *s );

    virtual double			GetVolume(int theVolIdx);
	virtual void			SetVolume(double theVolume);
	virtual void			SetVolume(int theVolIdx, double theVolume);
	virtual bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume){return false;};
	virtual bool			SetBasePan(unsigned int theSfxID, int theBasePan){return false;};

	virtual SoundInstance*	GetSoundInstance(unsigned int theSfxID);
	virtual SoundInstance*	GetSoundInstanceUnsafe(unsigned int theSfxID){ return NULL; };

//    	FMOD_SOUNDGROUP*        GetMasterVolumeSoundGroup( int theIdx ) const;

	virtual double			GetMasterVolume();
	virtual void			SetMasterVolume(double theVolume);

	virtual void			ReleaseSounds();
	virtual void			ReleaseChannels();

	virtual void			Update();
	virtual void			Flush();
	//virtual void			SetCooperativeWindow(HWND theHWnd, bool isWindowed);
	virtual void			StopAllSounds(){};
	virtual int	       		GetFreeSoundId();
	virtual int	       		GetNumSounds();

	int GetDefaultVolumeIdx() const        	{ return mDefaultVolumeIdx; }
	void SetDefaultVolumeIdx( int i_val )	{ mDefaultVolumeIdx = i_val; }

	bool LoadWAVSound(PFILE *pFile, XAudioSourceSound *pSound);
};

}

//*************************************************************************** End of Incluce *

#endif

