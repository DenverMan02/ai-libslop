//
//  Plant_Pepperpult.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 10/31/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Pepperpult__
#define __PlantsVersusZombies2__Plant_Pepperpult__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "ComponentWarmingRadius.h"

class PepperpultProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PepperpultProps, PlantPropertySheet, RtClass);
	
	PepperpultProps()
	{
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
		PlantfoodProjectilesToFire = 4;
	}
	
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
	int PlantfoodProjectilesToFire;
	
	ComponentWarmingRadiusProps NormalWarmingRadius;
	ComponentWarmingRadiusProps PlantfoodWarmingRadius;
};

class PepperpultProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PepperpultProjectileProps, ProjectilePropertySheet, RtClass);
    
    PepperpultProjectileProps()
    {
        BurnTime = 0.0f;
        BurnDPS = 0;
    }
    
    pvztime_t BurnTime;
    float BurnDPS;
};

class PlantPepperpult : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPepperpult, PlantFramework, RtClass);
    
	void Initialize() override;
	
    bool CanApplyPlantfood() override;
    void DoSpecial(int i_extraParam) override;
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void CancelPlantfood() override;
	void ApplyPlantfood() override;

protected:
    void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	
	void onKilled(bool i_instantKill) override;
	
private:
	void launchSpecialProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
    bool InGhostFireState();
	RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;

	std::vector<BoardEntityPtr> m_targetedBoardEntities;
	int m_timesSpecialFired = 0;
};

class PlantAnimRig_Pepperpult : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Pepperpult, PlantAnimRig, RtClass) {}
    void ShowGhostFire(bool show);
    std::vector<std::string> GetGhostFireLayers();
protected:
    virtual void onPopAnimInitialized() override;
    void onLevelUpdate() override;
private:
    virtual std::string getPlantFoodMainAnimName() override;
};

class PepperpultProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PepperpultProjectile, Projectile, RtClass) {}
    void SetBurnDamge(float dps, pvztime_t during);
protected:
	virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
private:
    void BurnZombie(Zombie* zombie, float dps, pvztime_t during, ZombieConditions type);
};

class PepperpultPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PepperpultPlantfoodProjectile, Projectile, RtClass);
	
private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

	void launchSpecialProjectile(SexyVector3 i_targetLoc);
	void launchProjectileAt(Projectile *i_projectile, const Sexy::SexyVector3 &i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
};

#endif /* defined(__PlantsVersusZombies2__Plant_Pepperpult__) */
