//
//  Plant_Kernelpult.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_KERNELPULT_H__
#define __PLANT_KERNELPULT_H__

#include "Precompile.h"
#include "PlantFramework.h"
#include "PvZ2IDs.h"

class PlantKernelpult : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantKernelpult, PlantFramework, RtClass);
	
	virtual void Initialize() override;

	virtual void PlayAttackAnimation() override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void DoSpecial(int i_extraParam) override;

	virtual void CancelPlantfood() override;
    void TestAndShine(bool i_shine);
    
protected:
    //PVZ2_CHINESE_BEGIN
	virtual void DoSpecialForAvatarNormal() override { m_fButterRand = 0.5f; }  // for avatar
    float m_fButterRand;
	//PVZ2_CHINESE_END

private:
	void launchMassButterAssault();
	void launchPlantFoodButterAtTarget(pvztime_t i_delay, float i_butterStunLength, ZombiePtr i_zombie, class GridItem* i_gridItem, SexyVector2* i_targetLoc);
	void launchProjectileAt(class Projectile* i_projectile, const SexyVector3& i_targetLoc);
    
    int  m_iFireCount;
	bool m_launchingButter;
    bool m_bFireRocket;
};

#endif // __PLANT_KERNELPULT_H__
