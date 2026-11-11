/*
 * NewPVPDataPackets.h
 *
 *  Created on: 2022-10-31
 *      Author: admin
 */

#ifndef NEWPVPDATAPACKETS_H_
#define NEWPVPDATAPACKETS_H_

#include "NetworkData.h"

enum TriggerEventType
{
	TriggerEventType_Player,
	TriggerEventType_CPU
};

enum class NewPVPAPIContext
{
	None,
	Get_MainEntry,
	Sync_MatchPlayer,
	Query_MatchPlayer,
	Cancel_MatchPlayer,
	Sync_StartPlay,
	Query_StartPlay,
	Post_EndPlay,
	Save_BattleInfo,
	LevelUp_Zombie,
	Report_Oppoent
};

enum class NewPVPAPIResponseStatus
{
	None,
	WaitingOnResponse,
	ResponseSuccess,// all challenges pass
	ResponseFailChallengeNetwork,// not all challenges pass
	ResponseFailNetwork,// time energy is over
	ResponseFailInvalidData
};

struct NewPVPCPULevelInfo
{
	NewPVPCPULevelInfo(int i_plantId, int i_startWave, int i_column, int i_level, bool i_replace)
	: PlantId(i_plantId)
	, StartWave(i_startWave)
	, Column(i_column)
	, Level(i_level)
	, Replace(i_replace)
	{

	}

	NewPVPCPULevelInfo()
	: PlantId(0)
	, StartWave(0)
	, Column(0)
	, Level(1)
	, Replace(false)
	{

	}

	int PlantId;
	int StartWave;
	int Column;
	int Level;
	bool Replace;
};

struct NewPVPTutorialPlantInfo
{
	NewPVPTutorialPlantInfo(int i_type, int i_col, int i_row, bool i_delay, int i_wave)
	: Type(i_type)
	, Col(i_col)
	, Row(i_row)
	, Delay(i_delay)
	, Wave(i_wave)
	{

	}

	NewPVPTutorialPlantInfo()
	: Type(0)
	, Col(0)
	, Row(0)
	, Delay(false)
	, Wave(-1)
	{

	}

	int Type;
	int Col;
	int Row;
	bool Delay;
	int Wave;
};

struct NewPVPTutorialInfo
{
	NewPVPTutorialInfo()
	: StartingSun(0)
	, SunAdd(0)
	{

	}

	int StartingSun;
	int SunAdd;
	std::vector<NewPVPTutorialPlantInfo> PlantInfos;
};

struct Network_NewPVPZombieLevelInfo
{
	Network_NewPVPZombieLevelInfo()
	: UnlockedTurn(-1)
	, Level(1)
	, Cost(0)
	, CostAddValue(0)
	{

	}

	Network_NewPVPZombieLevelInfo(int i_turn, int i_level, int i_cost, int i_addValue)
	: UnlockedTurn(i_turn)
	, Level(i_level)
	, Cost(i_cost)
	, CostAddValue(i_addValue)
	{

	}

	int UnlockedTurn;
	int Level;
	int Cost;
	int CostAddValue;
};

struct Network_NewPVPZombiePacketInfo
{
	Network_NewPVPZombiePacketInfo()
	: Type(-1)
	{

	}

	Network_NewPVPZombiePacketInfo(int i_type, const std::vector<Network_NewPVPZombieLevelInfo>& i_infos)
	: Type(i_type)
	, LevelInfos(i_infos)
	{

	}

	int Type;
	std::vector<Network_NewPVPZombieLevelInfo> LevelInfos;
};

struct Network_NewPVPPlantPacketInfo
{
	Network_NewPVPPlantPacketInfo()
	: UnlockedTurn(-1)
	, Level(1)
	{

	}

	Network_NewPVPPlantPacketInfo(int i_turn, int i_level)
	: UnlockedTurn(i_turn)
	, Level(i_level)
	{

	}

	int UnlockedTurn;
	int Level;
};

struct Network_NewPVPZombieSkillInfo
{
	Network_NewPVPZombieSkillInfo()
	: Type(-1)
	, Duration(0)
	, Value(0)
	{

	}

	Network_NewPVPZombieSkillInfo(int i_type, float i_duration, float i_value)
	: Type(i_type)
	, Duration(i_duration)
	, Value(i_value)
	{

	}

	int Type;
	float Duration;
	float Value;
};

struct Network_NewPVPZombieUpgradeInfo
{
	Network_NewPVPZombieUpgradeInfo()
	: Type(-1)
	, Cost(0)
	, Value(0)
	, UnlockedTurn(0)
	{

	}

	Network_NewPVPZombieUpgradeInfo(int i_type, int i_cost, float i_value, int i_turn)
	: Type(i_type)
	, Cost(i_cost)
	, Value(i_value)
	, UnlockedTurn(i_turn)
	{

	}

