//
//  ZombieAnimRig_DarkFlag.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 8/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_DarkFlag_h
#define PlantsVersusZombies2_ZombieAnimRig_DarkFlag_h

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_DarkFlag : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DarkFlag, ZombieAnimRig_Basic, RtClass) {}
	
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
