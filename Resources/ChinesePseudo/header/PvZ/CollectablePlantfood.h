//
//  CollectablePlantfood.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectablePlantfood_h
#define PlantsVersusZombies2_CollectablePlantfood_h

#include "Collectable.h"

class CollectablePlantfoodType : public CollectableType
{
	RT_CLASS_DEFINE(CollectablePlantfoodType, CollectableType, RtClass);
};

enum PlantfoodCategory
{
	Plantfood_Basic = 0,
	Plantfood_SpaceTime,
};

class CollectablePlantfood : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectablePlantfood, Collectable, RtClass);

	CollectablePlantfood();

		// ZombieRa functionality
	void StartCaptureEffect(std::string i_color);
	void StopCaptureEffect();
	void SetPlantfoodCategory(PlantfoodCategory i_category);

	PlantfoodCategory plantfoodCategory;
};

#endif
