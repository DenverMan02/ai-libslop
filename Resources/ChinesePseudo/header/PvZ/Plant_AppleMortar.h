//
//  Plant_AppleMortar.hpp
//  PlantsVersusZombies2
//
//  Created by Kobylarek, Alexander on 6/17/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_AppleMortar_h
#define Plant_AppleMortar_h

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "ComponentWarmingRadius.h"

class AppleMortarProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(AppleMortarProjectileProps, ProjectilePropertySheet, RtClass);
	
	AppleMortarProjectileProps()
	:StunDuration(0.0f)
	{}
	
	float StunDuration;
};

class AppleMortarProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(AppleMortarProjectile, Projectile, RtClass);
	
    bool isPoison = false;
    
protected:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void onSplashDamageHitEntity(BoardEntity *i_hitEntity)override;
	
private:
	void hitZombie(BoardEntity *i_hitEntity);
	
	bool shouldStun(BoardEntity* i_impactedEntity);
	void stunZombie(BoardEntity* i_impactedEntity);
};

class AppleMortarProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(AppleMortarProps, PlantPropertySheet, RtClass);
	
	AppleMortarProps()
	{
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
	}
	
	// Projectile properties
    float PoisonTime = 6;
    float PoisonDmg = 1;
    float FireChance1 = 0.25f;
    float FireChance2 = 0.5f;
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

class PlantAppleMortar : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantAppleMortar, PlantFramework, RtClass);
	
    virtual void	Initialize() override;
    
	Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	bool CanApplyPlantfood() override;
    void DoSpecial(int i_extraParam = 0) override;
    int  getPlantActionIdx();
    int  getPFPlantActionIdx();
    void PlayAttackAnimation2();
    void PlayAttackAnimation() override;
protected:
	BoardEntityPtr getTargetInRow(int rowOffset, PlantWeapon i_plantWeapon);
	void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	void launchSpecialProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
	std::multimap<int, Point> getPFTargetLocs();
    
	float m_boostSkill = 0;
    bool m_bWalkFire = false;
    bool m_bWalkFireStep = false;
};


class PlantAnimRig_AppleMortar : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_AppleMortar, PlantAnimRig, RtClass);
    
    PlantAnimRig_AppleMortar() {};
protected:
    virtual std::string getIdleAnimationName() override;
};


#endif /* Plant_AppleMortar_h */
