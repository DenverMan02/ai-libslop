//
//  CollectableStarType.h
//  PlantsVersusZombies2
//
//  Created by jsola on 4/2/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableStarType_h
#define PlantsVersusZombies2_CollectableStarType_h

#include "Collectable.h"

class CollectableStarType : public CollectableType
{
	RT_CLASS_DEFINE(CollectableStarType, CollectableType, RtClass);
};

class CollectableStar : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableStar, Collectable, RtClass){}
};

#endif