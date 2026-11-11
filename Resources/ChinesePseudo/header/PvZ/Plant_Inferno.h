/*
 * Plant_Inferno.h
 *
 *  Created on: 2021-12-7
 *      Author: admin
 */


#ifndef PLANT_INFERNO_H_
#define PLANT_INFERNO_H_


#include "ComponentDamageRadius.h"
#include "ComponentWarmingRadius.h"
#include "DamageInfo.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RestrictionSet.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "Zombie.h"
#include "ModularBoardEntity.h"
#include "ZombieTosser_SubSystem.h"


class InfernoTornado;

class PlantInferno : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantInferno, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void DoSpecial(int i_extraParam = 0) override;

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void setState(const uint i_state);
	Projectile* fireTornado();
	Projectile* firePFTornado();
	Projectile* fireAPFTornado();

private:
	enum State
	{
		STATE_FIRING = STATE_FRAMEWORK_BEGIN,
		STATE_PLANTFOOD_ATTACK,
	};

	RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
};

class InfernoProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(InfernoProps, PlantPropertySheet, RtClass);

	InfernoProps()
	: TornadoGridNum(3.0f)
	, PFTornadoGridNum(5.0f)
	, TornadoDuration(2.0f)
	, PFTornadoDuration(2.0f)
	, CycloneZombieCap(3)
	{}

	float TornadoGridNum;
	float PFTornadoGridNum;
	float TornadoDuration;
	float PFTornadoDuration;
	int CycloneZombieCap;
};

class PlantAnimRig_Inferno : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Inferno, PlantAnimRig, RtClass);

private:
    virtual	std::string getPlantFoodMainAnimName() override;
};

class InfernoProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(InfernoProjectileProps, ProjectilePropertySheet, RtClass);

	InfernoProjectileProps()
	: TimeBetweenDamagePulses(1.0f)
	{}

	float DamagePulseMultiple = 1;
	float TimeBetweenDamagePulses;
    ZombieRestrictionSet UnmovableZombies;
	GridItemRestrictionSet MeltableGridItems;

	float InitialExtraVelocityStart = 0;
	float InitialExtraVelocitySeconds = 0;
	CurveType InitialExtraVelocityCurve = CURVE_LINEAR;
};

class InfernoProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(InfernoProjectile, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_impactedEntity = NULL) override;
	virtual void SetTornadoDuration(float i_duration, bool i_startTimer = false);
	virtual void SetTornadoGridNum(float i_num);
	virtual bool CanPickUpZombie(Zombie* i_zombie);
	Sexy::SexyVector3 calcVelocity();
	virtual void registerForEvents() override;
	void SetTimeToExpire(float time){m_timeToExpire = time;}

protected:
	void onUpdate(pvztime_t i_dt) override;
	void onProjectileInitialized() override;
	void onDestroy() override;

	virtual void dropCarriedZombie();
	virtual void pickUpZombie(Zombie* i_zombie);
	virtual void moveZombie();
	virtual bool shouldDissipate();
	virtual void dissipateBackAnimation();
	virtual void doDamagePulse();
	void pulseDamageEntity(BoardEntity* i_entity);
	virtual void setUpBackAnimation();
	virtual void playDeathAnim();
	void moveThroughTime(pvztime_t i_dt) override;
	void onDeathAnimComplete(const std::string& i_animName);

	void setTornadoFull();
	void setNextPulseTime();
	void setExpireTime();
	bool readyToExpire();

	void playImpactEffect(BoardEntity* i_impactedEntity);
	float calcLerpVelocity();
	float getTornadoDuration() { return m_tornadoDuration; }
	float getElapsed() { return (PVZ_T() - m_startTime) / m_tornadoDuration; }
	void OnZombieMoveUpDownFinish(Zombie* zombie);

protected:
	float m_tornadoDuration;
	float m_tornadoGridNum;

private:
	RtWeakPtr<Zombie> m_carriedZombie;
	std::vector<RtWeakPtr<BoardEntity>> m_targetsAlreadyHit;
	bool m_hasPickedUpZombie;
	pvztime_t m_timeToExpire;
	pvztime_t m_timeOfNextDamagePulse;
	pvztime_t m_startTime;
	bool m_isDying;
	pvztime_t m_dethTime;
};

class InfernoPFProjectileProps : public InfernoProjectileProps
{
public:
	RT_CLASS_DEFINE(InfernoPFProjectileProps, InfernoProjectileProps, RtClass);

