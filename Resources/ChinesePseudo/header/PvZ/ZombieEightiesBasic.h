//
//  ZombieEightiesBasic.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 7/9/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEightiesBasic__
#define __PlantsVersusZombies2__ZombieEightiesBasic__

#include "ZombieAnimRig_Basic.h"
#include "ZombieBasic.h"
#include "ZombieEnums.h"

STATE_ENUM_CHILD_BEGIN(ZombieEightiesBasicState, ZombieState)
ZS_LCB_Tent,
STATE_ENUM_END(ZombieEightiesBasicState)

class ZombieEightiesBasic : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieEightiesBasic, ZombieBasic, RtClass);
};

class ZombieAnimRig_EightiesBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EightiesBasic, ZombieAnimRig_Basic, RtClass);
	
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

#endif /* defined(__PlantsVersusZombies2__ZombieEightiesBasic__) */
