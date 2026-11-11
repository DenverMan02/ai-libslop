//
//  PowerupPinchZombie.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 12/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PowerupPinchZombie_h
#define PlantsVersusZombies2_PowerupPinchZombie_h

#include "Effect_PopAnim.h"
#include "BasePowerup.h"

class PowerupPinchZombie : public BasePowerup
{
public:
	RT_CLASS_DEFINE(PowerupPinchZombie, BasePowerup, Sexy::RtClass) {}

	PowerupPinchZombie()
	{}

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

private:
	void handlePinch(Sexy::Point i_center, int i_distanceBetweenFingersSquared, float i_scaleDelta);
};

class Zombie;
namespace Message
{
	void ZombiePinched(Zombie* i_zombie);
}

#endif
