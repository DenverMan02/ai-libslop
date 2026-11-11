//
//  StarChallengeSunUsed.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/7/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeSunUsed_h
#define PlantsVersusZombies2_StarChallengeSunUsed_h

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "GameNotify.h"
#include "ScrollingCounter.h"
#include "TodStringFile.h"
#include "ChallengeUI.h"

class StarChallengeSunUsed : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeSunUsed, Challenge, RtClass);

	virtual void registerForEvents() override;

    StarChallengeSunUsed()
	: m_sunSpent(0)
	{}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onSunSpent(int i_amount);
	
	virtual ChallengeUI* getChallengeUI() override
	{
		return m_sunCounterWidget->Cast<ChallengeUI>();
	}

	int m_sunSpent;

	RtWeakPtr<UIWidget> m_sunCounterWidget;
};

class StarChallengeSunUsedProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeSunUsedProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeSunUsed::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumSun);
		return TodReplaceString(_S("[STARCHALLENGE_SUN_USED]"), _S("{COUNT}"), target);
	}
	
	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_SUN_USED_NAME]"));
	}
	
    StarChallengeSunUsedProps()
	: MaximumSun(0)
	{}

	int MaximumSun;
};

#endif
