//
//  Plant_BloomingHearts.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 12/1/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_BloomingHearts__
#define __PlantsVersusZombies2__Plant_BloomingHearts__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"

class BloomingHeartsProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BloomingHeartsProps, PlantPropertySheet, RtClass);
	
	BloomingHeartsProps()
	{
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
		PlantfoodProjectilesToFire = 4;
	}
	
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
	int PlantfoodProjectilesToFire;
};

class PlantBloomingHearts : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBloomingHearts, PlantFramework, RtClass);
	
	bool CanApplyPlantfood() override;
	void DoSpecial(int i_extraParam = 0) override;
	Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void ApplyPlantfood() override;
	ZombiePtr FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams, Rect i_attackRect) override;
	
protected:
	void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	
private:
	void launchSpecialProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
	
	std::vector<BoardEntityPtr> m_targetedBoardEntities;
	int m_timesSpecialFired;
};

class PlantAnimRig_BloomingHearts : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_BloomingHearts, PlantAnimRig, RtClass) {}
};

class BloomingHeartsProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BloomingHeartsProjectile, Projectile, RtClass);
	
	BloomingHeartsProjectile()
	{
		m_currentHitCount = 0.f;
	}
	
protected:
	void damageEntity(class BoardEntity* i_entity) override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	
private:
	std::string calcAnimForStacks(float i_stackCount);
	
	float m_currentHitCount;
};

class BloomingHeartsProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BloomingHeartsProjectileProps, ProjectilePropertySheet, RtClass);
	
	BloomingHeartsProjectileProps()
	{
		MaximumStacks = 5.f;
		AdditionalDamagePerStack = 10.f;
		StacksToAdd = 1.f;
		FocusFireRate = 0.5f;
		ImprovedFocusFireBonus = 1.0f;
		FocusFireDuration = 3.0f;
	};
	
	float MaximumStacks;
	float AdditionalDamagePerStack;
	float StacksToAdd;
	float FocusFireRate;
	float ImprovedFocusFireBonus;
	float FocusFireDuration;
};

#endif /* defined(__PlantsVersusZombies2__Plant_BloomingHearts__) */
