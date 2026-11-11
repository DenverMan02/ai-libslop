//
//  ZombiePvpDead.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 15/11/10.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZombiePvpDead_H__
#define __ZombiePvpDead_H__

#include "Precompile.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "Projectile.h"
#include "ZombieTombRaiser.h"


class ZombiePvpDeadProps  : public ZombieTombRaiserProps
{
public:
    RT_CLASS_DEFINE(ZombiePvpDeadProps, ZombieTombRaiserProps, RtClass);
    
    ZombiePvpDeadProps()
    {
        TimeBetweenCasts = 0.f;
        TimeBetweenRaisings = 6.0f;
        NumberOfTombsToSpawn = 2;
        SkillSpanTime = 20.0f;
        GravestoneHitPoints = 700.0f;
        SkillSpeedup = 1.5f;
        TimeBetweenSkillCasts = 0.0f;
    }
    
    float   TimeBetweenSkillCasts;
    float   GravestoneHitPoints;
    float   SkillSpanTime;
    float   SkillSpeedup;
};

class ZombiePvpDead : public ZombieTombRaiser
{
public:
	RT_CLASS_DEFINE(ZombiePvpDead, ZombieTombRaiser, RtClass);
    
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Waiting);

    virtual void TriggerPlaybackParams(int i_type) override;
protected:
	virtual void onZombieInitialize() override;
    virtual void onUpdate() override;
    virtual void startSpawnAnim() override;
    virtual void onSpawnAnimDone() override;
    virtual void onThrow() override;
    virtual void throwBone(const Sexy::Point& i_gridLoc) override;
    
    virtual void ApplyZombieFood() override;
    virtual void CancelZombieFood() override;
    
    bool findGraveTargetPosition(Sexy::Point& o_targetPoint);
    virtual bool findTargetPosition(Sexy::Point& o_targetPoint) override;
    
    float   m_skillTime;
    std::vector<Point> m_spawingPoint;
};

#endif
