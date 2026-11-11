//
//  ZombieAnimRig_DarkWizard.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 10/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_DARKWIZARD_H__
#define __ZOMBIEANIMRIG_DARKWIZARD_H__

#include <string>
#include <vector>

#include "PopAnimRig.h"
#include "RtObject.h"
#include "ZombieAnimRig.h"

enum ZombieAnimRigState_DarkWizard
{
	ZOMBIEANIM_DARKWIZARD_CASTING = ZOMBIEANIM_USERDEFINED,
    ZOMBIEANIM_DARKWIZARD_BIGCASTING,
};

class ZombieAnimRig_DarkWizard : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_DarkWizard, ZombieAnimRig, RtClass) {}
    
	// DarkWizard specific functionality
	bool StartCasting(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool StartBigCasting(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif // __ZOMBIEANIMRIG_DARKWIZARD_H__
