//
//  GridItemWhackPuddle.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 11/19/14
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemWhackPuddle__
#define __PlantsVersusZombies2__GridItemWhackPuddle__

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

class GridItemWhackPuddle : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemWhackPuddle, GridItemAnimation, RtClass);

	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	
protected:
	
	void onEntitySpawned(BoardEntity* i_entity);
	
	bool IsAbleToSpawn();

	void onGridItemInitialize() override;
	void onTakeDamage(const DamageInfo& i_damage) override;
	
	void registerForEvents() override;
};

#endif
