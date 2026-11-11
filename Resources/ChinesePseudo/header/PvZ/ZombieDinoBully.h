//
//  ZombieDinoBully.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 11/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieDinoBully__
#define __PlantsVersusZombies2__ZombieDinoBully__

#include <stdio.h>

#include "ZombieAnimRig_Basic.h"
#include "ZombieBasic.h"
#include "ZombieEnums.h"
#include "ZombieDinoBasic.h"

#pragma mark - ZombieAnimRig_DinoBully

class ZombieDinoBully : public ZombieDinoBasic
{
public:
	RT_CLASS_DEFINE(ZombieDinoBully, ZombieDinoBasic, RtClass);
	
protected:
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }
};

class ZombieAnimRig_DinoBully : public ZombieAnimRig_DinoBasic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DinoBully, ZombieAnimRig_DinoBasic, RtClass);
	
private:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif