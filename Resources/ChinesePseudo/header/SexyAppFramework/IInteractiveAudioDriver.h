#pragma once
#ifndef IINTERACTIVEAUDIODRIVER_H_INCLUDED
#define IINTERACTIVEAUDIODRIVER_H_INCLUDED

#include "common.h"

#if SEXY_IS_WWISE_ENABLED

#include "InteractiveSoundTypes.h"
#include "InteractiveSoundManager.h"


namespace Sexy
{
    class SexyAppBase;
    class SoundBank;
	class InteractiveSoundManager;


    class IInteractiveAudioDriver
    {
    public:
        static IInteractiveAudioDriver* CreateInteractiveAudioDriver(SexyAppBase*);
        virtual ~IInteractiveAudioDriver() {}

		virtual InteractiveSoundManager * CreateSoundManager() = 0;

		
        virtual bool InitInteractiveAudioDriver() = 0;
		virtual void TermInteractiveAudioDriver() = 0;
        
        // Update - generally called once per frame
        virtual void Update() {};
        virtual void GotFocus() = 0;
        virtual void LostFocus() = 0;
        
        // Event/RTPC/State changes
        virtual AudioPlayingId SendEvent( AudioEventId eventId, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
        virtual AudioPlayingId SendEvent( const char* eventName, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
		virtual AudioPlayingId SendEventCallback( AudioEventId eventId, InteractiveAudioCallbackType callbackType, IInteractiveAudioCallbackListener* callbackObject, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
		virtual AudioPlayingId SendEventCallback( const char* eventName, InteractiveAudioCallbackType callbackType, IInteractiveAudioCallbackListener* callbackObject, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
//        virtual AudioPlayingId SendEventRTPC( AudioEventId eventId, AudioRtpcId rtpcId, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
//        virtual AudioPlayingId SendEventRTPC( const char* eventName, const char* rtpcName, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;

        virtual bool           SetRTPCValue( AudioRtpcId rtpcId, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
        virtual bool           SetRTPCValue( const char* rtpcName, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
		
		virtual bool           GetRTPCValue( AudioRtpcId rtpcId, float& rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;
		virtual bool           GetRTPCValue( const char* rtpcName, float& rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT ) = 0;

        virtual bool           SetState( AudioStateGroupId groupId, AudioStateId StateId ) = 0;
        virtual bool           SetState( const char* groupName, const char* stateName ) = 0;
		virtual void		   RegisterGameObject(AudioGameObjectId objectId) = 0;
		virtual void		   UnregisterGameObject(AudioGameObjectId objectId) = 0;
        
        virtual void			SetGameObjectPosition(AudioGameObjectId i_objectId, const class SexyVector2& i_objectPosition) = 0;
		virtual void			SetListenerPosition(const class SexyVector2& i_listenerPosition, int i_listenerIndex = 0) = 0;

		virtual AudioRtpcId    GetRtpcIdFromString( char const * InRtpcName ) const = 0;
		virtual AudioRtpcId    GetEventIdFromString( char const * InRtpcName ) const = 0;

        virtual void           CancelEventCallback (AudioEventId eventId) = 0;
		virtual void           CancelEventCallbackByContext( void * pDeadContext ) = 0;
      
		virtual bool		   SetSwitch( AudioSwitchGroupId groupId, AudioSwitchStateId stateId, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT) = 0;
        virtual bool           SetSwitch(const char*  in_pszSwitchGroup, const char *in_pszSwitchState, AudioGameObjectId in_objectId = IA_GENERIC_GAME_OBJECT) = 0;
    };
};

#endif // SEXY_IS_WWISE_ENABLED

#endif
