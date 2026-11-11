//
//  ThrowZombieProjectile.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-10-24.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ThrowZombieProjectile__
#define __PlantsVersusZombies2__ThrowZombieProjectile__

#include "Projectile.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "Zombie.h"

class ThrowZombieProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ThrowZombieProjectile, Projectile, RtClass);
    
    void SetAttachedZombiePAM(ZombiePtr targetZombie, const SexyVector2 i_offset);
    virtual ~ThrowZombieProjectile();
protected:
    virtual void onUpdate(pvztime_t i_dt) override;
private:
    void CreateHaloEffect();
    void DestroyHaloEffect();
    void UpdateHaloEffect();
private:
    RtWeakPtr<class Effect_PopAnim>   m_haloEffect;
};

#endif /* defined(__PlantsVersusZombies2__ThrowZombieProjectile__) */
