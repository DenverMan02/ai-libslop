//
//  ZombieLollipops.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/4/20.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef ZombieLollipops_h
#define ZombieLollipops_h

//#include "ZombieTombRaiser.h"
//#include "GridItemGravestone.h"
#include "Precompile.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "Projectile.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_Lollipops, ZombieState)
    ZS_LP_Waiting,
    ZS_LP_Spawning,
STATE_ENUM_END(ZombieState_Lollipops)

//class GridItemLollipops : public GridItemGraveStone
//{
//public:
//    RT_CLASS_DEFINE(GridItemLollipops, GridItemGraveStone, RtClass);
//};

class LollipopsProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(LollipopsProjectile, Projectile, RtClass);
    
    LollipopsProjectile();
    
    virtual bool OnCollideGround() override;
    void SetGridTarget(const Sexy::Point& i_targetGridLoc) { m_targetGridLoc = i_targetGridLoc; }
    void SetGridStoneHitPoint(float hitpoint) {m_lollipopsHitPoint = hitpoint;}
    
private:
    float       m_lollipopsHitPoint;
    Sexy::Point m_targetGridLoc;
};

struct SpellBolt
{
    float posX;
    float posY;
    float velX;
    float velY;
    int lifetime;
    int targetCellX;
    int targetCellY;
};

class ZombieLollipops : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieLollipops, Zombie, RtClass);
    
protected:
    virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, Waiting);
    DECLARE_STATE_FUNCTIONS(ZombieState, Spawning);
    
    virtual void startSpawnAnim();
    virtual void onSpawnAnimDone();
    virtual void onThrow();
    virtual void throwLollipop(const Sexy::Point& i_gridLoc);
    bool isPendingGraveAt(int i_gridX, int i_gridY);
    bool isTombraiserZombieAt(int i_gridX, int i_gridY);
    
    virtual bool findTargetPosition(Sexy::Point& o_targetPoint);
    
protected:
    int m_remainingAmmo;
    int m_remainingGravespawnAttempts;
    pvztime_t m_startThrowTime;
    Point m_throwingTarget;
    
    std::vector<SpellBolt> m_pendingGraves;
};

#endif /* ZombieLollipops_h */
