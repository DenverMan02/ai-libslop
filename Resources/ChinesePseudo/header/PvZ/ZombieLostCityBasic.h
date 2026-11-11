//
//  ZombieLostCityBasic.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 5/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLostCityBasic__
#define __PlantsVersusZombies2__ZombieLostCityBasic__

#include "ZombieAnimRig_Basic.h"
#include "ZombieBasic.h"
#include "ZombieEnums.h"

STATE_ENUM_CHILD_BEGIN(ZombieLostCityBasicState, ZombieState)
ZS_LCB_Tent,
STATE_ENUM_END(ZombieLostCityBasicState)

class ZombieLostCityBasic : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieLostCityBasic, ZombieBasic, RtClass);
	void PlayTentAnimation();
	
protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, LcbTent);
	
	void onTentPlayed();
};

class ZombieAnimRig_LostCityBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_LostCityBasic, ZombieAnimRig_Basic, RtClass);
	
	void PlayTentAnimation(AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getFlagHandLayerNames() override;
	const std::vector<std::string>& getNoFlagHandLayerNames() override;
	const std::vector<std::string>& getConeLayerNames() override;
	const std::vector<std::string>& getBucketLayerNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieLostCityBasic__) */
