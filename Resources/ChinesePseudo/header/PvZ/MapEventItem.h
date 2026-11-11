//
//  MapEventItem.h
//  PlantsVersusZombies2
//
//  Extracted from WorldData.h by Bradley Buchanan and Matt Westhoff on 11/6/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MapEventItem__
#define __PlantsVersusZombies2__MapEventItem__

#include "Graphics.h"
#include "PlatformAutodetect.h"
#include "SexyVector.h"

namespace Sexy
{
	class PrimeTypeface;
	class PrimeTextWidget;
}

// When setting the status of an event, if a status already exists,
// it will ONLY be overridden if the new status is greater...
enum WorldMapEventStatus
{
	EVENTSTATUS_UNDISCOVERED,	// Undiscovered, player has not seed event
	EVENTSTATUS_LOCKED,			// Locked, can't click
	EVENTSTATUS_UNLOCKED,		// Unlocked, clickable
	EVENTSTATUS_CLEARED,		// Unlocked and cleared, clickable
    EVENTSTATUS_HARD_CLEARED,    // Unlocked and cleared and hard cleared, clickable
};

enum MapEventType
{
	MAPEVENT_NONE,
	MAPEVENT_LEVEL_ENTRANCE,
	MAPEVENT_REWARD_PLANT_BOX,
	MAPEVENT_REWARD_PLANT,
	MAPEVENT_REWARD_UPGRADE,
	MAPEVENT_REWARD_POWERUP,
    MAPEVENT_REWARD_BONUS,
	MAPEVENT_STAR_GATE,
	MAPEVENT_KEY_GATE,
	MAPEVENT_PATH_NODE,
	MAPEVENT_ISLAND,
	MAPEVENT_DOODAD,
	MAPEVENT_REWARD_GIFT_BOX,
	MAPEVENT_CUSTOM_ART,
    
    // special handled, though it's ugly...
    MAPEVENT_PVP_BEGIN,
    MAPEVENT_PVP_HOUSE,
    MAPEVENT_PVP_HOUSE_ACHIEVE,
    MAPEVENT_PVP_CLOUD,
    MAPEVENT_PVP_CLOUD_PRICE,
    MAPEVENT_PVP_END,
};

enum LevelNodeType
{
	NORMAL_LEVEL,
	MINIGAME_LEVEL,
	MINIBOSS_LEVEL,
	BOSS_LEVEL,
	NONFINAL_BOSS_LEVEL,
};

enum OldMapTutorialState
{
    // These must be in the ORDER THAT THEY APPEAR. Do not place an end-game tutorial
    // in the beginning of this list...
    OLD_TUTORIAL_NONE,
    OLD_TUTORIAL_MAP_INTRO_1,
    OLD_TUTORIAL_ALMANAC_INTRO_1,
    OLD_TUTORIAL_ALMANAC_INTRO_2,
    OLD_TUTORIAL_CONTINUE_EGYPT_LEVEL_3,
    OLD_TUTORIAL_KEYGATE_INTRO_1,
    OLD_TUTORIAL_KEYGATE_INTRO_2,
    OLD_TUTORIAL_KEYGATE_INTRO_3,
    OLD_TUTORIAL_CHALLENGE_INTRO_1,
    
    OLD_TUTORIAL_STARTASK_INTRO_1,
    OLD_TUTORIAL_AFTER_CHALLENGE_1,
    
    OLD_TUTORIAL_YETI_INTRO_1,
    OLD_TUTORIAL_STORE_INTRO_1,
    OLD_TUTORIAL_STARGATE_INTRO_1,
    OLD_TUTORIAL_COUNT,
    
    OLD_TUTORIAL_GACHA_INTRO_1,
    OLD_TUTORIAL_LEVEL_UP_INTRO_1,
    
    OLD_TUTORIAL_DAILY_INTRO_1,
    
    
   	OLD_TUTORIAL_GEMRETURN_INTRO,
    OLD_TUTORIAL_DANGERROOM_INTRO_1,
    OLD_TUTORIAL_MAP_PLANTBOX_INTRO_1,
    OLD_TUTORIAL_MAP_PLANTBOX_INTRO_2,
    
    OLD_TUTORIAL_MAP_PLANTGJ_INTRO_1,
    OLD_TUTORIAL_MAP_PLANTGJ_INTRO_2,
    
    OLD_TUTORIAL_PLANTADVENTURE_INTRO,
    OLD_TUTORIAL_MAP_PVP_INTRO,
    
