//
//  CollectableWorldKey.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CollectableWorldKey__
#define __PlantsVersusZombies2__CollectableWorldKey__

#include "Collectable.h"
#include "RtObject.h"

// This class only exists so that we can switch on the type.
class CollectableWorldKey : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableWorldKey, Collectable, RtClass) {}
};

#endif /* defined(__PlantsVersusZombies2__CollectableWorldKey__) */