	int Type;
	int Cost;
	float Value;
	int UnlockedTurn;
};

struct Network_NewPVPSunUpgradeInfo
{
	Network_NewPVPSunUpgradeInfo()
	: CD(0)
	, RequireNum(0)
	, SunAdd(0)
	, UpgradeCost(0)
	, MaxPlantNum(0)
	{

	}

	Network_NewPVPSunUpgradeInfo(float i_cd, int i_requireNum, int i_sunAdd, int i_upgradeCost, int i_maxPlantNum)
	: CD(i_cd)
	, RequireNum(i_requireNum)
	, SunAdd(i_sunAdd)
	, UpgradeCost(i_upgradeCost)
	, MaxPlantNum(i_maxPlantNum)
	{

	}

	float CD;
	int RequireNum;
	int SunAdd;
	int UpgradeCost;
	int MaxPlantNum;
};

struct Network_NewPVPSmallDuan
{
	Network_NewPVPSmallDuan() {}
	Network_NewPVPSmallDuan(int i_bNum, int i_sNum, int i_sReq, int i_rand, std::vector<S2C_BonusInfo> i_rewardInfo)
	{
		BigDuanNum = i_bNum;
		SmallDuanNum = i_sNum;
		StarNumRequired = i_sReq;
		RewardsInfo = i_rewardInfo;
	}

	int BigDuanNum = 1;
	int SmallDuanNum = 1;
	int StarNumRequired = 10;
	int Random = 0;

	std::vector<S2C_BonusInfo> RewardsInfo;
};

struct Network_NewPVPDuanState
{
	Network_NewPVPDuanState() {}
	Network_NewPVPDuanState(int i_big, int i_small, int i_star)
	: big(i_big)
	, small(i_small)
	, star(i_star)
	{}

	int big = 0;
	int small = 0;
	int star = 0;
};

struct Network_NewPVPZombieLevelUpValueData
{
	Network_NewPVPZombieLevelUpValueData()
	: Cost(0)
	, Hitpoints(0.0f)
	, DPS(0.0f)
	, Speed(0.0f)
	{

	}

	int Cost;
	float Hitpoints;
	float DPS;
	float Speed;
};

struct Network_NewPVPZombieLevelUpData
{
	Network_NewPVPZombieLevelUpData()
	: Type(-1)
	{

	}

	int Type;
	std::vector<Network_NewPVPZombieLevelUpValueData> ValueDatas;
};

// Networks
class Network_NewPVPPropertySheet : public INetworkData
{
public:
    RT_CLASS_DEFINE(Network_NewPVPPropertySheet, INetworkData, RtClass);

    float							CommonZombieCreatedCD = 2.0f;
    int								CommonMaxZombieCacheSize = 5;
    int								CommonPlantLevelUpValue = 1;
    int								StartingSun = 200;
    int                             SunLimit   = 10000;
    int                             SunAddBase = 100;
    int                             SunAddEachTurn = 10;
    std::vector<S2C_ZombieLevelStat>    ZombieLevelStats;
    std::vector<Network_NewPVPZombiePacketInfo>    ZombiePacketInfos;
    std::vector<Network_NewPVPPlantPacketInfo>    PlantPacketInfos;
    std::vector<Network_NewPVPZombieSkillInfo>    ZombieSkillInfos;
    std::vector<Network_NewPVPZombieUpgradeInfo>    ZombieUpgradeInfos;
    float							MaxHealthAmount;
    float							DealtDamage;
    float 							SunCostMultiplier;
    std::vector<Network_NewPVPSunUpgradeInfo> SunUpgradeInfos;
    std::vector<int> ChooserPlantBlacklist;
    std::vector<Network_NewPVPZombieLevelUpData> ZombieLevelUpInfos;
    std::vector<int> UnsyncPlantBlacklist;
};

enum NewPVPZombieBattleType
{
	BattleType_Melee,
	BattleType_Range,
	BattleType_Special
};

struct NewPVPZombieLevelUpValueData
{
	NewPVPZombieLevelUpValueData()
	: Cost(0)
	, Hitpoints(0.0f)
	, DPS(-1.0f)
	, Speed(-1.0f)
	{

	}

	int Cost;
	float Hitpoints;
	float DPS;
	float Speed;
};

struct NewPVPZombieLevelUpData
{
	NewPVPZombieLevelUpData()
	: Type(-1)
	, BattleType(BattleType_Melee)
	, Description("")
	{

	}

	int Type;
	NewPVPZombieBattleType BattleType;
	std::string Description;

	std::vector<NewPVPZombieLevelUpValueData> ValueDatas;
};