    OLD_TUTORIAL_EX_COUNT,
};

enum MapTutorialState
{
	// These must be in the ORDER THAT THEY APPEAR.
	// Only add new tutorial states to the END of this list!
	// DO NOT REMOVE ANYTHING EITHER!
	TUTORIAL_NONE,
	//TUTORIAL_MAP_INTRO_1,
	TUTORIAL_ALMANAC_INTRO_1,   // Deprecated
	//TUTORIAL_NEW_DAILY_SIGN,
	//TUTORIAL_CONTINUE_EGYPT_3,
	TUTORIAL_KEYGATE_INTRO_1,	// Deprecated
	TUTORIAL_KEYGATE_INTRO_2,	// Deprecated
	TUTORIAL_KEYGATE_INTRO_3,	// Deprecated
	TUTORIAL_CHALLENGE_INTRO_1,	// Deprecated
	TUTORIAL_AFTER_CHALLENGE_1,	// Deprecated
    //TUTORIAL_STAR_INTRO_1,
    TUTORIAL_STAR_TOUCHWOOD, // Deprecated
	TUTORIAL_STORE_INTRO_1,     // Deprecated
	TUTORIAL_STARGATE_INTRO_1, // Deprecated
	// End of first soft launch. Never add anything before this unless you
	
	// convert the player profile (DON'T DO THAT)
	TUTORIAL_STARGATE_PIRATE_INTRO_1,	// Deprecated
    TUTORIAL_ZOMBOSS_INTRO_1,			// Deprecated
    // End of Global candidate. Don't add anything before 'dis, mon.
	
	TUTORIAL_ZEN_GARDEN_SPROUTS, // Deprecated
	TUTORIAL_ZEN_GARDEN_RETURN_OFTEN, // Deprecated
	TUTORIAL_ZEN_GARDEN_EARN_MORE_COINS, // Deprecated

	TUTORIAL_MINIGAME_INTRO, // Deprecated
	// End of 3.0 EGGPLANT
	
	TUTORIAL_QUEST_INTRO, // Deprecated
	// End of 3.5 JASMINE
    TUTORIAL_DAILY_SIGN, // Deprecated
    //TUTORIAL_GACHA_INTRO_1,
    // Add new events before TUTORIAL_COUNT
	TUTORIAL_COUNT,
    
    // Chinese Ver
    // However this should be reconstructed after worldmap 1.0

	TUTORIAL_MAP_INTRO_1,
	TUTORIAL_NEW_DAILY_SIGN,
	TUTORIAL_CONTINUE_EGYPT_3,
	TUTORIAL_STAR_INTRO_1,
	TUTORIAL_GACHA_INTRO_1,
	//5
	TUTORIAL_GACHA_INTRO_2,
	TUTORIAL_CONTINUE_EGYPT_6,
	//6
	TUTORIAL_TRAVELLOG,
	//7
	TUTORIAL_CONTINUE_EGYPT_8,
	TUTORIAL_GACHA_INTRO_3,
	TUTORIAL_LEVEL_UP_INTRO_1,
	//8-1
	TUTORIAL_ACCESSORY,
	//8-2
    //9
    TUTORIAL_HARD_LEVEL,
    TUTORIAL_FIRST_RECHARGE,
    //10
    TUTORIAL_PLANTFAMILY,
    //11
    TUTORIAL_CHALLENGE,
    //12
    TUTORIAL_JOUST,
    //13
    TUTORIAL_DANGERROOM_INTRO_1,
    //14
    TUTORIAL_CRYSTAL_STORE,
    //15
    TUTORIAL_GALAXY,
    //16
    TUTORIAL_PLANTADVENTURE_INTRO,
    //17
    TUTORIAL_MAP_PVP_INTRO,
    //18
    TUTORIAL_TRANSGENOSIS,
    //19
    TUTORIAL_RIFT_WORLD_OPEN,
    //20
    //TUTORIAL_PVZ1_WORLD_OPEN,

    TUTORIAL_DAILY_INTRO_1,
   	TUTORIAL_GEMRETURN_INTRO,
    TUTORIAL_MAP_PLANTBOX_INTRO_1,
    TUTORIAL_MAP_PLANTBOX_INTRO_2,
    
    TUTORIAL_MAP_PLANTGJ_INTRO_1,
    TUTORIAL_MAP_PLANTGJ_INTRO_2,
    
    TUTORIAL_UNLOCK_WORLD1,
    TUTORIAL_UNLOCK_WORLD2,
    TUTORIAL_CR_STORE,

