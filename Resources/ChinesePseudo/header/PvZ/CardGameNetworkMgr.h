/*
 * CardGameNetworkMgr.h
 *
 *  Created on: 2022-6-23
 *      Author: admin
 */

#ifndef CARDGAMENETWORKMGR_H_
#define CARDGAMENETWORKMGR_H_

#include "Core.h"
#include "NetworkServiceManager.h"
#include "NetworkData.h"
#include "PVZ1ModeDataPacket.h"
#include "MapEventItem.h"
#include "PVZ2UnchartedModeNetworkMgr.h"

struct CardGameCardInfo
{
	CardGameCardInfo()
	: Id(0)
	, Count(0)
	{

	}

	CardGameCardInfo(int i_id, int i_count)
	: Id(i_id)
	, Count(i_count)
	{

	}

	int Id;
	int Count;
};

struct CardGameEndPlayParamData
{
	bool HardMode = false;// 0 : normal mode ,1 : hard mode
	std::string WorldName = "";
	int Level = 0;// level number from 0..
	std::string ChooseListStr = "";// challenge result.
};

struct CardGameStartPlayParamData
{

};

class CardGameEndOfPlayData : public INetworkData
{
public:
	RT_CLASS_DEFINE(CardGameEndOfPlayData, INetworkData, RtClass);

public:
	std::vector<S2C_BonusInfo> BonusList;
	std::vector<S2C_BonusInfo> ExtraBonusList;
	int AddStar;
	std::vector<CardGameCardInfo> CardInfos;
};


//奖励数据类型
struct CardGameLevelBonusData
{
	CardGameLevelBonusData()
	{
		ItemID = 0;
		ItemCount = 0;
		IsFirstReward = false;
	}
    int ItemID;// bonus item id
    int ItemCount;// bonus item count
    bool IsFirstReward;
};

//关卡数据
struct CardGameLevelData
{
	CardGameLevelData()
	{
		BasicBonusList.clear();
		FirstRewardBonusList.clear();
		ExtraBonusList.clear();
		ChallengeInfo.clear();
		KeyCost = 0;
		LevelStatus = 0;
	}
	std::vector<CardGameLevelBonusData> BasicBonusList;
	std::vector<CardGameLevelBonusData> FirstRewardBonusList;
	std::vector<CardGameLevelBonusData> ExtraBonusList;
	std::vector<int> ChallengeInfo;
	int KeyCost;
	int LevelStatus;
};

//奖励兑换数据
struct CardGameStarRewardData
{
	CardGameStarRewardData()
	{
		ItemID = 0;
		Amount = 0;
		Obtained = 0;
		StepStar = 0;
	}
	int ItemID;
	int Amount;
	int Obtained;
	int StepStar;
};

//每个世界数据
struct CardGameWorldData
{
	CardGameWorldData()
	{
		CurrentStar = 0;
		MaxStar = 0;
	}
	std::vector<S2C_BonusInfo> RewardPreview;

    int CurrentStar;
    int MaxStar;
	std::string PrefixWorld;
	std::string StartDate;
	std::string EndDate;

    std::vector<CardGameLevelData> NormalLevelInfo;
    std::vector<CardGameLevelData> HardLevelInfo;
	std::vector<CardGameStarRewardData> StarRewardInfo;
};

class NetworkCardGameResetInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkCardGameResetInfo, INetworkData, RtClass);

public:
	std::vector<CardGameLevelData> HardLevelInfo;
};

//总数据
class CardGameMainEntryData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(CardGameMainEntryData, Sexy::RtObject, Sexy::RtClass);

	CardGameMainEntryData()
	{
		CurrentKey = 0;
		MaxKey = 0;
	}

 	int CurrentKey;
    int MaxKey;
	std::vector<CardGameWorldData> WorldInfo;
	std::vector<CardGameCardInfo> CardInfos;
	std::vector<CardGameCardInfo> CardSelectInfos;
};


class CardGameNetworkMgr : public LazySingleton<CardGameNetworkMgr>
{
public:
	CardGameNetworkMgr();
	~CardGameNetworkMgr();

	void SetIsHard(bool i_hard);
	bool GetIsHard(){ return m_isHard; }

	void SetPrefixWorld(const std::string& i_prefixWorld);
	const std::string&  GetPrefixWorld(){ return m_prefixWorld; };
	const CardGameWorldData& GetCurrentWorldData();
	const CardGameWorldData& GetWorldData(const std::string& i_worldPrefix);

	bool IsHardLevelUnlocked(const std::string& i_worldPrefix);
	WorldMapEventStatus  GetLevelStatus(const std::string& i_worldPrefix, bool i_isHard, int i_eventIndex);

	void RequestMainEntryData(std::function<void()> i_afterAction);
	void syncMainEntryInfo();
	void RequestEndPlayData(CardGameEndPlayParamData data);

	void SetCurrentLevelIndex(int index) { m_currentLevelIndex = index; }
	int GetCurrentLevelIndex() const { return m_currentLevelIndex; }
	void SetCurrentLevel(std::string name) { m_currentLevel = name; }
	std::string GetCurrentLevel() const { return m_currentLevel; }

	// get world data
	int GetCurrentPrefixWorldIndex();
	int GetPrefixWorldIndex(const std::string& world);

	const CardGameMainEntryData& GetMainEntryData() { return m_mainEntryData; }
	const CardGameEndOfPlayData& GetEndPlayData() { return m_endPlayData; }

	// get level data
	std::vector<CardGameLevelBonusData> GetLevelBonus(bool hard, int levelIndex);
	std::vector<CardGameLevelBonusData> GetLevelFirstRewardBonus(bool hard, int levelIndex);
	std::vector<CardGameLevelBonusData> GetLevelCardBonus(bool hard, int levelIndex);
	int GetCurrentLevelFirstReward(bool hard, int levelIndex);
	int GetLevelStarNumber(const std::string& i_worldPrefix, bool i_isHard, const class MapEventItem *i_event);

	// get challenge data
	std::vector<int> GetChallengeStatus(int levelIndex, bool isHard = false);

	int GetCurrentStarNumber(const std::string& i_worldPrefix);
	int GetMaxStarNumber(const std::string& i_worldPrefix);
	void AddWorldStar(const std::string& i_worldPrefix, int i_addNumber);
	void SetWorldStar(const std::string& i_worldPrefix, int i_setNumber);
	void OnObtainStarReward(const std::string& i_worldPrefix, int i_rewardIndex);

private:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void testResponse();

	bool m_isHard;
	std::string m_prefixWorld;
	bool m_requested;
	std::function<void()> m_afterRequest;

	CardGameMainEntryData m_mainEntryData;
	CardGameEndOfPlayData m_endPlayData;

	int m_currentLevelIndex;
	std::string m_currentLevel;
};

#define gCardGameNetworkMgr (CardGameNetworkMgr::GetInstancePtr())


#endif /* CARDGAMENETWORKMGR_H_ */
