//
//  ZombieAnimRig_ZombossExplosive.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-2-13.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_ZombossExplosive__
#define __PlantsVersusZombies2__ZombieAnimRig_ZombossExplosive__

#include "Precompile.h"
#include "ZombieAnimRig_Zomboss.h"

class ZombieAnimRig_ZombossExplosive : public ZombieAnimRig_Zomboss
{
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossExplosive, ZombieAnimRig_Zomboss, RtClass);
    
public:
	bool PlaySummon(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlaySummonRocket(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
    bool PlayLaunchImp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayDropBombs(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayJumpStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayJumpLand(PopAnimRig::AnimStoppedReflectionDelegate  i_onAnimStopped);
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_ZombossExplosive__) */
