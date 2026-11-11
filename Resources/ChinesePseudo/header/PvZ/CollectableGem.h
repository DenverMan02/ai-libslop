//
//  CollectableGem.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableGem_h
#define PlantsVersusZombies2_CollectableGem_h

#include "Collectable.h"

class CollectableGemType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableGemType, CollectableType, RtClass);
	
	CollectableGemType()
	{
		GemValue = 0;
	}
	
	int GemValue;
};

class CollectableGemFake : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableGemFake, Collectable, RtClass) {}

	int GetGemValue() const;
	
};

class CollectableGemDangerDrop : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableGemDangerDrop, Collectable, RtClass) {}
    
	int GetGemValue() const;
	
};

#endif
