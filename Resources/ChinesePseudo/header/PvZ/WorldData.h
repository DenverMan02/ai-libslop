
//  WorldData.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 8/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldData_h
#define PlantsVersusZombies2_WorldData_h

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "Image.h"
#include "MapEventItem.h"
#include "PlatformAutodetect.h"
#include "Point.h"
#include "Rect.h"
#include "RtObject.h"
#include "dtypes.h"

class PopAnimRig;

struct WorldMapAsset
{
    Sexy::ImagePtr ImagePtr;
    PopAnimRig* PopAnimRigPtr;
    int Filter;
    bool IsLoaded;
};

struct WorldResourcesData;

constexpr const uint8 CurrentWorldDataVersion()
{
    // version 0: initial
    // version 1: start anim world art at index 100 (this is a hack)
    return 1;
}

class WorldData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(WorldData, Sexy::RtObject, Sexy::RtClass);
    
    WorldData()
    : Sexy::RtObject{}
    , m_mapPieces{}
    , m_eventList{}
    , m_worldName{}
    , m_creationTime{}
    , m_resGroupID{}
    , m_boundingRect{}
    , m_worldId{}
    , m_version{}
    , m_worldArtPieces{}
    , m_worldPopAnimRigs{}
    , m_additionalWorldResourceGroups{}
    , m_additionalWorldResourceGroupsBuilt{}
    , m_worldResourcesData{nullptr}
    {
    }
    
    // Serialized
    std::vector<MapEventItem>		m_mapPieces;			// List of map pieces that make up our map
    std::vector<MapEventItem>		m_eventList;			// List of all map events on the world map
    std::string						m_worldName;		// Name of the world map
    uint64							m_creationTime;		// File creation/Save time
    // m_resGroupID is always m_worldId -1 right now
    uint16							m_resGroupID;		// ID of Resource Group being used (resource groups defined in editor's JSON file)
    Sexy::Rect						m_boundingRect;		// Rect that holds everything in the map
    // m_worldId is always m_resGroupID +1 right now
    uint8							m_worldId;			// Unique ID for this world, used in serializaion.
    uint8							m_version;			// Version of WorldData
    
    // Not serialized
    std::vector<WorldMapAsset>		m_worldArtPieces;		// List of all world island images and animations.
    std::vector<PopAnimRig*>		m_worldPopAnimRigs;		// List of all the world popanim rigs.
    std::vector<std::string>		m_additionalWorldResourceGroups;	// Resource groups required by map event items in this world
    bool							m_additionalWorldResourceGroupsBuilt;
    WorldResourcesData*				m_worldResourcesData;	// Pointer to our resource data sheet
    
    void					DeletePopAnimRigData();
    uint16 					GetNextEventId();
    int						CountMainSpineLevels();
    
    const MapEventItem*		FindEventByEventId(int i_id) const;
    MapEventItem*			FindEventByName(const std::string& i_eventName);
    MapEventItem*			FindEventOfTypeByName(MapEventType i_eventType, const std::string& i_eventName);
    
    MapEventItem*			FindEventByDataName(const std::string& i_dataName);
    MapEventItem*			FindEventOfTypeByDataName(MapEventType i_eventType, const std::string& i_dataName);
    
    MapEventItem*			FindEvent(const std::function<bool (const MapEventItem*)>& i_acceptanceFunc);
    
    bool					ContainsEvent(const MapEventItem* i_event);
    
    SexyString				GetLocalizedWorldName() const;
};

class WorldDataManager
{
public:
    WorldDataManager();
    virtual ~WorldDataManager();
    
    // Rebuild world data from our loaded WorldMapList
    void			RebuildWorldData();
    
    /// Accessors into built world data
    ///		'Get' accessors will assert or crash on failure to find
    ///		'Find' accessors will return NULL if the find failed
    
    // Get WorldData entries
    int				GetWorldDataCount() const;
    WorldData*		GetWorldDataByIdx(int i_idx) const;
    
    WorldData*		GetWorldDataByWorldID(int i_worldID) const;
    WorldData*		GetWorldDataByWorldName(const std::string& i_worldName) const;
    WorldData*		GetWorldDataByIndexInMapList(int i_worldIndex) const;
    WorldData*		FindWorldDataByWorldID(int i_worldID) const;
    WorldData*		FindWorldDataByWorldName(const std::string& i_worldName) const;
    WorldData*		FindWorldDataByIndexInMapList(int i_worldIndex) const;
    
    WorldData*		FindWorldDataByEvent(const MapEventItem* i_event) const;
    WorldData*		FindWorldDataByLevelName(const std::string& i_levelName) const;
    
    // Get MapEventItem entries
    MapEventItem*	FindEventByName(const std::string& i_eventName) const;
    MapEventItem*	FindEventOfTypeByName(MapEventType i_eventType, const std::string& i_eventName) const;
    
