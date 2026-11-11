//
//  ZombieAnimRig_IceAgeBasic.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 10/30/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_IceAgeBasic_h
#define PlantsVersusZombies2_ZombieAnimRig_IceAgeBasic_h

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_IceAgeBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_IceAgeBasic, ZombieAnimRig_Basic, RtClass) {}

protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getFlagHandLayerNames() override;
	const std::vector<std::string>& getNoFlagHandLayerNames() override;
	const std::vector<std::string>& getConeLayerNames() override;
	const std::vector<std::string>& getBucketLayerNames() override;
	const std::vector<std::string>& getIceBlockLayerNames() override;
};

#endif
