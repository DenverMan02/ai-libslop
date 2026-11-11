//
//  PlantAnimRig_SnowPea.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-5-20.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_SnowPea_h
#define PlantsVersusZombies2_PlantAnimRig_SnowPea_h

#include "PlantAnimRig.h"

class PlantAnimRig_SnowPea : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_SnowPea, PlantAnimRig, RtClass);
    
protected:
    
    virtual void onAnimStopped() override;
    virtual void onPopAnimInitialized() override;
};

#endif
