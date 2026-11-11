//
//  GridItemConditionTracker.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/26/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __GRIDITEM_CONDITION_TRACKER_H__
#define __GRIDITEM_CONDITION_TRACKER_H__

#include <vector>

#include "EntityConditionTracker.h"
#include "dtypes.h"

enum GridItemConditions
{
	PVZ_BEGIN_ENUM(GCONDITION_),
	GCONDITION_DamageFlash,
	GCONDITION_HealFlash,
	GCONDITION_Haunted,
	GCONDITION_BloomingHeartDebuff,
	GCONDITION_Chilled,
	GCONDITION_Frozen,
	GCONDITION_Water,
	PVZ_END_ENUM(GCONDITION_)
};

class GridItemConditionTracker : public EntityConditionTracker<class GridItem, GridItemConditions>
{
public:
	GridItemConditionTracker()
	: EntityConditionTracker(getConditionMaxCount())
	{

	}

	void SetAdditionalValue(GridItemConditions i_condition, float i_value);

protected:
	virtual int getConditionMaxCount() const { return GCONDITION_End; }
	virtual void recomputeModifierValues();
	void recomputeDrawValues();

};

#endif
