#ifndef _INTERACTIVESOUNDTYPES_H_
#define _INTERACTIVESOUNDTYPES_H_

namespace Sexy
{
    typedef uint32 AudioBankId;
    typedef uint32 AudioEventId;
    typedef uint32 AudioPlayingId;
    typedef uint32 AudioStateGroupId;
    typedef uint32 AudioStateId;
    typedef uint32 AudioRtpcId;
    typedef uint32 AudioSwitchGroupId;
    typedef uint32 AudioSwitchStateId;
    typedef void*  AudioGameObjectId;
    
    static uint32 const IA_INVALID_UNIQUE_ID                    = 0;
    static void* const IA_INVALID_GAME_OBJECT                  = (AudioGameObjectId)-1;
    static uint32 const IA_INVALID_PLAYING_ID                   = (AudioPlayingId)IA_INVALID_UNIQUE_ID;
    
    static void* const IA_GENERIC_GAME_OBJECT                  = (AudioGameObjectId)0;
    static void* const IA_GLOBAL_GAME_OBJECT                  = (AudioGameObjectId)-1;
    
    // For now, mirror the WWise values
    enum InteractiveAudioCallbackType
    {
        IACT_EndOfEvent 				  = 0x0001,
        
        IACT_EndOfDynamicSequenceItem	  = 0x0002,
        IACT_Marker 					  = 0x0004,
        IACT_Duration					  = 0x0008,
        
        IACT_SpeakerVolumeMatrix		  = 0x0010,
        
        IACT_MusicPlayStarted			  = 0x0080,
        
        IACT_MusicSyncBeat				  = 0x0100,
        IACT_MusicSyncBar				  = 0x0200,
        
        IACT_MusicSyncEntry 			  = 0x0400,
        IACT_MusicSyncExit				  = 0x0800,
        
        IACT_MusicSyncGrid				  = 0x1000,
        IACT_MusicSyncUserCue			  = 0x2000,
        
        IACT_MusicSyncPoint 			  = 0x4000,
        
        IACT_MusicSyncAll				  = 0xff00,
        IACT_CallbackBits				  = 0xffff,
    };
    
    class IInteractiveAudioCallbackListener
    {
    public:
        virtual ~IInteractiveAudioCallbackListener()
        {}
        
        virtual void OnEndOfEvent( AudioGameObjectId id, AudioPlayingId playingId, AudioEventId eventId ) { assert(0); }
        
        virtual void OnEndOfDynamicSequenceItem( AudioGameObjectId id ) { assert(0); }
        virtual void OnMarker( AudioGameObjectId id ) { assert(0); }
        virtual void OnDuration( AudioGameObjectId id ) { assert(0); }
        
        virtual void OnSpeakerVolumeMatrix( AudioGameObjectId id ) { assert(0); }
        
        virtual void OnMusicPlayStarted( AudioGameObjectId id ) { assert(0); }
        
        virtual void OnMusicSyncBeat( AudioGameObjectId id ) { assert(0); }
        virtual void OnMusicSyncBar( AudioGameObjectId id ) { assert(0); }
        
        virtual void OnMusicSyncEntry( AudioGameObjectId id, AudioPlayingId playingId ) { assert(0); }
        virtual void OnMusicSyncExit( AudioGameObjectId id, AudioPlayingId playingId ) { assert(0); }
        
        virtual void OnMusicSyncGrid( AudioGameObjectId id ) { assert(0); }
        virtual void OnMusicSyncUserCue( AudioGameObjectId id ) { assert(0); }
        
        virtual void OnMusicSyncPoint( AudioGameObjectId id ) { assert(0); }
        
    };
} // namespace Sexy

#endif // _INTERACTIVESOUNDTYPES_H_

