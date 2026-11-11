//
//  ZombieLostCityExcavator.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 3/10/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLostCityExcavator__
#define __PlantsVersusZombies2__ZombieLostCityExcavator__

#include "DamageInfo.h"
#include "PlatformAutodetect.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieEnums.h"
#include "RestrictionSet.h"

STATE_ENUM_CHILD_BEGIN(ZombieExcavatorState, ZombieState)
	ZS_EXCAVATOR_Shovel,
	ZS_EXCAVATOR_Dropping_Shovel,
STATE_ENUM_END(ZombieExcavatorState)

class ZombieExcavator : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieExcavator, Zombie, RtClass);
	bool OverrideProjectileCollision(class Projectile* i_projectile) override;
	void TakeDamage(const DamageInfo& i_damage) override;
	Rect CalcShovelRect() const;
	Rect CalcZombieAttackRect() override;
	BoardEntity* FindShovelTarget();
	
protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, Shovel);
	DECLARE_STATE_FUNCTIONS(ZombieState, DroppingShovel);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	
	void onApplyCondition(ZombieConditions i_condition) override;
	
	void onZombieInitialize() override;
	void onSetHelm() override;

	bool canShovelPlantGroup(PlantGroupPtr i_plantGroup);
	void tossPlantGroup(PlantGroupPtr i_plantGroup);
	
	bool isProjectileArrivingAtBlockableAngle(Projectile* i_projectile);
	// void tossPlant(Plant* plant);
	void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
	class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
	virtual void refreshAnimRigForHelm();
	virtual void refreshHelmDamageState();
	void overrideTakeCollision(Projectile* i_projectile, bool shovelBlockingDamage);
	bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	void onShovelCompleted();
	// bool canShovelPlant(Plant* i_plant);
	
private:
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
	int32 m_helmDamageIndex = 0;
	// RtWeakPtr<Plant> m_plantToShovel;
	RtWeakPtr<PlantGroup> m_plantToShovel;
};

class ZombieExcavatorProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieExcavatorProps, ZombiePropertySheet, RtClass);
	
	ZombieExcavatorProps()
		: CatchArcDegrees(120.0f)
		, PreferredDistanceToThrowPlant(3)
		, ShovelAttackRectOffsetX(-30)
	{}
	
	float CatchArcDegrees;
	int PreferredDistanceToThrowPlant;
	int ShovelAttackRectOffsetX;
	Rect ShovelRect;
	PlantRestrictionSet	PlantsShovelableWhileInvincible;
	PlantRestrictionSet PlantsToBashInsteadOfShovel;
};

//
//  AnimRig!
//

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_LostCityExcavator : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_LostCityExcavator, ZombieAnimRig_Basic, RtClass);
	
	class ZombieParticle* DropHelm(HelmType i_helmType, class Zombie* i_zombie) override;
	void SetShovelDropped();
	void DoShovel(AnimStoppedReflectionDelegate i_onAnimStopped);
	void DropShovel(AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	void onPopAnimInitialized() override;
	
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getFlagHandLayerNames() override;
	const std::vector<std::string>& getNoFlagHandLayerNames() override;
	const std::vector<std::string>& getShovelLayerNames() override;
	
	const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	const std::string getEatAnimationName() override;
	const std::string getDieAnimationName() override;
	
private:
	bool m_hasShovel = true;
};

#endif /* defined(__PlantsVersusZombies2__ZombieLostCityExcavator__) */
