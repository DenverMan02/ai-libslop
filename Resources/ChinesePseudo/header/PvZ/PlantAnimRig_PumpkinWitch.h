//
//  PlantAnimRig_PumpkinWitch.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/10/21.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_PumpkinWitch__
#define __PlantsVersusZombies2__PlantAnimRig_PumpkinWitch__

#include <stdio.h>
#include "PlantAnimRig.h"

class PlantAnimRig_PumpkinWitch : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_PumpkinWitch, PlantAnimRig, RtClass) {}
    
    virtual bool PlayIdleLooped() override;
    virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
    
private:
//    virtual void onPopAnimInitialized();
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_PumpkinWitch__) */
