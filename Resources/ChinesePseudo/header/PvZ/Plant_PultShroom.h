//
//  PlantAnimRig_Pultshroom.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 9/24/2013.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//
#ifndef __PLANT_PULTSHROOM_H__
#define __PLANT_PULTSHROOM_H__

#include "Plant_Cabbagepult.h"

class PlantPultshroom : public PlantCabbagepult
{
public:
	RT_CLASS_DEFINE(PlantPultshroom, PlantCabbagepult, RtClass);
	
	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual bool CanApplyPlantfood() override;
	virtual bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
	void FireSelected(int i_faceId);
	
private:
	int getCommandID(const std::string& i_animCommand, const std::string& commandPrefix);
	
	pvztime_t m_swapForOtherPlantTime;
	int32 m_level;
};

#endif // __PLANT_PULTSHROOM_H__
