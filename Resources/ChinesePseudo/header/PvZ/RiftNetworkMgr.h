/*
 * RiftNetworkMgr.h
 *
 *  Created on: 2020-6-1
 *      Author: Administrator
 */

#ifndef RIFTNETWORKMGR_H_
#define RIFTNETWORKMGR_H_

#include "Core.h"
#include "RiftDataPacket.h"
#include "NetworkServiceManager.h"
#include "NetworkData.h"

class NetworkMainEntryInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkMainEntryInfo, Sexy::RtObject, Sexy::RtClass);

public:
    int CurrentZPS;
    int CurrentTheme;
    std::vector<int> TimedEventThemes;
    std::string CurrentWorld;
    int LeftTime;
    int ThemeLeftTime;
    int LimitedPlantId;
    int CurrentFuel;
    std::vector<RiftDifficultyReward> LevelRewards;
    RiftBossReward BossRewards;
    std::vector<RiftPerkData> UnlockedPerks;
    int FuelToPlay;
    int CurrentScore;
    int CurrentLeague = 0;
    int CurrentRank;
    RiftAPIResponseLeagueChange	LeagueChangeEvent;
    int BossStartTime;
    int BossRewardRatio;
    std::vector<int> LeagueRewards;
    bool CanPlay;
    std::vector<std::vector<int>> LevelMaxScores;
    std::vector<int> BossMaxScores;
    int BossAttemptCount;
	bool IsCheatingCheck;// if cheating check
};

class NetworkEndOfPlay : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkEndOfPlay, INetworkData, RtClass);

public:
	int CurrentZPS;
	std::vector<RiftPerkData> DrawPerks;
	std::vector<RiftBonusInfo> Rewards;
	std::vector<RiftBonusInfo> BonusRewards;
	std::vector<RiftBonusInfo> FirstClearRewards;
	int CurrentTotalScore;
	int CheatingCheckWarningLevel;// cheating check warning level
	int ConsumeDuel;
};

class NetworkPlay : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkPlay, INetworkData, RtClass);

public:
	int CurrentFuel;
	std::string ArtifactOrderId;
};

struct LegendReward
{
	int Score;
	std::vector<S2C_BonusInfo> RewardList;
	int CanGet;
	int IsGet;
};

class NetworkLeaderboardInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkLeaderboardInfo, INetworkData, RtClass);

public:
    int PlayerCrowns;
	int PlayerLeague;
	int PlayerLeaderboardPosition;

	std::vector<RiftPlayerData>	Leaderboard;

	std::vector<std::vector<RiftLeaderboardRewardInfo>> LeaderboardRewards;

	std::vector<int> LeagueRewards;

	std::vector<LegendReward> LegendRewardList;
};

struct EndLevelData
{
	EndLevelData()
	{
		m_endLevelScore = 0;
		m_levelTime = 0;
		m_bossLevelTime = 0;
	}

	int m_endLevelScore;
	pvztime_t m_levelTime;
	pvztime_t m_bossLevelTime;
};

class RiftNetworkMgr : public LazySingleton<RiftNetworkMgr>
{
public:
	RiftNetworkMgr();
    virtual ~RiftNetworkMgr();

    void RequestGetMainEntry();
    void RequestPostEndPlay(RiftPostEndPlay i_data);
    void RequestPlay(bool i_bossLevel);
    void RequestLeaderboard();

    const NetworkMainEntryInfo& GetMainEntryInfo() { return m_mainEntryInfo; }
    const NetworkEndOfPlay& GetEndOfPlayInfo() { return m_endInfo; }
    const NetworkPlay& GetPlayInfo() { return m_startInfo; }
    const NetworkLeaderboardInfo& GetLeaderboardInfo() { return m_leaderboardInfo; }

    RiftLeaderboardData& GetLeaderboardData() { return LeaderboardData; }

    bool HasLeagueChangeEvent()	{ return LeagueChangeEvent.HasLeagueChangeEvent; }
    bool HasSeasonChangeEvent()	{ return LeagueChangeEvent.HasSeasonChangeEvent; }
	const RiftAPIResponseLeagueChange& GetLeagueChangeEvent() { return LeagueChangeEvent; }
	void SetLeagueChangeEvent(RiftAPIResponseLeagueChange& i_leagueChange) { LeagueChangeEvent = i_leagueChange; }
	void ClearLeagueChangeEvent() { LeagueChangeEvent.HasLeagueChangeEvent = false; }
	bool HasPromoted();
	int GetPromotedReward();

	void AddFuel(int i_amount);

	void SetEndLevelScore(int i_score) { m_endLevelData.m_endLevelScore = i_score; }
	int GetEndLevelScore() { return m_endLevelData.m_endLevelScore; }

	void SetLevelTime(pvztime_t i_time) { m_endLevelData.m_levelTime = i_time; }
	pvztime_t GetLevelTime() { return m_endLevelData.m_levelTime; }

	void SetBossLevelTime(pvztime_t i_time) { m_endLevelData.m_bossLevelTime = i_time; }
	pvztime_t GetBossLevelTime() { return m_endLevelData.m_bossLevelTime; }

	void SetZombossRewardRatio(float value) { m_zombossRewardRatio = value; }
	float GetZombossRewardRatio() { return m_zombossRewardRatio; }

private:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void syncMainEntryInfo();
	void initTestData();
	void initLeaderboardTestData();
	std::string getEndPlayList(RiftPostEndPlay i_data);
	void ApplyLeaderboardInfo(NetworkLeaderboardInfo& i_response);

	bool m_requested;
	NetworkMainEntryInfo m_mainEntryInfo;
	NetworkEndOfPlay m_endInfo;
	NetworkPlay m_startInfo;
	NetworkLeaderboardInfo m_leaderboardInfo;

	RiftLeaderboardData LeaderboardData;
	RiftAPIResponseLeagueChange	LeagueChangeEvent;

	EndLevelData m_endLevelData;

	float m_zombossRewardRatio;
};


#endif /* RIFTNETWORKMGR_H_ */
