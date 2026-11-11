//
//  PlantAnimRig_Blover.h
//  PlantsVersusZombies2
//
//  Created by aseavy on 9/4/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Blover_h
#define PlantsVersusZombies2_PlantAnimRig_Blover_h

#include "PlantAnimRig_Sunflower.h"

class PlantAnimRig_Blover : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Blover, PlantAnimRig, RtClass) {}
	
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
};

#endif
