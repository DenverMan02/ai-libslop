//
//  Plant_StickybombRice
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/8/20
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef Plant_StickybombRice_h
#define Plant_StickybombRice_h

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "ModularBoardEntity.h"
#include "PlantPropertySheet.h"

enum StickybombState
{
	STICKYBOMB_PREINIT,
	STICKYBOMB_WAITING,
	STICKYBOMB_EXPLODE
};

class StickybombBomb : public ModularBoardEntity
{
public:
	RT_CLASS_DEFINE(StickybombBomb, ModularBoardEntity, RtClass);

	StickybombBomb();
	
	void IncrementBombCount(float i_damage, float i_timeToDetonate, float i_explodeRadius, float i_propagationMultiplier, float i_damageRate);
	void SetInstigator(RtWeakPtr<BoardEntity> i_instigator);
	void SetOwner(RtWeakPtr<Zombie> i_zombie) { m_ownerZombiePtr = i_zombie; }
	void SetAvatarEnable(bool i_flag);
	void TryTriggerCascade(int i_propagationCount);
	bool HasMaxBombs();
	void ExplodeImmediately();
	
protected:
	void onUpdate() override;
	void onZombieKilled(class Zombie* i_zombie, const DamageInfo* i_deathBlow);

private:
	void explode();
	void broadcastDamage();
	std::string getMainAnimForBombCount(int i_count);
	
	StickybombState m_state = STICKYBOMB_PREINIT;
	bool m_avatarEnable = false;
	int m_numberOfBombs = 0;
	int m_propagationCount = 0;
	float m_timeToDetonate = 0;
	float m_totalDamage = 0;
	float m_explodeRadius = 0;
	float m_propagationMultiplier = 0;
	float m_damageRate = 0;
	std::vector<std::string> m_plantFamilies;
	float m_resistancePiercingOverride = 0;
	RtWeakPtr<Zombie> m_ownerZombiePtr;
	RtWeakPtr<BoardEntity> m_instigator;
};

class StickybombRiceProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(StickybombRiceProjectile, Projectile, RtClass);
	
	void SetAvatarEnable(bool i_flag) { IsAvatar = i_flag; }
	void Initialize(float i_bombTimer, float i_bombExplodeRadius, float i_bombBaseDamage, float i_bombPropagationMultiplier) { CreatedBombTimer = i_bombTimer; CreatedBombExplodeRadius = i_bombExplodeRadius; CreatedBombBaseDamage = i_bombBaseDamage; CreatedBombPropagationMultiplier = i_bombPropagationMultiplier; }
	
protected:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void onSplashDamageHitEntity(BoardEntity *i_hitEntity)override;
	
private:
	void hitZombie(BoardEntity *i_hitEntity);
	
	bool IsAvatar = false;
	float CreatedBombTimer = 5;
	float CreatedBombExplodeRadius = 1;
	float CreatedBombBaseDamage = 100;
	float CreatedBombPropagationMultiplier = 0.1;
};

class StickybombRiceLV5Projectile : public Projectile
{
public:
	RT_CLASS_DEFINE(StickybombRiceLV5Projectile, Projectile, RtClass);

	void Initialize(float i_bombTimer, float i_bombExplodeRadius, float i_bombBaseDamage, float i_bombPropagationMultiplier) { CreatedBombTimer = i_bombTimer; CreatedBombExplodeRadius = i_bombExplodeRadius; CreatedBombBaseDamage = i_bombBaseDamage; CreatedBombPropagationMultiplier = i_bombPropagationMultiplier; }
    void setFlyTotalTime(float tTime, const SexyVector3& i_target, bool isOnfood, bool isAvatar);
    void onAnimStopped(const std::string &i_animName);
protected:
    virtual void onUpdate(pvztime_t i_dt) override;
    void doSplit();
    
    SexyVector3 m_targetVec;
    float  m_totalTime;
    float  m_flyTime;
    bool   m_isOnFood = false;
    bool   m_isAvatar = false;
    bool   m_needSplit   = false;
    bool   m_hasSplited  = false;

	float CreatedBombTimer = 5;
	float CreatedBombExplodeRadius = 1;
	float CreatedBombBaseDamage = 100;
	float CreatedBombPropagationMultiplier = 0.1;
};


class StickybombRiceProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(StickybombRiceProps, PlantPropertySheet, RtClass);
	
	// Projectile properties
	float ProjectileTimeOfFlight = 1.2f;
	float ProjectileLobHeight = 350.f;
	int ProjectileCount = 3;
	float Level5Rate = 0.2;
	
	float CreatedBombTimer = 5;
	float CreatedBombExplodeRadius = 1;
	float CreatedBombBaseDamage = 20;
	float CreatedBombPropagationMultiplier = 0.1;
	
	float PlantfoodCreatedBombTimer = 5;
	float PlantfoodCreatedBombExplodeRadius = 1;
	float PlantfoodCreatedBombBaseDamage = 50;
	float PlantfoodCreatedBombPropagationMultiplier = 0.1;
};

class PlantStickybombRice : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantStickybombRice, PlantFramework, RtClass);
	
	Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	bool CanApplyPlantfood() override;
	void DoSpecial(int i_extraParam = 0) override;

protected:
	BoardEntityPtr getTargetInRow(int rowOffset, PlantWeapon i_plantWeapon);
	void launchProjectileAt(Projectile *i_projectile, const Sexy::SexyVector3 &i_targetLoc, BoardEntityPtr i_targetZombie, float i_heightVariance, float i_timeOfFlightVariance);
	void launchLv5ProjectileAt(Projectile *i_projectile, const Sexy::SexyVector3 &i_targetLoc, BoardEntityPtr i_targetZombie, float i_heightVariance, float i_timeOfFlightVariance);
	void launchSpecialProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
	std::multimap<int, Point> getPFTargetLocs();
	
private:
	void findTargets(std::vector<BoardEntity*>& o_entities, PlantWeapon i_plantWeapon);
	Projectile* fireAtTarget(BoardEntity* i_target, PlantWeapon i_plantWeapon);
	bool isValidTarget(BoardEntity* i_target);
	bool isZombieFullOfBombs(Zombie* i_zombie);
	BoardEntity* getBestSingleTarget(PlantWeapon i_plantWeapon);
	void playAttackAnimation(bool i_faceRight);

};

class PlantAnimRig_StickybombRice : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_StickybombRice, PlantAnimRig, RtClass);

	void PlayLeftAttack();
	
protected:
	std::string getPlantFoodMainAnimName() override { return (m_bAvatar?"plantfood2_start":"plantfood_start"); }
	
};

#endif
