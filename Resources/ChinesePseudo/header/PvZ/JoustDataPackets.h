//
//  JoustDataPackets
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/8/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__JoustDataPackets__
#define __PlantsVersusZombies2__JoustDataPackets__

#include "LevelOfTheDay_RewardData.h"
#include "JoustSchedule.h"

typedef uint64 ScoreType;

enum JoustAPINetworkEnvironments
{
	Joust_Environment_Dev,
	Joust_Environment_Live,
	Joust_Environment_Future,
	Joust_Environment_Test // used for our playtests
};

struct JoustPlayerPlantData
{
	JoustPlayerPlantData() { Type = 0; Level = 0; Imitater = false; }
	JoustPlayerPlantData(int i_type, int i_level) { Type = i_type; Level = i_level; Imitater = false; }
	JoustPlayerPlantData(int i_type, int i_level, bool i_imitater) { Type = i_type; Level = i_level; Imitater = i_imitater; }

	int Type;
	int Level;
	bool Imitater;		// Note: This might be better expressed as flags such as IsImitater.
};

struct AwardInfo
{
	AwardInfo()
	{
		Type = AWARD_None;
		Id = 0;
	}
	AwardType Type;
	int Id;
};

struct JoustPlayerLoadoutData
{
	std::vector<JoustPlayerPlantData> Plants;
};

enum JoustLeagueType
{
	IRON_LEAGUE,
	COPPER_LEAGUE,
	SILVER__LEAGUE,
	GOLD_LEAGUE,
	JADE_LEAGUE,
	LEAGUE_COUNT
};

struct JoustBonusInfo
{
	JoustBonusInfo()
	{
		Id = 0;
		Quantity = 0;
	}
	int Id;
	int Quantity;
};

struct JoustLeaderboardRewardInfo
{
	JoustLeaderboardRewardInfo()
	{
		StartPlace = 0;
		EndPlace = 0;
	}

	int StartPlace;
	int EndPlace;
	std::vector<JoustBonusInfo> BonusInfo;
};

struct LocalJoustLeaderboardRewards
{
	LocalJoustLeaderboardRewards()
	{
		LeagueType = IRON_LEAGUE;
	}

	JoustLeagueType LeagueType;
	std::vector<JoustLeaderboardRewardInfo> Rewards;
};

struct JoustPlayerData
{
	JoustPlayerData()
	{
		PlayerId = -1;
		Avatar = 0;
		Crowns = 0;
		Name = L"";
		Color = 0;
		VIP = false;
	}
	
	virtual ~JoustPlayerData() {}
	
	int32 PlayerId;
	int Avatar;
	std::wstring Name;
	int Crowns;
	int Color;
	bool VIP;
	
	virtual SexyString ToString() const;
};

struct JoustLocalPlayerData : public JoustPlayerData
{
	JoustLocalPlayerData() : JoustPlayerData()
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
	
	SexyString ToString() const override;
};

enum class JoustAPIContext
{
	None,
	Post_Avatar,
	Get_Dashboard,
	Post_Match,
	Post_CompleteMatch,
	Post_RegisterForTournament
};

enum class JoustAPIResponseStatus
{
	None,
	WaitingOnResponse,
	ResponseSuccess,
	ResponseFailNetwork,
	ResponseFailInvalidData,
	ResponseFailInvalidMatch,
	ResponseFailInvalidTournamentExpired,
	ResponseFailInvalidTournamentNotRegistered,
	ResponseFailInvalidPlayer
};

enum JoustAPINetworkIssueDecision
{
	DecideRetry,
	DecideAbandon
};

enum JoustAPINetworkIssue
{
	Disconnected,
	InvalidMatch,
	Timeout,
	Timeout_AtEndOfLevel,
	TournamentExpired
};

struct JoustAPIResponse
{
	virtual ~JoustAPIResponse() {}
	
	JoustAPIContext Context;
	
	virtual std::string ToString() const;
};

struct JoustAPIResponseLeagueChange
{
	JoustAPIResponseLeagueChange()
	{
		HasLeagueChangeEvent = false;
		NewLeague = 0;
		PreviousLeague = 0;
		FinalPosition = 0;
	}
	
	bool HasLeagueChangeEvent;
	int NewLeague;
	int PreviousLeague;
	int FinalPosition;
	
	std::vector<JoustBonusInfo>	Rewards;
	
	SexyString ToString() const;
};

struct JoustTournamentData
{
	long	ID = 0;
	time_t	EndTime = PVZ_EOT();
};

struct JoustAPIResponseDashboard : public JoustAPIResponse
{
	long ServerTime;
	
	int PlayerCrowns;
	int PlayerWinStreak;
	int PlayerAvatarNameID;
	int PlayerAvatarIconID;
	int PlayerLeague;
	int PlayerTotalWins;
	int PlayerLeaderboardPosition;
	
	JoustTournamentData 			Tournament;
	
	std::vector<JoustPlayerData>	Leaderboard;

	JoustAPIResponseLeagueChange	LeagueChangeEvent;
	
	std::vector<std::vector<JoustLeaderboardRewardInfo>> LeaderboardRewards;

	std::vector<JoustBonusInfo>		WinStreakRewards;

	bool CanPlay;

	std::string ToString() const override;
};

struct JoustAPIResponseMatch : public JoustAPIResponse
{
	JoustAPIResponseMatch()
	{
		League = 0;
		Score = 0;
		MatchID = "";
		LevelSeed = "";
		OpponentID = "";
	}
	
	std::string MatchID;
	int League;
	std::string LevelSeed;
	std::string OpponentID;
	std::wstring OpponentName;
	int OpponentAvatar;
	int Score;
	Buffer ReplayData;
	
	std::string ToString() const override;
};

struct JoustAPIResponseMatchComplete : public JoustAPIResponse
{
	int 					CrownsToAward;
	std::vector<LevelOfTheDay_RewardItemType>	Rewards;
	bool					NeedsAward = false;
	LevelOfTheDay_RewardItemType CurrentReward;
	
	std::string ToString() const override;
};

struct JoustAPIPostAvatarChange
{
	int PlayerAvatarNameID;
	int PlayerAvatarIconID;
};

struct JoustAPIPostRequestMatch
{
	std::string MatchID;
	int PlayerWinStreak;
	int PlayerAvatarNameID;
	int PlayerAvatarIconID;
	int PlayerLeague;
};

struct JoustAPIPostCompleteMatch : public Sexy::RtObject
{
	
	std::string MatchID;
	std::string OpponentID;
	int WinRatio;
	std::string LevelSeed;
	int League;
	int Score;
	Buffer ReplayData;
	int PlantPower;
};

struct JoustIncompleteMatchData : public Sexy::RtObject
{
	RT_CLASS_DEFINE(JoustIncompleteMatchData, Sexy::RtObject, Sexy::RtClass);

	std::string MatchID;
	std::string OpponentID;
	std::string LevelSeed;
	int League;
};

namespace Message
{
	// Subscribe to handle the result of the JoustNetworkIssue dialog.
	void JoustNetworkIssueDecision(int i_context, int i_decision);
}

#endif
