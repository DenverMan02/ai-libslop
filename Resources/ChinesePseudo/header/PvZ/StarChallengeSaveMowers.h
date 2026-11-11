//
//  StarChallengeSaveMowers.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 5/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeSaveMowers_h
#define PlantsVersusZombies2_StarChallengeSaveMowers_h

#include "ChallengeModule.h"
#include "GameNotify.h"
#include "ScrollingCounter.h"
#include "TodStringFile.h"
#include "UIWidget.h"

class StarChallengeSaveMowers : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeSaveMowers, Challenge, RtClass);
	
	virtual void registerForEvents() override;

    StarChallengeSaveMowers()
	{
		// Do nothing.
	}

private:
    void onMowerTriggered(class LawnMower* i_mower);
    void gameplayEnded();
};

class StarChallengeSaveMowersProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeSaveMowersProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeSaveMowers::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_RETAIN_MOWERS]"));
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_RETAIN_MOWERS_NAME]"));
	}
	
    StarChallengeSaveMowersProps()
	{
		// Do nothing.
	}
};

#endif
