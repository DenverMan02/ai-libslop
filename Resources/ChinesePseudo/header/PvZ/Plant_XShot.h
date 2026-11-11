//
//  Plant_XShot.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 10/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_XShot__
#define __PlantsVersusZombies2__Plant_XShot__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "ProjectilePropertySheet.h"
#include "RtObject.h"
#include "TimeMgr.h"

#define NORTHEAST 0
#define SOUTHEAST 1
#define SOUTHWEST 2
#define NORTHWEST 3
#define DIRECTIONS_TO_FIRE 4

class XShotProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(XShotProps, PlantPropertySheet, RtClass);
    
    XShotProps()
    {
		PlantFoodProjectileCount = 1;
		PlantFoodAngleVarianceInDegrees = 5.0f;
        FireHeight = 0.32;
    }
    
	int PlantFoodProjectileCount;
	float PlantFoodAngleVarianceInDegrees;
    float FireHeight;
    std::vector<float> AdvancedProjectileProbability;
};

class PlantXShot : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantXShot, PlantFramework, RtClass);
	
	PlantXShot()
	{
		m_potentialTargets.resize(4);
	}
	
    virtual bool			CanApplyPlantfood() override;
    virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
	virtual bool			OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;

    virtual Projectile*		Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    
private:
    Projectile* fireProjectile(int i_index, ProjectilePropertySheetPtr i_projectileType);
	BoardEntityPtr calcValidTargetFromList(std::vector<BoardEntity*> i_touchedEntities);
    
    pvztime_t m_shotsPerSecond = 0;
    pvztime_t m_startTime = PVZ_EOT();
    int m_shotsFired = 0;
    int m_shotTotal = 0;
	bool m_plantfoodShouldFire = false;
	std::vector<BoardEntityPtr> m_potentialTargets;
};

class PlantAnimRig_XShot : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_XShot, PlantAnimRig, RtClass);
    
    bool PlayPreviewAnim(bool bHideLayer = false) override;
};

#endif /* defined(__PlantsVersusZombies2__Plant_XShot__) */
