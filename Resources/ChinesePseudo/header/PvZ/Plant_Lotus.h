#ifndef __PLANT_LOTUS_H__
#define __PLANT_LOTUS_H__

#include "PlantFramework.h"


class PlantLotus : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantLotus, PlantFramework, RtClass){}

	virtual bool CanApplyPlantfood() override;
    virtual void CancelPlantfood() override;
	virtual void DoSpecial(int i_extraParam) override;
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

private:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
};

#endif // __PLANT_LOTUS_H__
