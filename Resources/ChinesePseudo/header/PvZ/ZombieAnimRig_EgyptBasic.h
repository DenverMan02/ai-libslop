//
//  ZombieAnimRig_EgyptBasic.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_EGYPTBASIC_H__
#define __ZOMBIEANIMRIG_EGYPTBASIC_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_EgyptBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EgyptBasic, ZombieAnimRig_Basic, RtClass) {}

private:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    virtual const std::vector<std::string>& getFlagHandLayerNames() override;
    virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
    virtual const std::vector<std::string>& getConeLayerNames() override;
    virtual const std::vector<std::string>& getBucketLayerNames() override;
    virtual const std::vector<std::string>& getHelmetLayerNames() override;
};

#endif // __ZOMBIEANIMRIG_EGYPTBASIC_H__
