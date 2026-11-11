#ifndef __NULLSOUNDMANAGER_H__
#define __NULLSOUNDMANAGER_H__

#include "Common.h"
#include "SoundManager.h"
#include "SoundInstance.h"

namespace Sexy
{
	
	class NullSoundInstance;
	
	class NullSoundInstance : public SoundInstance
	{
	public:
		NullSoundInstance() {}
		virtual ~NullSoundInstance() {}
		virtual void			Release() {}
		
		virtual void			SetBaseVolume(double theBaseVolume) {} 
		virtual void			SetBasePan(int theBasePan) {}
		virtual void			SetBaseRate(double theBaseVolume) {}
		
		virtual void			AdjustPitch(double theNumSteps) {}
		
		virtual void			SetVolume(double theVolume) {}
		virtual void			SetMasterVolumeIdx(int theVolumeIdx) {}
		virtual void			SetPan(int thePosition) {}
		
		virtual bool			Play(bool looping, bool autoRelease) { return true; }
		virtual void			Stop() {}
		virtual bool			IsPlaying() { return false; }
		virtual bool			IsReleased() { return false; }
		virtual double			GetVolume() { return 0.0; }
	};
	
	
#define MAX_SOURCE_SOUNDS	4096
#define MAX_CHANNELS		32
	
	class NullSoundManager : public SoundManager
	{
	public:
		NullSoundManager() {}
		virtual ~NullSoundManager() {}
		
		virtual bool			Initialized() { return true; }
		
		virtual bool			LoadSound(unsigned int theSfxID, const std::string& theFilename) { return true; }
		virtual int				LoadSound(const std::string& theFilename) { return 0; }
		virtual void			ReleaseSound(unsigned int theSfxID) { }
		

        virtual double			GetVolume(int theVolIdx)  { return 0.0; }
		virtual void			SetVolume(double theVolume) {}
		virtual void			SetVolume(int theVolIdx, double theVolume) {}
		virtual bool			SetBaseVolume(unsigned int theSfxID, double theBaseVolume) { return true;}
		virtual bool			SetBasePan(unsigned int theSfxID, int theBasePan) { return true;}
		
		virtual SoundInstance*	GetSoundInstance(unsigned int theSfxID) { return &mSoundInstance; }
		
		virtual void			ReleaseSounds() {}
		virtual void			ReleaseChannels() {}
		
		virtual double			GetMasterVolume() { return 0.0f; }
		virtual void			SetMasterVolume(double theVolume) {}		
		virtual void			Flush() {}
		
		virtual void			StopAllSounds() {}
		virtual int				GetFreeSoundId() { return 0;}
		virtual int				GetNumSounds() { return 0;}
		
		virtual void			Update() {}

        virtual int             GetDefaultVolumeIdx() const { return 0; }
        virtual void            SetDefaultVolumeIdx( int i_val )  {}
		
	private:
		NullSoundInstance	mSoundInstance;
		
	};
	
	
}

#endif //__SOUNDMANAGER_H__