    TUTORIAL_COBCANNON,
    TUTORIAL_DANGERROOM_INTRO_2,
	TUTORIAL_NEWAVATAR,
	TUTORIAL_DANGERROOM_SELECT,
	TUTORIAL_SUPER_ACCESSORY,

	//extra
	TUTORIAL_ARTIFACT,
	TUTORIAL_PVZ1_WORLD_OPEN,

	TUTORIAL_CUSTOM_LEVEL,

	TUTORIAL_CUSTOM_LEVEL_CREATOR,
	TUTORIAL_CUSTOM_LEVEL_PLAY,

	TUTORIAL_PENNY_CLASSROOM,
	TUTORIAL_PVZ2_UNCHARTED_MODE,

	TUTORIAL_CARD_GAME,
	TUTORIAL_CARD_GAME_PLAY,

	TUTORIAL_CARD_GAME_PLAY_NEW,
	TUTORIAL_GENEENHANCEMENT,//Deprecated
	TUTORIAL_NEWPVP,
	TUTORIAL_GENEENHANCEMENT_NEW,
	TUTORIAL_SPECIAL_UNCHARTED_EVENT,
	TUTORIAL_SPECIAL_UNCHARTED_ANNIVERSARY_EVENT,
	TUTORIAL_SPECIAL_UNCHARTED_ANNIVERSARY_HALLOWEEN_EVENT,
	TUTORIAL_SPECIAL_UNCHARTED_ICEAGE_EVENT,
	TUTORIAL_SPECIAL_UNCHARTED_SPRING_FESTIVAL_2024_EVENT,

    TUTORIAL_EX_COUNT,
};

enum FlagOrientation
{
	FO_NONE,
	FO_LEFT,
	FO_RIGHT,
};

// Used in rifts to decide what secondary icon to draw denoting the type of level
enum MapEventSubType
{
    EVENT_SUBTYPE_NONE,
    EVENT_SUBTYPE_NORMAL,
    EVENT_SUBTYPE_TIMED,
    EVENT_SUBTYPE_LASTSTAND,
    EVENT_SUBTYPE_MINIGAME,
    EVENT_SUBTYPE_ARENA,
    EVENT_SUBTYPE_CONVEYOR,
    EVENT_SUBTYPE_ZOMBOSS,
    EVENT_SUBTYPE_PVZ1_NORMAL,
    EVENT_SUBTYPE_PVZ1_CONVEYOR,
    EVENT_SUBTYPE_PVZ1_LASTSTAND,
    EVENT_SUBTYPE_PVZ1_ELITE,
    EVENT_SUBTYPE_PVZ1_ZOMBOSS,
    EVENT_SUBTYPE_RIFT_TIMED
};

class PlayerInfo;
class WorldMap;
class WorldData;
class WorldMapCamera;

class MapEventItem
{
public:

	MapEventItem();
	MapEventItem (const MapEventItem& i_mapEventItem);
	virtual ~MapEventItem();

	void PrepareForWorldMapSave();

	virtual void				DrawIslandLayer(Sexy::Graphics* i_g, WorldMapCamera* i_camera = NULL, const float i_parallaxOffset = 0.0f);
	virtual void				DrawEventLayer(Sexy::Graphics* i_g, WorldMapCamera* i_camera = NULL, const float i_parallaxOffset = 0.0f);
	virtual void				EditorDraw(Sexy::Graphics* i_g, bool i_isEventLayer, WorldMapCamera* i_camera, const float i_parallaxOffset, const bool i_isInCurrentEditorMode, const bool i_isInCurrentLayer);
	virtual void				OnPrecedingPathRevealComplete(WorldMap& i_worldMap);

	void						CompleteEvent(PlayerInfo* io_info) const;
	bool						IsEventComplete(PlayerInfo* i_info) const;

	bool						DoesPlayerOwnReward(PlayerInfo* i_info) const;
	bool						DoesEventGiveReward() const;
	void						GivePlayerReward(PlayerInfo* io_info) const;

	inline void					SetPosition(const Sexy::SexyVector2& i_position);
	inline const Sexy::SexyVector2&	GetPosition() const;

	inline void					SetImageID(const uint16 i_imageID);
	inline const uint16			GetImageID() const;

	inline void					SetImageData(const Sexy::ImagePtr i_imagePtr, const Sexy::Point i_imageOffset);
	inline void					GetImageData(Sexy::ImagePtr& o_imagePtr, Sexy::Point& o_imageOffset) const;
	inline bool					HasImageData() const;

