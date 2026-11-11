//
//  SpawnPumpkinScarecrowWaveAction.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 8/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __SPAWN_PUMPKINSCARECROW_WAVE_ACTION__
#define __SPAWN_PUMPKINSCARECROW_WAVE_ACTION__

#include "SpawnGravestonesWaveAction.h"

class SpawnPumpkinScarecrowWaveAction : public SpawnGridItemsWaveAction
{
public:
	RT_CLASS_DEFINE(SpawnPumpkinScarecrowWaveAction, SpawnGridItemsWaveAction, RtClass);

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:
	void onGridItemSpawn(GridItem* i_gridItem) override;
	std::vector<GridItemTypePtr> generateSpawnPool() override;
};

class SpawnPumpkinScarecrowWaveActionProps : public SpawnGridItemsWaveActionProps
{
public:
	RT_CLASS_DEFINE(SpawnPumpkinScarecrowWaveActionProps, SpawnGridItemsWaveActionProps, RtClass);

	RtClass* GetActionClass() const override
	{
		return SpawnPumpkinScarecrowWaveAction::StaticGetClass();
	}

	std::vector<GridItemPoolEntry>		GetGridItemPool() const override { return PumpkinScarecrowPool; }
	std::vector<Point>					GetSpawnPositionsPool() const override;
	
	std::vector<GridItemPoolEntry>		PumpkinScarecrowPool;
	std::vector<Point>					SpawnPositionsPool;
	Rect                                SpawnPositionsRect;
	float 								Hitpoints = 0.f;
	int 								Level = 1;
};

#endif /* __SPAWN_PUMPKINSCARECROW_WAVE_ACTION__ */
