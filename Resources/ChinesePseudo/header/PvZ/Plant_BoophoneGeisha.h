/*
 * Plant_BoophoneGeisha.h
 *
 *  Created on: 2021-3-15
 *      Author: admin
 */

#ifndef PLANT_BOOPHONEGEISHA_H_
#define PLANT_BOOPHONEGEISHA_H_

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "ActionSubSystem.h"
#include "Projectile.h"

class GeishaProjectile : public Projectile
{
public:
	enum GeishaProjectileTrajectory
	{
		E_HIGH,
		E_NORMAL,
		E_LOW
	};

	RT_CLASS_DEFINE(GeishaProjectile, Projectile, RtClass);

	GeishaProjectile(): slot(0), flightTime(0.f){}
	void InitTrajectory(GeishaProjectileTrajectory trajectory, const SexyVector3& i_pos);
	void SetPierce(bool i_pierce) { m_pierce = i_pierce; }

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void onUpdate(pvztime_t i_dt) override;

	void ReturnBack();
	void SetCanReturn(bool i_return) { m_canReturn = i_return; }
	virtual bool OnCollideRoof() override;

	uint32 slot;
	float flightTime;

protected:
	virtual void onFlyToTargetDone(BoardEntity * target);
	virtual void onFlyBackDone(BoardEntity * target);
	void onPlantDie(Plant* plant);

	void SetTrajectoryHigh();
	void SetTrajectoryNormal();
	void SetTrajectoryLow();

	void GetBackControllPoint(ccBezierConfig& i_config);
	bool ReachLastEnemy();
	virtual bool ShouldReturnBack();
	bool CheckEdge();

protected:
	SexyVector3 initPos;
	ccBezierConfig go;
	ccBezierConfig back;

	GeishaProjectileTrajectory m_type = E_HIGH;
	bool m_pierce = false;
	bool m_canReturn = true;
};

class GeishaSuperProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(GeishaSuperProjectileProps, ProjectilePropertySheet, RtClass);

	float BackStabMultiplier;
};

class GeishaSuperProjectile : public GeishaProjectile
{
public:
	RT_CLASS_DEFINE(GeishaSuperProjectile, GeishaProjectile, RtClass);

	void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
	std::string getImpactPam() override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

private:
	bool CanBackstab(BoardEntity * pImpactedEntity);

	bool m_isBackStab = false;
};

class GeishaPlantfoodProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(GeishaPlantfoodProjectileProps, ProjectilePropertySheet, RtClass);

	int DistanceGrids;
	float Duration;
	float SplitProjectileTimeOfFlight;
};

class GeishaPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(GeishaPlantfoodProjectile, Projectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void SetInitPos(const SexyVector3& i_pos) { m_initPos = i_pos; }
	const SexyVector3& GetInitPos() { return m_initPos; }
	void SetAvatar(bool i_avatar) { m_avatar = i_avatar; }

protected:
	virtual void createSplitProjectiles();

private:
	void knockbackEnemies(BoardEntity* i_impactedEntity);

	SexyVector3 m_initPos;
	bool m_avatar = false;
};

class GeishaPlantfoodSplitProjectile : public GeishaProjectile
{
public:
	RT_CLASS_DEFINE(GeishaPlantfoodSplitProjectile, GeishaProjectile, RtClass);

protected:
	void onFlyBackDone(BoardEntity * target) override;
};



class GeishaPropertySheet : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(GeishaPropertySheet, PlantPropertySheet, RtClass);

    GeishaPropertySheet() : Level2SkillRate(0.2f), Level3SkillRate(0.4f), Level4SkillRate(0.1f) {}

    float ProjectileTimeOfFlight;

    float Level2SkillRate;
    float Level3SkillRate;
    float Level4SkillRate;
    float Level5SkillRate;
};

class PlantBoophoneGeisha : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBoophoneGeisha, PlantFramework, RtClass);

	virtual void Initialize() override;

	virtual bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	void PlayAttackAnimation() override;
	void PlayProjectileBack();

	bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	virtual void DoSpecial(int i_extraParam = 0) override;

	void ResetProjectileSlot(uint32 slotIndex);
	void SetIsAttacking(bool i_attacking) { m_isAttacking = i_attacking; }

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	int m_attackCount;
	bool m_isAttacking;
};

class PlantAnimRig_BoophoneGeisha : public PlantAnimRig
{
public:

	RT_CLASS_DEFINE(PlantAnimRig_BoophoneGeisha, PlantAnimRig, RtClass);

	void SetIdleAnimation(const std::string& idle) { m_idle = idle; }

private:
    std::string getIdleAnimationName() { return m_idle; }
    //std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;

private:
    std::string m_idle = "idle";
};


#endif /* PLANT_BOOPHONEGEISHA_H_ */
