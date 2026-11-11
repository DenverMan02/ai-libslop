//
//  PlantAnimRig_Kernelpult.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_KERNELPULT_H__
#define __PLANTANIMRIG_KERNELPULT_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Kernelpult : public PlantAnimRig 
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Kernelpult, PlantAnimRig, RtClass){}
	
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
	virtual bool PlayButterAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    virtual bool PlayRocketAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	virtual bool PlayPlantFoodEnd() override;
	virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
};

#endif // __PLANTANIMRIG_KERNELPULT_H__
