//
//  ZombiePrototype.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/15/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePrototype_h
#define PlantsVersusZombies2_ZombiePrototype_h

#include "Zombie.h"

class ZombiePrototype : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePrototype, Zombie, RtClass) {}
	
	void SetColor(Color i_color);

protected:
	virtual void onZombieInitialize() override;
};

#endif
