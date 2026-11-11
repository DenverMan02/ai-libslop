//
//  ZombieAnimRig_PirateBarrelPusher.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_PIRATEBARRELPUSHER_H__
#define __ZOMBIEANIMRIG_PIRATEBARRELPUSHER_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_PirateBarrelPusher : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_PirateBarrelPusher, ZombieAnimRig, RtClass);
	
	ZombieAnimRig_PirateBarrelPusher();
	
	void					SetHasShield(bool i_hasShield);
	void					HideBarrel();
	bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;

	const std::string GetArmParticleName() override;

protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::string getWalkAnimationName() override;
	const std::string getEatAnimationName() override;

private:
	bool					m_hasShield;
};

#endif
