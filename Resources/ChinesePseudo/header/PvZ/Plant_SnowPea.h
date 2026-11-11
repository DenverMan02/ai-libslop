//
//  Plant_SnowPea.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_SNOWPEA_H__
#define __PLANT_SNOWPEA_H__

#include "PlantFramework.h"
#include "PlantUtils.h"

class Effect_PopAnim;

class PlantSnowPea : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSnowPea, PlantFramework, RtClass);

    PlantSnowPea();
    virtual ~PlantSnowPea();
    
    virtual void Initialize() override;
    
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void onPlantfoodEnded() override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void Idle() override;
private:
	void onPlantfoodStarted() override;
	PeashooterPlantfood m_plantfood;
	RtWeakPtr<Effect_PopAnim> m_plantfoodEffect;
};

#endif //__PLANT_SNOWPEA_H__
