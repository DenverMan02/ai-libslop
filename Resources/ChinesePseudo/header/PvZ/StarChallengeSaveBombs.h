//
//  StarChallengeSaveBombs.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 5/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeSaveBombs_h
#define PlantsVersusZombies2_StarChallengeSaveBombs_h

#include "ChallengeModule.h"
#include "GameNotify.h"
#include "ScrollingCounter.h"
#include "TodStringFile.h"
#include "UIWidget.h"

class StarChallengeSaveBombs : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeSaveBombs, Challenge, RtClass);
	
	virtual void registerForEvents() override;

    StarChallengeSaveBombs()
	{
		// Do nothing.
	}

private:
    void onBombTriggered(class Bomb* i_bomb);
    void gameplayEnded();
};

class StarChallengeSaveBombsProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeSaveBombsProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeSaveBombs::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_RETAIN_BOMBS]"));
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_RETAIN_BOMBS_NAME]"));
	}
	
    StarChallengeSaveBombsProps()
	{
		// Do nothing.
	}
};

#endif
