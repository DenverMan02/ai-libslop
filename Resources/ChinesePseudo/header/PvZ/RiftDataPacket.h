/*
 * RiftDataPacket.h
 *
 *  Created on: 2020-6-1
 *      Author: Administrator
 */

#ifndef RIFTDATAPACKET_H_
#define RIFTDATAPACKET_H_

#include "LevelOfTheDay_RewardData.h"

struct RiftAwardInfo
{
	RiftAwardInfo()
	{
		Type = AWARD_None;
		Id = 0;
	}
	AwardType Type;
	int Id;
};

enum RiftLeagueType
{
	RIFT_IRON_LEAGUE,
	RIFT_COPPER_LEAGUE,
	RIFT_SILVER__LEAGUE,
	RIFT_GOLD_LEAGUE,
	RIFT_JADE_LEAGUE,
	RIFT_LEAGUE_COUNT
};

struct RiftBonusInfo
{
	RiftBonusInfo()
	{
		Id = 0;
		Quantity = 0;
	}
	int Id;
	int Quantity;
};

struct RiftLeaderboardRewardInfo
{
	RiftLeaderboardRewardInfo()
	{
		StartPlace = 0;
		EndPlace = 0;
	}

	int StartPlace;
	int EndPlace;
	std::vector<RiftBonusInfo> BonusInfo;
};

struct LocalRiftLeaderboardRewards
{
	LocalRiftLeaderboardRewards()
	{
		LeagueType = RIFT_IRON_LEAGUE;
	}

	RiftLeagueType LeagueType;
	std::vector<RiftLeaderboardRewardInfo> Rewards;
};

struct RiftPlayerData
{
	RiftPlayerData()
	{
		PlayerId = -1;
		Avatar = 0;
		Crowns = 0;
		Name = L"";
		Color = 0;
		VIP = false;
		RankAvatar = 0;
	}

	virtual ~RiftPlayerData() {}

	int32 PlayerId;
	int Avatar;
	std::wstring Name;
	int Crowns;
	int Color;
	bool VIP;
	int RankAvatar;
};

struct RiftLocalPlayerData : public RiftPlayerData
{
	RiftLocalPlayerData() : RiftPlayerData()
	{
		WinStreak = 0;
		League = 0;
		TotalWins = 0;
		LeaderboardPosition = -1;
	}

	int WinStreak;
	int League;
	int TotalWins;
	int LeaderboardPosition;
};

class RiftLeaderboardData
{
public:
	std::vector<RiftPlayerData>	Players;

	RiftLocalPlayerData			LocalPlayer;
};

enum class RiftAPIContext
{
	None,
	Get_MainEntry,
	Get_LeaderBoardEntry,
	Get_StoreEntry,
	Get_PerkEntry,
	Get_FuelEntry,
	Post_Play,
	Post_EndPlay
};

enum class RiftAPIResponseStatus
{
	None,
	WaitingOnResponse,
	ResponseSuccess,
	ResponseFailNetwork,
	ResponseFailInvalidData
};

enum RiftAPINetworkIssueDecision
{
	Rift_DecideRetry,
	Rift_DecideAbandon
};

enum class RiftAPINetworkIssue
{
	Disconnected,
	InvalidMatch,
	Timeout,
	Timeout_AtEndOfLevel,
	TournamentExpired
};

struct RiftAPIResponse
{
	virtual ~RiftAPIResponse() {}

	RiftAPIContext Context;
};

struct RiftAPIResponseLeagueChange
{
	RiftAPIResponseLeagueChange()
	{
		HasLeagueChangeEvent = false;
		HasSeasonChangeEvent = false;
		NewLeague = 0;
		PreviousLeague = 0;
		FinalPosition = 0;
	}

	bool HasLeagueChangeEvent;
	bool HasSeasonChangeEvent;
	int NewLeague;
	int PreviousLeague;
	int FinalPosition;

	std::vector<RiftBonusInfo>	Rewards;
};

struct RiftDifficultyInfo
{
	RiftDifficultyInfo()
	{
		ZpsRewards = 0;
	}

	int ZpsRewards;
	std::vector<RiftBonusInfo> Rewards;
};

struct RiftDifficultyReward
{
	RiftDifficultyInfo	Lvl1Rewards;
	RiftDifficultyInfo	Lvl2Rewards;
	RiftDifficultyInfo	Lvl3Rewards;
};

struct RiftBossReward
{
	std::vector<RiftBonusInfo> Phase1Rewards;
	std::vector<RiftBonusInfo> Phase2Rewards;
	std::vector<RiftBonusInfo> Phase3Rewards;
	std::vector<RiftBonusInfo> NormalRewards;
};

struct RiftPerkData
{
	RiftPerkData()
	{
		Id = 0;
		Level = 0;
	}

	int Id;
	int Level;
};

enum RiftLevelType
{
	None,
	Normal_Level,
	Boss_Level
};

enum RiftResultType
{
	Rift_Result_None = -1,
	Rift_Result_Lose,
	Rift_Result_Win
};

struct RiftPostEndPlay
{
	RiftPostEndPlay()
	{
		LevelType = None;
		LevelIndex = 0;
		DifficultLevel = 0;
		Score = 0;
		Result = Rift_Result_None;
		PerkDraw = false;
		BossStageRewardRatio = 1.0f;
	}

	RiftLevelType LevelType;
	int LevelIndex;
	int DifficultLevel;
	int Score;
	RiftResultType Result;
	bool PerkDraw;
	float BossStageRewardRatio;
};

namespace Message
{
	// Subscribe to handle the result of the JoustNetworkIssue dialog.
	void RiftNetworkIssueDecision(int i_context, int i_decision);
}


#endif /* RIFTDATAPACKET_H_ */
