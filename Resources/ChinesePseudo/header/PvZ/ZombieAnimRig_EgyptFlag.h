//
//  ZombieAnimRig_EgyptFlag.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/18/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_EgyptFlag_h
#define PlantsVersusZombies2_ZombieAnimRig_EgyptFlag_h

#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_EgyptFlag : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EgyptFlag, ZombieAnimRig_Basic, RtClass) {}
	
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
