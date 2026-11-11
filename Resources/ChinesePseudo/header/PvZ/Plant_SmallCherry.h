//
//  Plant_SmallCherry.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-7-17.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_SmallCherry_h
#define PlantsVersusZombies2_Plant_SmallCherry_h

#include "PlantFramework.h"

class PlantSmallCherry : public PlantFramework
{
    
public:
    
	RT_CLASS_DEFINE(PlantSmallCherry, PlantFramework, RtClass){}
    
public:
    
	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
	virtual bool	CanApplyPlantfood() override;
	virtual bool	HasShadow() override;
    
	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override
	{
		return (COLLIDE_GROUND_ZOMBIES | COLLIDE_DYING_ZOMBIES);
	}
    
	virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
	virtual bool 	CanBeShoveled() override;
	virtual bool	IsInvincible() const override;
    
	virtual bool	CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    
private:
	void			Explode();
};

#endif
