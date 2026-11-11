//
//  ZombossRiftBattleModule.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/16/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombossRiftBattleModule_h
#define PlantsVersusZombies2_ZombossRiftBattleModule_h

#include <string>
#include <vector>

#include "BoardEnums.h"
#include "LevelModule.h"
#include "RtObject.h"
#include "ZombossBattleModule.h"

namespace Message
{
    void BossRiftEnterLootPhase();
}

namespace ProfileUtils
{
    class ChallengeStatusHolder;
}

class ZombossRiftBattleModule : public ZombossBattleModule
{
public:
    RT_CLASS_DEFINE(ZombossRiftBattleModule, ZombossBattleModule, RtClass);
    
    
    int GetTotalZombossStages() const;
    bool IsVictory();
    void CheatForceVictory();
    void HandlePointOfLoss(pvztime_t i_timeAdded);
    void AddTime(pvztime_t i_time);
    void CheatSetTime(pvztime_t i_time);
    
    void    onGameplayStarted();
    void    onGameplayEnded();
    void    onGameplayUpdate();

protected:
    void registerForEvents() override;
    void onLossImminent();

private:
    void onShowProgressMeter();
    void onSetCurrentPhase(int i_currentPhase, int i_scoreValue);
    
    void onLoadComplete() override;
    
    bool getPreventSave();

    void endLevel();
    
    void gatherExtraChallenges(ProfileUtils::ChallengeStatusHolder *io_extraChallenges);

    int m_zombossPhaseReached = 0;
};

class ZombossRiftBattleModuleProperties : public ZombossBattleModuleProperties
{
public:
    RT_CLASS_DEFINE(ZombossRiftBattleModuleProperties, ZombossBattleModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return ZombossRiftBattleModule::StaticGetClass();
    }

    int ZombossPhases = 1;
    pvztime_t TimeLimit = 180;
};

#endif
