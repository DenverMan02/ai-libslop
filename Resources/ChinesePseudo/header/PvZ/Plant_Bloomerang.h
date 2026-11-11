//
//  Plant_Bloomerang.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Bloomerang_h
#define PlantsVersusZombies2_Plant_Bloomerang_h

#include "PlantFramework.h"
#include "Projectile.h"

class BloomerangProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BloomerangProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;

	void SetBoundaryPosition(const SexyVector2& i_startingPosition, const SexyVector2& i_boundaryPosition);
	void SetTargets(const SexyVector2 &i_startingPosition, const SexyVector2 &i_target);
	void SetBaseVelocity(const SexyVector3 &i_velocity);
	void SetSlowdown(float i_radius, float i_minVelocityPercentage);
	void SetPauseDuration(float i_duration, bool i_stunsZombies);
	void SetOutgoingHitCount(int i_hitCount);   


protected:
	virtual void onInitialized() override;
	virtual void onUpdate(pvztime_t i_dt) override;
	void onDeflection(class BoardEntity* i_deflector) override;
private:
	bool m_turnedAround;
	std::vector<BoardEntityPtr> m_hitEntities;
	std::vector<BoardEntityPtr> m_forbiddenEntities;

	SexyVector2 m_boundaryPosition;
	SexyVector2 m_targetPosition;
	SexyVector2 m_startingPosition;
	SexyVector3 m_baseVelocity;
	
	pvztime_t m_pauseEndTime;
	
	int m_maxHits;
	int m_currentHitCount;
	float m_slowdownRadius;
	float m_minVelocityPercentage;
	float m_pauseDuration;
	bool m_pauseStunsZombies;
    bool m_deflected;
};

class PlantBloomerang : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBloomerang, PlantFramework, RtClass);

	virtual void Initialize() override;
	
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;

	virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
	void OnProjectileReturned(BloomerangProjectile* i_projectile);

	virtual void onKilled(bool i_instantKill) override;
    virtual float GetRefundSunAmount() override;
    
    virtual bool 		OverrideProjectileCollision(class Projectile* i_projectile) override;
private:
	Projectile *fireBoomerang(const SexyVector2 &i_targetPoint, const SexyVector3 &i_direction, bool i_fromPlantfood);
	pvztime_t m_nextPlantfoodRoundTime;
	int m_plantfoodRounds;
	
	bool m_preventReturnAnimation;
    
};

class PlantTypeBloomerang : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeBloomerang, PlantType, RtClass);
    virtual int GetCost(PlantAvatarType i_avatarType) const override;
    int GetCost(int count, PlantAvatarType i_avatarType = E_AVATAR_ILLEGAL) const;
    int GetPlantCount() const;
};

#endif
