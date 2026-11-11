//
//  ZombieAnimRig_TombRaiser.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_TOMBRAISER_H__
#define __ZOMBIEANIMRIG_TOMBRAISER_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_TombRaiser : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_TombRaiser, ZombieAnimRig, RtClass);
	
	typedef RtReflectionDelegate<Delegate0> PowerAnimDoneReflectionDelegate;
	typedef RtReflectionDelegate<Delegate0> ThrowBoneReflectionDelegate;

	// New functionality
	virtual bool PlayPowerAnim(PowerAnimDoneReflectionDelegate i_onAnimDone, ThrowBoneReflectionDelegate i_onThrow);
		
protected:
	virtual void onAnimStopped() override;
	virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	PowerAnimDoneReflectionDelegate m_onAnimDone;
	ThrowBoneReflectionDelegate m_onThrow;
};

#endif // __ZOMBIEANIMRIG_TOMBRAISER_H__
