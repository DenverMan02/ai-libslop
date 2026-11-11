//
//  PlantAnimRig_EMPea.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_EMPea_h
#define PlantsVersusZombies2_PlantAnimRig_EMPea_h

#include "PlantAnimRig_SpringBean.h"

class PlantAnimRig_EMPea : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_EMPea, PlantAnimRig, RtClass) {}
	
	virtual bool PlayIdleLooped() override;
};

#endif
