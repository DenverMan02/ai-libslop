#ifndef NGSSOUNDINSTANCE_H_INCLUDED
#define NGSSOUNDINSTANCE_H_INCLUDED

#include "Common.h"
#include "SoundInstance.h"
#include "ngs_common.h"

namespace Sexy
{

class NGSSoundManager;

class NGSSoundInstance
	: public SoundInstance
{
	friend class NGSSoundManager;
	
public:
	NGSSoundInstance( NGSSoundManager* theSoundManager, SoundInfo* theSourceSound, SceNgsHVoice theVoice);
	~NGSSoundInstance();
	
	void			Release();
		
	void			SetBaseVolume(double theBaseVolume); 
	void			SetBasePan(int theBasePan);
	void			SetBaseRate(double theBaseRate);

	void			AdjustPitch(double theNumSteps);

	void			SetVolume(double theVolume); 
	void			SetMasterVolumeIdx(int theVolumeIdx);
	void			SetPan(int thePosition); //-hundredth db to +hundredth db = left to right

	bool			Play(bool looping, bool autoRelease);	
	void			Stop();
	bool			IsPlaying();
	bool			IsReleased();
	bool			IsDormant();
	bool			IsFree();
	double			GetVolume();

	bool IsAutoRelease();
	void Zombify();
	
protected:

	void Rehup();
	void RehupVolumes();
	NGSSoundManager* mSoundManager;
	SoundInfo* mSource;
	SceNgsHVoice mVoice;


	bool mUsingVarispeed;
	uint32 mPlaybackPacket;
	bool mLooping;
	bool mAutoRelease;
	
	bool mPlayParamLooping;
	bool mPlayParamAutoRelease;
	
	int mBasePan;
	int mPan;
	int mMasterVolumeIdx;
	double mBaseVolume;
	double mVolume;
	double mBaseRate;
	double mRate;
	
		enum State
	{
		/** not maintenanced, not rendering.
		 * only application thread calls must leave DORMANT state.
		 * only audio system thread callbacks must enter DORMANT state.
		 */
		DORMANT,
		
		/** maintenanced, not rendering */
		STOPPED,
		
		/** maintenanced, rendering */
		PREPARING,
		PLAYING,
		
		/** maintenanced, rendering, but all data has been played. */
		FINISHED,
	
	};
	
	State mState;


};

}

#endif //__NGSSoundInstance_H__