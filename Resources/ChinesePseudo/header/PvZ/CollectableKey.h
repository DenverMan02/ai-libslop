//
//  CollectableKey.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableKey_h
#define PlantsVersusZombies2_CollectableKey_h

#include "Collectable.h"

class CollectableKeyType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableKeyType, CollectableType, RtClass);
	
	CollectableKeyType()
	{
	}
};

#endif
