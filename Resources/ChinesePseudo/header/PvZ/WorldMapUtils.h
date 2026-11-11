//
//  WorldMapUtils.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 2/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MapHelper__
#define __PlantsVersusZombies2__MapHelper__

#include <string>
#include <utility>
#include <vector>

#include "MagentoService.h"
#include "MapEventItem.h"
#include "PlatformAutodetect.h"
#include "SexyString.h"
#include "dtypes.h"

class WorldData;
class WorldDataManager;
class WorldMapList;

namespace WorldMapUtils
{
	enum NextWorldEventSearchFlags
	{
		NEXTEVENT_SEARCH_OFF_MAIN_SPINE             = 0x01,     // Allow searching off the main spine

		NEXTEVENT_SEARCH_SKIP_UNREADY               = 0x02,     // Skip if level locked or not yet discovered
		NEXTEVENT_SEARCH_SKIP_COMPLETED				= 0x04,     // Skip if level has been completed once

		// Helpers
		NEXTEVENT_SEARCH_READY_FOR_FIRST_PLAY       = NEXTEVENT_SEARCH_SKIP_UNREADY | NEXTEVENT_SEARCH_SKIP_COMPLETED,

		// All skip flags (used for optimization)
		NEXTEVENT_SEARCH_SKIP_ALL_FLAGS             = (NEXTEVENT_SEARCH_SKIP_UNREADY | NEXTEVENT_SEARCH_SKIP_COMPLETED),
	};

	// This must be called before we do anything
	void						LoadWorldMapData();

	// Returns a const version of the WorldMapList
	// This list contains every defined world, including those that are hidden or otherwise disabled
	// If you want a list of worlds currently available in the game, use GetWorldData instead!
	const WorldMapList*			GetWorldMapList();

	// TODO -- Wrap this behind a define, it SHOULD only be necessary for level editor builds
	WorldMapList*				GetWorldMapListForEdit();

	// Returns a const version of the generated WorldData
	// This list contains only those worlds that are enabled for the current build of the game
	const WorldDataManager*		GetWorldData();
	void DestroyWorldData();

	// TODO -- Wrap this behind a define, it SHOULD only be necessary for level editor builds
	WorldDataManager*			GetWorldDataForEdit();

	// Loads the given map name into a table, returns the bare pointer to the data, and
	// clears the table.
	// ** You are responsible for deleting the WorldData* when done! **
	enum FilterSelection
	{
		FILTER_Active,
		FILTER_All
	};
	WorldData*					LoadSerializedMapData(const std::string& i_mapName, FilterSelection i_filterSelection);

	MagentoProductPropsPtr		FindGateMagentoInformation(const MapEventItem* i_gateEvent);
	const MapEventItem*			GetExitStargateLinkedToStartStargate(const MapEventItem* i_eventItem);
	bool						WorldIsPurchasable(const std::string& i_worldName);
	void						UnlockStargateForWorld(const std::string& i_worldName, const bool i_wasBypassed);
	void						UnlockStargate(const MapEventItem* i_startStargate, const bool i_wasBypassed);

	const MapEventItem*			GetNextWorldEventOfType(const std::string &i_startingEventName, MapEventType i_eventType, uint i_nextWorldEventSearchFlags = 0);
	const MapEventItem*			GetNextWorldEventOfType(const std::string &i_startingEventName, const std::vector<MapEventType> &i_eventTypes, uint i_nextWorldEventSearchFlags = 0);

	std::string					GetNextLevelOnPath(const std::string& i_eventName);
	const MapEventItem*			GetLevelToCenterOnInWorld(const std::string& i_worldName);
	const MapEventItem*			GetDangerRoomUnlockedFromLevelOrEventName(const std::string& i_levelName);

	const std::string           GetFirstLevelInWorld(const std::string& i_worldName);

	void						GetAllEventsOfType(MapEventType i_eventType, std::vector<const MapEventItem*> &o_events);

	const SexyString			TranslateWorldKeyToName(const std::string& i_worldName);
	const WorldData*			GetWorldDataById(uint8 i_worldId);
	const MapEventItem*			GetWorldMapEventByIds(uint8 i_worldId, uint16 i_eventId);
	uint8						GetNextWorldId();
	uint8						GetNextWorldResourceDataId();

	bool						LevelIsOnSpine(const std::string &i_levelName);

	bool						GetOrderedMainSpinePath(const std::string& i_worldName, std::vector<const MapEventItem*>& o_events);
	bool						GetOrderedPathToEvent(const MapEventItem* i_endEvent, std::vector<const MapEventItem*>& o_events);
	const MapEventItem*			GetLastCompletedLevelNodeOnPath(const std::vector<const MapEventItem*>& i_events, PlayerInfo* i_playerInfo);
	const MapEventItem*			GetLastUnlockedNodeOnPath(const std::vector<const MapEventItem*>& i_events, PlayerInfo* i_playerInfo);
	const MapEventItem*			FindLastPlayableEventInWorld(const std::string& i_worldName);
	const MapEventItem*			FindZombossNodeInWorld(const std::string& i_worldName);
	int							GetIndexOfEventOnPath(const MapEventItem* i_event, const std::vector<const MapEventItem*>& i_events);

	WorldMapEventStatus			GetVisualMapEventStatus(const MapEventItem* i_mapEvent, PlayerInfo* i_info);

	bool						IsMapEventToggledOff(const MapEventItem* i_mapEvent);

	std::string					DetermineNextLevelToPlay();

	int							CalculateProgressAlongSpine(std::string& i_worldName);
	int							CalculatePositionAlongSpine(MapEventItem* i_mapEvent);
	int							CalculateLevelCountUntilPositionAlongSpine(MapEventItem* i_mapEvent);
	
	int							CalculateBossNodeCompletionIndex(const MapEventItem* i_mapEvent, int i_currentIndex = -1);
	int							CalculateBossNodeUnlockIndex(const MapEventItem* i_mapEvent, int i_currentIndex = -1);

	SexyString					GetLocalizedWorldName(const std::string& i_worldName);
    
    bool                        WorldHasHardModule(uint8 i_worldId);
    bool                        WorldHasHardModule(const std::string& i_worldName);
    bool                        GachaIsOpen();
    bool                        UniverseIsOpen();

    bool                        IsRiftWorld(const std::string& i_worldName);
    bool                        IsPVZ1World(const std::string& i_worldName);
	bool                        IsUnchartedWorld(const std::string& i_worldName);
	bool						IsCardGameWorld(const std::string& i_worldName);
}

#endif /* defined(__PlantsVersusZombies2__MapHelper__) */
