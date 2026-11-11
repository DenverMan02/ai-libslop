//
//  Plant_Turkeypult.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 5/26/20.
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef Plant_Turkeypult_h
#define Plant_Turkeypult_h

#include "PlantFramework.h"
#include "Projectile.h"
#include "Zombie.h"

class TurkeypultProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(TurkeypultProps, PlantPropertySheet, RtClass);

	TurkeypultProps()
	:	TurkeyTypeToSpawn("turkeypult_basic")
	,	PlantfoodTurkeyTypeToSpawn("turkeypult_turkzilla")
	,	AvatarPlantfoodTurkeyTypeToSpawn("turkeypult_turkzilla_avatar")
	, 	TurkeyTypeToSpawnLv5("turkeypult_turkzilla_lv5")
	,	TurkeyLevel(1)
	,	PlantfoodTurkeysToLaunch(5)
	,	AvatarPlantfoodTurkeysToLaunch(5)
	,	Level2ReducedSunCost(50)
	,	Level3ReducedSunCost(50)
	,	Level2ReducedCd(0)
	, 	Level3ReducedCd(0)
	, 	Level5Rate(0.8)
	{}

	std::string TurkeyTypeToSpawn;
	std::string PlantfoodTurkeyTypeToSpawn;
	std::string AvatarPlantfoodTurkeyTypeToSpawn;
	std::string TurkeyTypeToSpawnLv5;
	int TurkeyLevel;
	int PlantfoodTurkeysToLaunch;
	int AvatarPlantfoodTurkeysToLaunch;

	int Level2ReducedSunCost;
	int Level3ReducedSunCost;
	float Level2ReducedCd;
	float Level3ReducedCd;
	float Level5Rate;

	PultProjectileProps NormalLaunchProps;
	PultProjectileProps PlantfoodLaunchProps;
};

class PlantTurkeypult : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantTurkeypult, PlantFramework, RtClass);

	virtual void Initialize() override;
	bool CanApplyPlantfood() override { return true; }
	void DoSpecial(int i_extraParam = 0) override;
	Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
};

class PlantAnimRig_Turkeypult : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Turkeypult, PlantAnimRig, RtClass);

	std::string getPlantFoodOnAnimName() override { return "plantfood_start"; }
	std::string getPlantFoodMainAnimName() override { return "plantfood_loop"; }
	std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }
};

class TurkeypultProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(TurkeypultProjectile, Projectile, RtClass);

	TurkeypultProjectile()
	:	m_spawnType("turkeypult_basic")
	,	m_spawnLevel(1)
	{}

	void InitializeProjectileValues(std::string i_spawnType, int i_spawnLevel)
		{ m_spawnType = i_spawnType;  m_spawnLevel = i_spawnLevel; }

private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void spawnTurkey();

	std::string m_spawnType;
	int m_spawnLevel;
};

class PlantTypeTurkeypult : PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeTurkeypult, PlantType, RtClass);

    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
    virtual int GetCost(int level) const;
};

#endif /* Plant_Turkeypult_h */
