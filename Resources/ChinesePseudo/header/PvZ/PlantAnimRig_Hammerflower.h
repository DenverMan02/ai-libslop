//
//  PlantAnimRig_Hammerflower.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_HAMMERFLOWER_H__
#define __PLANTANIMRIG_HAMMERFLOWER_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Hammerflower : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Hammerflower, PlantAnimRig, RtClass);
	
	enum AttackType
	{
		ATTACK_PUNCH_LEFT,
		ATTACK_PUNCH_RIGHT,
		ATTACK_UPPERCUT_LEFT,
		ATTACK_UPPERCUT_RIGHT,
		ATTACK_SUPERCUT_LEFT,
		ATTACK_SUPERCUT_RIGHT,
	};
//	virtual bool PlayIdleLooped() override;
	virtual bool PlayPunchAttack(PlantAnimRig_Hammerflower::AttackType i_attackType, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
//    virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
//
//    virtual bool playPlantFoodOn() override;
//	virtual bool playPlantFoodMain() override;
//	virtual bool playPlantFoodOff() override;

private:
	std::string m_lastUsedIdleAnim;
    std::string getIdleAnimationName() override;
    virtual std::string getPlantFoodMainAnimName() override;
    virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
};

#endif // __PLANTANIMRIG_HAMMERFLOWER_H__
