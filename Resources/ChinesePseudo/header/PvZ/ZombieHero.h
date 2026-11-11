//
//  ZombieHero.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 10/17/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEHERO_H__
#define __ZOMBIEHERO_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieHeroState, ZombieState)
    ZS_Hero_CustomBehavior,
STATE_ENUM_END(ZombieHeroState);

class ZombieHero : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieHero, Zombie, RtClass);

	// Hero zombies don't drop their heads.
	virtual float getHeadDropFraction() const override;

	virtual void onUpdate() override;

	void OverrideBehavior(ZombieHeroBehavior i_behavior, PropertySheetPtr i_behaviorProps);
	void SetBeaming(bool i_beamsIn, bool i_beamsOut);

	virtual void chooseDeathState(const DamageInfo& i_deathBlow) override;
	virtual void onMowedDown() override;

private:
	DECLARE_STATE_FUNCTIONS(ZombieState, CustomBehavior);

	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
	void onBehaviorAnimFinished(const std::string&);

	void triggerSpawnBehavior();
	SexyVector3 clampBoardPosition(const SexyVector3 &i_pos);

	void playBeamInOut();

	ZombieHeroBehavior m_behavior;
	PropertySheetPtr m_behaviorProps;

	bool m_beamsIn;
	bool m_beamsOut;

	// Custom Behavior Triggers
	pvztime_t m_nextBehaviorTime;
	int m_behaviorTriggerCount;
};

#endif