    MapEventItem*	FindEventByDataName(const std::string& i_dataName) const;
    MapEventItem*	FindEventOfTypeByDataName(MapEventType i_eventType, const std::string& i_dataName) const;
    
    MapEventItem*	FindEventByLevelName(const std::string& i_levelName) const;
    MapEventItem*	FindEvent(const std::string& i_levelNameOrEventName) const;
    
    void			FindEventsUnlockedByEvent(const MapEventItem* i_event, std::vector<MapEventItem*>& o_events) const;
    
    bool			GetEventIDsByLevelName(const std::string &i_levelName, int& o_worldID, int& o_eventID) const;
    
    // This is only public because the WorldMap calls it frequently.
    // This is up to mfromwiller to refactor away, if possible.
    void			RemapWorldMapEvents();
    
    // This is WorldMapEditor only!
    void			ReplaceWorldDataByName(const std::string& i_name, WorldData* i_newWorldData);
    void			AppendNewWorldData(WorldData* i_newWorldData);
    
    // this will use worldId in config.
    bool            IsValidWorldId(int i_worldID);
    bool            IsValidWorldName(std::string i_worldName);
    std::string     GetWorldNameById(int i_worldID);
    int             GetWorldIdByName(std::string i_worldName);
    
private:
    void			clearData();
    
    // All generated, run-time world map data
    std::vector<WorldData*>		m_worldDataList;
    // List of group names for packages that this system has loaded
    std::vector<std::string>	m_loadedWorldMapPackageGroups;
};

struct AnimationDetailInfo
{
    AnimationDetailInfo()
    {
        AnimNumber = 1;
        AnimReplayDelayTimeMin = 0.0f;
        AnimReplayDelayTimeMax = 0.0f;
        UsesRasterizedImagesInAnim = false;
    }
    
    // Serialized
    int16		AnimNumber;
    float		AnimReplayDelayTimeMin;
    float		AnimReplayDelayTimeMax;
    bool		UsesRasterizedImagesInAnim;
};

struct WorldResourcesData: public Sexy::RtObject
{
    RT_CLASS_DEFINE(WorldResourcesData, Sexy::RtObject, Sexy::RtClass);
    
    WorldResourcesData()
    {
        // Defaults to tutorial artwork if not set up.
        
        // Serialized
        ID = 0;
        ImagePrefix = "IMAGE_WORLDMAP_TUTORIAL_";
        AnimationPrefix = "";
        
        // Non-serialized
        ResGroupLoaded = false;
    }
    
    // Serialized
    uint16								ID;
    std::vector<std::string>			ResGroups;
    std::string							ImagePrefix;
    std::string							AnimationPrefix;
    std::vector<AnimationDetailInfo>	AnimationDetails;
    
    // Non-serialized
    bool								ResGroupLoaded;
    
};

struct MapListNode
{
    MapListNode()
    : MapName{}
    , UnlockedFrom{}
    , EntryPoint{}
    , LastLevel{}
    , ComingSoon{false}
    , Hidden{false}
    , UniverseIconOffset{0, 0}
    , Disabled{false}
    , UseNightSpiral{false}
    , NumFilters{0}
    , ActiveFilter{0}
    , DrawWorldName{true}
    , Difficulty{1}
    , HardDifficulty{1}
    , WorldId{0}
    , IsRiftWorld{false}
    , IsPVZ1World{false}
    , IsUnchartedWorld{false}
    , IsCardGameWorld{false}
    {
    }
    
    // Serialized
    std::string					MapName;			// Name of the world file (and Universe mode PAM)
    std::string					UnlockedFrom;		// Event name that unlocks this world (typically, a stargate START)
    std::string					EntryPoint;			// Event to center on when the user enters the world. If not specified, will use the UnlockedFrom param
    std::vector<std::string>	LastLevel;			// Event that is considered the last level in the world (for end of world sequence)
    bool						ComingSoon;			// Specify if the world is coming soon (can not be seen)
    bool						DrawWorldName;		// Draw the world name string in the Universe View
    bool						Hidden;				// Specify that the world should not show up in any navigation.
    int							Difficulty;			// Draw the difficulty in the Universe View
    int							HardDifficulty;		// Draw the hard difficulty in the Universe View
    int                         WorldId;            // For Unlock By Server (iOS).
    Sexy::Point					UniverseIconOffset;	// Offset to be applied when drawing the icon for the world on the universe view screen
    bool						Disabled;			// This world has been disabled and world map events should not be loaded for it.
    bool						UseNightSpiral;		// This world uses the night time space spiral
    WorldResourcesData			WorldResources;		// World resource information for the world
    int8						NumFilters;			// Number of (mutually exclusive) filters for this world
    int8						ActiveFilter;		// Presently active filter
    bool                        IsRiftWorld;        // This world is a Rift world and will be treated differently in the UI.
    bool						IsPVZ1World;
    bool                        IsUnchartedWorld;
    bool						IsCardGameWorld;
};

