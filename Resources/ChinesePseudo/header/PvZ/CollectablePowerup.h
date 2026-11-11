//
//  CollectablePowerup.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/22/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectablePowerup_h
#define PlantsVersusZombies2_CollectablePowerup_h

#include "Collectable.h"

// This class only exists so that we can switch on the type.
class CollectablePowerup : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectablePowerup, Collectable, RtClass) {}
};

#endif