struct NewPVPZombieLevelUpPropertySheet
{
	// LevelUp Zombie Infos
	std::vector<NewPVPZombieLevelUpData> ZombieLevelUpInfos;
};

struct NewPVPZombieLevelInfo
{
	NewPVPZombieLevelInfo()
	: UnlockedTurn(-1)
	, Level(1)
	, Cost(0)
	, CostAddValue(0)
	{

	}

	NewPVPZombieLevelInfo(int i_turn, int i_level, int i_cost, int i_addValue)
	: UnlockedTurn(i_turn)
	, Level(i_level)
	, Cost(i_cost)
	, CostAddValue(i_addValue)
	{

	}

	int UnlockedTurn;
	int Level;
	int Cost;
	int CostAddValue;
};

struct NewPVPZombiePacketInfo
{
	NewPVPZombiePacketInfo()
	: Type(-1)
	{

	}

	NewPVPZombiePacketInfo(int i_type, const std::vector<NewPVPZombieLevelInfo>& i_infos)
	: Type(i_type)
	, LevelInfos(i_infos)
	{

	}

	int Type;
	std::vector<NewPVPZombieLevelInfo> LevelInfos;
};

struct NewPVPPlantPacketInfo
{
	NewPVPPlantPacketInfo()
	: UnlockedTurn(-1)
	, Level(1)
	{

	}

	NewPVPPlantPacketInfo(int i_turn, int i_level)
	: UnlockedTurn(i_turn)
	, Level(i_level)
	{

	}

	int UnlockedTurn;
	int Level;
};

struct NewPVPZombieSkillInfo
{
	NewPVPZombieSkillInfo()
	: Type(-1)
	, Duration(0)
	, Value(0)
	{

	}

	NewPVPZombieSkillInfo(int i_type, float i_duration, float i_value)
	: Type(i_type)
	, Duration(i_duration)
	, Value(i_value)
	{

	}

	int Type;
	float Duration;
	float Value;
};

struct NewPVPZombieUpgradeInfo
{
	NewPVPZombieUpgradeInfo()
	: Type(-1)
	, Cost(0)
	, Value(0)
	, UnlockedTurn(0)
	{

	}

	NewPVPZombieUpgradeInfo(int i_type, int i_cost, float i_value, int i_turn)
	: Type(i_type)
	, Cost(i_cost)
	, Value(i_value)
	, UnlockedTurn(i_turn)
	{

	}

	int Type;
	int Cost;
	float Value;
	int UnlockedTurn;
};

struct NewPVPSunUpgradeInfo
{
	NewPVPSunUpgradeInfo()
	: CD(0)
	, RequireNum(0)
	, SunAdd(0)
	, UpgradeCost(0)
	, MaxPlantNum(0)
	{

	}

	NewPVPSunUpgradeInfo(float i_cd, int i_requireNum, int i_sunAdd, int i_upgradeCost, int i_maxPlantNum)
	: CD(i_cd)
	, RequireNum(i_requireNum)
	, SunAdd(i_sunAdd)
	, UpgradeCost(i_upgradeCost)
	, MaxPlantNum(i_maxPlantNum)
	{

	}

	float CD;
	int RequireNum;
	int SunAdd;
	int UpgradeCost;
	int MaxPlantNum;
};

// Network Zombie Static Config
struct NewPVPZombieRareInfo
{
	NewPVPZombieRareInfo()
	: m_id(-1)
	, m_rare(0)
	{

	}

	int m_id;
	int m_rare;
};

struct NewPVPZombieConfig
{
	std::vector<NewPVPZombieRareInfo> m_rareInfos;
	std::vector<std::vector<int>> m_levelInfos;
};

// Network Zombie Player Info
struct NewPVPZombiePacketLevelInfo
{
	NewPVPZombiePacketLevelInfo()
	: m_id(-1)
	, m_level(0)
	{

	}

	int m_id;
	int m_level;
};

struct NewPVPZombiePieceInfo
{
	NewPVPZombiePieceInfo()
	: m_id(-1)
	, m_quantity(0)
	{

	}

	int m_id;
	int m_quantity;
};

struct NewPVPZombiePlayerInfo
{
	std::vector<std::vector<int>> m_inBattleZombies;
	std::vector<NewPVPZombiePacketLevelInfo> m_zombieLevelInfos;
	std::vector<NewPVPZombiePieceInfo> m_zombiePieceInfos;
	int m_inBattleIndex;
};

class NewPVPSyncPlayerData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPSyncPlayerData, INetworkData, RtClass);

public:
	int m_result;
};

class NewPVPSaveBattleInfoData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPSaveBattleInfoData, INetworkData, RtClass);

public:
	NewPVPZombiePlayerInfo m_zombiePlayerInfo;
};

