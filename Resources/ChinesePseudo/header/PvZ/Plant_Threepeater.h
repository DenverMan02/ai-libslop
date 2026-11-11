#ifndef __PLANT_THREEPEATER_H__
#define __PLANT_THREEPEATER_H__

#include "PlantFramework.h"
#include "Projectile.h"

/*
============================================================== 
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

class ThreepeaterProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ThreepeaterProjectile, Projectile, RtClass);

	virtual void moveThroughTime(pvztime_t i_dt) override;
	void SetNormalMotion(bool i_normalMotion);

protected:
	virtual void onInitialized() override;

private:
	bool m_normalMotion;
};

class PlantThreepeater : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantThreepeater, PlantFramework, RtClass);

	void	Initialize() override;
	void	UpdateActions() override;
	bool	CanApplyPlantfood() override;
	void	ApplyPlantfood() override;
//	bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
private:
	Projectile*	Level5Fire(int i_row);

    pvztime_t m_nextPlantFoodShotTime = PVZ_EOT();
    int m_plantFoodShotAngle = 0;
};

#endif //__PLANT_THREEPEATER_H__
