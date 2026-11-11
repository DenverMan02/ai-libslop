//
//  Plant_Scaredyshroom.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 8/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PLANT_SCAREDYSHROOM_H__
#define __PLANT_SCAREDYSHROOM_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"

class Zombie;

enum ScaredyState
{
	SCAREDYSTATE_SCARED = STATE_FRAMEWORK_BEGIN,
};

class PlantScaredyshroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantScaredyshroom, PlantFramework, RtClass);
	
	virtual void UpdateActions() override;
	virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;
    
    virtual Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
private:
	bool isZombieInScaredRange();

	PeashooterPlantfood m_plantfood;
};

#endif //__PLANT_SCAREDYSHROOM_H__
