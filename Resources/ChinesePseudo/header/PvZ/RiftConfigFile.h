//
//  RiftConfigFile.hpp
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 6/18/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef RiftConfigFile_h
#define RiftConfigFile_h

#include "LevelOfTheDay_RewardData.h"
//#include "PropertySheetBase.h"
#include "ZombiePropertySheet.h"

enum LeagueFrameType
{
	LeagueFrameType_Normal = -1,
	LeagueFrameType_Gold,
	LeagueFrameType_Silver,
	LeagueFrameType_Bronze
};

struct LeagueFrameRange
{
	LeagueFrameRange()
	: Start(0)
	, End(0)
	, Type(LeagueFrameType_Normal)
	, NextLeague(0)
	{

	}

	int Start;
	int End;
	LeagueFrameType Type;
	int NextLeague;
};

class RiftConfigSheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(RiftConfigSheet, PropertySheetBase, RtClass);
	RiftConfigSheet()
	{
		ZombossUnlockCost = 100;
		ZPSResetValue = 5;
		ZPSCap = 150;
		ZPSDecayPeriodSeconds = 0;
		ZombossAvailableHours = 24;
		RiftLevelCosts = {0, 25, 50};
		ZPSGainedPerDifficultyLevel = {5, 15, 25};
		EnergyRefillPeriodSeconds = 60;
		EnergyRefillCap = 400;
		PerkSelectionCosts = {0, 3, 6};
		ZombossCycleHours = 24;
		ZombossFightsPerCycle = 1;
		BaseScoreFactor1 = 0.0f;
		BaseScoreFactor3 = 0.0f;
		RiftTimedLevelBaseScoreFactor1 = 0.0f;
		RiftTimedLevelBaseScoreFactor2 = 0.0f;
		
		if (ZPSBackupRewards.empty())
		{
			LevelOfTheDay_RewardItemType baseReward;
			baseReward.Award = AWARD_Coins;
			baseReward.AwardQuantity = 500;
			ZPSBackupRewards.push_back(baseReward);
		}
	}
	
	int ZombossUnlockCost;
	int ZPSResetValue;
	int ZPSCap;
	serializable_time_t ZPSDecayPeriodSeconds; // May be removed; still pending design.  For now, should treat 0 and below as no decay.
	int ZombossAvailableHours;
	std::vector<int> RiftLevelCosts;
	std::vector<int> ZPSGainedPerDifficultyLevel;
	serializable_time_t EnergyRefillPeriodSeconds;
	int EnergyRefillCap;
	std::vector<int> PerkSelectionCosts;
	std::vector<LevelOfTheDay_RewardItemType> ZPSBackupRewards;
	int ZombossCycleHours; //In hours - How long the player has until Zomboss is available again.  Timed from event start - if Zomboss is defeated right before the end of the cycle, it will be available again in that very next cycle.
	int ZombossFightsPerCycle;
	std::vector<ZombieLevelStat> ZombieLevelStats;
	std::vector<int> ZombieLevelForDifficulty;
	float BaseScoreFactor1;
	std::vector<float> BaseScoreFactor2;
	float BaseScoreFactor3;
	float RiftTimedLevelBaseScoreFactor1;
	float RiftTimedLevelBaseScoreFactor2;
	std::vector<int> MaxScoreNormal;
	std::vector<int> MaxScoreRiftTimed;
	std::vector<int> MaxScoreTimeLimited;
	int 			 MaxScoreBoss;
	std::vector<float> BonusScoreFactor;
	std::vector<float> BossScoreFactor;
	std::vector<std::string>	LeagueIcons;
	std::vector<std::string>	LeagueSmallIcons;
	std::vector<std::string>	LeagueNames;
	std::vector<std::string>	ShortLeagueNames;
	
	std::vector<std::vector<LeagueFrameRange>> FrameMaps;

	std::string ToString();
	
	static RiftConfigSheet* GetProperties(const std::string& i_configKey);
};

#endif /* RiftConfigFile_h */
