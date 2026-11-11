//
//  ZombieAnimRig_Rocket.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-22.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_Rocket__
#define __PlantsVersusZombies2__ZombieAnimRig_Rocket__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Rocket : public ZombieAnimRig
{
	RT_CLASS_DEFINE(ZombieAnimRig_Rocket, ZombieAnimRig, RtClass);
	
public:
	bool PlayDropIn(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlayFlyDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlayFlying();
	
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_Rocket__) */
