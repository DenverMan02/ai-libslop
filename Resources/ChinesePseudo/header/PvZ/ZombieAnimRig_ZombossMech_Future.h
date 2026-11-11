//
//  ZombieAnimRig_ZombossMech_Future.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/20/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Future__
#define __PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Future__

#include "ZombieAnimRig_ZombossMech.h"
#include "PowerTileSubsystem.h"

class ZombieAnimRig_ZombossMech_Future : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Future, ZombieAnimRig_ZombossMech, RtClass);
	
	ZombieAnimRig_ZombossMech_Future();
	
	void SetRocketStartAnimFromTileType(PowerTileClass i_class);

	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
	virtual const char* getRocketStartAnimName() const override;

private:
	PowerTileClass m_queuedTileClass;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_ZombossMech_Future__) */
