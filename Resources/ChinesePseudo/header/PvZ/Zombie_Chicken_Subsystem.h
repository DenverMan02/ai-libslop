//
//  Zombie_Chicken_Subsystem.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_CHICKEN_SUBSYSTEM_H__
#define __ZOMBIE_CHICKEN_SUBSYSTEM_H__

#include <vector>

#include "GameSubSystem.h"
#include "RtObject.h"
#include "TimeMgr.h"

struct Chickening
{
    int Row;
    int X;
    pvztime_t NextChickenTime;
    pvztime_t EndTime;
    TeamFlags Team;
    std::string ChickenTypeName;
    pvztime_t Duration;
    pvztime_t DurationVariance;
    pvztime_t Interval;
    pvztime_t IntervalVariance;
    ZombieConditions Condition;
};

class ZombieChickenSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ZombieChickenSubsystem, GameSubSystem, RtClass);
    
    virtual void Update() override;
    virtual void StartChickening(const std::string& i_typeName
                         , float i_x, int i_row
                         , TeamFlags i_team, pvztime_t i_duration
                         , pvztime_t i_durationVariance
                         , pvztime_t i_interval
                         , pvztime_t i_intervalVariance
                         , ZombieConditions i_condition
                         , int i_level);
    virtual void StopAllChickening();
    
protected:
    virtual Zombie* spawnChicken(const std::string& i_typeName
                         , float i_x, int i_row
                         , TeamFlags i_team
                         , ZombieConditions i_condition
                         , int i_level);
    std::vector<Chickening> m_chickenings;
    int m_level = 1;
};

class ZombieChickenEliteSubsystem : public ZombieChickenSubsystem
{
public:
    RT_CLASS_DEFINE(ZombieChickenEliteSubsystem, ZombieChickenSubsystem, RtClass);

    virtual void Update() override;
};

#endif
