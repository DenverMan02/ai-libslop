//
//  Plant_PowerLily.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 10/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_PowerLily__
#define __PlantsVersusZombies2__Plant_PowerLily__

#include "PlantFramework.h"

class PlantPowerLily : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPowerLily, PlantFramework, RtClass);
    
	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void DoSpecial(int i_extraParam = 0) override;
	virtual void ProduceSun(const PlantAction& i_fromAction) override;
    
    bool CanBeShoveled() override { return false; }
    bool CanBeTargeted() override { return false; }

	virtual void onAnimStoppedCallback(const std::string &i_animLabel) override;

	bool OverrideProjectileCollision(class Projectile* pProjectile) override;
    
private:
	bool m_spawningPlantFood = false;
};

#endif /* defined(__PlantsVersusZombies2__Plant_PowerLily__) */
