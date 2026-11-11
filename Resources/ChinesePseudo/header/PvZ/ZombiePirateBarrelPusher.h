//
//  ZombiePirateBarrelPusher.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEPIRATEBARRELPUSHER_H__
#define __ZOMBIEPIRATEBARRELPUSHER_H__

#include "Zombie.h"
#include "GameNotify.h"

class ZombieBarrelPusherProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieBarrelPusherProps, ZombiePropertySheet, RtClass);
    ZombieBarrelPusherProps();
    std::string BarrelType;
};

class ZombiePirateBarrelPusher : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombiePirateBarrelPusher, Zombie, RtClass);
    
    ZombiePirateBarrelPusher() : m_bManualPause(false) {}
    
    void OnBarrelDied();
    
    void disconnectBarrel();
    
    void SetIsManualPause(bool bPause) { m_bManualPause = bPause; }
    
protected:
    virtual void onZombieInitialize() override;
    virtual void onPlaceOnStreet() override;
    virtual void onPlaceOnBoard() override;
    
    virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
    OVERRIDE_STATE_UPDATE(ZombieState, Idle);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    virtual void onEnterState_BleedingOut(ZombieState i_oldState) override;
    
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    virtual void onEndCondition(ZombieConditions i_condition) override;
    
    virtual void onDestroy() override;
    
    virtual void registerForEvents() override;
    
private:
    void spawnBarrelZombie();
    void onZombieTossed(Zombie* i_zombie);
    
    void repositionBarrel();
    
    ZombiePtr m_myBarrel;
    
    bool m_bManualPause;
};

#endif
