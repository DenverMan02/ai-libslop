//
//  PlantAnimRig_LightningReed.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-7-4.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_LightningReed__
#define __PlantsVersusZombies2__PlantAnimRig_LightningReed__

#include <iostream>
#include "PlantAnimRig.h"

class PlantAnimRig_LightningReed : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_LightningReed, PlantAnimRig, RtClass) {}
	
	virtual bool PlayAttackAnim(const std::string& i_attackAnim);
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_LightningReed__) */
