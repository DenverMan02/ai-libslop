//
//  PlantAnimRig_Agave.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/12/3.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantAnimRig_Agave_h
#define PlantAnimRig_Agave_h

#include "Precompile.h"
#include "PlantAnimRig.h"


class PlantAnimRig_Agave : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Agave, PlantAnimRig, RtClass){}
    
    virtual bool PlayCharge(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    virtual bool PlayNormalAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    virtual bool PlayChargeAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

};

#endif /* PlantAnimRig_Agave_hpp */
