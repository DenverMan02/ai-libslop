//
//  DangerRoomEightiesDesigners.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomEightiesDesigners__
#define __PlantsVersusZombies2__DangerRoomEightiesDesigners__

#include "DangerRoomLevelDesigner.h"
#include "InitialGridItemPlacer.h"
#include "Utils.h"

class DangerRoomJamDesigner : public DangerRoomLevelDesigner
{
public:
	RT_CLASS_DEFINE(DangerRoomJamDesigner, DangerRoomLevelDesigner, RtClass);
	DangerRoomJamDesigner()
	{
		LevelRange = ValueRange(1, 100);
	}
	virtual ~DangerRoomJamDesigner() {}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void GenerateEvents(const int i_level, Sexy::MTRand& io_rand, WaveManagerProperties* io_props) const override;

	ValueRange LevelRange;
	ValueRange FirstJamWavesMin;
	ValueRange FirstJamWavesMax;
	ValueRange NextJamWavesMin;
	ValueRange NextJamWavesMax;
	ValueRange JamTypesMin;
	ValueRange JamTypesMax;
	
	ValueRange ZombieAddLevelRange;
	ValueRange JamZombiesToReplaceMin;
	ValueRange JamZombiesToReplaceMax;
	
	int	LevelToIntroduceMetalJam;
};

#endif /* defined(__PlantsVersusZombies2__DangerRoomEightiesDesigners__) */
