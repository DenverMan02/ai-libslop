#pragma once
#ifndef __PLANT_SNAPPEA_H__
#define __PLANT_SNAPPEA_H__

#include <vector>

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "EffectObject.h"

class Zombie;

class EffectObject_BurrowAttack;
typedef RtWeakPtr<EffectObject_BurrowAttack> BurrowAttackEffectPtr;

// Plant props
class SnapPeaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SnapPeaProps, PlantPropertySheet, RtClass);

	std::vector<float> ChewTimeSeconds;
	float FiredZombieHeadAttackCooldownSeconds;
	float CouldNotEatAttackCooldownSeconds;
	int PlantfoodTargetCount;
	float Probability;
	std::vector<std::string> ZombieEatBlacklist;
	std::vector<std::string> ZombieBurrowAttackBlacklist;
};

// Plant
class PlantSnapPea : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSnapPea, PlantFramework, RtClass);
	virtual ~PlantSnapPea();

	bool CanBeShoveled() override;
	bool CanBeTargeted() override;
	bool IsInvincible() const override;

	void CancelPlantfood() override;

	void onPlantfoodEnded() override;

	void OnZombieEaten(RtWeakPtr<ZombieParticle> i_eatenZombieHead);
	void OnBurrowAttackEnded(BurrowAttackEffectPtr burrow);
	bool IsZombieBlacklistedForEating(ZombiePtr i_zombie);

protected:
	enum SnapPeaState
	{
		SNAPPEASTATE_IDLE,
		SNAPPEASTATE_ARMED,
		SNAPPEASTATE_ATTACKING,
		SNAPPEASTATE_CHEWING,
	};

	void Initialize() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void UpdateActions() override;
    bool CanTargetGrid(const int i_gridX, const int i_gridY) override;
	void onAnimStoppedCallback(const std::string& i_anim) override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	void onLevelEnd();
	void onGameWon();

private:
	ZombiePtr findZombieToEat();
	bool canEatZombie(const ZombiePtr& i_potentialZombie);
	void targetZombie(ZombiePtr i_zombie);
	Projectile* fireZombieHead();
	bool isZombieBlacklisted(ZombiePtr i_zombie, std::vector<std::string>& i_blacklist);
	void Level5Attack();

	std::vector<RtWeakPtr<ZombieParticle>> m_eatenZombieHeads;
	std::vector<BurrowAttackEffectPtr> m_deployedAttacks;
	std::vector<std::string> m_zombieEatBlacklist;
	std::vector<std::string> m_zombieBurrowAttackBlacklist;
	float m_timeUntilNextAttack;
	float m_plantfoodEndTime;
	int m_state;

};

class PlantAnimRig_SnapPea : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_SnapPea, PlantAnimRig, RtClass);
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	bool PlayBurrowStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayBurrowIdle();
	bool PlayBurrowReturnChewing(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayBurrowReturnIdle(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayChewingIdle();

protected:
	void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;

private:
	std::string getPlantFoodOnAnimName() override { return "head_fire_pf_start"; }
	std::string getPlantFoodMainAnimName() override { return "head_fire_pf_loop"; }
	std::string getPlantFoodOffAnimName() override { return "head_fire_pf_end"; }
};

class EffectObject_BurrowAttackProps : public EffectObjectPropertySheet
{
public:
RT_CLASS_DEFINE(EffectObject_BurrowAttackProps, EffectObjectPropertySheet, RtClass);

	SexyVector2 AttackSpawnOffset;
};

class EffectObject_BurrowAttack : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_BurrowAttack, EffectObject, RtClass);

	typedef RtReflectionDelegate<Delegate1<ZombieTypePtr>> OnZombieEaten;
	typedef RtReflectionDelegate<Delegate1<BurrowAttackEffectPtr>> OnBurrowAttackEnded;

	void SetOwner(PlantPtr i_owner);
	void SetTargetZombie(ZombiePtr i_targetZombie);
	void AttackTargetZombie();

protected:
	void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void onAnimStopped(const std::string &i_animLabel) override;

private:
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	std::string determineAttackAnimation();
	void fireProjectiles();
	void setActiveCostume() const;

	PlantPtr m_owner;
	ZombiePtr m_targetZombie;
	float m_zPosition;
	bool m_isZombieBlacklisted;
};

#endif //__PLANT_SNAPPEA_H__
