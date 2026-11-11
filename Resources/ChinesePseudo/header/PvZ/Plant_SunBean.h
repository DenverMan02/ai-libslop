//
//  Plant_SunBean.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/11/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_SunBean__
#define __PlantsVersusZombies2__Plant_SunBean__

#include "PlantFramework.h"
#include "GameSubSystem.h"

class PlantSunBean : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSunBean, PlantFramework, RtClass);

	void Initialize() override;

	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

private:
	bool m_isSuperSized = false;
};

// -----------

enum ZombieSupernovaState
{
	PVZ_BEGIN_ENUM(ZSUPERNOVA_),
	ZSUPERNOVA_Sick,
	ZSUPERNOVA_Exploding,
	ZSUPERNOVA_Done,
	PVZ_END_ENUM(ZSUPERNOVA_)
};

class ZombieSupernova
{
public:
	void Update();

	int State;
	float SunMultiplierOnBurst;
	float MaxSunToSpawn;
	pvztime_t StartTime;
	pvztime_t StateDuration;

	RtWeakPtr<class Zombie> ZombieToExplode;

private:
	
	void playNovaExplode(class Zombie* i_zombie);
	void playNovaExplodePart2(Zombie* i_zombie);
};

struct SpewingZombieTracker
{
public:
	RtWeakPtr<class Zombie> Zombie;
	float LastKnownHealth;
	float SunMaxRemaining;
	SexyVector3 LastKnownPosition;
};

class PlantSunBeanSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantSunBeanSubSystem, GameSubSystem, RtClass);

	bool CanZombieSpewSun(class Zombie* i_zombie) const;
	void MakeZombieSpewSun(class Zombie* i_zombie, RtWeakPtr<SunBeanProps> i_props, bool i_fromPlantfoodedPlant);

    void StopMakingZombieSpewSun(class Zombie* i_zombie);
    
    void CauseZombieSupernova(Zombie* i_zombie, RtWeakPtr<SunBeanProps> i_props);
    void StopMakingZombieSupernova(Zombie* i_zombie);

	void Update() override;

	void SetPropertySheet(RtWeakPtr<class SunBeanProps> i_props);

	static float SpewSun(float i_sunAmount, Sexy::SexyVector3 i_atPosition, bool i_onlyLargeSun);
	float GetSunAmountToSpew(const float i_maxSun, const float i_healthAmount, const bool i_plantfooded) const;

private:
	int findTrackerForZombie(Zombie* i_zombie) const;
	float getSunPerHitpoint() const;

	void convertHitpointsToSun(float i_maxSun, float i_healthAmount, Sexy::SexyVector3 i_atPosition, float& o_hitpointsConsumed, float& o_sunProduced);

	std::vector<SpewingZombieTracker> m_spewingZombies;
	RtWeakPtr<class SunBeanProps> m_props;

	std::vector<ZombieSupernova> m_zombieSupernovae;

};

#endif /* defined(__PlantsVersusZombies2__Plant_SunBean__) */
