//
//  ZombieDinoBasic.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 9/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieDinoBasic__
#define __PlantsVersusZombies2__ZombieDinoBasic__

#include <stdio.h>

#include "ZombieAnimRig_Basic.h"
#include "ZombieBasic.h"
#include "ZombieEnums.h"



#pragma mark - ZombieDinoBasicState

STATE_ENUM_CHILD_BEGIN(ZombieDinoBasicState, ZombieState)
	ZDBS_Dropping,
	ZDBS_Grabbed,
	ZDBS_GrabbedIdle,
STATE_ENUM_END(ZombieDinoBasicState);



#pragma mark - ZombieDinoBasic

class ZombieDinoBasic : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieDinoBasic, ZombieBasic, RtClass);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, Dropping);
	DECLARE_STATE_FUNCTIONS(ZombieState, Grabbed);
	DECLARE_STATE_FUNCTIONS(ZombieState, GrabbedIdle);
	
	void PterodactylGrab(ZombieAnimRig_Basic::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void PterodactylDrop(ZombieAnimRig_Basic::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
	bool IsHelmMetallic() override;
	
private:
	void setDamageAndTargetingEnabled(bool i_enabled);
	
	void onDroppingAnimationStopped(const std::string& i_animName);
	void onGrabbedAnimationStopped(const std::string& i_animName);
	
	AnimHandle m_watchAnimHandle;
	ZombieAnimRig_Basic::AnimStoppedReflectionDelegate m_onPterodactylGrab;
	ZombieAnimRig_Basic::AnimStoppedReflectionDelegate m_onPterodactylDrop;
};


#pragma mark - ZombieAnimRig_DinoBasic

class ZombieAnimRig_DinoBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DinoBasic, ZombieAnimRig_Basic, RtClass);
	
	void PlayDropping(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void PlayGrabbed(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void PlayGrabbedIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
		
private:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getFlagHandLayerNames() override;
	const std::vector<std::string>& getNoFlagHandLayerNames() override;
	const std::vector<std::string>& getConeLayerNames() override;
	const std::vector<std::string>& getBucketLayerNames() override;
	const std::vector<std::string>& getCrownLayerNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieDinoBasic__) */
