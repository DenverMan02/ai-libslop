//
//  PlantAnimRig_PowerLily.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 10/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_PowerLily__
#define __PlantsVersusZombies2__PlantAnimRig_PowerLily__

#include "PlantAnimRig.h"

class PlantAnimRig_PowerLily : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_PowerLily, PlantAnimRig, RtClass);
	
	bool PlayPlantFoodSpawn(AnimStoppedReflectionDelegate i_onAnimStopped);
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_PowerLily__) */
