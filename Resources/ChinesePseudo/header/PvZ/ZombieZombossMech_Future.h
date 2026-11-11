//
//  ZombieZombossMech_Future.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/20/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_Future__
#define __PlantsVersusZombies2__ZombieZombossMech_Future__

#include "ZombieZombossMech.h"

class ZombossRocket;

class ZombieZombossMechFutureProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechFutureProps, ZombieZombossMechProps, RtClass);
	
	ZombieZombossMechFutureProps()
	{}
};

class ZombieZombossMech_Future : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Future, ZombieZombossMech, RtClass);
	
	void OnRocketHitGround(ZombossRocket* i_rocket) override;
	void EMPeachStun(pvztime_t i_time) override;
	
protected:
	void registerForEvents() override;
	
private:
	void onPlantPlantfooded(class Plant* i_plant);
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_Future__) */
