//
//  ZombiePVPChickenFarmer.h
//  PlantsVersusZombies2
//
//  Created by Ruoqian, Chen on 04/05/2016.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_PVP_CHICKEN_FARMER_H__
#define __ZOMBIE_PVP_CHICKEN_FARMER_H__

#include "DamageInfo.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieChicken.h"
#include "ZombieChickenFarmer.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_PVPChickenFarmer, ZombieState)
ZS_PVP_CF_SPAWN,
STATE_ENUM_END(ZombieState_PVPChickenFarmer)

class ZombiePVPChickenFarmer : public ZombieChickenFarmer
{
public:
    RT_CLASS_DEFINE(ZombiePVPChickenFarmer, ZombieChickenFarmer, RtClass);
protected:
    DECLARE_STATE_FUNCTIONS(ZombieState, Spawn);
    
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    virtual void ApplyZombieFood() override;
    void onAnimStopped(const std::string& i_animLabel);

    void SpawnChicken(void);
};

class ZombiePVPChicken : public ZombieChicken
{
public:
    ZombiePVPChicken();
    RT_CLASS_DEFINE(ZombiePVPChicken, ZombieChicken, RtClass);
    virtual void CreateArenaSpawnEffect() override;
    virtual void CreateZombieLevelEffect(bool i_street) override;
    virtual void updateState_Walk() override;
    
protected:
    void onAnimStopped(const std::string& i_animLabel);

    bool m_bSlowMove;;
};


class ZombiePVPChickenFarmerProps : public ZombieChickenFarmerProps
{
public:
    RT_CLASS_DEFINE(ZombiePVPChickenFarmerProps, ZombieChickenFarmerProps, RtClass);
    std::string ActiveChickenTypeName;
};

#endif
