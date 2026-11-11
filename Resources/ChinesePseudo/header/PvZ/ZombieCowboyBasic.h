//
//  ZombieCowboyBasic.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/13/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieCowboyBasic__
#define __PlantsVersusZombies2__ZombieCowboyBasic__

#include "ZombieBasic.h"

class ZombieCowboyBasic : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieCowboyBasic, ZombieBasic, RtClass) {}

protected:
	virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
    class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieCowboyBasic__) */
