//
//  PlantAnimRig_Ents.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_ENTS_H__
#define __PLANTANIMRIG_ENTS_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Ents : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Ents, PlantAnimRig, RtClass);
	typedef PopAnimRig::AnimStoppedReflectionDelegate EmergeAnimDone;
	
	enum AttackType
	{
		ATTACK_PUNCH_LEFT,
		ATTACK_PUNCH_RIGHT,
		ATTACK_UPPERCUT_LEFT,
		ATTACK_UPPERCUT_RIGHT,
		ATTACK_SUPERCUT_LEFT,
		ATTACK_SUPERCUT_RIGHT,
	};

	int m_amulet = 2;
	bool IsBreak = false;
	virtual bool PlayIdleLooped() override;
	virtual bool PlayPunchAttack(PlantAnimRig_Ents::AttackType i_attackType, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	virtual bool PlayFall(int i_type, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
//    virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
//
//    virtual bool playPlantFoodOn() override;
//	virtual bool playPlantFoodMain() override;
//	virtual bool playPlantFoodOff() override;

private:
//	std::string m_lastUsedIdleAnim;
    std::string getIdleAnimationName() override;
    virtual std::string getPlantFoodMainAnimName() override;
    virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
};

#endif // __PLANTANIMRIG_ENTS_H__
