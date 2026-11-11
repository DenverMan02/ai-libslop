//
//  ZombieAnimRig_ZombossMech_Cowboy.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Cowboy__
#define __PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Cowboy__

#include "ZombieAnimRig_ZombossMech.h"

class ZombieAnimRig_ZombossMech_Cowboy : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Cowboy, ZombieAnimRig_ZombossMech, RtClass);

	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Cowboy__) */
