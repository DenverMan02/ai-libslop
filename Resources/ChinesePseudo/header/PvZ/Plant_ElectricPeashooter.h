/*
 * Plant_ElectricPeashooter.h
 *
 *  Created on: 2018-1-17
 *      Author: Administrator
 */

#ifndef PLANT_ELECTRICPEASHOOTER_H_
#define PLANT_ELECTRICPEASHOOTER_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GridItemAnimation.h"

class Zombie;

class ElectricBoltEffect : public BoardEntity
{
public:
	RT_CLASS_DEFINE(ElectricBoltEffect, BoardEntity, RtClass);

	ElectricBoltEffect();
	~ElectricBoltEffect();

	void SetupEffect(std::string i_pamName, std::string i_animName, float i_activeLength);
	void SetActive(RtWeakPtr<RealObject> i_target, RtWeakPtr<RealObject> i_source, const std::string& i_hitLabel);

protected:
	void onUpdate() override;

private:

	RtWeakPtr<Effect_PopAnim> m_effect;
	RtWeakPtr<RealObject> m_target;
	RtWeakPtr<RealObject> m_source;

	bool m_active;
	float m_activeLength;
	pvztime_t m_activeTime;
};

class ElectricPeaProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ElectricPeaProjectile, Projectile, RtClass);
	virtual ~ElectricPeaProjectile();

	void SetProjectileData(float i_boltFrequency, int i_maxBoltCount, float i_boltRadius,  float i_boltDamage);
	bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
	void onUpdate(pvztime_t i_dt) override;

private:
	void spawnBolts();

	std::vector<RtWeakPtr<ElectricBoltEffect> > m_boltEffects;
	float m_boltRadius;

	float m_boltFrequency;
	pvztime_t m_lastBoltTime;
	float m_boltDamage;

	std::vector<BoardEntityPtr> m_targetsAlreadyHit;
};

class ElectricPeaAdvancedProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ElectricPeaAdvancedProjectileProps, ProjectilePropertySheet, RtClass);

	ElectricPeaAdvancedProjectileProps()
	{
		StunDuration = 1.0f;
	}

	float StunDuration;
};

class ElectricPeaAdvancedProjectile : public ElectricPeaProjectile
{
public:
	RT_CLASS_DEFINE(ElectricPeaAdvancedProjectile, ElectricPeaProjectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
private:
	bool shouldStuck(Zombie* i_zombie);
};

class ElectricPeaPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ElectricPeaPlantfoodProjectile, Projectile, RtClass);
	virtual ~ElectricPeaPlantfoodProjectile() {}

	void SetProjectileData(ProjectilePropertySheetPtr i_spawnedProjectilePropsPtr, int i_projectileSpawnCount, float i_projectileSpawnXVelocityOverride, float i_projectileSpawnDamageOverride);
	bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
	void onUpdate(pvztime_t i_dt) override {}
	virtual void CreateSubProjectile(BoardEntity* i_entity);

	ProjectilePropertySheetPtr m_spawnedProjectilePropsPtr;
	int m_projectileSpawnCount;
	float m_projectileSpawnXVelocityOverride;
	float m_projectileSpawnDamageOverride;
};

class ElectricPeaAvatarProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ElectricPeaAvatarProjectileProps, ProjectilePropertySheet, RtClass);

	ElectricPeaAvatarProjectileProps()
	{
		StunDuration = 2.0f;
		StunDamage = 100.0f;
	}

	float StunDuration;
	float StunDamage;
};

class ElectricPeaAvatarProjectile : public ElectricPeaPlantfoodProjectile
{
public:
	RT_CLASS_DEFINE(ElectricPeaAvatarProjectile, ElectricPeaPlantfoodProjectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	bool shouldStun(Zombie* i_zombie);
	void stunZombie(BoardEntity* i_impactedEntity);

protected:
	void CreateSubProjectile(BoardEntity* i_entity) override;
};

class ElectricPeaPlantfoodSubProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ElectricPeaPlantfoodSubProps, ProjectilePropertySheet, RtClass);

	ElectricPeaPlantfoodSubProps()
	{
		SlowDownPercentage = 0.2f;
		SlowDownTime = 0.5f;
	}

	float SlowDownPercentage;
	float SlowDownTime;
};

class ElectricPeaPlantfoodSubProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ElectricPeaPlantfoodSubProjectile, Projectile, RtClass);
	virtual ~ElectricPeaPlantfoodSubProjectile() {}

	void onUpdate(pvztime_t i_dt) override;

	void SetProjectileData(BoardEntityPtr i_ignoreTarget);
	bool OnCollideEntity(BoardEntity* i_entity) override;

protected:

	BoardEntityPtr m_ignoreTarget;
	SexyVector3 m_initialVelocity;
	SexyVector3 m_finalVelocity;
	float m_tweenAmount;
};

class ElectricPeashooterProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ElectricPeashooterProps, PlantPropertySheet, RtClass);

	ElectricPeashooterProps()
	{
		BoltFrequency = 2.0f;
		BoltCount = 3;
		BoltRange = 2.0f;
		BoltDamage = 1.0f;

		PFProjectileSpawnCount = 4;
		PFSubProjectileSpawnCount = 4;

		Lvl5Rate = 1.0f;
		AvatarExtraCount = 2;
		PlasmaRate = 1.0f;
		ImprovedPlasmaBonus = 1.0f;
	}

	float BoltFrequency;
	int BoltCount;
	float BoltRange;
	float BoltDamage;

	int PFProjectileSpawnCount;
	int PFSubProjectileSpawnCount;
	float Lvl5Rate;
	int AvatarExtraCount;
	float PlasmaRate;
	float ImprovedPlasmaBonus;
};

class PlantElectricPeashooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantElectricPeashooter, PlantFramework, RtClass);

	bool			CanApplyPlantfood() override;
	Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void			DoSpecial(int i_extraParam = 0) override;

private:
	Projectile* launchElectricBall();
};

enum GridItemElectricStromState
{
    PVZ_BEGIN_ENUM(ELECTRICSTATE_),
    ELECTRICSTATE_UNKNOWN,
    ELECTRICSTATE_RESETTING,
    ELECTRICSTATE_IDLE,
    ELECTRICSTATE_DEAD,
    PVZ_END_ENUM(ELECTRICSTATE_)
};

class GridItemElectricStrom : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemElectricStrom, GridItemAnimation, RtClass);

    GridItemElectricStrom();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(ELECTRICSTATE_IDLE); }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemElectricStromState i_state);
    void tryAbsorbZombies();

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onResetFinished(const std::string &i_animName);
    void onDeadFinished(const std::string &i_animName);
    void onZombieLanding(Zombie *i_zombie);

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    GridItemElectricStromState m_state;
};

class GridItemElectricStromProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemElectricStromProps, GridItemAnimationProps, RtClass);
    GridItemElectricStromProps()
    : Lifetime(1.0)
    , EffectRectRight(1)
    , EffectRectLeft(1)
    , EffectRectTop(1)
    , EffectRectBottom(1)
    , ElectricDamage(0.0f)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    pvztime_t Lifetime;
    std::vector<std::string> ZombieBlacklist;
    float ElectricDamage;
};

class ElectricBallProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ElectricBallProps, ProjectilePropertySheet, RtClass);

	ElectricBallProps()
	{
		StromRate = 1.0f;
		StormItemName = "storm";
	}

	float StromRate;
	std::string StormItemName;
};

class ElectricBall : public Projectile
{
public:
	RT_CLASS_DEFINE(ElectricBall, Projectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

#endif /* PLANT_ELECTRICPEASHOOTER_H_ */
