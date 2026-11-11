//
//  Plant_Gumnut
//  PlantsVersusZombies2
//
//  Created by Evelyn Moss on 11/27/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PLANT_GUMNUT_H__
#define __PLANT_GUMNUT_H__

#include "ClassBucketFilter.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Projectile.h"

class Zombie;

//Props
class GumnutProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GumnutProps, PlantPropertySheet, RtClass);
	
	GumnutProps()
    :   GumZombieType("gum")
	,	LV5GumZombieType("poison_gum")
	,	BaseGumHealth(4000)
	,	ZombieGumHealthPercent(100)
	,	PFZombiesGummed(5)
	,	PFAvatarZombiesGummed(8)
	,	ProjectileLobHeight(300)
	,	ProjectileTimeOfFlight(0.5)
	,	MAXHealth(100000)
    {}
	std::string GumZombieType;
	std::string LV5GumZombieType;
	float BaseGumHealth;
	float ZombieGumHealthPercent;
	int PFZombiesGummed;
	int PFAvatarZombiesGummed;
	float ProjectileLobHeight;
	float ProjectileTimeOfFlight;
	float MAXHealth;
	std::vector<std::string> GumBlacklist;
	
	ClassBucketFilter TargetPriorityBuckets;
};

class PlantGumnut : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantGumnut, PlantFramework, RtClass);

	void PostInitialize() override;
	void SetPopAnimDelegates(class PlantAnimRig* i_rig) override;
	
	bool CanApplyPlantfood() override;
	void CancelPlantfood() override;
	
	void UpdateActions() override;
	void DoSpecial(int i_extraParam = 0) override;
	
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	bool IsInvincible() const override;
	bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	
protected:
	void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heighVariance, float i_timeOfFlightVariance);
	void popGumCallback(pvztime_t i_atTime);
	int calcZombieTargetWeight(Zombie* i_zombie, PlantTargetParams& i_targetParams) override;
	bool isInBlackList(ZombiePtr i_zombie);
	
private:	
	void gumZombie(ZombiePtr i_zombie);
	float calcGumHitpoints(ZombiePtr i_zombie);
};

class GumnutPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(GumnutPlantfoodProjectile, Projectile, RtClass);
	
	GumnutPlantfoodProjectile()
    :   m_gumZombieType("gum")
	,	m_baseGumHealth(0)
	,	m_zombieGumHealthPercent(0)
	,	m_maxHealth(100000)
    {}
	
	virtual bool OnCollideGround() override;
	void InitializeGumValues(std::string i_gumType, float i_baseGumHealth, float i_zombieGumHealthPercent, float i_maxHealth) { m_gumZombieType = i_gumType; m_baseGumHealth = i_baseGumHealth; m_zombieGumHealthPercent = i_zombieGumHealthPercent; m_maxHealth = i_maxHealth; }
	
private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void gumZombie(ZombiePtr i_zombie);
	float calcGumHitpoints(ZombiePtr i_zombie);
	bool canAffectZombie(Zombie* i_zombie);
	bool isInBlackList(Zombie* i_zombie);
	
	std::string m_gumZombieType;
	float m_baseGumHealth;
	float m_zombieGumHealthPercent;
	float m_maxHealth;
};

#pragma mark - PlantAnimRig_Gumnut

class PlantAnimRig_Gumnut : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Gumnut, PlantAnimRig, RtClass);

private:
	std::string getPlantFoodMainAnimName() override;
};

#endif // __PLANT_GUMNUT_H__
