//
//  BoulderProjectile.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/20/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BoulderProjectile__
#define __PlantsVersusZombies2__BoulderProjectile__

#include "Projectile.h"

class BoulderProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BoulderProjectileProps, ProjectilePropertySheet, RtClass);
	
	BoulderProjectileProps()
	{
		BounceElasticity = 0.3f;
		BounceThreshold = 0.005f;
	}
	
	SexyVector3 RollingVelocity;
	float		BounceElasticity;
	float		BounceThreshold;
};

class BoulderProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BoulderProjectile, Projectile, RtClass);
	
	virtual ~BoulderProjectile();
	
	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool OnCollideGround() override;
	
protected:
	void onProjectileInitialized() override;
	
private:
	bool isToTheRight(BoardEntity* i_entity);
	
	int32_t m_currentState = 0;
};

#endif /* defined(__PlantsVersusZombies2__BoulderProjectile__) */
