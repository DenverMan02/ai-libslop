//
//  ZombieEightiesBreakDancer.h
//  PlantsVersusZombies2
//
//  Created by Mina, Elliott on 8/11/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEightiesBreakDancer__
#define __PlantsVersusZombies2__ZombieEightiesBreakDancer__

#include <stdio.h>
#include "DamageInfo.h"
#include "PlatformAutodetect.h"
#include "RtObject.h"
#include "Zombie.h"
#include "Plant.h"
#include "ZombieAnimRig_Basic.h"

#pragma mark - Props

class ZombieEightiesBreakDancerProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieEightiesBreakDancerProps, ZombiePropertySheet, RtClass);
    
    ZombieEightiesBreakDancerProps()
    {
        JamStyle = "";
		JamWalkSpeedMult = 0.0f;
		TossTime = 0.0f;
		TossHeight = 0.0f;
		TossDistance = 0.0f;
    }
    
    std::string JamStyle;
	float JamWalkSpeedMult;
	float TossTime;
	float TossHeight;
	float TossDistance;
	Rect TossTargetRect;
};

#pragma mark - Zombie

STATE_ENUM_CHILD_BEGIN(ZombieState_EightiesBreakDancer, ZombieState)
ZS_StartToss,
ZS_Tossing,
STATE_ENUM_END(ZombieState_EightiesBreakDancer)

class ZombieEightiesBreakDancer : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieEightiesBreakDancer, Zombie, RtClass);
    ZombieEightiesBreakDancer();

    void StartJamming() override;
	void StopJamming() override;
	std::string GetJamStyle() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	DECLARE_STATE_FUNCTIONS(ZombieState, StartToss);
	DECLARE_STATE_FUNCTIONS(ZombieState, Tossing);

private:
	bool	m_isJamming;
	
	bool						canTossZombies();
	std::vector<BoardEntity*>	getTossTargets(Rect collisionRect);
	Rect						calcTossRect(Rect relativeRect);
	void						removeInvalidTargets(std::vector<class BoardEntity*> &o_targets);
	bool						isTossable(BoardEntity* i_entity);
	void						tossZombies();
	void						tossZombie(BoardEntity* i_entity);
	void						spinIntroComplete(const std::string&);
	void						spinMainComplete(const std::string&);
	void						spinOutroComplete(const std::string&);
};

# pragma mark - Rig

class ZombieAnimRig_EightiesBreakDancer : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EightiesBreakDancer, ZombieAnimRig, RtClass);
	ZombieAnimRig_EightiesBreakDancer()
	{
		m_jamActive = false;
	}
	void ActivateJam(ZombieEightiesBreakDancer* i_zombie);
	void DeactivateJam(ZombieEightiesBreakDancer* i_zombie);
	void SpinIntro(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SpinMain(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SpinOutro(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::string getWalkAnimationName() override;
	const std::string getIdleAnimationName() override;
	
private:
	bool m_jamActive;
};

#endif /* defined(__PlantsVersusZombies2__ZombieEightiesBreakDancer__) */
