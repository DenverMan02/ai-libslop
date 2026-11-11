//
//  Plant_Pitaya.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-28.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Pitaya__
#define __PlantsVersusZombies2__Plant_Pitaya__

#include "PlantFramework.h"

class PlantPitaya : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPitaya, PlantFramework, RtClass);
    
	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void DoSpecial(int i_extraParam) override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    
private:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, PlantWeapon i_plantWeapon);
	
	virtual void playFireSound();
	virtual void playPlantfoodLaunchSound();
    
	std::vector<BoardEntityPtr> m_targettedBoardEntities;
	int m_timesSpecialFired = 0;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Pitaya__) */
