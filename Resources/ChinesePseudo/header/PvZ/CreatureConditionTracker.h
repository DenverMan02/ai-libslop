//
//  CreatureConditionTracker.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/17/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __CREATURE_CONDITION_TRACKER_H__
#define __CREATURE_CONDITION_TRACKER_H__

#include <vector>

#include "EntityConditionTracker.h"
#include "TimeMgr.h"
#include "dtypes.h"

class Creature;

enum CreatureConditions
{
	PVZ_BEGIN_ENUM(CCONDITION_),
	CCONDITION_RushOnscreen,
	CCONDITION_Charmed,
	CCONDITION_Unsuspendable,
	CCONDITION_ExitScreen,
	PVZ_END_ENUM(CCONDITION_)
};

class CreatureConditionTracker : public EntityConditionTracker < Creature, CreatureConditions >
{
public:
	CreatureConditionTracker()
	: EntityConditionTracker(getConditionMaxCount())
	{
	}
	
	float GetDrawScale();
	void SetAdditionalValue(CreatureConditions i_condition, float i_value);
	
protected:
	virtual int getConditionMaxCount() const { return CCONDITION_End; }
	virtual void recomputeModifierValues();

private:
	void recomputeSpeed(bool i_isSuspended);
	void recomputeScaleAndColor();

	float m_cachedDrawScale;
};

#endif
