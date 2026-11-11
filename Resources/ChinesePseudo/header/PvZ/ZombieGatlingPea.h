/*
 * ZombieGatlingPea.h
 *
 *  Created on: 2020-10-22
 *      Author: admin
 */

#ifndef ZOMBIEGATLINGPEA_H_
#define ZOMBIEGATLINGPEA_H_

#include "ZombieShooter.h"
#include "Projectile.h"

class GatlingPeaZombieProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(GatlingPeaZombieProjectile, Projectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

class ZombieGatlingPea : public ZombieShooter
{
public:
	RT_CLASS_DEFINE(ZombieGatlingPea, ZombieShooter, RtClass);

protected:
    virtual void onZombieInitialize() override;
};


#endif /* ZOMBIEGATLINGPEA_H_ */
