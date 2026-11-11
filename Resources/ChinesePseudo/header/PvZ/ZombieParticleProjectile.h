//
//  ZombieParticleProjectile.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/17/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieParticleProjectile__
#define __PlantsVersusZombies2__ZombieParticleProjectile__

#include "Projectile.h"
#include "ZombieParticle.h"

class ZombieParticleProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ZombieParticleProjectile, Projectile, RtClass);
	
	void SetControlledParticle(ZombieParticle* i_particle);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	
protected:
	void onPostUpdate() override;
	void onDestroy() override;
private:
	RtWeakPtr<ZombieParticle> m_controlledParticle;
};

#endif /* defined(__PlantsVersusZombies2__ZombieParticleProjectile__) */
