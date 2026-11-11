//
//  ZombieAnimRig_Prospector.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/7/12
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_QIGONG_H
#define PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_QIGONG_H

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Qigong : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Qigong, ZombieAnimRig, RtClass);

    pvztime_t GetPullDuration();
    
    void PlayPull(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);


protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif
