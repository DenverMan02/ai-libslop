//
//  JoustOutro.h
//  PlantsVersusZombies2
//
//  Created by Randy Knapp on 9/5/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__JoustOutro__
#define __PlantsVersusZombies2__JoustOutro__

#include <vector>
#include "AwardDiff.hpp"
#include "OutroModule.h"
#include "RtObject.h"
#include "AdaptorJoustResultsScreen.h"
#include "AdaptorJoustWinStreakDialog.h"
#include "JoustDataPackets.h"

class JoustOutro : public OutroModule
{
public:
    RT_CLASS_DEFINE(JoustOutro, OutroModule, RtClass);

	JoustOutro();
	virtual ~JoustOutro();
	
    void registerForEvents() override;

private:
	void startWinOutro();
	void startLossOutro();
	void giveAwards();
	int  giveCrowns();
	void recordLevelEnd(bool i_victory);
	
	void onResultsScreenDismissed();
	
	void showResultsScreen(bool i_victory, int i_playerScore, int i_opponentScore);
	void showWinStreakDisplay();
	void showAwardScreen();
	
	void onWinStreakDismissed();
	void onAwardScreenDismissed();
	
	void onJoustNetworkResponse(int i_context, int i_status);
	void onJoustNetworkIssueDecision(int i_context, int i_decision);
	
	AdaptorJoustResultsScreen* m_resultsScreen;
	AdaptorJoustWinStreakDialog* m_winStreak;
	
	class LevelOfTheDay_RewardItemType m_reward;
	std::vector<class LevelOfTheDay_RewardItemType> m_subRewards;
	AwardDiffSet m_awardSet;
	
	bool m_levelHasEnded;
	bool m_levelWasWon;
};

class JoustOutroProperties : OutroModuleProperties
{
    RT_CLASS_DEFINE(JoustOutroProperties, OutroModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return JoustOutro::StaticGetClass();
	}
};

#endif
