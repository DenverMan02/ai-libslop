//
//  ZombieChickenFarmer.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_CHICKEN_FARMER_H__
#define __ZOMBIE_CHICKEN_FARMER_H__

#include "DamageInfo.h"
#include "RtObject.h"
#include "Zombie.h"

class ZombieChickenFarmer : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieChickenFarmer, Zombie, RtClass);
    
    virtual void SetHasChickened(bool i_hasChickened);
    virtual void onApplyCondition(ZombieConditions i_condition) override;

    bool HasChickened() { return m_hasChickened; }

protected:
    virtual void onZombieInitialize() override;
    virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
    virtual void updateState_Eat() override;
    virtual void onChangeTeams(TeamFlags i_oldTeams, TeamFlags i_newTeams) override;
    
    virtual void tryStartChickening();
    bool m_hasChickened;
    
protected:
    virtual bool shouldSpawnChickensOnEatAttack() { return true; }
};

class ZombieChickenFarmerProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieChickenFarmerProps, ZombiePropertySheet, RtClass);
    
    ZombieChickenFarmerProps()
    {
        ChickeningHealthPercentage = 0.80f;
        ChickeningDuration = 2.0f;
        ChickeningDurationVariance = 1.0f;
        ChickeningInterval = 0.2f;
        ChickeningIntervalVariance = 0.1f;
    }
    
    float ChickeningHealthPercentage;
    std::string ChickenTypeName;
    std::string ChickeningSound;
    pvztime_t ChickeningDuration;
    pvztime_t ChickeningDurationVariance;
    pvztime_t ChickeningInterval;
    pvztime_t ChickeningIntervalVariance;
};

class ZombieWeaselHoarderEliteProps : public ZombieChickenFarmerProps
{
public:
    RT_CLASS_DEFINE(ZombieWeaselHoarderEliteProps, ZombieChickenFarmerProps, RtClass);

    ZombieWeaselHoarderEliteProps() {
    	SpawnWeaselInterval = 10.0f;
    	SpawnWeaselCount1 = 2;
    	SpawnWeaselCount2 = 4;
    }

    pvztime_t SpawnWeaselInterval;
    int SpawnWeaselCount1;
    int SpawnWeaselCount2;
};

class ZombieWeaselHoarder : public ZombieChickenFarmer
{
public:
    RT_CLASS_DEFINE(ZombieWeaselHoarder, ZombieChickenFarmer, RtClass);
    
protected:
    void tryStartChickening() override;
    void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
    virtual void onWeaselAttackEnd(const std::string&);
    bool shouldSpawnChickensOnEatAttack() override { return false; }
    void onPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params) override;
    
    bool m_hasStartedChickening = false;
};


class ZombieWeaselHoarderElite : public ZombieWeaselHoarder
{
public:
    RT_CLASS_DEFINE(ZombieWeaselHoarderElite, ZombieWeaselHoarder, RtClass);

protected:
    void onPlaceOnBoard() override;
    void onZombieInitialize() override;
    void tryStartChickening() override;
    void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
    void updateState_Eat() override;
    void updateState_Walk() override;
    void onPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params) override;
    void onWeaselAttackEnd(const std::string&) override;

    void SpawnWeasel();

protected:
    pvztime_t m_spawnWeaselTime;
};



#endif