	void						SetAssetFilter(const int i_filter);
	void						OverrideFilter(const int i_filter);
	int							GetFilter() const;

	inline void					SetEventType(const MapEventType i_eventType);
	inline const MapEventType	GetEventType() const;

	void 						SetEventId(uint16 i_eventId);
	uint16 						GetEventId() const;

	inline void					SetName(const std::string& i_name);
	inline const std::string&	GetName() const;
	inline std::string*			GetNameRef();

	void						SetToggleName(const std::string& i_toggle);
	const std::string&			GetToggleName() const;
	std::string*				GetToggleNameRef();
    
    void						SetAdventurePlantName(const std::string& plantName);
    void				        SetAdventurePlantLockStatus(bool locked);
    
	inline void					SetDataString(const std::string& i_string);
	inline const std::string&	GetDataString() const;
	inline std::string*			GetDataStringRef();

	// Returns a const ref to the string that the profile uses to test whether we are unlocked
	inline const std::string&	GetPlayerProfileStatusString() const;

	inline void					SetUnlockedFrom(const std::string& i_string);
	inline const std::string&	GetUnlockedFrom() const;
	inline void					SetUnlockedFromPtr(MapEventItem* i_ptr);
	inline MapEventItem*		GetUnlockedFromPtr() const;

	inline void					SetVisibleFrom(const std::string& i_string);
	inline const std::string&	GetVisibleFrom() const;
	inline void					SetVisibleFromPtr(MapEventItem* i_ptr);
	inline MapEventItem*		GetVisibleFromPtr() const;

	inline void					SetParentEvent(const std::string& i_string);
	inline const std::string&	GetParentEvent() const;
	void						SetParentEventPtr(MapEventItem* i_ptr);
	inline MapEventItem*		GetParentEventPtr() const;

	inline void					SetDisplayText(const std::string& i_string);
	inline const std::string&	GetDisplayText() const;
	inline std::string*			GetDisplayTextRef();
	Sexy::PrimeTypeface*        GetAdviceFont();

	inline void					SetAutoVisible(const bool i_isAutoVisible);
	inline const bool			IsAutoVisible() const;

	inline void					SetIsFlashing(const bool i_isFlashing);
	inline const bool			IsFlashing() const;

	inline void					SetWorldMapTutorial(const MapTutorialState i_newTutorialName);
	inline MapTutorialState		GetWorldMapTutorial() const;

	inline void					SetIsArtFlipped(const bool i_isArtFlipped);
	inline const bool			IsArtFlipped() const;

	inline void					SetIsChallengeType(const bool isChallengeType);
	inline const bool			IsChallengeType() const;

	inline void					SetLevelNodeType(const LevelNodeType i_nodeType);
	inline const LevelNodeType	GetLevelNodeType() const;

	inline void					SetArtRotation(const int16 i_rotation);
	inline int16				GetArtRotation() const;

	inline void					SetArtRotationRate(float i_rotationRate);
	inline float				GetArtRotationRate() const;

	inline void					SetScaleX(const float i_scaleX);
	inline float				GetScaleX() const;

	inline void					SetScaleY(const float i_scaleY);
	inline float				GetScaleY() const;

	inline void					SetParallaxLayer(const int8 i_layer);
	inline int8					GetParallaxLayer() const;

	inline void					SetCost(const uint32 i_cost);
	inline const uint32			GetCost() const;
	inline uint32*				GetCostRef();

	inline void					SetCompletedNarrationID(const std::string& i_cost);
	inline const std::string&	GetCompletedNarrationID() const;
	inline std::string*			GetCompletedNarrationIDRef();

	inline void					SetUnlockedNarrationID(const std::string& i_cost);
	inline const std::string&	GetUnlockedNarrationID() const;
	inline std::string*			GetUnlockedNarrationIDRef();

	inline void					SetIsVisible(const bool i_isVisible);
	inline const bool			IsVisible() const;

	inline void					SetIsUnlocked(const bool i_isUnlocked);
	inline const bool			IsUnlocked() const;

	inline void					SetIsCleared(const bool i_isCleared);
	inline const bool			IsCleared() const;
    
    inline void					SetStarCount(int i_totalStars);
    inline void					SetCurrentStarCount(int i_totalStars);
    inline void					SetStarCompletionMask(uint i_completionMask);
    inline int					GetStarCount() const;
    inline int					GetCurrentStarCount() const;
    inline bool					GetStarCompletion(int i_starIndex) const;

