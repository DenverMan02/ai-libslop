//
//  DangerRoomUtils.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 4/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomUtils__
#define __PlantsVersusZombies2__DangerRoomUtils__

#include "DangerRoomInfo.h"

class MapEventItem;

struct DangerRoomHighScoreInfo
{
	std::string WorldName;
	bool IsUnlocked;
	int HighScore;
};

namespace DangerRoomUtils
{
	void				GoToDangerRoomForWorld(const std::string& i_worldName);
	MapEventItem*		FindDangerRoomForWorld(const std::string& i_worldName);
	const std::string	GetDangerRoomDataNameForWorld(const std::string& i_worldName);
	const bool			WorldHasDangerRoom(const std::string& i_worldName);
	
	bool IsMapEventDangerRoom(const MapEventItem& i_mapEvent);
	bool IsLevelNameDangerRoomLevelName(const std::string& i_levelDataName);
	
	bool ShouldShowDangerRoomIcon();
	bool IsDangerRoomUnlocked(const std::string& i_worldName);
	bool IsAnyDangerRoomUnlocked();
	
	const int								GetTotalDangerRoomHighScore();
	std::vector<DangerRoomHighScoreInfo>	GetDangerRoomHighScoreInfo();
	DangerRoomHighScoreInfo					GetDangerRoomHighScoreInfoForWorld(const std::string& i_worldName);
};

namespace Message
{
	void DangerRoomHighScoreChanged();
}

#endif /* defined(__PlantsVersusZombies2__DangerRoomUtils__) */
