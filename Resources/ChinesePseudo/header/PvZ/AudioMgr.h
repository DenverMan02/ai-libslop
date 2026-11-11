//
//  AudioMgr.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 6/22/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

// 

#ifndef PlantsVersusZombies2_AudioMgr_h
#define PlantsVersusZombies2_AudioMgr_h

#include "Singleton.h"
#include "LocklessQueue.h"
#include <map>
#include "TimeMgr.h"

namespace Message
{
    void MusicBeatReceived();
    void MusicBarReceived();
};

class AudioMgr : public LazySingleton<AudioMgr> 
{
public:
   
    // Call Init after resources have been loaded. 
    void Init();
    void Term();
    void OnLevelEnded();

    // SendEventThrottled
    // - send an event only if throttle time has expired. 
    uint32 SendEventThrottled(const std::string& i_eventName, pvztime_t i_throttleTime, void* i_objectId=NULL);
    
    uint32 SendEvent(uint32 i_eventId, void* i_objectId=NULL);
           
    uint32 SendEvent(const char* i_eventName, void* i_objectId=NULL);
    
    uint32 SendEvent(const std::string& i_eventName, void* i_objectId=NULL);
    
    uint32 SendEventCallback(uint32 i_eventId, InteractiveAudioCallbackType i_callbackType, IInteractiveAudioCallbackListener* i_callbackFunction, void* i_objectId= NULL);
    
    uint32 SendEventCallback(const char* i_eventName, InteractiveAudioCallbackType i_callbackType, IInteractiveAudioCallbackListener* i_callbackFunction, void* i_objectId= NULL);
    
    uint32 SendEventCallback(const std::string& i_eventName, InteractiveAudioCallbackType i_callbackType, IInteractiveAudioCallbackListener* i_callbackFunction, void* i_objectId= NULL);
    
    void CancelEventCallback(uint32 i_eventId);
    
    bool SetRTPCValue(uint32 i_rtpcId, double i_rtpcValue, void* i_objectId);
    
    bool SetRTPCValue(const char* i_rtpcName, double i_rtpcValue, void* i_objectId);

    bool SetRTPCValue(uint32 i_rtpcId, double i_rtpcValue);
    
    bool SetRTPCValue(const char* i_rtpcName, double i_rtpcValue);
    
    bool SetState(uint32 i_stateGroupId, uint32 i_stateGroupValue);

    bool SetState(const char* i_stateGroupName, const char* i_stateGroupValue);
    
    bool SetSwitch(const char* i_switchGroup,				///< Name of the switch group
                   const char* i_switchState, 				///< Name of the switch
                   void*       i_gameObjectID = NULL);
    
    void RegisterForAudio(void* i_objectId);

    void UnregisterForAudio(void* i_objectId);
	
	void SetObjectPosition(void* i_objectId, const SexyVector2& i_position);
	
	void SetListenerPosition(const SexyVector2& i_position, int i_listenerIndex = 0);
    
    // Audio/gameplay thread interaction functions.
    
    // Should be called from audio thread only.
    void AddDataToCallbackQueue(uint32 i_data);
    
    // Should be called from gameplay thread only.
    bool ReadDataFromCallbackQueue(uint32& o_data);
    void BroadcastCallbackMessages();

    
#if SEXY_IS_WWISE_ENABLED
    void SetAudioDriver(IInteractiveAudioDriver* pdriver){m_audioDriver = pdriver;}
#else
    void SetAudioDriver(IAudioDriver* pdriver){m_audioDriver = pdriver;}
#endif
    
private:
#if SEXY_IS_WWISE_ENABLED
	IInteractiveAudioDriver* m_audioDriver;
#else
	IAudioDriver*			m_audioDriver;
#endif

    std::map<const std::string, pvztime_t>	m_throttledAudios;
	
    // For audio/gameplay thread interaction
    LocklessQueue<uint32> CallbackDataQueue;

public:
	// PVZ Specific Implementation
	// Uses a totally different internal listener position for playing positional audio
	//
	// TODO: Refactor into a better home if this section grows
	void SetListenerInternalPosition(const SexyVector2& i_position);
	
	void SendPositionalAudioValue(void *i_objectId, const Sexy::SexyVector3 &i_position);
	
private:
	// PVZ Specific Implementation
	Sexy::SexyVector2						m_internalListenerPosition;
};




#define gAudioMgr (AudioMgr::GetInstancePtr())

#endif
