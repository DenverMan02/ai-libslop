//
//  ZombieModernBalloon.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 11/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieModernBalloon__
#define __PlantsVersusZombies2__ZombieModernBalloon__

#include <string>

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieBalloonState, ZombieState)
	ZS_BALLOON_Flying_Up,
	ZS_BALLOON_Flying_Over,
	ZS_BALLOON_Flying_Down,
	ZS_BALLOON_Pop,
STATE_ENUM_END(ZombieBalloonState)

//
// NOTE: If the Balloon ends up having some unique functionality aside from layer names, consider
// extracting a common 'ZombieCarrier' base class.
//
// For now, design assures me the balloon is an exact duplicate of the bug.
//

class ZombieModernBalloon : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieModernBalloon, Zombie, RtClass);
	
protected:
	void onZombieInitialize() override;
	void onTakeBodyDamage(const DamageInfo& i_receivedDamage) override;
	void onArmorDropped(std::string i_armorType) override;
	void onFlyUpCompleted();
	void onFlyOverCompleted();
	void onFlyDownCompleted();
	void onPopBalloonCompleted();
	
	std::string getElectrocutePAMName() const override;
	std::string getAshPAMName() const override;
	
private:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingUp);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingOver);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingDown);
	DECLARE_STATE_FUNCTIONS(ZombieState, Pop);
};

//
//  Anim rig
//

class ZombieAnimRig_ModernBalloon : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ModernBalloon, ZombieAnimRig, RtClass);
	ZombieAnimRig_ModernBalloon() :m_hasBalloon(true) {}
	bool HasBalloon() const { return m_hasBalloon; }
	void SetHasBalloon(bool i_hasBalloon);
	void PopBalloon(AnimStoppedReflectionDelegate i_onAnimStopped);
	
	void PlayFlyingUp(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayFlyingOver(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayFlyingDown(AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	const std::string getWalkAnimationName() override;
	const std::string getIdleAnimationName() override;
	
	const std::string getEatAnimationName() override;
	const std::string getDieAnimationName() override;
	
private:
	bool m_hasBalloon;
};

#endif /* defined(__PlantsVersusZombies2__ZombieModernBalloon__) */
