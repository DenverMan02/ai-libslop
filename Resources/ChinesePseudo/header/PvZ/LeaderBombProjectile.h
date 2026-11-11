//
//  LeaderBombProjectile.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16/11/16.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LeaderBombProjectile__
#define __PlantsVersusZombies2__LeaderBombProjectile__

#include "Projectile.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"

class LeaderBombProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(LeaderBombProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual bool OnCollideGround() override;
    virtual void onProjectileInitialized() override;
    
    
    void         onAnimCommand(const std::string& i_animLabel,
                                      pvztime_t i_timeStamp,
                                      const std::string& i_animCommand,
                                      const std::string& i_animCommandParam);
    void         onAnimStopped(const std::string& i_animLabelName);
};

#endif /* defined(__PlantsVersusZombies2__SnowballProjectile__) */
