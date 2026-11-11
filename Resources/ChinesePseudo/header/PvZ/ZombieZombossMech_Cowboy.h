//
//  ZombieZombossMech_Cowboy.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_Cowboy__
#define __PlantsVersusZombies2__ZombieZombossMech_Cowboy__

#include "ZombieZombossMech.h"

class ZombossRocket;

class ZombieZombossMechCowboyProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechCowboyProps, ZombieZombossMechProps, RtClass);
	
	ZombieZombossMechCowboyProps()
	{}
};

class ZombieZombossMech_Cowboy : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Cowboy, ZombieZombossMech, RtClass);
	
	void OnRocketHitGround(ZombossRocket* i_rocket) override;
	
protected:
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_Cowboy__) */
