/*
 * ZombieSnowPea.h
 *
 *  Created on: 2020-10-21
 *      Author: admin
 */

#ifndef ZOMBIESNOWPEA_H_
#define ZOMBIESNOWPEA_H_

#include "ZombieShooter.h"
#include "Projectile.h"

class SnowPeaZombieProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SnowPeaZombieProjectile, Projectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

class SnowPeaZombieProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(SnowPeaZombieProjectileProps, ProjectilePropertySheet, RtClass);

	SnowPeaZombieProjectileProps()
	{
		SlowDuration = 1.0f;
	}

	float SlowDuration;
};

class ZombieSnowPea : public ZombieShooter
{
public:
	RT_CLASS_DEFINE(ZombieSnowPea, ZombieShooter, RtClass);

protected:
    virtual void onZombieInitialize() override;
};

#endif /* ZOMBIESNOWPEA_H_ */