	inline void					SetIsClaimable(const bool i_isClaimable);
	inline const bool			IsClaimable() const;

	inline void					SetIsWorldBeingEdited(const bool i_isWorldBeingEdited);
	inline const bool			IsWorldBeingEdited() const;

	inline void					SetPopanimID(const int16 i_popanimID);
	inline const int16			GetPopanimID() const;

	inline void					SetWorldPopanimID(const int16 i_worldPopanimID);
	inline const int16			GetWorldPopanimID() const;

	inline void					SetWorldDataPtr(WorldData* i_worldData);
	inline WorldData*			GetWorldDataPtr() const;

	inline void					SetDrawLayer(const int8 i_drawLayer);
	inline int8					GetDrawLayer() const;

	inline void					AddChild(MapEventItem* i_child);
	inline void					RemoveChild(MapEventItem* i_child);
	const std::vector<MapEventItem*>& GetChildren() const;

	void						ResetPointers();
	void						InitializeMembers();

	void 						setZombossNodePopAnimStr(std::string i_str) { m_zombossNodePopAnimStr = i_str; }

private:
	void						prepareLevelTitleText();
    void                        DrawMapStars(Sexy::Graphics* i_g, WorldMapCamera* i_camera);
    void                        DrawMapAdventurePlant(Sexy::Graphics* i_g, WorldMapCamera* i_camera);
    void                        drawRiftEventAdditionalIcons(Sexy::Graphics* i_g, WorldMapCamera* i_camera);
    bool						isPVZ1Node(MapEventSubType i_type);

public:

	// Serialized
	Sexy::SexyVector2			m_position;				// Position on the map;
	uint16						m_imageID;				// Image ID to use
	MapEventType				m_eventType;			// Type of event we have
	MapEventSubType             m_eventSubType;         // SubType of event we have (used for Rifts to display the type of level)
	std::string					m_name;					// Name of the event
	std::string					m_dataString;			// Name of  reward to give, based on event type (plant name, etc)
	std::string					m_unlockedFrom;			// If specified, name of event that must be completed in order to unlock this event
	std::string					m_visibleFrom;			// If specified, name of event that must be completed in order to see this event
	std::string					m_parentEvent;			// If specified, name of event that links to this event (for paths and stuff)
	std::string					m_displayText;			// If specified, text to be displayed on the map under the event
	std::string					m_toggleName;			// If specified, the liveconfig toggle that controls whether this event is enabled
	uint32						m_cost;					// Cost of unlock (coins or stars)
	std::string					m_unlockedNarrationID;	// Narration ID to play when the event is first unlocked.
	std::string					m_completedNarrationID;	// Narration ID to play when the event is first completed.
	MapTutorialState			m_worldMapTutorial;		// If specified, the world map will try and do a tutorial with this name when our status is...
	WorldMapEventStatus			m_worldMapTutorialVisibleWhen; // ... this value!
	LevelNodeType				m_levelNodeType;		// Level node type to use for level entrance nodes
	int8						m_drawLayer;			// Rendering order for the object. 0 is default, can go -127 to 127
	int16						m_rotationAngle;		// Angle to draw image, default is 0
	float						m_rotationRate;
	float						m_scaleX;				// Scale X to draw image, default is 1.0f. Min, Max, and increment size defined WorldMap.cpp (k_editorScalePieceMinSize, k_editorScalePieceMaxSize, k_editorScalePieceIncrement)
	float						m_scaleY;				// Scale Y to draw image, default is 1.0f. Min, Max, and increment size defined WorldMap.cpp (k_editorScalePieceMinSize, k_editorScalePieceMaxSize, k_editorScalePieceIncrement)
	int8						m_parallaxLayer;		// Parallax layer the art appears on
	uint16						m_eventId;				// Unique ID for this event.
	int8						m_filter;				// MapFilter used by this asset

