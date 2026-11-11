//
//  StarChallengeModule.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeModule_h
#define PlantsVersusZombies2_StarChallengeModule_h

#include <vector>

#include "ChallengeModule.h"
#include "LevelModule.h"
#include "RtObject.h"
#include "BaseChallengeModule.h"

class StarChallengeModule : public BaseChallengeModule
{
public:
    RT_CLASS_DEFINE(StarChallengeModule, BaseChallengeModule, RtClass);
    
//    bool	IsChallengeActive() override;
//    void	SetActiveChallengesCompleted() override;
//
//private:
//    void	initializeModule() override;
//
//    void 	getActiveChallenges(std::vector<class Challenge*>& o_challenges) override;
//
//    bool	m_challengesActive;
};

class StarChallengeModuleProperties : public BaseChallengeModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeModuleProperties, BaseChallengeModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return StarChallengeModule::StaticGetClass();
    }
    
//    StarChallengeModuleProperties()
//    {
//        //ChallengesAlwaysAvailable = false;
//    }
    
    //bool ChallengesAlwaysAvailable;
};

#endif
