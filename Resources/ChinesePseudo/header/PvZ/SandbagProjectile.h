//
//  SandbagProjectile.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 6/8/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SandbagProjectile__
#define __PlantsVersusZombies2__SandbagProjectile__

#include "Projectile.h"

class SandbagProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(SandbagProjectileProps, ProjectilePropertySheet, RtClass);
	
	SandbagProjectileProps()
	{
		ImpactRadiusX = 0;
		ImpactRadiusY = 0;
	}
	
	int32_t		ImpactRadiusX;
	int32_t		ImpactRadiusY;
};

class SandbagProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SandbagProjectile, Projectile, RtClass);
	
	int GetRenderOrder() const override;
	
	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool OnCollideGround() override;
};

#endif /* defined(__PlantsVersusZombies2__SandbagProjectile__) */
