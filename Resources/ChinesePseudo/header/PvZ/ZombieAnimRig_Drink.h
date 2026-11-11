//
//  ZombieAnimRig_Drink.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-15.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_Drink__
#define __PlantsVersusZombies2__ZombieAnimRig_Drink__

#include "ZombieAnimRig.h"

class ZombieAnimRig_Drink : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Drink, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_Drink();
    bool becomeCrazy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool recover(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    
    virtual const std::string getIdleAnimationName() override;
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;
    virtual const std::string getDieAnimationName() override;
    virtual const std::string getStunAnimationName() override;
    
    
    bool m_bCrazy;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_Drink__) */
