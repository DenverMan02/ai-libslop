//
//  ZombieSwashbuckler.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 5/18/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_LOSTCITY_RELICHUNTER_H__
#define __ZOMBIE_LOSTCITY_RELICHUNTER_H__

#include <string>

#include "DamageInfo.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "ZombieEnums.h"
#include "ZombieSwashbuckler.h"

class ZombieLostCityRelicHunterProps : public ZombieSwashbucklerProps
{
public:
	RT_CLASS_DEFINE(ZombieLostCityRelicHunterProps, ZombieSwashbucklerProps, RtClass);
};

class ZombieLostCityRelicHunter : public ZombieSwashbuckler
{
public:
	RT_CLASS_DEFINE(ZombieLostCityRelicHunter, ZombieSwashbuckler, RtClass);

protected:

private:

};

class ZombieAnimRig_RelicHunter : public ZombieAnimRig_Swashbuckler
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_RelicHunter, ZombieAnimRig_Swashbuckler, RtClass);
	
	SexyVector2 GetLocationOffset() override;
	SexyVector2 GetSwingFootOffset() override;
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif
