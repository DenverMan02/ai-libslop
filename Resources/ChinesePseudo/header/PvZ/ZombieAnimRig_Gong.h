//
//  ZombieAnimRig_Gong.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-20.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_Gong__
#define __PlantsVersusZombies2__ZombieAnimRig_Gong__

#include "Precompile.h"
#include "ZombieAnimRig.h"

enum ZombieAnimRigState_Gong
{
	ZOMBIEANIM_GONG_POWERON = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_GONG_POWER,
	ZOMBIEANIM_GONG_POWEROFF,
};

class ZombieAnimRig_Gong : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Gong, ZombieAnimRig, RtClass) {}
    
    bool StartGongging();
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_Gong__) */
