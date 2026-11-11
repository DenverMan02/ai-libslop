/*
 * Plant_Parsnip.h
 *
 *  Created on: 2017-10-12
 *      Author: Administrator
 */

#ifndef PLANT_PARSNIP_H_
#define PLANT_PARSNIP_H_

#include <stdio.h>
#include "MeleePlantTargeter.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"

class GridItem;
class IdleAnimationSelector;

enum ParsnipState
{
	PARSNIPSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
	PARSNIPSTATE_ATTACKING,
	PARSNIPSTATE_FIRING,
	PARSNIPSTATE_PLANTFOOD,
	PARSNIPSTATE_STATE_FIRING,
	PARSNIPSTATE_STATE_FIRING_DURATION
};

enum ParsnipAnimation
{
	PARSNIPANIM_DROP,
	PARSNIPANIM_POP
};

enum PlantAnimRigState_Parsnip
{
	PLANTANIM_PARSNIP_FIRING = PLANTANIM_USERDEFINED,
	PLANTANIM_PARSNIP_ULTRA_FIRING
};

#pragma mark
class ParsnipProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ParsnipProps, PlantPropertySheet, RtClass);

	ParsnipProps()
	: MegaPunchRate(0.5f)
	, ImprovedMegaPunchBonus(1.0f)
	, UltraProjectileRate(0.5f)
	, BoomerangSlowdownRadius(150.0f)
	, BoomerangMinSpeedPercentage(0.1f)
	{
		// Do nothing.
	}

	float MegaPunchRate;
	float ImprovedMegaPunchBonus;
	float UltraProjectileRate;
	float BoomerangSlowdownRadius;
	float BoomerangMinSpeedPercentage;
};

class ParsnipUltraProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ParsnipUltraProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;

	void SetBoundaryPosition(const SexyVector2& i_startingPosition, const SexyVector2& i_boundaryPosition);
	void SetBaseVelocity(const SexyVector3 &i_velocity);
	void SetSlowdown(float i_radius, float i_minVelocityPercentage);
	virtual void onDestroy() override;

protected:
	virtual void onInitialized() override;
	virtual void onUpdate(pvztime_t i_dt) override;
	void onDeflection(class BoardEntity* i_deflector) override;
private:
	bool m_turnedAround;

	SexyVector2 m_boundaryPosition;
	SexyVector2 m_targetPosition;
	SexyVector2 m_startingPosition;
	SexyVector3 m_baseVelocity;

	float m_slowdownRadius;
	float m_minVelocityPercentage;
    bool m_deflected;
    bool m_normalDestroyed;
    std::vector<BoardEntityPtr> m_normalHitEntities;
    bool m_waitForReturn;

    void OnTurnAroundAnimDone(const std::string &i_animName);
};

class PlantAnimRig_Parsnip : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Parsnip, PlantAnimRig, RtClass);

	bool PlayIdleLooped() override;
	bool PlayPunchAttack(bool i_special, MeleePlantTargeter::TargetDirection i_attackType, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayAnimation(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped, ParsnipAnimation i_anim);

	void SetPopAnimCommandDelegate(PopAnimCommandDelegate i_onPopAnimCommand);

	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	int GetPlantfoodLeftCount() { return m_plantFoodPlayCount; }
	//virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	void PlayUltraAttack();

protected:
	std::string getPlantFoodOnAnimName() override { return "drop"; }
	std::string getPlantFoodMainAnimName() override;
	std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }
};

class PlantParsnip : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantParsnip, PlantFramework, RtClass);

	void Initialize() override;

	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	void Trigger();
	void Punch();
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;

	bool IsInvincible() const override;

	DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;

	int	GetPlantFoodPlayCount() override;

	void OnProjectileReturned(ParsnipUltraProjectile* i_projectile);
	Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	bool OverrideProjectileCollision(class Projectile* i_projectile) override;
	ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	void PlayAttackAnimation() override;
	void onSleeped(bool sleeped) override;

private:

	bool canAutoTrigger() const;
	void shootParsnip();
	void shootMegaParsnip();
	void setToIdle();

	void fireProjectileCallback(pvztime_t i_atTime);

	void findTargetsAndPlayAttackAnim();
	void onAnimStoppedCallback(const std::string& i_anim) override;

	DamageInfo getDamage(PlantWeapon i_plantWeapon);

	void attack();
	bool isReadyToFire();
	void OnProjectileDestroyed(ParsnipUltraProjectile* i_projectile);
	void setState(int i_newState);
	Projectile *fireBoomerang(const SexyVector2 &i_targetPoint, const SexyVector3 &i_direction);
	void OnReturnedAnimDone(const std::string &i_animName);

	// Serialized
	pvztime_t m_plantfoodDamageEndTime;
	MeleePlantTargeter::TargetDirection m_attackDirection;
	bool m_usingSpecialPunch;
	RtWeakPtr<ParsnipUltraProjectile> m_currentProjectile;
	bool m_projectileReturned;
	bool m_preventReturnAnimation;
};

class ParsnipProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ParsnipProjectile, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	void StartAnimation(bool i_isInPlantfoodState);
	bool ShouldClipWithWater() const override { return true; }
	void SetDamageRatio(float i_ratio) { m_damageRatio = i_ratio; }

protected:

//private:
	void onProjectileInitialized() override;
	void onUpdate(pvztime_t i_dt) override;

	void onAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	virtual void chomp(void);
	virtual void playAnimation();

	pvztime_t m_nextChompTime;
	bool m_isInPlantFoodState;

	AnimHandle m_animHandle;
	float m_damageRatio;
};

class ParsnipAvatarProjectile : public ParsnipProjectile
{
public:
	RT_CLASS_DEFINE(ParsnipAvatarProjectile, ParsnipProjectile, RtClass);
protected:
	void playAnimation() override;
	void chomp(void) override;
};

class ParsnipProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ParsnipProjectileProps, ProjectilePropertySheet, RtClass);

	ParsnipProjectileProps()
	: ChompsPerSecond(1.0f)
	, DamagePerChomp(100.0f)
	{
		// Do nothing.
	}

	float ChompsPerSecond;
	float DamagePerChomp;
};

namespace Message
{
    void ParsnipProjectileDestoryed(ParsnipUltraProjectile* i_projectile);
};

#endif /* PLANT_PARSNIP_H_ */
