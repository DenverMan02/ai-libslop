//
//  ZombieAnimRig_ZombossMech_Pirate.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Pirate__
#define __PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Pirate__

#include "ZombieAnimRig_ZombossMech.h"

class ZombieAnimRig_ZombossMech_Pirate : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Pirate, ZombieAnimRig_ZombossMech, RtClass);
	
	void PlayRocketLaunchLoop();
	void PlayRocketLaunchFire(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
	
	virtual const char* getRocketLaunchAnimName() const override;
	virtual const char* getRocketLaunchLoopAnimName() const;
	virtual const char* getRocketLaunchFireName() const;
};

	
#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Pirate__) */
