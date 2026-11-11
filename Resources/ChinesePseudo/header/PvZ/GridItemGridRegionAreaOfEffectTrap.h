//
//  GridItemGridRegionAreaOfEffectTrap.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemGridRegionAreaOfEffectTrap__
#define __PlantsVersusZombies2__GridItemGridRegionAreaOfEffectTrap__

#include "Core.h"
#include "EffectObject.h"
#include "GridItemTriggerTile.h"

class GridItemGridRegionAreaOfEffectTrapProps : public GridItemTriggerTileProps
{
public:
	RT_CLASS_DEFINE(GridItemGridRegionAreaOfEffectTrapProps, GridItemTriggerTileProps, RtClass);
	
	GridItemGridRegionAreaOfEffectTrapProps()
	{
		ColumnRadius = 1;
		RowRadius = 1;
		TimeBetweenDamageEffectSpawnsInSeconds = 0.0f;
	}
	
	std::string					EffectObjectName;
	std::string					TileBaseAnimation;
	
	int							ColumnRadius;
	int							RowRadius;
	pvztime_t					TimeBetweenDamageEffectSpawnsInSeconds;
};

class GridItemGridRegionAreaOfEffectTrap : public GridItemTriggerTile
{
public:
	RT_CLASS_DEFINE(GridItemGridRegionAreaOfEffectTrap, GridItemTriggerTile, RtClass);
	
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
	bool CanTriggerTile() override;
	
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	void handleTargetCollisions(const std::vector<BoardEntity*>& i_entities) override;
	
private:
	int getLargestGridDistanceFromOurPosition(const Sexy::Point& i_point) const;
	void spawnDamageEffectAtGridLocation(const Sexy::Point& i_point) const;
	
	pvztime_t					m_nextSpawnTime = PVZ_EOT();
	
	int32_t						m_currentState = 0;
	std::vector<Sexy::Point>	m_gridLocationsLeftToSpawn;
};

#endif /* defined(__PlantsVersusZombies2__GridItemGridRegionAreaOfEffectTrap__) */
