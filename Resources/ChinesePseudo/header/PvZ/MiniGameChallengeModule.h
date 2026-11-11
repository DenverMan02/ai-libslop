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
#include "TimeChallengeEndLevelUI.h"

class MiniGameChallengeModule : public ChallengeModule
{
public:
    RT_CLASS_DEFINE(MiniGameChallengeModule, ChallengeModule, RtClass);
    
    bool	IsChallengeActive() override;
    void	SetActiveChallengesCompleted() override;

	void OnRequestBossChallengeLevelEnd(int result, const class S2C_MiniGameResult* data);
	void KillEndLevelUI();
	void ShowEndLevelUI();
	void setIsFinsh(bool isFinish);
	bool gegIsFinish() const;
protected:
	void registerForEvents() override;
	void DropLoot(const VacationMaterialItem& loot);
	void DropLoot(int id, int count);
private:
    void	initializeModule() override;
    
    void 	getActiveChallenges(std::vector<class Challenge*>& o_challenges) override;
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	void GameplayStarted();
	void GameplayEnded();
    bool	m_challengesActive;
	void OnContinue(TimeChallengeEndLevelUI* ui);
	void Update();
	int getStageScore(int index) const;
private:
	int m_state = 0;
	int m_score = 0;
	pvztime_t m_stateTime = 0;
	TimeChallengeEndLevelUI* m_endLevelUI = nullptr;
	bool m_bIsFinish;
};

class MiniGameChallengeModuleProperties : public ChallengeModuleProperties
{
public:
    RT_CLASS_DEFINE(MiniGameChallengeModuleProperties, ChallengeModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return MiniGameChallengeModule::StaticGetClass();
    }
    
    MiniGameChallengeModuleProperties()
    {
        ChallengesAlwaysAvailable = false;
    }
    
    bool ChallengesAlwaysAvailable;
};

#endif
