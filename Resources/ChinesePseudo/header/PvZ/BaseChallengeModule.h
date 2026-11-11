//
//  BaseChallengeModule.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_BaseChallengeModule_h
#define PlantsVersusZombies2_BaseChallengeModule_h

#include <vector>

#include "ChallengeModule.h"
#include "LevelModule.h"
#include "RtObject.h"

class BaseChallengeModule : public ChallengeModule
{
public:
	RT_CLASS_DEFINE(BaseChallengeModule, ChallengeModule, RtClass);
	
	void	GatherDependentModulePropertySheets(std::vector<LevelModulePropertiesPtr>& io_dependent) override;
	bool	IsChallengeActive() override;
	void	SetActiveChallengesCompleted() override;
	void 	getActiveChallenges(std::vector<class Challenge*>& o_challenges) override;
    void    getChallenges(std::vector<class Challenge*>& o_challenges) override;
    void    getChallengesByChoose(std::vector<class Challenge*>& o_challenges, std::vector<bool> chooseList);
private:
	void	initializeModule() override;

	bool	m_challengesActive;
};

class BaseChallengeModuleProperties : public ChallengeModuleProperties
{
public:
	RT_CLASS_DEFINE(BaseChallengeModuleProperties, ChallengeModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return BaseChallengeModule::StaticGetClass();
	}
	
	BaseChallengeModuleProperties()
	{
		ChallengesAlwaysAvailable = false;
	}
	
	bool ChallengesAlwaysAvailable;
};

#endif
