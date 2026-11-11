//
//  ZombieAnimRig_MonkDrink.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-1-2.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_MonkDrink__
#define __PlantsVersusZombies2__ZombieAnimRig_MonkDrink__

#include "ZombieAnimRig.h"

class ZombieAnimRig_MonkDrink : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_MonkDrink, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_MonkDrink();
    
    void SetRedEyeLayers(const bool i_visible);
    
    bool becomeCrazy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool recover(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
    bool PlayAttackEat(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    
    //virtual const std::string getIdleAnimationName();
	//virtual const std::string getWalkAnimationName();
	virtual const std::string getEatAnimationName() override;
    //virtual const std::string getDieAnimationName();
    
    
    bool m_bCrazy;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_MonkDrink__) */
