//
//  CollectableMoneyBag.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableMoneyBag_h
#define PlantsVersusZombies2_CollectableMoneyBag_h

#include "Collectable.h"

class CollectableMoneyBagType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableMoneyBagType, CollectableType, RtClass);
	
	CollectableMoneyBagType()
	{
		ContentsCount = 0;
	}

	std::string 	ContentsType;
	int 			ContentsCount;
};

#endif
