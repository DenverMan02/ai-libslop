#ifndef _INTERACTIVESOUNDMANAGER_H_
#define _INTERACTIVESOUNDMANAGER_H_

#include "IInteractiveAudioDriver.h"

#if SEXY_IS_WWISE_ENABLED

namespace Sexy
{

class InteractiveSoundManager;
class IInteractiveAudioDriver;

struct InteractiveSoundManagerConfig
{
	InteractiveSoundManagerConfig()
		: mMasterVolumeParamName(NULL)
		, mSfxVolumeParamName( "sfx_volume" )
		, mMusicVolumeParamName( "music_volume" )
	{
		mLoadGroups.push_back( "WiseInit" );
		mLoadIndexGroups.push_back( "StreamingWave" );
	}

	std::vector< std::string > mLoadGroups;
	std::vector< std::string > mLoadIndexGroups;
    
#if defined(PRIME_FOR_PVZ2)
    std::map<std::string, std::string> mFileIdToPathMap;
#endif
    
	char const * mMasterVolumeParamName;
	char const * mSfxVolumeParamName;
	char const * mMusicVolumeParamName;
};

class InteractiveSoundManager
{
public:
//PVZ2_CHINESE_START
	InteractiveSoundManager( IInteractiveAudioDriver * InDriver );
//PVZ2_CHINESE_END
	bool Initialize( InteractiveSoundManagerConfig const & config );
	void Terminate();

//PVZ2_CHINESE_START
	void PauseAll(bool bPause);
	void StopAll();
//PVZ2_CHINESE_END

	void Update();

	void SetSfxVolume( float newVolume );
	float GetSfxVolume() const;

	void SetMusicVolume( float newMusicVolume );
	float GetMusicVolume() const;

	float GetMasterVolume() const;
	void SetMasterVolume( float newVolume );

	
	void RegisterAudioGameObject( AudioGameObjectId newObject );
	void UnregisterAudioGameObject( AudioGameObjectId newObject );

	AudioPlayingId SendEvent( char const * InEventName, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT );
	AudioPlayingId SendEvent( AudioEventId InEventId, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT );

	AudioPlayingId SendEventCallback( const char* InEventName
									, InteractiveAudioCallbackType InCallbackType
									, IInteractiveAudioCallbackListener* InCallbackObject
									, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT);
	
	AudioPlayingId SendEventCallback( AudioEventId InEventId
									, InteractiveAudioCallbackType InCallbackType
									, IInteractiveAudioCallbackListener* InCallbackObject
									, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT);

	bool SetRTPCValue( char const* InRtpcName, float InRtpcValue, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT );
	bool SetRTPCValue( AudioRtpcId InRtpcId, float InRtpcValue, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT );
	bool GetRTPCValue( char const* InRtpcName, float& OutRtpcValue, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT ) const;
	bool GetRTPCValue( AudioRtpcId InRtpcId, float& OutRtpcValue, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT ) const;


	AudioPlayingId SendEventRTPC( char const* InEventName, char const * InRtpcName, float InRtpcValue, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT );
	AudioPlayingId SendEventRTPC( AudioEventId InEventId, AudioRtpcId InRtpcId, float InRtpcValue, AudioGameObjectId InGameObjectId = IA_GENERIC_GAME_OBJECT );

	AudioRtpcId    GetRtpcIdFromString( char const * InRtpcName ) const;
	AudioRtpcId    GetEventIdFromString( char const * InRtpcName ) const;

    void CancelEventCallback( AudioEventId InEventId );
	void CancelEventCallbackByContext( void * InContext );


protected:
	typedef std::map<AudioGameObjectId,uint> AudioGameObjectRegistry;
	AudioGameObjectRegistry mGameObjects;
/*
	typedef std::map<AudioPlayingId, IPersistentAudioListener*> PersistentEventMap;
	PersistentEventMap mPersistentEvents;
*/
	IInteractiveAudioDriver * mAudioDriver;

	AudioRtpcId mMasterVolumeRTPC;
	AudioRtpcId mSfxVolumeRTPC;
	AudioRtpcId mMusicVolumeRTPC;

	std::vector<class ResourceGroup*> mLoadedGroups;
	std::vector<class ResourceGroup*> mLoadedIndexGroups;

	bool mbPause;	//PVZ2_CHINESE
    bool mbResLoaded = false;
};

}

#endif

#endif // _INTERACTIVESOUNDMANAGER_H_
