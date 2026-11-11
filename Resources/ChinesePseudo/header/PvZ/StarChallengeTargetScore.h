//
//  StarChallengeTargetScore.h
//  PlantsVersusZombies2
//
//  Created by Alex Kobylarek on 06/21/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeTargetScore_h
#define PlantsVersusZombies2_StarChallengeTargetScore_h

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "LevelModule.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyAppFramework/Common.h"
#include "SexyString.h"
#include "TodCommon.h"
#include "TodStringFile.h"
#include "UIWidget.h"
#include "string.h"

namespace Message
{
    void ScoreChallengeCompleted();
}

class StarChallengeTargetScore : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeTargetScore, Challenge, RtClass);

	void registerForEvents() override;

	StarChallengeTargetScore();
	
	//SexyString GetDescriptionFailure() const override;
	SexyString GetDescription() const override;

	SexyString GetProgressDescription() const override;

private:
	void gameplayEnded();

	void onScoreUpdated(int amount, float i_bonusMultiplier);
	void onScoreCalculated(int score, const std::string& i_ruleset, float i_bonusMultiplier);
	
	float m_currentScore;
	float m_bonusMultiplier;
};

class StarChallengeTargetScoreProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeTargetScoreProps, LevelModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return StarChallengeTargetScore::StaticGetClass();
	}
	
	SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), (int)TargetScore);
		return TodReplaceString(StringToSexyString(Description), _S("{NUMBER}"), target);
	}
	
	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(StringToSexyString(DescriptiveName));
	}
	
	StarChallengeTargetScoreProps()
	: TargetScore(0.0f)
	, Description("")
	, DescriptionFailure("")
	, DescriptiveName("")
	{}
	
	float TargetScore;
	std::string Description;
	std::string DescriptionFailure;
	std::string DescriptiveName;
};
#endif