	// Not serialized
	Sexy::ImagePtr				m_image;				// Image to draw
	Sexy::Point					m_imageOffset;			// Offset of image to draw
	Sexy::ImagePtr				m_keyImg;				// Key image to draw on the keygate flag
	MapEventItem*				m_parent;				// The pointer to our parent event from the text
	std::vector<MapEventItem*>  m_children;				// Pointers to all items that have set their parent to this item.
	MapEventItem*				m_visibleFromEvent;		// The pointer to our visibleFrom event from the text
	MapEventItem*				m_unlockedFromEvent;	// The pointer to our unlockedFrom event from the text
	int16						m_popanimID;			// ID of popanim assigned to this event
	int16						m_worldPopanimID;		// ID of popanim assigned to this event
	WorldData*					m_worldDataPtr;			// WorldData* for the world that this event belongs to
	bool						m_isVisible;			// Specifies if the event is visible (based upon requirements from WorldMapEventItem)
	bool						m_isUnlocked;			// Specifies if the event is locked
	bool						m_isCleared;			// Specifies if the event is cleared
    int							m_starCount;			// Total available stars
    int                         m_currentStarCount;
    uint						m_starCompletionMask;	// Bitmask of completed stars out of m_starCount possible. First bit == first star, etc.
	bool						m_autoVisible;			// If specified, event is made visible when the map is loaded.
	bool						m_canBeClaimed;			// Specify if this event item can be claimed for free via restore purchases.
	bool						m_flashing;				// Specify if this event item is flashing (tutorial use)
	bool						m_isArtFlipped;			// If specified, flips the art horizontally when drawn
	bool						m_isChallengeType;		// If specified, the path that comes from the event is a challenge type

	bool						m_isWorldBeingEdited;	// Specifies if the event's world is being edited
	bool						m_isSelected;			// Specify if this event item is selected (editor use)
	bool						m_inheritAssetFilter;	// Does this event inherit its filter from its art asset?

	int8						m_assetFilter;			// Filter specified by the asset

	Sexy::PrimeTextWidget*		m_eventText;			// Main text string to cache off for display
    std::string					m_adventurePlantName;
    bool						m_isAdventurePlantLocked;
    std::string					m_zombossNodePopAnimStr;	// Specifies the boss's floating island popanim name
    

private:
	void						drawImageFlashing(Sexy::Graphics* i_g, WorldMapCamera* i_camera, Sexy::Image* i_image, int i_posX, int i_posY);
	void						drawImageFlashing(Sexy::Graphics* i_g, WorldMapCamera* i_camera, Sexy::Image* i_image, int i_posX, int i_posY, int i_width, int i_height);

	FlagOrientation				getFlagOrientation();

};

inline void MapEventItem::SetPosition(const Sexy::SexyVector2 &i_position)
{
	m_position.x = i_position.x;
	m_position.y = i_position.y;
}

inline const Sexy::SexyVector2&	MapEventItem::GetPosition() const
{
	return m_position;
}

inline void	MapEventItem::SetImageID(const uint16 i_imageID)
{
	m_imageID = i_imageID;
}

inline const uint16 MapEventItem::GetImageID() const
{
	return m_imageID;
}

inline void	MapEventItem::SetImageData(const Sexy::ImagePtr i_imagePtr, const Sexy::Point i_imageOffset)
{
	m_image = i_imagePtr;
	m_imageOffset = i_imageOffset;
}

inline void MapEventItem::GetImageData(Sexy::ImagePtr& o_imagePtr, Sexy::Point& o_imageOffset) const
{
	o_imagePtr = m_image;
	o_imageOffset = m_imageOffset;
}

inline bool MapEventItem::HasImageData() const
{
	return (m_image.IsValid());
}

inline void MapEventItem::SetEventType(const MapEventType i_eventType)
{
	m_eventType = i_eventType;
}

inline const MapEventType MapEventItem::GetEventType() const
{
	return m_eventType;
}

inline void MapEventItem::SetName(const std::string& i_name)
{
	m_name = i_name;
}

inline const std::string& MapEventItem::GetName() const
{
	return m_name;
}

inline std::string* MapEventItem::GetNameRef()
{
	return &m_name;
}

inline void MapEventItem::SetDataString(const std::string& i_string)
{
	m_dataString = i_string;
}

inline const std::string& MapEventItem::GetDataString() const
{
	return m_dataString;
}

inline std::string* MapEventItem::GetDataStringRef()
{
	return &m_dataString;
}

inline const std::string& MapEventItem::GetPlayerProfileStatusString() const
{
	switch (m_eventType)
	{
		case MAPEVENT_KEY_GATE:
		case MAPEVENT_STAR_GATE:
		case MAPEVENT_PATH_NODE:
		case MAPEVENT_REWARD_GIFT_BOX:
			return m_name;

		case MAPEVENT_REWARD_PLANT:
		case MAPEVENT_REWARD_PLANT_BOX:
		case MAPEVENT_REWARD_UPGRADE:
		case MAPEVENT_REWARD_POWERUP:
		case MAPEVENT_LEVEL_ENTRANCE:
			return m_dataString;

		default:
			return m_name;
	}
}

