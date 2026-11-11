//
//  GridItemProjectileTrap.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/19/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemProjectileTrap__
#define __PlantsVersusZombies2__GridItemProjectileTrap__

#include <stdio.h>

#include "Core.h"
#include "GridItemTriggerTile.h"
#include "Projectile.h"

enum GridItemProjectileTrapPositioningFlags
{
	PVZ_BEGIN_FLAG_ENUM(PROJECTILETRAPPOSITION_),
	PVZ_FLAG(PROJECTILETRAPPOSITION_LOCKX),
	PVZ_FLAG(PROJECTILETRAPPOSITION_LOCKY),
	PVZ_END_FLAG_ENUM(PROJECTILETRAPPOSITION_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(GridItemProjectileTrapPositioningFlags);

class GridItemProjectileTrapProps : public GridItemTriggerTileProps
{
public:
	RT_CLASS_DEFINE(GridItemProjectileTrapProps, GridItemTriggerTileProps, RtClass);
	
	GridItemProjectileTrapProps()
	: JSONPositioningFlags { PROJECTILETRAPPOSITION_Everything }
	{}
	
	std::vector<GridItemProjectileTrapPositioningFlags> JSONPositioningFlags;
	ProjectilePropertySheetPtr	ProjectileTypeToSpawn;
	std::string					TileBaseAnimation;
	SexyVector3					ProjectileFireOriginOffset;
};

class GridItemProjectileTrap : public GridItemTriggerTile
{
public:
	RT_CLASS_DEFINE(GridItemProjectileTrap, GridItemTriggerTile, RtClass);
    
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	void handleTargetCollisions(const std::vector<BoardEntity*>& i_entities) override;
	
private:
	GridItemProjectileTrapPositioningFlags getPositioningFlags() const;
	
	int32_t m_currentState = 1;
};

#endif /* defined(__PlantsVersusZombies2__GridItemTrapTile__) */
