//
//  PlantAnimRig_Dartshroom.h
//  PlantsVersusZombies2
//
//  Created by Erik Rydeman on 10/15/2013.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//
#ifndef __PLANT_Dartshroom_H__
#define __PLANT_Dartshroom_H__

#include "Plant.h"
#include "PlantUtils.h"
#include "Plant_Cabbagepult.h"
#include "Rect.h"
#include "RtObject.h"

class Projectile;
class Zombie;

class PlantDartshroom : public PlantCabbagepult
{
public:
	RT_CLASS_DEFINE(PlantDartshroom, PlantCabbagepult, RtClass);
	
	virtual void Initialize() override;
	
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	
    virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
	virtual Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	
private:
	PlantFoodCounter m_plantfoodCounter;
	
};

#endif // __PLANT_Dartshroom_H__
