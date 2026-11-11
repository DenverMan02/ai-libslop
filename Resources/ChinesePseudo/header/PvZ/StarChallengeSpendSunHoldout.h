//
//  StarChallengeSpendSunHoldout.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/22/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeSpendSunHoldout_h
#define PlantsVersusZombies2_StarChallengeSpendSunHoldout_h

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "GameNotify.h"
#include "TodStringFile.h"
#include "Tribool.h"
#include "UIWidget.h"

class StarChallengeSpendSunHoldout : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeSpendSunHoldout, Challenge, RtClass);

	virtual void registerForEvents() override;

    StarChallengeSpendSunHoldout()
    : m_lastSunSpentTime(0.0f)
    {
        // Do nothing.
    }

private:
	void gameplayStarted();
	void gameplayUpdate();
	void gameplayEnded();

	void onSunSpent(int i_amount);
	
	virtual ChallengeUI* getChallengeUI() override
	{
		return m_sunCounterWidget->Cast<ChallengeUI>();
	}

	pvztime_t m_lastSunSpentTime;
	RtWeakPtr<UIWidget> m_sunCounterWidget;
};

class StarChallengeSpendSunHoldoutProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeSpendSunHoldoutProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeSpendSunHoldout::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), HoldoutSeconds);
		return TodReplaceString(_S("[STARCHALLENGE_SPEND_SUN_HOLDOUT]"), _S("{COUNT}"), target);
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_SPEND_SUN_HOLDOUT_NAME]"));
	}
	
    StarChallengeSpendSunHoldoutProps()
	: HoldoutSeconds(0)
	{}

	int HoldoutSeconds;
};

#endif
