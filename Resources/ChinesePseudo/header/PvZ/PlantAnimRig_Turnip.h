//
//  PlantAnimRig_Turnip.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang & Jonathan Han on 13-11-29.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_Turnip__
#define __PlantsVersusZombies2__PlantAnimRig_Turnip__



#include "Precompile.h"
#include "PlantAnimRig.h"

enum PlantAnimRigState_Turnip
{
	PLANTANIM_TURNIP_PLANTED = PLANTANIM_USERDEFINED,
	PLANTANIM_TURNIP_EMERGE,
};

class PlantAnimRig_Turnip : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Turnip, PlantAnimRig, RtClass){}
	
	bool PlayEmergeFromGround();
	bool PlaySpinningTurnip();
	bool PlayDefend();
	bool PlayDefendBladeKee(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayLevelAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayPrepareAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayResumeIdle(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
	virtual bool PlayPlantFoodEnd() override;
};






#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_Turnip__) */
