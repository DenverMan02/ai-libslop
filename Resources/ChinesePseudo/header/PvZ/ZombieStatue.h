//
//  ZombieStatue.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 1/24/20.
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef ZombieStatue_h
#define ZombieStatue_h

#include <stdio.h>
#include "DamageLifetime.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"

class ZombieStatueProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieStatueProps, ZombiePropertySheet, RtClass);

	ZombieStatueProps()
	{}

	DamageLifetime DamagePhases;
	std::string BreakEffect;
};

class ZombieStatue : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieStatue, Zombie, RtClass);
	ZombieStatue();
	virtual ~ZombieStatue();

	void TakeDamage(const DamageInfo& i_damage) override;
	void InitializeStatue(float i_hitpoints);
	bool CanDropHead() const override { return false; }
	bool CanDropArm() const override { return false; }
	bool ShouldDrawShadow() const override { return false; }
	bool CanBeTossedByPlants(ZombieTossedPower i_tossStrength) const override { return false; }

protected:
	void onPlaceOnBoard() override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void spawnBreakEffect(int i_damageLevel);

private:
	int m_damagePhase;
	bool m_playingDamageAnim;
};

class ZombieAnimRig_Statue : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Statue, ZombieAnimRig, RtClass);
};

#endif /* ZombieStatue_h */
