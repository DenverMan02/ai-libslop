//
//  ZombieAnimRig_Ra.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_RA_H__
#define __ZOMBIEANIMRIG_RA_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

enum ZombieAnimRigState_Ra
{
	ZOMBIEANIM_RA_POWERON = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_RA_POWER,
	ZOMBIEANIM_RA_POWEROFF,
};

class ZombieAnimRig_Ra : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Ra, ZombieAnimRig, RtClass) {}
    
	// Ra specific functionality
	virtual bool StartPowerSuck();
	virtual bool StopPowerSuck(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	virtual SexyVector2 GetHeadOffset() override;
	
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	virtual void onAnimStopped() override;
};

#endif // __ZOMBIEANIMRIG_H__
