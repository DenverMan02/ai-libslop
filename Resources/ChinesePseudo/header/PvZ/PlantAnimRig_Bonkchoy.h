//
//  PlantAnimRig_Bonkchoy.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_BONKCHOY_H__
#define __PLANTANIMRIG_BONKCHOY_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Bonkchoy : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Bonkchoy, PlantAnimRig, RtClass);
	
	enum AttackType
	{
		ATTACK_PUNCH_LEFT,
		ATTACK_PUNCH_RIGHT,
		ATTACK_UPPERCUT_LEFT,
		ATTACK_UPPERCUT_RIGHT,
		ATTACK_SUPERCUT_LEFT,
		ATTACK_SUPERCUT_RIGHT,
	};
	virtual bool PlayIdleLooped() override;
	virtual bool PlayPunchAttack(PlantAnimRig_Bonkchoy::AttackType i_attackType, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
    virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
    
    virtual bool playPlantFoodOn() override;
	virtual bool playPlantFoodMain() override;
	virtual bool playPlantFoodOff() override;

private:
	std::string m_lastUsedIdleAnim;
};

#endif // __PLANTANIMRIG_BONKCHOY_H__
