//
//  PlantAnimRig_Imitater.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/4/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Imitater_h
#define PlantsVersusZombies2_PlantAnimRig_Imitater_h

#include "PlantAnimRig.h"

class PlantAnimRig_Imitater : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Imitater, PlantAnimRig, RtClass) {}
	
	virtual bool PlayIdleLooped() override;
};

#endif
