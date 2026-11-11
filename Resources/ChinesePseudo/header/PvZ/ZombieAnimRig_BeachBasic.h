//
//  ZombieAnimRig_BeachBasic.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 6/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_BeachBasic_h
#define PlantsVersusZombies2_ZombieAnimRig_BeachBasic_h

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_BeachBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_BeachBasic, ZombieAnimRig_Basic, RtClass);

private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::vector<std::string>& getBucketLayerNames() override;
	
	void onPopAnimInitialized() override;
	
};

#endif