class NewPVPLevelUpData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPLevelUpData, INetworkData, RtClass);

public:
	NewPVPZombiePlayerInfo m_zombiePlayerInfo;
};

class NewPVPReportData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPReportData, INetworkData, RtClass);

public:
	int m_result;
};

struct Network_PlayerSyncData
{
	Network_PlayerSyncData()
	: m_profileId("")
	, m_matchId("")
	, m_name("")
	, m_headshot(0)
	, m_currentMap(0)
	, m_rank(0)
	, m_progress(0)
	, m_status(0)
	, m_rankAvatar(0)
	, m_matchingScore(0)
	, m_highestMatchingScore(0)
	{

	}

	std::string m_profileId;
	std::string m_matchId;
	std::string m_name;
	int m_headshot;
	std::vector<int> m_startPlants;
	std::vector<int> m_maps;
	int m_currentMap;
	int m_rank;
	int m_progress;
	int m_status;
	std::vector<int> m_area;
	int m_rankAvatar;
	int m_matchingScore;
	int m_highestMatchingScore;
};

class NewPVPQueryPlayerData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPQueryPlayerData, INetworkData, RtClass);

public:
	std::string m_matchId;
	std::vector<Network_PlayerSyncData> m_players;
	int m_timeout;
};

class NewPVPMatchPlayer : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPMatchPlayer, INetworkData, RtClass);

public:
	std::string m_matchId;
	int m_result;
};

class NewPVPEndPlay : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPEndPlay, INetworkData, RtClass);

public:
	int m_result;
	int m_winCount;
	Network_NewPVPDuanState m_rank;
	int m_matchingScore;
	int m_oppoentMatchingScore;
};

struct NewPVPPlayerInfo
{
	int m_fightCount;
	int m_winCount;
	int m_perfectWinCount;
	int m_loseCount;
	int m_doubleWinCount;
	int m_doubleWinMax;
	int m_ratingMax;
	int m_plantsCount;
	int m_killZombiesCount;
	int m_createZombiesCount;
	Network_NewPVPDuanState m_currentRank;
	Network_NewPVPDuanState m_currentTopRank;
	Network_NewPVPDuanState m_previousTopRank;
	Network_NewPVPDuanState m_topRank;
	int m_matchingScore;
	int m_highestMatchingScore;
};

class NewPVPMainEntry : public INetworkData
{
public:
    RT_CLASS_DEFINE(NewPVPMainEntry, INetworkData, Sexy::RtClass);

    NewPVPMainEntry()
    : m_configVersion(0)
    , m_maxSyncPlayerTryTime(30)
    , m_syncQueueInterval(0)
    , m_syncPlayerInterval(0)
    , m_syncGameInterval(0)
    , m_syncGameDisconnectLimit(5)
    , m_matchingDisconnectLimit(3)
    , m_timeout(false)
    , m_estimatedQueueingTime(200)
    , m_outsideFPSLimit(25)
    , m_insideFPSLimit(15)
    , m_lowFPSCount(0)
    , m_FPSBlockStart(0)
    , m_lastGameLowFPS(0)
    , m_seasonEndTime(0)
    , m_isSeasonEnd(0)
    , m_seasonCount(0)
    {

    }

public:
    int m_configVersion;
    int m_maxSyncPlayerTryTime;
    int m_syncQueueInterval;
    int m_syncPlayerInterval;
    int m_syncGameInterval;
    int m_syncGameDisconnectLimit;
    int m_matchingDisconnectLimit;
    int m_timeout;
    std::vector<int> m_estimitedMatchingTime;
    int m_estimatedQueueingTime;

    // config
    Network_NewPVPPropertySheet m_config;
    std::vector<Network_NewPVPSmallDuan> m_duanList;
    std::vector<int> m_duanRewardStatus;
    Network_NewPVPDuanState m_topDuanStatus;
    int m_needFightCount;
    int m_fightCount;
    int m_outsideFPSLimit;
    int m_insideFPSLimit;
    int m_lowFPSCount;
    int m_FPSBlockStart;
    int m_lastGameLowFPS;
    int m_seasonEndTime;
    int m_isSeasonEnd;
    int m_seasonCount;

    NewPVPPlayerInfo m_playerInfo;
    NewPVPZombieConfig m_zombieConfig;
    NewPVPZombiePlayerInfo m_zombiePlayerInfo;
};

namespace Message
{
	// Subscribe to handle the result of the PVZ1NetworkIssue dialog.
	void NewPVPNetworkIssueDecision(int i_context, int i_decision);
	void NewPVPNetworkResponseReceived(int i_context, int i_status);
}

#endif /* NEWPVPDATAPACKETS_H_ */
