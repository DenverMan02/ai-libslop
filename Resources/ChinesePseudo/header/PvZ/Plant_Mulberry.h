/*
 * Plant_Mulberry.h
 *
 *  Created on: 2017-12-28
 *      Author: Administrator
 */

#ifndef PLANT_MULBERRY_H_
#define PLANT_MULBERRY_H_

#include <stdio.h>
#include "MeleePlantTargeter.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"

class MulberryProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(MulberryProps, PlantPropertySheet, RtClass);

	MulberryProps()
	: SplitGrenadeRate(0.5f)
	, ImprovedGrenadeBonus(1.0f)
	, Level5AttackRate(0.6f)
	, PlasmaSection(0.2f)
	, FlashSection(0.6f)
	, NormalProjectileTimeOfFlight(1.2f)
	, NormalProjectileLobHeight(350.f)
	, PlantfoodProjectileLobHeight(500.f)
	, PlantfoodProjectileTimeOfFlight(2.0f)
	{
		// Do nothing.
	}

	float SplitGrenadeRate;
	float ImprovedGrenadeBonus;
	float Level5AttackRate;
	float PlasmaSection;
	float FlashSection;
	// Projectile properties
	float NormalProjectileTimeOfFlight;
	float NormalProjectileLobHeight;
	float PlantfoodProjectileTimeOfFlight;
	float PlantfoodProjectileLobHeight;
};

class PlantMulberry : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMulberry, PlantFramework, RtClass);

	void Initialize() override;
	Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	Projectile* shootBerry(bool i_advanced);
	Projectile* launchSuperGrenade();
	Projectile* launchFlashGrenade();
	Projectile* launchGasGrenade();
	virtual void DoSpecial(int i_extraParam) override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void PlayAttackAnimation() override;

protected:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, PlantWeapon i_plantWeapon);
	void DoNonSuperAttack();

	std::vector<BoardEntityPtr> m_targettedBoardEntities;
	int m_timesSpecialFired;
};

class MulberryProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(MulberryProjectile, Projectile, RtClass);
	void StartAnimation();
	void SetAdvanced(bool i_advanced) { m_advanced = i_advanced; }
protected:
	void onProjectileInitialized() override;
	void onAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	virtual void playAnimation(bool i_advanced);
private:
	bool m_advanced;
};

class MulberryPlasmaGrenadeProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(MulberryPlasmaGrenadeProps, ProjectilePropertySheet, RtClass);

	MulberryPlasmaGrenadeProps()
	{
		MinTossAngle = 25.0f;
		MaxTossAngle = 55.0f;
		TossSpeed = 600.0f;
		TossSpinRadiansPerSecond = -500.0f;
		FlickRate = 0.8f;
	}

	float MinTossAngle;
	float MaxTossAngle;
	float TossSpeed;
	float TossSpinRadiansPerSecond;
	float FlickRate;
};

class MulberryPlasmaGrenade : public Projectile
{
public:
	RT_CLASS_DEFINE(MulberryPlasmaGrenade, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	void hitNormalZombie(Zombie* i_zombie);
	void playHitEffect(BoardEntity* i_thitOwner, bool i_playSpark);
};

class MulberryFlashGrenadeProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(MulberryFlashGrenadeProps, ProjectilePropertySheet, RtClass);

	MulberryFlashGrenadeProps()
	{
		StunDuration = 2.0f;
	}

	float StunDuration;
};

class MulberryFlashGrenade : public Projectile
{
public:
	RT_CLASS_DEFINE(MulberryFlashGrenade, Projectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	bool shouldStun(Zombie* i_zombie);
	void stunZombie(BoardEntity* i_impactedEntity);
};

class MulberryGasGrenadeProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(MulberryGasGrenadeProps, ProjectilePropertySheet, RtClass);

	MulberryGasGrenadeProps()
	{
		PoisonDuration = 10.0f;
		PoisonDamage = 100.0f;
	}

	float PoisonDuration;
	float PoisonDamage;
};

class MulberryGasGrenade : public Projectile
{
public:
	RT_CLASS_DEFINE(MulberryGasGrenade, Projectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	bool shouldPoison(Zombie* i_zombie);
	void poisonZombie(BoardEntity* i_impactedEntity);
};

class PlantAnimRig_Mulberry : public PlantAnimRig
{
public:
	enum AttackType
	{
		NORMAL_ATTACK,
		ADVANCED_ATTACK,
		SUPER_ATTACK_PLASMA,
		SUPER_ATTACK_FLASH,
		SUPER_ATTACK_GAS
	};
	RT_CLASS_DEFINE(PlantAnimRig_Mulberry, PlantAnimRig, RtClass);

	std::string getAttackAnimationName() override;
	std::string getPlantFoodMainAnimName() override;
	void SetAttackType(AttackType i_type) { m_attackType = i_type; }
	AttackType GetAttackType() { return m_attackType; }
private:
	AttackType m_attackType;
};


#endif /* PLANT_MULBERRY_H_ */
