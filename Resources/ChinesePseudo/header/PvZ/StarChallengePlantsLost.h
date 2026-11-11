//
//  StarChallengePlantsLost.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/8/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengePlantsLost_h
#define PlantsVersusZombies2_StarChallengePlantsLost_h

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "GameNotify.h"
#include "ScrollingCounter.h"
#include "TodStringFile.h"
#include "UIWidget.h"

class StarChallengePlantsLost : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengePlantsLost, Challenge, RtClass);
	
	virtual void registerForEvents() override;

    StarChallengePlantsLost()
	: m_plantsLost(0)
	{}

	SexyString GetProgressDescription() const override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onPlantLost(class Plant* i_plant);
    void onLilyPadDied(class GridItemLilyPad* i_lilyPad);
	void onFlowerPotDied(class GridItemFlowerPot* i_flowerPot);
    void handlePlantDied();
	
	virtual ChallengeUI* getChallengeUI() override
	{
		return m_plantCountUI->Cast<ChallengeUI>();
	}

	int m_plantsLost;

	RtWeakPtr<UIWidget> m_plantCountUI;
};

class StarChallengePlantsLostProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengePlantsLostProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengePlantsLost::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumPlantsLost);
        if (MaximumPlantsLost == 1)
        {
            return TodReplaceString(_S("[STARCHALLENGE_PLANTS_LOST_SINGLE]"), _S("{COUNT}"), target);
        }
        else
        {
            return TodReplaceString(_S("[STARCHALLENGE_PLANTS_LOST]"), _S("{COUNT}"), target);
        }
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANTS_LOST_NAME]"));
	}
	
    StarChallengePlantsLostProps()
	: MaximumPlantsLost(0)
	{}

	int MaximumPlantsLost;
};

#endif