inline void MapEventItem::SetAutoVisible(const bool i_isAutoVisible)
{
	m_autoVisible = i_isAutoVisible;
}

inline const bool MapEventItem::IsAutoVisible() const
{
	return m_autoVisible;
}

inline void MapEventItem::SetIsFlashing(const bool i_isFlashing)
{
	m_flashing = i_isFlashing;
}

inline const bool MapEventItem::IsFlashing() const
{
	return m_flashing;
}

inline void MapEventItem::SetWorldMapTutorial(const MapTutorialState i_newTutorialName)
{
	m_worldMapTutorial = i_newTutorialName;
}
inline MapTutorialState MapEventItem::GetWorldMapTutorial() const
{
	return m_worldMapTutorial;
}

inline void MapEventItem::SetIsArtFlipped(const bool i_isArtFlipped)
{
	m_isArtFlipped = i_isArtFlipped;
}

inline const bool MapEventItem::IsArtFlipped() const
{
	return m_isArtFlipped;
}

inline void MapEventItem::SetIsChallengeType(const bool i_isChallenge)
{
	m_isChallengeType = i_isChallenge;
}

inline const bool MapEventItem::IsChallengeType() const
{
	return m_isChallengeType;
}

inline void MapEventItem::SetLevelNodeType(const LevelNodeType i_nodeType)
{
	m_levelNodeType = i_nodeType;
}

inline const LevelNodeType MapEventItem::GetLevelNodeType() const
{
	return m_levelNodeType;
}

inline void	MapEventItem::SetArtRotation(const int16 i_rotationAngle)
{
	m_rotationAngle = i_rotationAngle;
}

inline int16 MapEventItem::GetArtRotation() const
{
	return m_rotationAngle;
}

inline void MapEventItem::SetArtRotationRate(float i_rotationRate)
{
	m_rotationRate = i_rotationRate;
}

inline float MapEventItem::GetArtRotationRate() const
{
	return m_rotationRate;
}

inline void	MapEventItem::SetScaleX(const float i_scaleX)
{
	m_scaleX = i_scaleX;
}

inline float MapEventItem::GetScaleX() const
{
	return m_scaleX;
}

inline void	MapEventItem::SetScaleY(const float i_scaleY)
{
	m_scaleY = i_scaleY;
}

inline float MapEventItem::GetScaleY() const
{
	return m_scaleY;
}

inline void	MapEventItem::SetParallaxLayer(const int8 i_layer)
{
	m_parallaxLayer = i_layer;
}

inline int8 MapEventItem::GetParallaxLayer() const
{
	return m_parallaxLayer;
}

inline void MapEventItem::SetUnlockedFrom(const std::string& i_string)
{
	m_unlockedFrom = i_string;
}

inline const std::string& MapEventItem::GetUnlockedFrom() const
{
	return m_unlockedFrom;
}

inline void MapEventItem::SetUnlockedFromPtr(MapEventItem* i_ptr)
{
	m_unlockedFromEvent = i_ptr;
}

inline MapEventItem* MapEventItem::GetUnlockedFromPtr() const
{
	return m_unlockedFromEvent;
}

inline void MapEventItem::SetVisibleFrom(const std::string& i_string)
{
	m_visibleFrom = i_string;
}

inline const std::string& MapEventItem::GetVisibleFrom() const
{
	return m_visibleFrom;
}

inline void MapEventItem::SetVisibleFromPtr(MapEventItem* i_ptr)
{
	m_visibleFromEvent = i_ptr;
}

inline MapEventItem* MapEventItem::GetVisibleFromPtr() const
{
	return m_visibleFromEvent;
}

inline void MapEventItem::SetParentEvent(const std::string& i_string)
{
	m_parentEvent = i_string;
}

inline const std::string& MapEventItem::GetParentEvent() const
{
	return m_parentEvent;
}

inline void MapEventItem::AddChild(MapEventItem* i_child)
{
	DBG_ASSERT(std::find(m_children.begin(), m_children.end(), i_child) == m_children.end());
	m_children.push_back(i_child);
}

inline void MapEventItem::RemoveChild(MapEventItem* i_child)
{
	DBG_ASSERT(std::find(m_children.begin(), m_children.end(), i_child) != m_children.end());
	m_children.erase(std::find(m_children.begin(), m_children.end(), i_child));
}

inline const std::vector<MapEventItem*>& MapEventItem::GetChildren() const
{
	return m_children;
}

