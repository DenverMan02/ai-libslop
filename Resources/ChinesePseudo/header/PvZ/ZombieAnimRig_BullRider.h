//
//  ZombieAnimRig_BullRider.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/14/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_BullRider_h
#define PlantsVersusZombies2_ZombieAnimRig_BullRider_h

#include "ZombieAnimRig_Imp.h"

class ZombieAnimRig_BullRider : public ZombieAnimRig_Imp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_BullRider, ZombieAnimRig_Imp, RtClass) {}

	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::string getIdleAnimationName() override;
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;
	virtual const std::string getDieAnimationName() override;
	virtual const std::string GetHeadParticleName() override;
	virtual const std::string GetArmParticleName() override;

	virtual bool PlayFlying() override;
	virtual bool PlayLand(AnimStoppedReflectionDelegate i_onAnimStopped) override;
	virtual bool PlayBonk(AnimStoppedReflectionDelegate i_onAnimStopped) override;
	virtual bool PlayFalling() override;
	virtual bool PlayGetUp(AnimStoppedReflectionDelegate i_onAnimStopped) override;
};

#endif
