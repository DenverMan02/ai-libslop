#ifndef __AIRPLAYSOUNDINSTANCE_H__
#define __AIRPLAYSOUNDINSTANCE_H__

#include "SoundInstance.h"

namespace Sexy
{
	class AirplaySoundInstance : public SoundInstance
	{
    friend class AirplaySoundManager;

	  public:

		  virtual ~AirplaySoundInstance(); 

		  virtual void			SetVolume(double theVolume); 
    	virtual void			SetMasterVolumeIdx(int theVolumeIdx);
		  virtual void			SetPan(int thePosition); //-db to +db = left to right

		  virtual bool			Play(bool looping, bool autoRelease);
		  virtual void			Stop();
		  virtual bool			IsPlaying();
		  virtual bool			IsReleased();

		  virtual void			SetBaseVolume(double theBaseVolume); 
		  virtual void			SetBasePan(int theBasePan);

		  virtual void			AdjustPitch(double theNumSteps);
		  virtual double	  GetVolume();

    protected:
		
      AirplaySoundInstance(AirplaySoundManager* pcMgr, int iSoundIndex);
		  virtual void Release();

	  private:

		  bool mAutoRelease;

		  bool mReleased;       

      int32 mChannelIndex;          // channel index sound is being played on

      AirplaySoundManager* mpcMgr;  // pointer to manager

      int miSoundIndex;             // sound index (within manager) this instance represents
	};

}

#endif // __AIRPLAYSOUNDINSTANCE_H__
