//
//  ZombieGeneralBase.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/3/18.
//  Copyright (c) 2018 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieGeneralBase_h
#define PlantsVersusZombies2_ZombieGeneralBase_h

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieAnimRig_BeachBasic.h"
#include "ZombieGeneralActions.h"
#include "ZombieWithActions.h"


class BoardEntity;
class Effect_PopAnim;
class Plant;

enum ZombieGeneralCollide
{
	ZOMBIE_GENERAL_COLLIDE_IGNORE,
	ZOMBIE_GENERAL_COLLIDE_CRUSH,
	ZOMBIE_GENERAL_COLLIDE_BURN
};

class ZombieGeneralProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieGeneralProps, ZombieWithActionsProps, RtClass);
	
	pvztime_t	LifetimeSeconds = 0;
	int			GeneralPhase = 0;
	
	ZombieGeneralCollide	CollidePlants = ZOMBIE_GENERAL_COLLIDE_CRUSH;
	ZombieGeneralCollide	CollideHypnotizedZombies = ZOMBIE_GENERAL_COLLIDE_CRUSH;
};

class ZombieGeneralBase : public ZombieWithActions
{
public:
    RT_CLASS_DEFINE(ZombieGeneralBase, ZombieWithActions, RtClass);
	
	void SetLifetime(pvztime_t i_lifetime);
	int GetGeneralPhase() const { return GetProps<ZombieGeneralProps>()->GeneralPhase; }
//	  bool CanTargetEntityHeight(BoardEntityHeight i_entityHeight) override { return true; }
	  bool CanTargetEntityHeight(BoardEntityHeight i_entityHeight)  { return true; }

    pvztime_t m_stunDuration;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, ZombiePickNextAction);
	
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }
	
	GroundEffectType GetTideEffect() const override { return GROUND_EFFECT_Tide_With_Tail; }
	
//    bool CanEatZombies() const override;
    bool CanEatZombies() const;
	bool CanBeHypnotized() const override { return false; }
	bool CanBeMowed() const override { return false; }
	bool CanBeBlovered() const override { return false; }
	bool CanBeFlickedOff() const override { return false; }
	bool CanBeTossedByPlants(ZombieTossedPower i_tossStrength) const override { return false; }
//	bool CanBleedOut() const override { return false; }
	bool CanBleedOut() const { return false; }
	bool CanDropArm() const override;
//	bool CanBeAttractedOrRepulsed() const override { return false; }
	bool CanBeAttractedOrRepulsed() const  { return false; }
    
	// Generals cannot have their animations overridden externally
	void SetIdleState() override {}
//	void SetWalkingState() override {}
	void SetWalkingState() {}
	void SetGrabbedState() override {}
	void SetDamageStateOverride(int i_index) { m_damageStateOverride = i_index; updateDamageState(); }
	
protected:
    void onZombieInitialize() override;
	void onPlaceOnBoard() override;
	void onUpdate() override;
	void chooseDeathState(const DamageInfo& i_deathBlow) override;
    void setupDeathPhase(const DamageInfo &i_deathBlow);
//    void onZombieOffscreenRight() override;
    void onZombieOffscreenRight() ;
	void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
	void onApplyCondition(ZombieConditions i_condition) override;
	bool isImmuneToShrinking() override { return true; }

	bool hasHeadParticle() const override { return false; }
	
    virtual bool shouldCrushPlants();
    
private:
	void pickNextAction();
	void tryCrushPlants();
	
	void updateDamageState();
	void setDamageState(int i_index);

	pvztime_t	m_timeToRetreat;
	int m_damageStateOverride;
};

class ZombieAnimRig_GeneralBase : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_GeneralBase, ZombieAnimRig, RtClass) {}
	
	const std::string getRangedAttackAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	void UpdateDamageLayers(int i_phase, float i_damagePercent, int i_overrideDamageState);
	
	virtual const std::vector<std::vector<std::vector<std::string>>>& getDamageLayers();
	virtual const std::vector<std::vector<std::string>>& getBaseLayers();
};

#endif
