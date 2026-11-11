/*
 * Plant_Acorn.h
 *
 *  Created on: 2015-3-23
 *      Author: jianglc
 */

#ifndef PLANT_ACORN_H_
#define PLANT_ACORN_H_

#include "PlantFramework.h"
#include "Projectile.h"

enum AcornState
{
	ACORN_STATE_FIRING = STATE_FRAMEWORK_BEGIN,
	ACORN_STATE_FIRING_DURATION,
	ACORN_STATE_RECOVER_LOOP,
	ACORN_STATE_RECOVER_END
};

class AcornProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(AcornProjectile, Projectile, RtClass);

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
};

class PlantAcorn : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantAcorn, PlantFramework, RtClass);

	virtual void Initialize() override;

	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;

	virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	void OnProjectileReturned(AcornProjectile* i_projectile);

    virtual bool 		OverrideProjectileCollision(class Projectile* i_projectile) override;
    virtual ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    virtual void UpdateActions() override;
    virtual void PlayAttackAnimation() override;
//    virtual GridItemPtr FindTargetDamageableGridItem(int i_col, int i_row, PlantWeapon i_plantWeapon);
    void registerForEvents() override;
    void unregisterForEvents() override;
private:
	Projectile *fireBoomerang(const SexyVector2 &i_targetPoint, const SexyVector3 &i_direction);
	void setState(int i_newState);
	bool isReadyToFire();
	float GetProjectileCooldown();
	void OnReturnedAnimDone(const std::string &i_animName);
	void OnProjectileDestroyed(AcornProjectile* i_projectile);

	bool m_preventReturnAnimation;
	pvztime_t   m_nextLaserDamageTime;
	std::vector<RtWeakPtr<BoardEntity> > m_hitEntities;
	bool m_hasHittedUpRow;
	bool m_hasHittedDownRow;
	RtWeakPtr<AcornProjectile> m_currentProjectile;
	bool m_projectileReturned;

};

class PlantAnimRig_Acorn : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Acorn, PlantAnimRig, RtClass);

	virtual bool playPlantFoodMain() override;
};

namespace Message
{
    void AcornProjectileDestoryed(AcornProjectile* i_projectile);
};


#endif /* PLANT_ACORN_H_ */
