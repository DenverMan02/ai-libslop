//
//  ZombieConditionTracker.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_CONDITION_TRACKER_H__
#define __ZOMBIE_CONDITION_TRACKER_H__

#include <vector>

#include "EntityConditionTracker.h"
#include "TimeMgr.h"
#include "ZombieEnums.h"
#include "dtypes.h"
#include "EliminateItem.h"

class Zombie;

class ZombieConditionTracker : public EntityConditionTracker < Zombie, ZombieConditions >
{
public:
    ZombieConditionTracker();
	float GetDrawScale();
	void SetAdditionalValue(ZombieConditions i_condition, float i_value);
	void SetExtraAdditionalValue(ZombieConditions i_condition, float i_value);
	void SetExtraAdditionalValue2(ZombieConditions i_condition, float i_value);
    void SetEliminateColor(EEliminateType i_color);
    
protected:
	virtual int getConditionMaxCount() const { return ZCONDITION_End; }
	virtual void recomputeModifierValues();

private:
	void recomputeSpeedAndDps(bool i_isSuspended);
	void recomputeDot();
	void recomputeDamageScale(bool i_isSuspended);
	void recomputeScaleAndColor();
	void computePotionScaleAndColor(float& o_scale, Color& o_color, bool& o_hasDrawOverlayColor) const;

	void continueWarpingZombieIn();
	void continueWarpingZombieOut();
	void continueShrinkingZombie();
	void continueHocusCrocusShrinkingZombie();
	void continueHocusCrocusShrinkRecoveringZombie();
	
	void blinkWarpingZombie();
	void scaleZombie(float startTime, float endTime, float timeInWarp, float start, float end, bool wantsBounce);
    float GetRageSpeed();
    float GetRageDamage();
    void CalcRageScale();
	float m_cachedDrawScale;
    float m_rageSpeedScale;
    float m_rageDamageScale;
    EEliminateType m_eliminateColor = EEliminateType_None;
};

#endif