	InfernoPFProjectileProps()
	: LaneChangeTime(0.6)
	, TimeBetweenLaneChanges(5.0)
	, CyclonePullSquareRange(1.5)
	, ExplodeDamage(0)
	{}

	float LaneChangeTime;
	float TimeBetweenLaneChanges;
	float CyclonePullSquareRange;
	float ExplodeDamage;
};

class InfernoPFProjectile : public InfernoProjectile
{
public:
	RT_CLASS_DEFINE(InfernoPFProjectile, InfernoProjectile, RtClass);

	void onUpdate(pvztime_t i_dt) override;

	void SetMaxCarriedZombies(int i_max);

	std::vector<RtWeakPtr<Zombie>> getCarriedZombies() { return m_carriedZombies; }
	RtWeakPtr<InfernoPFProjectile> getBrotherProj() { return m_brotherProj; }
	int getMaxCarriedZombies() { return m_maxCarriedZombies; }
	SexyVector3 getRotateCenterPosition() { return m_rotateCenterPosition; }
	virtual void SetTornadoGridNum(float i_num) { m_tornadoGridNum = i_num - 1; }

	void setRotateCenterPosition();
	void setTornadoValues(float i_startRad, RtWeakPtr<InfernoPFProjectile> i_brotherProj);
	void affectBrotherProj(bool i_flg);
	void setHasGargantuar() { m_hasGargantuar = true; }
	bool hasGargantuar() { return m_hasGargantuar; }
	void setFlg(int i_flg) { m_flg = i_flg; }
	void setHasDroped() { m_hasDroped = true; }

protected:
	void onProjectileInitialized() override;
	void onDestroy() override;

	void moveThroughTime(pvztime_t i_dt) override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);

	virtual void pickUpZombie(Zombie* i_zombie) override;
	void moveZombie() override;
	virtual void dropCarriedZombie() override;
	bool shouldDissipate() override;
	void doDamagePulse() override;
	void setUpBackAnimation() override;
	void playDeathAnim() override;
	void dissipateBackAnimation() override;
	Rect calcPullRect();

private:
	std::vector<RtWeakPtr<Zombie>> m_carriedZombies;
	std::vector<RtWeakPtr<Zombie>> m_explodeZombies;

	RtWeakPtr<InfernoPFProjectile> m_brotherProj;

	int m_maxCarriedZombies;

	float m_currentRad;
	float m_startAngularVelocity;
	float m_angularVelocity;
	float m_startRotateRadius;
	float m_rotateRadius;
	bool m_hasGargantuar;
	SexyVector3 m_rotateCenterPosition;
	int m_flg;
	bool m_hasDroped;


};


class InfernoAPFProjectileProps : public InfernoPFProjectileProps
{
public:
	RT_CLASS_DEFINE(InfernoAPFProjectileProps, InfernoPFProjectileProps, RtClass);

};


class InfernoAPFProjectile : public InfernoPFProjectile
{
public:
	RT_CLASS_DEFINE(InfernoAPFProjectile, InfernoPFProjectile, RtClass);

	void setUpBackAnimation() override;
	void dissipateBackAnimation() override;
	void playDeathAnim() override;
	void dropCarriedZombie() override;


protected:
	void onProjectileInitialized();
	void moveThroughTime(pvztime_t i_dt) override;



private:
	bool m_isDying;


};


class InfernoSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(InfernoSubsystem, GameSubSystem, RtClass);

	void RegisterCyclone(InfernoPFProjectile* i_cyclone);
	void RegisterPull(InfernoPFProjectile* i_cyclone, const std::vector<Zombie*>& i_pulledZombies);

	void Update() override;

private:
	void clearDeadCyclones();
	bool isCycloneRegistered(InfernoPFProjectile* i_cyclone) const;
	bool canCyclonePull(InfernoPFProjectile* i_cyclone) const;
	InfernoPFProjectile* pickAttractor(Zombie* i_zombie, const std::vector<InfernoPFProjectile*> i_cyclones) const;

	std::vector<RtWeakPtr<InfernoPFProjectile>> m_cyclones;

	void moveZombieToCycloneLane(Zombie* i_zombie, InfernoPFProjectile* i_cyclone);

	std::map<Zombie*, std::vector<InfernoPFProjectile*>> m_zombieToCycloneMap;
};

#endif /* PLANT_INFERNO_H */
