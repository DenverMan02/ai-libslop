#ifndef _WWISEINTERACTIVEAUDIODRIVER_H_INCLUDED_
#define _WWISEINTERACTIVEAUDIODRIVER_H_INCLUDED_

#include "Common.h"

#if SEXY_IS_WWISE_ENABLED

#include "IInteractiveAudioDriver.h"

//fwd dcl for wwise IO
class SexyIOHookBlocking;


namespace Sexy
{
    class WwiseInteractiveAudioDriver : public IInteractiveAudioDriver
    {
    public:
        WwiseInteractiveAudioDriver();
        virtual ~WwiseInteractiveAudioDriver();

		virtual InteractiveSoundManager * CreateSoundManager();

		
        virtual bool InitInteractiveAudioDriver();
		virtual void TermInteractiveAudioDriver();
        
        virtual void Update();
        
        // Event/RTPC/State changes
        // FIXME!AUDIO: there should be a mechanism in the Wwise implementation that allows CueSound and CueRealTime to
        // reference external sources.
        virtual AudioPlayingId SendEvent( AudioEventId eventId, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
        virtual AudioPlayingId SendEvent( const char* eventName, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
		virtual AudioPlayingId SendEventCallback( AudioEventId eventId, InteractiveAudioCallbackType callbackType, IInteractiveAudioCallbackListener* callbackObject, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
		virtual AudioPlayingId SendEventCallback( const char* eventName, InteractiveAudioCallbackType callbackType, IInteractiveAudioCallbackListener* callbackObject, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
//        virtual AudioPlayingId SendEventRTPC( AudioEventId eventId, AudioRtpcId rtpcId, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
//        virtual AudioPlayingId SendEventRTPC( const char* eventName, const char* rtpcName, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
        virtual bool           SetRTPCValue( AudioRtpcId rtpcId, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
        virtual bool           SetRTPCValue( const char* rtpcName, float rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );

		virtual bool           GetRTPCValue( AudioRtpcId rtpcId, float& rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );
		virtual bool           GetRTPCValue( const char* rtpcName, float& rtpcValue, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT );

        virtual bool           SetState( AudioStateGroupId groupId, AudioStateId StateId );
        virtual bool           SetState( const char* groupName, const char* stateName );
		virtual void		   RegisterGameObject(AudioGameObjectId objectId);
		virtual void		   UnregisterGameObject(AudioGameObjectId objectId);

		virtual AudioRtpcId    GetRtpcIdFromString( char const * InRtpcName ) const;
		virtual AudioRtpcId    GetEventIdFromString( char const * InRtpcName ) const;
        
        virtual void		   CancelEventCallback (AudioEventId eventId);
        virtual void           CancelEventCallbackByContext( void * pDeadContext);


        virtual bool           SetSwitch(const char*  in_pszSwitchGroup, const char *in_pszSwitchState, AudioGameObjectId in_objectId = IA_GENERIC_GAME_OBJECT);
		virtual bool		   SetSwitch( AudioSwitchGroupId groupId, AudioSwitchStateId stateId, AudioGameObjectId objectId = IA_GENERIC_GAME_OBJECT);
        
        virtual void           SetGameObjectPosition(AudioGameObjectId i_objectId, const class SexyVector2& i_objectPosition);
		virtual void           SetListenerPosition(const class SexyVector2& i_listenerPosition, int i_listenerIndex = 0);

#if defined(HOST_IPHONEOS)
        void                   HACK_SetPvZStreamingFilePathMap( std::map<std::string, std::string> fileIdToPathMap );
#endif

#if defined(HOST_ANDROID)
		void                   HACK_SetPvZStreamingFilePathMap( std::map<std::string, std::string> fileIdToPathMap );
		void                   HACK_SetAndroidAssetInfo( std::string const & in_fullPath );
#endif

#if defined(HOST_WINDOWS)
		void                   HACK_SetPvZStreamingFilePathMap(std::map<std::string, std::string> fileIdToPathMap);
#endif

#if SEXY_IS_PLATFORM_IOS
		virtual void iOS_WillGetFocus();
#endif // SEXY_IS_PLATFORM_IOS

		virtual void GotFocus();
		virtual void LostFocus();
        
    public:
        
        static bool             m_hasError;

    private:
		AudioRtpcId             GetIdFromString( char const * InRtpcName ) const;

        std::string m_filePath;
        SexyIOHookBlocking* m_pLowLevelIO;
		bool mbWwiseIsInitialized;
    };
    
}

#endif //SEXY_IS_WWISE_ENABLED

#endif
