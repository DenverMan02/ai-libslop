//
//  ZombieLaneChangingSubsystem.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 10/3/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLaneChangingSubsystem__
#define __PlantsVersusZombies2__ZombieLaneChangingSubsystem__

#include "GameSubSystem.h"
#include "Core.h"
#include "Curve.h"
#include "TimeMgr.h"

class Zombie;

namespace Message {
    void ZombieLaneChangeStarted(Zombie* zombie);
    void ZombieLaneChangeEnded(Zombie* zombie);
}

enum ZombieLaneChangingState
{
    PVZ_BEGIN_ENUM(ZLANECHANGE_),
    ZLANECHANGE_Active,
    ZLANECHANGE_BlacklistDelay,	// Delay on completing a lane change to blacklist zombie for future lane change attempts
    PVZ_END_ENUM(ZLANECHANGE_)
};

struct ZombieLaneChangingRecord
{
    ZombieLaneChangingRecord()
    :ptrZombie(nullptr)
    ,StartingRow(0)
    ,TargetRow(0)
    ,ElapsedTime(0.0f)
    ,Duration(0.0f)
    ,Curve(CURVE_EASE_IN_OUT)
    ,LaneChangeTime(0.0f)
    ,CooldownAfterTime(0.0f)
    ,State(ZLANECHANGE_Active)
    {}
    
    RtWeakPtr<Zombie> ptrZombie;
    int StartingRow;
    int TargetRow;
    pvztime_t ElapsedTime;
    pvztime_t Duration;
    CurveType Curve;
    
    pvztime_t LaneChangeTime;
    pvztime_t CooldownAfterTime;
    ZombieLaneChangingState State;
};

class ZombieLaneChangingSubsystem : public GameSubSystem
{
    RT_CLASS_DEFINE(ZombieLaneChangingSubsystem, GameSubSystem, RtClass);
    
    void Update() override;
    
    bool ForceLaneChange(Zombie* i_zombie, int i_newRow, float i_travelTime, CurveType i_curveType, pvztime_t i_cooldownTime);
    bool ForceLaneChange(ZombieLaneChangingRecord& zombieRecord);
    
    bool IsZombieChangingLanes(Zombie* i_zombie) const;
    void RemoveZombie(Zombie* i_zombie);
    
    static bool CanZombieMoveUp(Zombie* i_zombie);
    static bool CanZombieMoveDown(Zombie* i_zombie);
    static bool CanZombieMoveTo(Zombie *i_zombie, int i_newRow);
    
protected:
    void onInitialized() override;
    void registerForEvents() override;
    
private:
    bool isNotValidMoveTarget(RtWeakPtr<Zombie> i_zombie, int withTargetRow);
    float getYForRow(int i_row) const;
    int getChangerRecordIndexFor(RtWeakPtr<Zombie> i_zombie) const;
    
    void checkIncompatability(ZombieLaneChangingRecord& i_record);
    
    bool isDoneWithCurrentState(ZombieLaneChangingRecord& i_record);
    
    void checkForTimeToDelete(ZombieLaneChangingRecord& i_record);
    void updateZombiePosition(ZombieLaneChangingRecord& i_record);
    void setComplete(ZombieLaneChangingRecord& i_record);
    
    void updateStateAndDuration(ZombieLaneChangingRecord& i_record, ZombieLaneChangingState i_state, float i_duration);
    
    std::vector<ZombieLaneChangingRecord> m_laneChangers;
};

#endif /* defined(__PlantsVersusZombies2__ZombieLaneChangingSubsystem__) */
