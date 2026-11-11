//
//  ZombieAnimRig_Explorer.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 7/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Explorer_h
#define PlantsVersusZombies2_ZombieAnimRig_Explorer_h

#include "ZombieAnimRig.h"

class ZombieAnimRig_Explorer : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Explorer, ZombieAnimRig, RtClass) {}

	void SetTorchLayers(const bool i_visible);

private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif
