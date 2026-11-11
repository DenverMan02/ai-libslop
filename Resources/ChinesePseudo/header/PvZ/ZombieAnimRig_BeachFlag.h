//
//  ZombieAnimRig_BeachFlag.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 8/12/14.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_BeachFlag_h
#define PlantsVersusZombies2_ZombieAnimRig_BeachFlag_h

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_BeachFlag : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_BeachFlag, ZombieAnimRig_Basic, RtClass) {}

private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::vector<std::string>& getFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::vector<std::string>& getBucketLayerNames() override;
};

#endif
