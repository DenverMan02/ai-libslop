//
//  ZombieAnimRig_Hero.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 10/18/2012.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Hero_h
#define PlantsVersusZombies2_ZombieAnimRig_Hero_h

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Hero : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Hero, ZombieAnimRig, RtClass);

	ZombieAnimRig_Hero();

	void PlayTaunt(AnimStoppedReflectionDelegate onFinished);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif
