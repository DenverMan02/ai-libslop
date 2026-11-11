#ifndef __PLANT_CABBAGEPULT_H__
#define __PLANT_CABBAGEPULT_H__

#include "PlantFramework.h"

class PlantCabbagepult : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCabbagepult, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual void DoSpecial(int i_extraParam) override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

protected:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
    
private:
    Projectile* avatarFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    Projectile* normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
};

class PlantAnimRig_Cabbagepult : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Cabbagepult, PlantAnimRig, RtClass);
    
protected:
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;
};

#endif // __PLANT_CABBAGEPULT_H__
