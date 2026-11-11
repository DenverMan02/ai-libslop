//
//  StarChallengeBeatTheLevel.h
//  PlantsVersusZombies2
//
//  Created by jsola on 4/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeBeatTheLevel_h
#define PlantsVersusZombies2_StarChallengeBeatTheLevel_h

#include "ChallengeModule.h"
#include "TodStringFile.h"

class StarChallengeBeatTheLevel : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeBeatTheLevel, Challenge, RtClass);
	
    StarChallengeBeatTheLevel()
	{}

    void registerForEvents() override;
    
private:
    void gameplayEnded();
};

class StarChallengeBeatTheLevelProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeBeatTheLevelProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeBeatTheLevel::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		return TodStringTranslate(StringToSexyStringFast(Description));
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(StringToSexyStringFast(DescriptiveName));
	}
	
    StarChallengeBeatTheLevelProps()
	{}

	std::string				Description;
	std::string				DescriptiveName;
};


#endif
