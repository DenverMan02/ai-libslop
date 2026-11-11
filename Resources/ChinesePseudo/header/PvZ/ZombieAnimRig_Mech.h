//
//  ZombieAnimRig_Mech.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Mech_h
#define PlantsVersusZombies2_ZombieAnimRig_Mech_h

#include "ZombieAnimRig_Gargantuar.h"

class ZombieAnimRig_Mech : public ZombieAnimRig_Gargantuar
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Mech, ZombieAnimRig_Gargantuar, RtClass);
	
	void PlayEMPeachStunStart();
	void PlayEMPeachStunIdle();
	void PlayEMPeachStunEnd();
	
	void PlayLaserStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayLaserIdle();
	void PlayLaserEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	virtual void SetDamageState(int i_damageState);
	
protected:
	void onPopAnimInitialized() override;
	void onStunStartEnd(const std::string& i_animLabelName);
};

class ZombieAnimRig_ConeMech : public ZombieAnimRig_Mech
{
public:	
	RT_CLASS_DEFINE(ZombieAnimRig_ConeMech, ZombieAnimRig_Mech, RtClass);
	
	void SetDamageState(int i_damageState) override;
};

class ZombieAnimRig_FootballMech : public ZombieAnimRig_Mech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_FootballMech, ZombieAnimRig_Mech, RtClass);
	
	void SetDamageState(int i_damageState) override;
};


#endif
