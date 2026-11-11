//
//  ZombieAnimRig_MonkImp.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 14-1-2.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_MonkImp__
#define __PlantsVersusZombies2__ZombieAnimRig_MonkImp__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_MonkImp : public ZombieAnimRig
{
	RT_CLASS_DEFINE(ZombieAnimRig_MonkImp, ZombieAnimRig, RtClass);

public:
	bool PlayPreparing(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayJumping(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayFlying();
	bool PlayLanding(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayFalling(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayFlyingDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);


protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_MonkImp__) */
