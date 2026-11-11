//
//  JoustSchedule
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/5/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__JoustSchedule__
#define __PlantsVersusZombies2__JoustSchedule__

#include "PropertySheetBase.h"
#include "LevelOfTheDay_RewardData.h"

class JoustTournamentDefinition
{
public:
	JoustTournamentDefinition()
	{
		StartDate = 0;
	}
	
	long StartDate;
	
	std::string LeaderboardDefinitionKey;
	std::string CrownRewardKey;
	std::string LevelSetKey;
	std::vector<std::string> ProgressiveRewardKeys;
	std::vector<std::string> TournamentRewardKeys;
};

class JoustSchedule : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(JoustSchedule, PropertySheetBase, RtClass);
	
	JoustSchedule()
	{
	}
	
	std::vector<JoustTournamentDefinition>	TournamentDefinitions;
	
public:
	
	const JoustTournamentDefinition* GetTournamentDefinition(long i_tournamentStartTime);
	
public:
	static JoustSchedule* GetSchedule();
};

class JoustLeaderboardDefinition : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(JoustLeaderboardDefinition, PropertySheetBase, RtClass);
	
	JoustLeaderboardDefinition()
	{
		NumLeagues = 8;
		LeaderboardSize = 15;
		PromotionCount = 3;
		DemotionCount = 3;
		MinimumPlayerCountBeforeDemotion = 10;
		MinimumLeagueBeforeDemotion = 2;
	}
	
	int NumLeagues;
	int LeaderboardSize;
	int PromotionCount;
	int DemotionCount;
	int MinimumPlayerCountBeforeDemotion;
	int MinimumLeagueBeforeDemotion;
	
public:
	static JoustLeaderboardDefinition* GetProperties(const std::string& i_leaderboardKey);
};

class JoustCrownRewardDefinition : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(JoustCrownRewardDefinition, PropertySheetBase, RtClass);
	
	JoustCrownRewardDefinition()
	{
		CrownsWinBase = 0;
		CrownsLoss = 0;
	}
	
	int CrownsLoss;
	int CrownsWinBase;
	std::vector<int>	CrownsProgressiveBonus;
	
public:
	static JoustCrownRewardDefinition* GetProperties(const std::string& i_crownRewardKey);
};

class JoustLevelSet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(JoustLevelSet, PropertySheetBase, RtClass);
	
	JoustLevelSet()
	{
	}
	
	std::string LevelName;
	std::vector<uint32> LevelSeeds;
	
public:
	static JoustLevelSet* GetProperties(const std::string& i_levelSet);
};

class JoustProgressiveRewardDefinition : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(JoustProgressiveRewardDefinition, PropertySheetBase, RtClass);
	std::vector<LevelOfTheDay_RewardItemType> ProgressiveRewards;
	
public:
	static JoustProgressiveRewardDefinition* GetProperties(const std::string& i_rewardKey);
};

class JoustTournamentRewardDefinition : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(JoustTournamentRewardDefinition, PropertySheetBase, RtClass);
	std::vector< std::vector<LevelOfTheDay_RewardItemType> > PlacementRewards;
	
public:
	static JoustTournamentRewardDefinition* GetProperties(const std::string& i_rewardKey);
};

#endif