class WorldMapList : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(WorldMapList, Sexy::RtObject, Sexy::RtClass);
    
    WorldMapList()
    {
        MapResourceGridWidth = 0;
        MapResourceGridHeight = 0;
        MapResourceGridOffsetX = 0;
        MapResourceGridOffsetY = 0;
    }
    
    // Serialized
    std::vector<MapListNode>			MapList;
    std::vector<std::vector<uint8> >	MapResourceGrid;
    int32								MapResourceGridWidth;
    int32								MapResourceGridHeight;
    int32								MapResourceGridOffsetX;
    int32								MapResourceGridOffsetY;
    
    // Not serialized
    Sexy::Rect							MapBoundingRect;
    
    const MapListNode*					GetMapListNodeByName(const std::string& i_name) const;
    const MapListNode*                  GetMapListNodeById(const int& i_worldId) const;
    bool								IsWorldEnabled(const std::string& i_name) const;
    bool								IsWorldComingSoon(const std::string& i_name) const;
};

//PVZ2_CHINESE_BEGIN
struct DropOutItemData
{
    std::string DropItemName;
    uint16		DropItemWeight;
    
    DropOutItemData():DropItemWeight(0)
    {
        
    }
};



struct DropOutItemGroup
{
public:
    DropOutItemGroup()
    {}
    std::string RandGetDropItem();			//get drop item from group ,rand by weight
    
    std::string 				 DropGroupId;
    std::vector<DropOutItemData> Items;
    
private:
    bool                         CheckItemCanDrop(const std::string& dropItemName);
};

class DropOutItems : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(DropOutItems, Sexy::RtObject, Sexy::RtClass);
    
    // Serialized
    std::vector<DropOutItemGroup> DropOutGroupList;
    std::string GetDropItemByGroupId(const std::string& groupId);
};

/////challege data begin
struct ChallengeItemData
{
public:
    ChallengeItemData()
    {
        DropItemName = "";
        min = 0;
        max = 0;
    }
    
    std::string DropItemName;
    int min;
    int max;
};

struct ChallengeGroupData
{
public:
    ChallengeGroupData(){}
    
    std::vector<ChallengeItemData> Items;
};

struct ChallengeDropOutItemGroup
{
public:
    ChallengeDropOutItemGroup()
    {
        DropGroupId = "";
    }
    std::string 				 DropGroupId;
    std::vector<ChallengeGroupData> Groups;
};

class ChallengeDropOutItems : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(ChallengeDropOutItems, Sexy::RtObject, Sexy::RtClass);
    
    // Serialized
    std::vector<ChallengeDropOutItemGroup> DropOutGroupList;
};
/////challege data end

struct DropGroupNode
{
    DropGroupNode()
    {
        
    }
    
    std::string WorldName;
    std::string	Difficult;//easy, normal, hard
    std::string YetiDropGroupId;
    std::string YetiDirectDropGroupId;
    std::string GargantuarDirectDropGroupId;
    std::string DevilDirectDropGroupId;
};

enum E_ActivityType
{
    E_Activity_YETI,
    //E_Activity_MINIGAME,//not use right now.
    E_Activity_YETI_DIRECT,
    E_Activity_GARGANTUAR_DIRECT,
    E_Activity_DEVIL_DIRECT,
    E_Activity_COUNT
};

class ActivityDropGroup: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(ActivityDropGroup, Sexy::RtObject, Sexy::RtClass);
    
    ActivityDropGroup();
    
    // Serialized
    int                             yetiCountPerDay;
    int                             yetiCountPerDayVersion;
    
    
    std::vector<DropGroupNode>		DropGroupList;
    std::string                     GetDropItemName(std::string worldName, E_ActivityType type, std::string difficult = "normal");
    
    std::string                     GetDropItemNameNoRand(std::string worldName, E_ActivityType type);
private:
    std::string GetYetiDropGroupId(const std::string& worldName, const std::string& difficult);
    std::string GetYetiDirectDropGroupId(const std::string& worldName, const std::string& difficult);
    std::string GetGargantuarDirectDropGroupId(const std::string& worldName, const std::string& difficult);
    std::string GetDevilDirectDropGroupId(const std::string & worldName, const std::string & difficult);
    
    std::string GetNameOfRandDropPieceSpecially(E_ActivityType eType);
    
    std::string GetNameOfDropPieceSpecially(E_ActivityType eType);
};

//PVZ2_CHINESE_END


#endif
