//
//  GoldCabbageProjectile.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16-10-28.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GoldCabbageProjectile__
#define __PlantsVersusZombies2__GoldCabbageProjectile__

#include "Projectile.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "Zombie.h"

class GoldCabbageProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(GoldCabbageProjectile, Projectile, RtClass);
    virtual ~GoldCabbageProjectile();
    
    void    setFlyTotalTime(float tTime, const SexyVector3& i_target, bool isOnfood, bool isAvatar);
    
    void    onAnimStopped(const std::string &i_animName);
protected:
    virtual void onUpdate(pvztime_t i_dt) override;
    
    void    doSplit();
    
    SexyVector3 m_targetVec;
    float  m_totalTime;
    float  m_flyTime;
    bool   m_isOnFood = false;
    bool   m_isAvatar = false;
    bool   m_needSplit   = false;
    bool   m_hasSplited  = false;

};

#endif /* defined(__PlantsVersusZombies2__ThrowZombieProjectile__) */