inline MapEventItem* MapEventItem::GetParentEventPtr() const
{
	return m_parent;
}

inline void MapEventItem::SetDisplayText(const std::string& i_string)
{
	m_displayText = i_string;
}

inline const std::string& MapEventItem::GetDisplayText() const
{
	return m_displayText;
}

inline std::string* MapEventItem::GetDisplayTextRef()
{
	return &m_displayText;
}

inline void MapEventItem::SetCost(const uint32 i_cost)
{
	m_cost = i_cost;
}

inline const uint32 MapEventItem::GetCost() const
{
	return m_cost;
}

inline uint32* MapEventItem::GetCostRef()
{
	return &m_cost;
}

inline void MapEventItem::SetCompletedNarrationID(const std::string& i_narrationID)
{
	m_completedNarrationID = i_narrationID;
}

inline const std::string& MapEventItem::GetCompletedNarrationID() const
{
	return m_completedNarrationID;
}

inline std::string* MapEventItem::GetCompletedNarrationIDRef()
{
	return &m_completedNarrationID;
}

inline void MapEventItem::SetUnlockedNarrationID(const std::string& i_narrationID)
{
	m_unlockedNarrationID = i_narrationID;
}
inline const std::string& MapEventItem::GetUnlockedNarrationID() const
{
	return m_unlockedNarrationID;
}
inline std::string* MapEventItem::GetUnlockedNarrationIDRef()
{
	return &m_unlockedNarrationID;
}

inline void MapEventItem::SetIsVisible(const bool i_isVisible)
{
	m_isVisible = i_isVisible;
}

inline const bool MapEventItem::IsVisible() const
{
	return m_isVisible;
}

inline void MapEventItem::SetIsUnlocked(const bool i_isUnlocked)
{
	m_isUnlocked = i_isUnlocked;
}

inline const bool MapEventItem::IsUnlocked() const
{
	return m_isUnlocked;
}

inline void MapEventItem::SetIsCleared(const bool i_isCleared)
{
	m_isCleared = i_isCleared;
}

inline const bool MapEventItem::IsCleared() const
{
	return m_isCleared;
}

inline void MapEventItem::SetStarCount(int i_totalStars)
{
    m_starCount = i_totalStars;
}
inline void MapEventItem::SetCurrentStarCount(int i_totalStars)
{
    m_currentStarCount = i_totalStars;
}
inline void MapEventItem::SetStarCompletionMask(uint i_completionMask)
{
    m_starCompletionMask = i_completionMask;
}
inline int MapEventItem::GetStarCount() const
{
    return m_starCount;
}
inline int MapEventItem::GetCurrentStarCount() const
{
    return m_currentStarCount;
}
inline bool MapEventItem::GetStarCompletion(int i_starIndex) const
{
    return (m_currentStarCount == 1 && i_starIndex == 0) || (m_currentStarCount == 3);
}

inline void MapEventItem::SetIsClaimable(const bool i_isClaimable)
{
	m_canBeClaimed = i_isClaimable;
}

inline const bool MapEventItem::IsClaimable() const
{
	return m_canBeClaimed;
}

inline void MapEventItem::SetIsWorldBeingEdited(const bool i_isWorldBeingEdited)
{
	m_isWorldBeingEdited = i_isWorldBeingEdited;
}

inline const bool MapEventItem::IsWorldBeingEdited() const
{
	return m_isWorldBeingEdited;
}

inline void MapEventItem::SetPopanimID(const int16 i_popanimID)
{
	m_popanimID = i_popanimID;
}

inline const int16 MapEventItem::GetPopanimID() const
{
	return m_popanimID;
}

inline void MapEventItem::SetWorldPopanimID(const int16 i_worldPopanimID)
{
	m_worldPopanimID = i_worldPopanimID;
}

inline const int16 MapEventItem::GetWorldPopanimID() const
{
	return m_worldPopanimID;
}

inline void MapEventItem::SetWorldDataPtr(WorldData* i_worldData)
{
	m_worldDataPtr = i_worldData;
}

inline WorldData* MapEventItem::GetWorldDataPtr() const
{
	return m_worldDataPtr;
}

inline void MapEventItem::SetDrawLayer(const int8 i_drawLayer)
{
	m_drawLayer = i_drawLayer;
}

inline int8 MapEventItem::GetDrawLayer() const
{
	return m_drawLayer;
}


#endif /* defined(__PlantsVersusZombies2__MapEventItem__) */
