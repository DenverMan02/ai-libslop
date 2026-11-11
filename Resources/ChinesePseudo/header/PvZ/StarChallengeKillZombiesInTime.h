//
//  StarChallengeKillZombiesInTime.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarChallengeKillZombiesInTime__
#define __PlantsVersusZombies2__StarChallengeKillZombiesInTime__

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "GameNotify.h"
#include "TodStringFile.h"
#include "UIWidget.h"
#include "DamageInfo.h"

class StarChallengeKillZombiesInTime : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeKillZombiesInTime, Challenge, RtClass);

	virtual void registerForEvents() override;

    StarChallengeKillZombiesInTime()
	{
	}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
    void gameplayEnded();
	void onUpdate();

	void onZombieKilled(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	
	virtual ChallengeUI* getChallengeUI() override
	{
		return m_comboMeter->Cast<ChallengeUI>();
	}

	std::vector<pvztime_t> m_zombiesKilled;
	RtWeakPtr<UIWidget> m_comboMeter;
};

class StarChallengeKillZombiesInTimeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeKillZombiesInTimeProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeKillZombiesInTime::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString zombies = StrFormat(_S("%d"), ZombiesToKill);
		SexyString time = StrFormat(_S("%d"), (int)Time);

		SexyString endString = TodReplaceString(_S("[STARCHALLENGE_KILL_ZOMBIES_IN_TIME]"), _S("{ZOMBIES}"), zombies);
		endString = TodReplaceString(endString, _S("{TIME}"), time);

		return endString;
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_KILL_ZOMBIES_IN_TIME_NAME]"));
	}
	
    StarChallengeKillZombiesInTimeProps()
	: ZombiesToKill(0)
	, Time(0.f)
	{}

	int ZombiesToKill;
	float Time;
};

#endif /* defined(__PlantsVersusZombies2__StarChallengeKillZombiesInTime__) */
