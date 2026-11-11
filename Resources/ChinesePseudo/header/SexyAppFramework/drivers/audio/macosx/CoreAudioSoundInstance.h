#ifndef __COREAUDIOSOUNDINSTANCE_H__
#define __COREAUDIOSOUNDINSTANCE_H__

#include "Common.h"
#include "SoundInstance.h"
#include "CoreAudioUtility.h"
#include <libkern/OSAtomic.h>

namespace Sexy
{

class CoreAudioSoundManager;

class CoreAudioSoundInstance
	: public SoundInstance
{
	friend class CoreAudioSoundManager;
	
public:
	CoreAudioSoundInstance( CoreAudioSoundManager* theSoundManager, CoreAudioSoundBuffer* theSourceSound, AudioStreamBasicDescription* busFormat, OSSpinLock* lock );
	~CoreAudioSoundInstance();
	
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

	static OSStatus RenderProc( void* inRefCon, AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp, UInt32 inBusNumber, UInt32 inNumFrames, AudioBufferList* ioData );
	OSStatus FeedAudioUnit( AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp, UInt32 inNumFrames, AudioBufferList* ioData );
	
	static OSStatus ConverterProc( AudioConverterRef inAudioConverter, UInt32* ioNumberDataPackets, AudioBufferList* ioData, AudioStreamPacketDescription** outDataPacketDescription, void* inUserData );
	OSStatus FeedConverter( AudioConverterRef inAudioConverter, UInt32* ioNumberDataPackets, AudioBufferList* ioData, AudioStreamPacketDescription** outDataPacketDescription );
	
	OSStatus DoPostRenderMaintenance( AudioUnit mixerUnit, UInt32 mixerBus, AudioUnit varispeedUnit, double masterVolume );
	bool IsAutoRelease();
	void Zombify();
	
protected:

	void RehupVolume();
	void RehupPan();
	void RehupRate();
	
	CoreAudioSoundManager* mSoundManager;
	CoreAudioSoundBuffer* mSource;
	AudioStreamBasicDescription mBusFormat;
	AudioConverterRef mConverter;
	bool mUsingVarispeed;
	UInt32 mPlaybackPacket;
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
		PLAYING,
		
		/** maintenanced, rendering, but all data has been played. */
		FINISHED,
	
	};
	
	State mState;

	enum MaintenanceBits
	{
		kPlay,
		kStop,
		kRelease,
		kUpdatePan,
		kUpdateVolume,
		kUpdateRate,
	};
	
	uint32_t mMaintenanceFlags;
	uint32_t mMaintenanceFlagsMask;

	void DisallowMaintenanceFlag( uint32_t bit )
	{
		UInt32 mask = 0;
		*((char*) &mask + (bit >> 3)) = (0x80 >> (bit & 7));
		mMaintenanceFlagsMask &= ~mask;
	}
	
	void SetMaintenanceFlag( uint32_t bit )
	{
		UInt32 mask = 0;
		*((char*) &mask + (bit >> 3)) = (0x80 >> (bit & 7));
		mask &= mMaintenanceFlagsMask;
		::OSAtomicOr32Barrier( mask, &mMaintenanceFlags );
	}
	
	bool ReadMaintenanceFlag( uint32_t bit )
    {
		UInt32 mask = 0;
		*((char*) &mask + (bit >> 3)) = (0x80 >> (bit & 7));
        return mask & mMaintenanceFlags;
    }
	
	bool TestMaintenanceFlag( uint32_t bit )
	{
		return ::OSAtomicTestAndClearBarrier( bit, &mMaintenanceFlags );
	}
	
	OSSpinLock* mLock;

	bool mDebugRender;
	bool mDebugMaintenance;

};

}

#endif //__COREAUDIOSOUNDINSTANCE_H__