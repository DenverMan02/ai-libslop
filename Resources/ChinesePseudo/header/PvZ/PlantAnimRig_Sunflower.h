//
//  PlantAnimRig_Sunflower.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_SUNFLOWER_H__
#define __PLANTANIMRIG_SUNFLOWER_H__

#include "PlantAnimRig.h"

class PlantAnimRig_Sunflower : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Sunflower, PlantAnimRig, RtClass);
	
	virtual bool PlaySunSpawn();
    virtual bool PlayGoToSleep();
	
protected:
	virtual void onAnimStopped() override;
private:
	virtual std::string getSpecialAnimName() { return "special"; }
};

#endif // __PLANTANIMRIG_SUNFLOWER_H__
