//
//  ZombieAnimRig_Parrot.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 8/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_PARROT_H__
#define __ZOMBIEANIMRIG_PARROT_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Parrot : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Parrot, ZombieAnimRig, RtClass);

	bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;

	virtual bool PlayFly();
    virtual bool PlayFlyBack();
    virtual bool PlayCarry();
protected:
	void onNeedsToDie() override;
};

#endif
