//
//  Plant_GhostPepper.h
//  PlantsVersusZombies2
//
//  Created by Andrew Khosravian on 9/2/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __Plant_GhostPepper__
#define __Plant_GhostPepper__

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "BoardEntity.h"
#include "PlantPropertySheet.h"

enum GhostPepperState
{
	GHOSTSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
	GHOSTSTATE_ABOUT_TO_HAUNT,
	GHOSTSTATE_ABOUT_TO_HAUNT_PLANTFOOD,
	GHOSTSTATE_ATTACK,
	GHOSTSTATE_PLANTFOOD,
	GHOSTSTATE_ENDING_HAUNT,
	GHOSTSTATE_DEATH_EXPLOSION
};

class PlantGhostPepper : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantGhostPepper, PlantFramework, RtClass);

	PlantGhostPepper();

	void Initialize() override;
	bool CanApplyPlantfood() override;
	void UpdateActions() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	int CalcRenderOrder() override;
	bool IsInvincible() const override;
	bool HasShadow() override { return false; }
	bool CanBeTargeted() override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) override;

	void TakeSmashAttack(ZombiePtr i_srcZombie) override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;

	void onAnimStoppedCallback(const std::string &i_animLabel) override;
	void onDestroy() override;

private:

	void setState(const GhostPepperState i_state);

	void findTargets(std::vector<BoardEntity*> *o_targets, const PlantWeapon i_plantWeapon);
	void updateAttack();
	bool haunt(const PlantWeapon i_plantWeapon);
	void endHaunting();
	void findTargetsAndPlayAttackAnim();
	void startDeathExplosion();
	void explode();
	void filterTargets(const std::vector<BoardEntity*>& i_entities, std::vector<BoardEntity*> *o_targets);
	void causeDamage(const std::vector<BoardEntity*>& i_targets, const DamageInfo &i_damageInfo);
	void createAttackOverlay();
	void destroyAttackOverlay();
    void GetLevel2AppendTarget(std::vector<class BoardEntity *>& entityList);
    void UniqueAppend(std::vector<class BoardEntity *>& dest, const std::vector<class BoardEntity *>& src);
    void ApplyStun(const std::vector<class BoardEntity *>& targets);
    
	pvztime_t m_lastAttackTime;
	pvztime_t m_deathTime;

	std::vector<RtWeakPtr<class GhostPepperAttackAnim>> m_attackFog;
    std::vector<ZombiePtr> m_stunZombie;
};

class PlantAnimRig_GhostPepper : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_GhostPepper, PlantAnimRig, RtClass);

	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	void StopAttacking(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void StartDeathExplosion(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	std::string getPlantFoodOnAnimName() override { return "plantfood_start"; }
	std::string getPlantFoodMainAnimName() override { return "plantfood_loop"; }
	std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }

private:

	void onAttackStartFinished(const std::string &i_animLabel);
};

class GhostPepperAttackAnim : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(GhostPepperAttackAnim, Effect_PopAnim, RtClass);

	void StartFog();
	void StopFog();
    void Lengthen(bool value) { m_lengthen = value; }
protected:

	void onAnimStopped(const std::string& i_animLabel) override;
    bool m_lengthen;
};

class GhostPepperProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GhostPepperProps, PlantPropertySheet, RtClass);

	GhostPepperProps()
	{
		DamagePerPulse = 50.f;
		RateOfDamagePulsing = 3.f;
		ChainDamage = 20.f;
		NumChainJumps = 1;
		Lifetime = 200.f;
		DeathExplosionDamage = 200.f;
		DeathExplosionRadius = 200.f;
		PlantfoodDamageMult = 3.f;
		PlantfoodDamageRadiusMult = 3.f;
        AvatarStunTime = 2.0f;
	}

	float DamagePerPulse;
	float RateOfDamagePulsing;
	float ChainDamage;
	int NumChainJumps;
	float Lifetime;
	float DeathExplosionDamage;
	float DeathExplosionRadius;
	float PlantfoodDamageMult;
	float PlantfoodDamageRadiusMult;
    pvztime_t AvatarStunTime;
};

#endif /* defined(__Plant_GhostPepper__) */
