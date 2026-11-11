//
//  BoardEntityPusher.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/11/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BoardEntityPusher__
#define __PlantsVersusZombies2__BoardEntityPusher__

#include "Core.h"
#include "PlantEnums.h"
#include "PVZTypes.h"

class BoardEntity;
class GridItem;
class Plant;

struct PushPlantGroupProps
{
    PushPlantGroupProps(PlantGroupPtr i_plantGroup, const int i_direction, const int i_desiredDistance)
    {
        plantGroup = i_plantGroup;
        direction = i_direction;
        desiredDistance = i_desiredDistance;
    }
    
    PlantGroupPtr plantGroup;
    int direction;
    int desiredDistance;
    bool forcePlantOffBoard = false;
    bool forceJump = false;
};

class BoardEntityPusher
{
public:
	BoardEntityPusher(BoardEntity* i_instigator, const std::string& i_flingAudioEventName = "Play_Zomb_Future_Football_Mvmt_Fling");
	
	static int PUSH_DIRECTION_LEFT;
	static int PUSH_DIRECTION_RIGHT;
	static int PUSH_DISTANCE_DEFAULT;
	
	static float PUSH_DEFAULT_DURATION;
	static float PUSH_DEFAULT_APEX_HEIGHT;
	static float PUSH_BIGMOVE_APEX_HEIGHT;
	static float PUSH_OFFSCREEN_DURATION;
	static float PUSH_OFFSCREEN_APEX_HEIGHT;
	
	static bool CanPushPlant(Plant* i_plant);
	static int GetOffBoardGridLocation(const int i_direction, Plant* i_plant);
	
	void BlacklistBoardLocation(const int i_gridX, const int i_gridY);
	void PushRowLeft(int i_gridX, int i_gridY) const;
	void PullRowRight(int i_gridX, int i_gridY) const;
	// void PushPlant(Plant* i_plant, const int i_direction, const int i_desiredDistance, bool i_forcePlantOffBoard = false) const;
	
	// plant group function
	void PushPlantGroup(PushPlantGroupProps& i_pushProps) const;

private:
	void moveRowFromGridLocInDirection(int i_gridX, int i_gridY, const int i_direction) const;
	void pushGridItem(GridItem* i_gridItem, const int i_direction) const;
	
	bool	isLocationBlacklisted(const int i_gridX, const int i_gridY) const;
	// int		getNextValidColumnInDirection(const int i_startColumn, const int i_startRow, const int i_direction, const int i_desiredDistance) const;
	// bool	plantIsBeingPushedOffBoard(const Plant* i_plant, const int i_direction, const int i_desiredDistance) const;
	bool	plantWillBeDrowned(Plant* i_plant, const int i_direction) const;

	// plant group function
	int     getNextValidColumnInDirection(PlantGroupPtr i_plantGroup, const int i_direction, const int i_desiredDistance) const;
    bool    plantGroupIsBeingPushedOffBoard(const PlantGroupPtr i_plant, const int i_direction, const int i_desiredDistance) const;
	void pushPlantGroup(PushPlantGroupProps& i_pushProps) const;
	
	BoardEntity* m_instigator;
	std::vector<Sexy::Point> m_blacklistedLocations;
	const std::string m_flingAudioEventName;
};

#endif /* defined(__PlantsVersusZombies2__BoardEntityPusher__) */
