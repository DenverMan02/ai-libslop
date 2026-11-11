#ifndef __PLANT_PEASHOOTER_H__
#define __PLANT_PEASHOOTER_H__

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "PlantAnimRig_Peashooter.h"

class PeashooterProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PeashooterProps, PlantPropertySheet, RtClass);
    
    int PlantFoodProjectileCount = 1;
    std::vector<float> SpecialRate;
};

class PlantPeashooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPeashooter, PlantFramework, RtClass);

	virtual void			Initialize() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
	virtual bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

protected:
	void DoLevelSpecial(int state, PlantWeapon i_plantWeapon);

protected:
    
    PeashooterPlantfood m_plantfood;
	int32 m_comboCount;
	float m_reShootRate;
};

#endif //__PLANT_PEASHOOTER_H__
