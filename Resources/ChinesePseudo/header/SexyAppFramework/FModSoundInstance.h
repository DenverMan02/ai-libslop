#ifndef __FMODSOUNDINSTANCE_H__
#define __FMODSOUNDINSTANCE_H__

#include "SoundInstance.h"

#include <fmod.h>
#include <fmod_errors.h>

namespace Sexy
{
	class FModSoundManager;
	class FModSoundInstance : public SoundInstance
	{
	public:
		virtual ~FModSoundInstance(); 

			
		virtual void			SetVolume(double theVolume); 
		virtual void			SetMasterVolumeIdx(int theVolumeIdx);
		virtual void			SetPan(int thePosition); //-db to +db = left to right

		virtual bool			Play(bool looping, bool autoRelease);
		virtual void			Stop();
		virtual bool			IsPlaying();
		virtual bool			IsReleased();

		virtual void			SetBaseVolume(double theBaseVolume); 
		virtual void			SetBasePan(int theBasePan);
		virtual void			SetBaseRate(double theBaseRate);

		virtual void			AdjustPitch(double theNumSteps);
		virtual double			GetVolume();
        void                    RehupVolume();

	protected:
		friend class FModSoundManager;

		FModSoundInstance( FModSoundManager *mgr );
		void Prepare( FMOD_SOUND *sound );
		virtual void Release();

	private:
		FModSoundManager *mMgr;

		bool mAutoRelease;
		bool mPrepared;
		bool mReleased;
		double mBaseRate;

        int mMasterVolumeIdx;

		FMOD_SOUND*				mStream;
		FMOD_CHANNEL*			mChannel;
	};

}

#endif //__FMODSOUNDINSTANCE_H__
