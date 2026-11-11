//
//  ZombieAnimRig_SkyCityBasic.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/12.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_SkyCityBasic_h
#define PlantsVersusZombies2_ZombieAnimRig_SkyCityBasic_h

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_SkyCityBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_SkyCityBasic, ZombieAnimRig_Basic, RtClass) {}

protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getFlagHandLayerNames() override;
	const std::vector<std::string>& getNoFlagHandLayerNames() override;
	const std::vector<std::string>& getConeLayerNames() override;
	const std::vector<std::string>& getBucketLayerNames() override;
};

#endif
