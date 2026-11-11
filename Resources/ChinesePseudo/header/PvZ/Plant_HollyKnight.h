//
//  Plant_HollyKnight.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/4/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_HollyKnight__
#define __PlantsVersusZombies2__Plant_HollyKnight__

#include "PlantFramework.h"
#include "ComponentPlantLauncher.h"
#include "DamageLifetime.h"
#include "GameSubSystem.h"

class HollyKnightProps : public PlantLauncherProps
{
public:
	RT_CLASS_DEFINE(HollyKnightProps, PlantLauncherProps, RtClass);

	HollyKnightProps()
	:StartingNumCharges(3)
	,KnockbackGrid(2)
	{
	}
	int KnockbackGrid;
	float AttackDamage;
	int StartingNumCharges;
	DamageLifetime DamagePhases;
};

class PlantHollyKnight : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHollyKnight, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;

	bool HasCharges();
	void onHealed() override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;

	bool CanUpgrade();

	void registerForEvents() override;
	
protected:

	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void onKilled(bool i_instantKill = false) override;

private:

	void SetupLevelBasedProjectileProps(const HollyKnightProps* props);
	void PlayAttackEffect(std::string i_animName);
	bool OnSelected();
	void OnDeselected();
	void OnFiring();
	static void OnFiredProjectile(Projectile& projectile, const PlantPropertySheet* props);
	void UpdateCharges(int num);
	void OnHealthChanged();

	enum State
	{
		STATE_START_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_ATTACK,
		STATE_FINISH_ATTACK
	};

	void setState(const uint i_state);

private:
	pvztime_t m_lastAttack;

	int m_numCharges;
	int m_damagePhase;

	bool m_hasTarget;
	BoardEntityPtr m_target;
	RtWeakPtr<ComponentPlantLauncher> m_launcherComponent;
	std::vector<RtWeakPtr<BoardEntity>> m_pfTargets;
};

class PlantAnimRig_HollyKnight : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HollyKnight, PlantAnimRig, RtClass);

	PlantAnimRig_HollyKnight() : m_numDamageStates(0), m_isLevel5(false) {}
	void onPopAnimInitialized() override;
	void onPopAnimCommand(pvztime_t i_atTime, const std::string &i_command, const std::string &i_param) override;

	void ShowNumBerries(int num);
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	bool PlaySelected();
	bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
	int CalcDamageStateCount() override;
	void SetNumDamageStates(int value);
	void SetIsLevel5(bool i_flag){
		m_isLevel5 = i_flag;
	};

	static const std::string BerryIdleLayerNames[];
	static const std::string BerryFireLayerNames[];
	static const std::string BerryReadyLayerNames[];
	static const std::string LeafReadyLayerNames[];
	static const int NumBerryLayers;

private:
	int m_numDamageStates;
	bool m_isLevel5;
};

class HollyKnightLeafProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(HollyKnightLeafProps, ProjectilePropertySheet, RtClass);

	HollyKnightLeafProps()
	:KnockbackTime(0.0f)
	,KnockbackHeight(0.0f)
	,KnockbackGrid(0)
	,IsAvatarSkill(false)
	{}

	bool IsAvatarSkill;
	int KnockbackGrid;
	float KnockbackTime;
	float KnockbackHeight;

};

class HollyKnightLeaf : public Projectile
{
public:
	RT_CLASS_DEFINE(HollyKnightLeaf, Projectile, RtClass);
	HollyKnightLeaf();
	void setChildLevel(int i_level){
		m_level = i_level;
	};

protected:
	bool OnCollideGround() override;
	void onSplashDamageHitEntity(BoardEntity *i_hitEntity) override;

public:
	int ProjectileKnockback;
	float BarrierLeafDamage;

private:
	void hitZombie(BoardEntity *i_hitEntity);
	bool shouldKnockback(BoardEntity* i_impactedEntity);

	int m_level;
};

class PlantTypeHollyKnight : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeHollyKnight, PlantType, RtClass) {}
	// Holly can be replanted even if it's at full health as long as it's missing at least one berry
	// void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
	bool CanPlantOnPlant(Plant* plant) const override;
};

#endif /* defined(__PlantsVersusZombies2__Plant_HollyKnight__) */
