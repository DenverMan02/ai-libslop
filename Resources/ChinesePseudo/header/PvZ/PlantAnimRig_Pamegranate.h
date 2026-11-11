//
//  PlantAnimRig_Pamegranate.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 14-11-5.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_Pamegranate__
#define __PlantsVersusZombies2__PlantAnimRig_Pamegranate__

#include "PlantAnimRig.h"

class PlantAnimRig_Pamegranate : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Pamegranate, PlantAnimRig, RtClass);
    bool PlayAdvancedAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_Pamegranate__) */
