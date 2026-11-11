//
//  ZombieAnimRig_DarkBasic.h
//  PlantsVersusZombies2
//
//  Created by erydeman on 8/16/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_DarkBasic_h
#define PlantsVersusZombies2_ZombieAnimRig_DarkBasic_h

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_DarkBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DarkBasic, ZombieAnimRig_Basic, RtClass) {}

	virtual void SetLayerVisibilityForCurrentState() override;

private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::vector<std::string>& getFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::vector<std::string>& getBucketLayerNames() override;
	virtual const std::vector<std::string>& getCrownLayerNames() override;
};

#endif
