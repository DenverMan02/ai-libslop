//
//  EffectAnimRig_CoconutCannonball.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_CoconutCannonball_h
#define PlantsVersusZombies2_EffectAnimRig_CoconutCannonball_h

#include "Precompile.h"
#include "PopAnimRig.h"

class EffectAnimRig_CoconutCannonball : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_CoconutCannonball, PopAnimRig, RtClass) {}

	bool PlayNormalFlightLooped();
	bool PlayPlantFoodFlightLooped();
	bool PlayPlantFoodFlightFuse(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayExplosion(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
    
    //Star Effect
    bool PlayStarPlantFoodFlightLooped();
	bool PlayStarPlantFoodFlightFuse(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayStarExplosion(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
	
	pvztime_t CalcFuseAnimLength();
	
private:
};

#endif
