//
//  ZombieEighties8BitBasic.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 8/27/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEighties8BitBasic__
#define __PlantsVersusZombies2__ZombieEighties8BitBasic__

#include <stdio.h>

#include "ZombieEightiesBasic.h"

class ZombieEighties8BitBasic : public ZombieEightiesBasic
{
public:
	RT_CLASS_DEFINE(ZombieEighties8BitBasic, ZombieEightiesBasic, RtClass);
	
	void playEatSound() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieEighties8BitBasic__) */
