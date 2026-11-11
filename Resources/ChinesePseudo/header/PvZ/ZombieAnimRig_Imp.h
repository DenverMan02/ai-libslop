//
//  ZombieAnimRig_Imp.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_IMP_H__
#define __ZOMBIEANIMRIG_IMP_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Imp : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Imp, ZombieAnimRig, RtClass);
	
	virtual bool PlayFlying();
	virtual bool PlayLand(AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual bool PlayBonk(AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual bool PlayFalling();
	virtual bool PlayGetUp(AnimStoppedReflectionDelegate i_onAnimStopped);
	 
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;

	enum PirateImpAnimState
	{
		IMP_ANIM_FLYING = ZOMBIEANIM_USERDEFINED,
	};
};

#endif
