//
//  Plant_SunPod.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/17/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_SunPod__
#define __PlantsVersusZombies2__Plant_SunPod__

#include <string>

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"

class Zombie;

class PlantSunpod : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSunpod, PlantFramework, RtClass);
	
	void Initialize() override;
	bool CanApplyPlantfood() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
	void	UpdateActions() override;
	
	void SetLevel(int i_level);
	void FireSelected(int i_faceId);
	
	std::string GetFireSoundEvent() const override;
	
	int GetLevel() const { return m_level; }
	
private:
	int m_level = 0;
};

#endif /* defined(__PlantsVersusZombies2__Plant_SunPod__) */
