//
//  StarChallengeSunProduced.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeSunProduced_h
#define PlantsVersusZombies2_StarChallengeSunProduced_h

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "GameNotify.h"
#include "ScrollingCounter.h"
#include "TodStringFile.h"
#include "UIWidget.h"

class StarChallengeSunProduced : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeSunProduced, Challenge, RtClass);

	virtual void registerForEvents() override;

    StarChallengeSunProduced();

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

    void onSunProduced(int amount);
    void onSunProducedByPlant(class CollectableSun* i_sun);
    void updateSunCounterWidget();
	
	virtual ChallengeUI* getChallengeUI() override
	{
		return m_sunCounterWidget->Cast<ChallengeUI>();
	}

	float m_sunProduced;
	
	RtWeakPtr<UIWidget> m_sunCounterWidget;
};

class StarChallengeSunProducedProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeSunProducedProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeSunProduced::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"),(int)TargetSun);
		return TodReplaceString(_S("[STARCHALLENGE_SUN_PRODUCED]"), _S("{COUNT}"), target);
	}	

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_SUN_PRODUCED_NAME]"));
	}
	
    StarChallengeSunProducedProps()
	: TargetSun(0.0f)
	{}

	float TargetSun;
};

#endif
