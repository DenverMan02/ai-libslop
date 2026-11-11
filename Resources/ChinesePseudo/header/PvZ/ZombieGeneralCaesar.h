//
//  ZombieGeneralCaesar.cpp
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 12/19/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieGeneralCaesar_h
#define PlantsVersusZombies2_ZombieGeneralCaesar_h

#include "DamageInfo.h"
#include "GridItemPlantConditionTarget.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieAnimRig_BeachBasic.h"
#include "ZombieGeneralBase.h"

class BoardEntity;
class Effect_PopAnim;
class Plant;

class ZombieGeneralCaesar : public ZombieGeneralBase
{
public:
    RT_CLASS_DEFINE(ZombieGeneralCaesar, ZombieGeneralBase, RtClass);
	
    Zombie* FindFriendlyTarget(std::vector<BoardEntityPtr> i_ignoreTargets = std::vector<RtWeakPtr<BoardEntity>>()) const override;
//	bool 	IsValidFriendlyTarget(Zombie *i_zombie) const override;
    bool 	IsValidFriendlyTarget(Zombie *i_zombie) const ;
    void onUpdate() override;
	bool 	CanDropArm() const override { return false; }
	
protected:
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }
	
	GroundEffectType GetTideEffect() const override { return GROUND_EFFECT_Tide_With_Tail; }
	
	void onApplyCondition(ZombieConditions i_condition) override;

private:
    void onZombieInitialize() override;
};

class ZombieAnimRig_GeneralCaesar : public ZombieAnimRig_GeneralBase
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_GeneralCaesar, ZombieAnimRig_GeneralBase, RtClass) {}
	
	const std::string getRangedAttackAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	const std::vector<std::vector<std::vector<std::string>>>& getDamageLayers() override;
	const std::vector<std::vector<std::string>>& getBaseLayers() override;
	
	const std::string getWalkReverseAnimationName() override {return "walk_off2";}
};

class ZombieGeneralCaesarProps : public ZombieGeneralProps
{
public:
	RT_CLASS_DEFINE(ZombieGeneralCaesarProps, ZombieGeneralProps, RtClass);
	
	Rect ActionAttackTargetRect;
};

class SauceProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(SauceProjectile, Projectile, RtClass) {}
    
protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
};

class SaucedPlantConditionTargetProps : public GridItemBoardEntityConditionTargetProps
{
public:
    RT_CLASS_DEFINE(SaucedPlantConditionTargetProps, GridItemBoardEntityConditionTargetProps, RtClass);
    
    SaucedPlantConditionTargetProps()
    {
        EvaporateTimeSeconds = 5;
    }
    
    float EvaporateTimeSeconds;
};

class Sauced_GridItemPlantConditionTarget : public GridItemPlantConditionTarget
{
public:
    RT_CLASS_DEFINE(Sauced_GridItemPlantConditionTarget, GridItemPlantConditionTarget, RtClass);

    void TakeDamage(const DamageInfo& i_damage) override;
	
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;
    
private:
    void broadcastAroma();
    
    float m_nextAromaTime;
    float m_evaporateTime;
};

#endif
