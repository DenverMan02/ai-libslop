//
//  PlantAnimRig_FireGourd.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-11-29.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_FireGourd__
#define __PlantsVersusZombies2__PlantAnimRig_FireGourd__



#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_FireGourd : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_FireGourd, PlantAnimRig, RtClass);
	
	virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
	
    bool PlayAnimLooped(std::string animName);
    bool PlayAnimOnce(std::string animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	
    bool PlayIdleLooped() override;

    virtual bool playPlantFoodMain() override;
    
private:
	virtual void onPopAnimInitialized() override;
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_FireGourd__) */
