//
//  StarChallengeLevelTimer.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 5/7/2019.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TimedGameModule_h
#define PlantsVersusZombies2_TimedGameModule_h

#include <vector>

#include "BoardEnums.h"
#include "Core.h"
#include "LevelModule.h"

#include "ChallengeModule.h"
#include "Wave.h"

class UIWidget;

class StarChallengeLevelTimer : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeLevelTimer, Challenge, RtClass);
	
    StarChallengeLevelTimer();
	void	AddTime(pvztime_t i_time);
    void    CheatSetTime(pvztime_t i_time);
    
    void    onGameplayStarted();
    void    onGameplayEnded();
    void    onGameplayUpdate();
    void    registerForEvents() override;

    // Star Challenge impl
    SexyString GetDescription() const override;
    
    float   CalcLevelProgress();
    
private:
    
    void initLevelTimer();
    void endLevel();
    void gameplayWinConditionTest();
};


class StarChallengeLevelTimerProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeLevelTimerProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return StarChallengeLevelTimer::StaticGetClass();
	}

	StarChallengeLevelTimerProperties()
	{
		TimeLimit = 0.0f;
	}
	
	float TimeLimit;
};

#endif
