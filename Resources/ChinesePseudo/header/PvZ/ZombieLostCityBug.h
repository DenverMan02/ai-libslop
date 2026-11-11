//
//  ZombieLostCityBug.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 5/6/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLostCityBug__
#define __PlantsVersusZombies2__ZombieLostCityBug__

#include <string>

#include "BoardEntity.h"
#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieEnums.h"
#include "RestrictionSet.h"

STATE_ENUM_CHILD_BEGIN(ZombieBugState, ZombieState)
	ZS_BUG_Flying_Up,
	ZS_BUG_Flying_Over,
	ZS_BUG_Flying_Down,
STATE_ENUM_END(ZombieBugState)

enum BasicHelmType
{
	BASIC_HELM_NONE,
	BASIC_HELM_CONE,
	BASIC_HELM_BUCKET
};

class ZombieLostCityBug : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieLostCityBug, Zombie, RtClass);
	void TakeDamage(const DamageInfo& i_damage) override;
	void AssignCatastrophicDamage() override { m_hasTakenCatastrophicDamage = true; }
    
    bool IsShrunkenWhenDying() { return m_shrunkenWhenDying; }
	
protected:
	bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	void onZombieInitialize() override;
	void setBasicHelm(BasicHelmType i_helm);
	bool hasHeadParticle() const override;
	
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_LOSTCITY_BUG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_LOSTCITY_BUG_ASH"; }
	std::string getBasicAshPAMName() const { return "POPANIM_EFFECTS_ZOMBIE_ASH"; }
	
private:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	OVERRIDE_STATE_ONENTER(ZombieState, Electrocute);
	OVERRIDE_STATE_ONENTER(ZombieState, Ash);
	OVERRIDE_STATE_ONENTER(ZombieState, Die);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingUp);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingOver);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingDown);
	
	void onApplyCondition(ZombieConditions i_condition) override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
	void onFlyUpCompleted();
	void onFlyOverCompleted();
	void onFlyDownCompleted();
	virtual void onDieCompleted();
	void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
	virtual void addBasicAshDeathEffect();
	void popBasicZombieParticles();
	
	BasicHelmType m_basicHelm;
	bool m_hasTakenCatastrophicDamage;
	bool m_shrunkenWhenDying;
};

class ZombieBugProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBugProps, ZombiePropertySheet, RtClass);
	
	ZombieBugProps()
	: BasicHelm(BASIC_HELM_NONE)
	, DamageFraction(0.5)
	, DamageAmountWhichAlsoKillsBasic(1000.f)
	{
        SpawnedZombieName = "lostcity";
    }
	
	BasicHelmType BasicHelm;
    float DamageFraction;
    PlantRestrictionSet PlantsWhichAlsoKillBasic;
	float DamageAmountWhichAlsoKillsBasic;
    std::string SpawnedZombieName;
};

//
//  Anim rig
//

class ZombieAnimRig_LostCityBug : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_LostCityBug, ZombieAnimRig, RtClass);
	ZombieAnimRig_LostCityBug();
	void SetLayerVisibilityForCurrentState(bool i_damaged);
	
	void PlayFlyingUp(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayFlyingOver(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayFlyingDown(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayDieNoBug();
	void SetHelmType(BasicHelmType i_basicHelm) { m_basicHelm = i_basicHelm; }
	void SetHasTakenCatastrophicDamage() { m_hasTakenCatastrophicDamage = true; }
	
protected:
	void onPopAnimInitialized() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	void onNeedsToDie()override;
	const std::string getDieAnimationName() override;
	
private:
	const std::string getHelmLayerName(BasicHelmType i_helmType);
	void updateHelmLayerVisibility(BasicHelmType i_helmType);
	void updateDamageLayerVisibility(bool i_damaged);
	bool hasHelm(BasicHelmType i_helmType);
	
	BasicHelmType m_basicHelm;
	bool m_hasTakenCatastrophicDamage;
};

#endif /* defined(__PlantsVersusZombies2__ZombieLostCityBug__) */
