//
//  Plant_LightningReed.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/21/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_LightningReed_h
#define PlantsVersusZombies2_Plant_LightningReed_h

#include "PlantFramework.h"

class PlantLightningReed : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantLightningReed, PlantFramework, RtClass);

    virtual void Initialize() override;
    
	virtual bool CanApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual float GetShadowScaling() override;
    
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
//	virtual GridItemPtr FindTargetDamageableGridItem(int i_col, int i_row, PlantWeapon i_plantWeapon) override;

	virtual DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;
    PlantTargetParams GetTargetParamsForWeapon(PlantWeapon i_plantWeapon) override;
	virtual std::string GetFireSoundEvent() const override;
    
private:
    bool m_starAttack = false;
	float m_chainAttackRate = 0;
};

#endif
