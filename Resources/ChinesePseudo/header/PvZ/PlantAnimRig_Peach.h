//
//  PlantAnimRig_Peach.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-12-2.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_Peach__
#define __PlantsVersusZombies2__PlantAnimRig_Peach__

#include "PlantAnimRig.h"

class PlantAnimRig_Peach : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Peach, PlantAnimRig, RtClass) {}
	
	virtual bool PlayCureSpawn(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	
protected:
	virtual void onAnimStopped() override;
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_Peach__) */
