//
//  PlantAnimRig_Torchwood.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/4/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_TORCHWOOD_H__
#define __PLANTANIMRIG_TORCHWOOD_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Torchwood : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Torchwood, PlantAnimRig, RtClass){}

    virtual bool playPlantFoodOn() override;
    virtual bool playPlantFoodMain() override;
	virtual bool PlayPlantFoodEnd() override;
};

#endif // __PLANTANIMRIG_TORCHWOOD_H__
