//
//  ZombieAnimRig_ZombossQigong.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 1-26-14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_ZombossQigong__
#define __PlantsVersusZombies2__ZombieAnimRig_ZombossQigong__

#include "Precompile.h"
#include "ZombieAnimRig_Zomboss.h"

class ZombieAnimRig_ZombossQigong : public ZombieAnimRig_Zomboss
{
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossQigong, ZombieAnimRig_Zomboss, RtClass);
    
    void PlayFly(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayFall(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayFlyIdle();
    void PlaySummon(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayFlick(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayJumpUp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayJumpMid(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayJumpDown(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayCureStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayCureIdle();
    void PlayPK(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    const char* getFlyAnimName() const;
    const char* getFallAnimName() const;
    const char* getFlyIdleAnimName() const;
    const char* getSummonAnimName() const;
    const char* getFlickAnimName() const;
    const char* getJumpUpAnimName() const;
    const char* getJumpMidAnimName() const;
    const char* getJumpDownAnimName() const;
    const char* getCureStartAnimName() const;
    const char* getCureIdleAnimName() const;
    const char* getPKAnimName() const;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_ZombossQigong__) */
