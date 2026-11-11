/*
 * Plant_Rafflesia.h
 *
 *  Created on: 2015-3-18
 *      Author: jianglc
 */

#ifndef PLANT_RAFFLESIA_H_
#define PLANT_RAFFLESIA_H_

#include "PlantFramework.h"
#include "GameSubSystem.h"
#include "Projectile.h"

class RafflesiaSpecialProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(RafflesiaSpecialProjectile, Projectile, RtClass);

	void SetTargetLoc(const SexyVector3& i_targetLoc) { m_targetPosition = i_targetLoc; }
	const SexyVector3 & GetTargetLoc() const { return m_targetPosition; }
	void SetTarget(BoardEntityPtr i_target) { m_target = i_target; }
	void SetFlightTime(const float i_time) { m_flightTime = i_time; }
	void SetFlightHeight(const float i_height) { m_flightHeight = i_height; }
	void LaunchToTarget();

protected:
	virtual void onInitialized() override;
	virtual void onProjectileInitialized() override;
	virtual void onUpdate(pvztime_t i_dt) override;
private:
	SexyVector3 m_targetPosition;
	BoardEntityPtr m_target;
	float m_flightTime;
	float m_flightHeight;

	void onFallDown(const std::string &i_animName);
};

class RafflesiaAvatarProjectile : public RafflesiaSpecialProjectile
{
public:
	RT_CLASS_DEFINE(RafflesiaAvatarProjectile, RafflesiaSpecialProjectile, RtClass);

    virtual bool OnCollideGround() override;
};

class RafflesiaProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(RafflesiaProjectile, Projectile, RtClass);

	void SetTarget(BoardEntityPtr i_target) { m_target = i_target; }

protected:
	virtual void onProjectileInitialized() override;
	virtual void onUpdate(pvztime_t i_dt) override;
private:
	void findTarget();
	void onFallDown(const std::string &i_animName);
    BoardEntityPtr m_target;
};

class PlantRafflesia : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantRafflesia, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
//	virtual GridItemPtr FindTargetDamageableGridItem(int i_col, int i_row, PlantWeapon i_plantWeapon);

	virtual void ApplyPlantfood() override;
	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;

private:
    Projectile* normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);

    ZombiePtr FindTargetZombieForRow(PlantWeapon i_plantWeapon, int i_row);

    void addShot(float plantFoodFireTime, int& io_shot, const SexyVector3& i_point, BoardEntityPtr i_tarEntity, int i_num);

    void queueShot(pvztime_t i_launchTime, const SexyVector3& i_targetLocation, BoardEntityPtr i_tarEntity, int i_num);
};

class RafflesiaSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(RafflesiaSubSystem, GameSubSystem, RtClass);

	RafflesiaSubSystem();

	void QueueShot(PlantRafflesia* i_owner, pvztime_t i_launchTime, const SexyVector3& i_target, BoardEntityPtr i_tarEntity, int i_num);

	struct RafflesiaEntry
	{
		RafflesiaEntry() {}
		RafflesiaEntry(PlantRafflesia* i_owner, pvztime_t i_launchTime, const SexyVector3& i_target, BoardEntityPtr i_tarEntity, int i_num);

		PlantPtr Owner;
		RtWeakPtr<const RafflesiaProps> RafflesiaPropertySheet;
		pvztime_t LaunchTime;
		SexyVector3 Target;
		BoardEntityPtr TargetEntity;
		int	Number;
	};

	virtual void Update() override;

	void LaunchAllProjectiles();

private:
	void launch(const RafflesiaEntry& i_entry);

	std::vector<RafflesiaEntry> m_shots;
	std::vector<ProjectilePtr> m_projectiles;
};

#endif /* PLANT_RAFFLESIA_H_ */
