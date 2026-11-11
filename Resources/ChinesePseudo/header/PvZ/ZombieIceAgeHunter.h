//
//  ZombieIceAgeHunter.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 11/5/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieIceAgeHunter_h
#define PlantsVersusZombies2_ZombieIceAgeHunter_h

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieWithActions.h"

class ZombieIceAgeHunterProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeHunterProps, ZombieWithActionsProps, RtClass);
	
    int NearAttackRange = 4;
    int FarAttackRange = 7;
	int SnowballsPerBarrage = 3;
};

class ZombieIceAgeHunterEliteProps : public ZombieIceAgeHunterProps
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeHunterEliteProps, ZombieIceAgeHunterProps, RtClass);

	ZombieIceAgeHunterEliteProps() {
		SkillSpecialInterval = 3;
	}

	int SkillSpecialInterval;// count for a big special skill time. when value % SkillSpecialInterval == 0, it is.
};

class ZombieIceAgeHunter : public ZombieWithActions
{
public:
    RT_CLASS_DEFINE(ZombieIceAgeHunter, ZombieWithActions, RtClass);
	
protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	
	GroundEffectType GetTideEffect() const override { return GROUND_EFFECT_Tide_With_Tail; }
	
protected:
    virtual void onZombieInitialize() override;
	virtual void doZap(ZombieActionDefinitionPtr i_action);
    virtual bool isGridItemValidTarget(GridItem* gridItem);
    virtual bool isNearestTargetInRange();
	
	pvztime_t m_nextCastTime;
	
    int m_snowballsPerBarrage;
    int m_nearRange;
    int m_farRange;
    int m_snowballsThrown;
};

class ZombieIceAgeHunterElite : public ZombieIceAgeHunter
{
public:
    RT_CLASS_DEFINE(ZombieIceAgeHunterElite, ZombieIceAgeHunter, RtClass);

    BoardEntityPtr FindNearestTargetInRange(int row);

    void AddSpecialSkillTimeCount() { ++m_skillTimeCount; }
    void ResetSpecialSkillTimeCount() { m_skillTimeCount = 1; }
    bool IsSpecialSkillTime();

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_ONENTER(ZombieState, Eat);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);

	virtual void onPlaceOnBoard() override;
    virtual void onZombieInitialize() override;
    virtual bool isNearestTargetInRange() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

protected:
	AnimHandle m_watchAnimHandle;
	int m_skillTimeCount;
};

class ZombieAnimRig_Hunter : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Hunter, ZombieAnimRig, RtClass) {}
	
	const std::string getRangedAttackAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

class HunterSnowballProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(HunterSnowballProjectile, Projectile, RtClass) {}
    
    bool OnCollideEntity(BoardEntity* i_entity) override;
};

class HunterSnowballEliteProjectile : public HunterSnowballProjectile
{
public:
	RT_CLASS_DEFINE(HunterSnowballEliteProjectile, HunterSnowballProjectile, RtClass) {}

    bool OnCollideEntity(BoardEntity* i_entity) override;
};

#endif
