//
//  ZombieAnimRig_Prospector.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/7/12
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_HAMMER_H
#define PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_HAMMER_H

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Hammer : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Hammer, ZombieAnimRig, RtClass);
	
	virtual void PlayRest();
    void PlayBlock(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    virtual void PlayBlock();
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	virtual void onPopAnimInitialized() override;

};

#endif
