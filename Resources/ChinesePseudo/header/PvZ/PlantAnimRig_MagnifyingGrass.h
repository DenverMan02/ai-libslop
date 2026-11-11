//
//  PlantAnimRig_MagnifyingGrass.h
//  PlantsVersusZombies2
//
//  Created by jsola on 9/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_MagnifyingGrass_h
#define PlantsVersusZombies2_PlantAnimRig_MagnifyingGrass_h

#include "PlantAnimRig.h"

class PlantAnimRig_MagnifyingGrass : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_MagnifyingGrass, PlantAnimRig, RtClass) {}
	
	virtual bool PlayIdleLooped() override;
	bool PlayTapAttack(PopAnimRig::AnimStoppedDelegate i_onAnimStopped = PopAnimRig::AnimStoppedDelegate());
};

#endif
