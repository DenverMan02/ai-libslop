//
//  ZombieBeachOctopus.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/23/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieBeachOctopus_h
#define PlantsVersusZombies2_ZombieBeachOctopus_h

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieAnimRig_BeachBasic.h"
#include "ZombieWithActions.h"

class BoardEntity;
class Effect_PopAnim;
class Plant;

class ZombieBeachOctopus : public ZombieWithActions
{
public:
    RT_CLASS_DEFINE(ZombieBeachOctopus, ZombieWithActions, RtClass);
	
	class PlantGroup* FindSpellTarget();
	
	void onPlaceOnBoard() override;
	Rect calcRangedTargetGridRect() override;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	
	GroundEffectType GetTideEffect() const override { return GROUND_EFFECT_Tide_With_Tail; }
	
private:
    void onZombieInitialize() override;
	void doZap();
	
	pvztime_t m_nextCastTime = PVZ_EOT();
	int m_castCount = 0;
};

class ZombieAnimRig_Octopus : public ZombieAnimRig_BeachBasic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Octopus, ZombieAnimRig_BeachBasic, RtClass) {}
	
	const std::string getRangedAttackAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

class SquidProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SquidProjectile, Projectile, RtClass) {}
	
	bool OnCollideEntity(BoardEntity* i_entity) override;
};

#endif
