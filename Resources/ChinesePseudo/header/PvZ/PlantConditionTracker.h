//
//  PlantConditionTracker.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_CONDITION_TRACKER_H__
#define __PLANT_CONDITION_TRACKER_H__

#include <vector>

#include "EntityConditionTracker.h"
#include "PlantEnums.h"
#include "dtypes.h"

class Plant;

class PlantConditionTracker : public EntityConditionTracker < Plant, PlantConditions >
{
public:
	PlantConditionTracker()
	: EntityConditionTracker(getConditionMaxCount())
	{
		
	}

	void SetAdditionalValue(PlantConditions i_condition, float i_value);

protected:
	virtual int getConditionMaxCount() const { return PCONDITION_End; }
	virtual void recomputeModifierValues();
	void recomputeDrawValues();
	
};

#endif
