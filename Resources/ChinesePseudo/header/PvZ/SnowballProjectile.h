//
//  SnowballProjectile.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 12/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SnowballProjectile__
#define __PlantsVersusZombies2__SnowballProjectile__

#include "Projectile.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"

class SnowballProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SnowballProjectile, Projectile, RtClass);

	virtual void damageEntity(class BoardEntity* i_entity);
};

#endif /* defined(__PlantsVersusZombies2__SnowballProjectile__) */
