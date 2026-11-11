#ifndef PVZ2_UNCHARTED_MODE_NETWORKMGR_H_
#define PVZ2_UNCHARTED_MODE_NETWORKMGR_H_


#include "Core.h"
#include "NetworkServiceManager.h"
#include "NetworkData.h"
#include "PVZ1ModeDataPacket.h"
#include "MapEventItem.h"
#include "SeedBankModule.h"
#include "LevelModule.h"
#include "UIEasyButtonWidget.h"

struct PVZ2UnchartedModeEndPlayParamData
{
	bool HardMode = false;// 0 : normal mode ,1 : hard mode
	std::string WorldName = "";
	int Level = 0;// level number from 0..
	std::string ChooseListStr = "";// challenge result.
	bool HasWon = false;
};

struct PVZ2UnchartedModeStartPlayParamData
{

};

class UnchartedModeEndOfPlayData : public INetworkData
{
public:
	RT_CLASS_DEFINE(UnchartedModeEndOfPlayData, INetworkData, RtClass);

public:
	std::vector<S2C_BonusInfo> BonusList;
	std::vector<S2C_BonusInfo> ExtraBonusList;
	std::vector<S2C_BonusInfo> ArtifactBonusList;
	int AddStar;
};

// 战令数据结构
struct UnchartedModeFestivalRewardData
{
	UnchartedModeFestivalRewardData() {
		StarCondition = 0;
		NormalObtained = 0;
		AdvanceObtained = 0;
	}

	int StarCondition;
	std::vector<S2C_BonusInfo> NormalRewards;
	std::vector<S2C_BonusInfo> AdvanceRewards;
	int NormalObtained;
	int AdvanceObtained;
};


//奖励数据类型
struct UnchartedModeLevelBonusData
{
	UnchartedModeLevelBonusData() {
		ItemID = 0;
		ItemCount = 0;
		IsFirstReward = false;
	}
    int ItemID;// bonus item id
    int ItemCount;// bonus item count
    bool IsFirstReward;
};

//关卡数据
struct UnchartedModeLevelData
{
	UnchartedModeLevelData() {
		BasicBonusList.clear();
		FirstRewardBonusList.clear();
		ExtraBonusList.clear();
		ChallengeInfo.clear();
		KeyCost = 0;
		LevelStatus = 0;
		MaxStars = 0;
		CurrentStars = 0;
		LevelThemes.clear();
	}
	std::vector<UnchartedModeLevelBonusData> BasicBonusList;
	std::vector<UnchartedModeLevelBonusData> FirstRewardBonusList;
	std::vector<UnchartedModeLevelBonusData> ExtraBonusList;
	std::vector<UnchartedModeLevelBonusData> PreviewBonusList;
	std::vector<int> ChallengeInfo;
	int KeyCost;
	int LevelStatus;
	int MaxStars;
	int CurrentStars;
	std::vector<int> LevelThemes;
};

//奖励兑换数据
struct UnchartedModeStarRewardData
{
	UnchartedModeStarRewardData()
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
struct UnchartedBirthdayTaskInfo
{
	UnchartedBirthdayTaskInfo()
	: TaskId(0)
	, Obtained(false)
	{

	}

	int TaskId;
	bool Obtained;
	std::vector<S2C_BonusInfo> Rewards;
};

enum UnchartedWorldType
{
	UnchartedWorldType_Invalid = -1,
	UnchartedWorldType_Normal,
	UnchartedWorldType_Anniversary,
	UnchartedWorldType_Iceage,
	UnchartedWorldType_SpringFestival2024,
	UnchartedWorldType_Max,
};


struct UnchartedModeRecordData
{
	std::string Crc = "";
	std::string Id = "";
};

struct UnchartedModeBoostData
{
	std::vector<int> ChooseCardsPool;
	std::vector<int> GotCardsPool;
};

class UnchartedModeBoardRecord : public RtObject
{
public:
	RT_CLASS_DEFINE(UnchartedModeBoardRecord, RtObject, RtClass);
	UnchartedModeBoardRecord() {}

	bool SerializeJson(const std::string &i_json);
	std::string SerializeObj();
	bool Copy(UnchartedModeBoardRecord data);

	std::string Crc = "";
	int CurrentSun = 0;
	std::vector<std::string> CurrentPlantList;
};

struct UnchartedModeWorldData
{
	UnchartedModeWorldData()
	{
		CurrentStar = 0;
		MaxStar = 0;
		IsTimeLimitWorld = 0;
		CurrentEarnedStars = 0;
		MaxEarnedStars = 0;
		AnniversayHeadshotBonusId = 0;
		Version = 0;
		WorldType = UnchartedWorldType_Normal;
	}
	std::vector<S2C_BonusInfo> RewardPreview;
   
    int CurrentStar;
    int MaxStar;
	std::string PrefixWorld;
	std::string StartDate;
	std::string EndDate;
	int LevelOpen;
	int IsTimeLimitWorld;
	int IsPrivilege;
	int Version;

	int CurrentEarnedStars;
	int MaxEarnedStars;
	std::vector<std::vector<UnchartedBirthdayTaskInfo>> BirthdayTaskInfos;

    std::vector<UnchartedModeLevelData> NormalLevelInfo;
    std::vector<UnchartedModeLevelData> HardLevelInfo;
	std::vector<UnchartedModeStarRewardData> StarRewardInfo;
	std::vector<UnchartedModeFestivalRewardData> FestivalRewardInfo;
	std::vector<S2C_BonusInfo> AnniversaryBonus;
	int AnniversayHeadshotBonusId;// always be there
	UnchartedWorldType WorldType;
	std::vector<UnchartedModeBoardRecord> BoardRecordList;
	std::vector<UnchartedModeBoostData> BoostList;
};


//总数据
class UnchartedModeMainEntryData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(UnchartedModeMainEntryData, Sexy::RtObject, Sexy::RtClass);

	UnchartedModeMainEntryData()
	{
		CurrentKey = 0;
		MaxKey = 0;	
		Version = 0;
	}

 	int CurrentKey;
    int MaxKey;
	std::vector<UnchartedModeWorldData> WorldInfo;
	std::vector<S2C_BonusInfo> AnniversaryBonus;
	int Version;
	std::vector<std::string> AnniversaryWorldNames;
	std::vector<std::string> AnniversarySelectLevelWorldNames;
	std::vector<std::string> NormalWorldWithHardmodeNames;
	std::vector<std::string> TutorialWorldNames;
};

class UnchartedModeNetworkMgr : public LazySingleton<UnchartedModeNetworkMgr>
{
public:
	UnchartedModeNetworkMgr();
	~UnchartedModeNetworkMgr();

	void RequestMainEntryData(std::function<void()> i_afterAction = nullptr);
	void RequestEndPlayData(PVZ2UnchartedModeEndPlayParamData data);
	void RequestNetwork();

	int GetSpringFestival2024CurrentLevelIndex();

	void SetIsHard(bool i_hard);
	bool GetIsHard();
	void SetPrefixWorld(const std::string& i_prefixWorld);
	const std::string& GetPrefixWorld();
	const std::string GetWorldResourcePrefix();
	int GetCurrentPrefixWorldIndex();
	int GetPrefixWorldIndex(const std::string& world);

	const UnchartedModeMainEntryData& GetMainEntryData() { return m_mainEntryData; }
	const UnchartedModeEndOfPlayData GetEndPlayData() { return m_endPlayData; }
	const UnchartedModeWorldData& GetCurrentWorldData();
	const std::vector<UnchartedModeFestivalRewardData> GetCurrentWorldFestivalRewardData();
	const UnchartedModeWorldData& GetWorldData(const std::string& i_worldPrefix);

	const std::vector<int>& GetCurrentOwnedCardList();
	std::vector<int> GetCurrentLeftCardList();
	void SyncCards(const std::vector<int>& i_ids);
	bool HasUnlockedHeroPlant();

	int GetCurrentKeyNumber();
	int GetMaxKeyNumber();
	
	int GetCurrentStarNumber(const std::string& i_worldPrefix);
	int GetMaxStarNumber(const std::string& i_worldPrefix);
	void AddWorldStar(const std::string& i_worldPrefix, int i_addNumber);
	void SetWorldStar(const std::string& i_worldPrefix, int i_setNumber);

	bool IsWorldNameVaild(const std::string& i_worldPrefix);
	bool IsWorldOpen(const std::string& i_worldPrefix);
	bool IsTimeLimitWorld(const std::string& i_worldPrefix);
	std::string GetTimeLimitWorld();
	time_t GetWorldStartTime(const std::string& i_worldPrefix);
	time_t GetWorldEndTime(const std::string& i_worldPrefix);

    int GetWorldCount();
    bool HasLockedHardLevel();
    bool CheckShowTips();
    bool CheckShowNotice();
    bool CheckHasAvailableRewards(std::string i_worldPrefix);

    // Uncharted birthday
    bool IsUnchartedBirthday();
    bool IsUnchartedBirthday(const std::string& i_worldName);
    bool IsAnniversarySelectLevel();
    bool IsAnniversarySelectLevel(const std::string& i_worldName);
    bool IsNormalSelectLevelWithHardmode();
    bool IsNormalSelectLevelWithHardmode(const std::string& i_worldName);
    UnchartedWorldType GetUnchartedWorldType();
    UnchartedWorldType GetUnchartedWorldType(const std::string& i_worldName);
    bool IsTutorialWorld();
    bool IsTutorialWorld(const std::string& i_worldName);
    int GetAnniversaryHeadshotBonusId();
    int GetBirthdayCurrentLevelStar(int levelIndex);
    int GetBirthdayCurrentLevelMaxStar(int levelIndex);
    int GetBirthdayMaxEarnedStars();
    int GetBirthdayCurrentEarnedStars();
    bool IsTaskIdValidInCurrentLevel(int i_id);

	bool IsHardLevelUnlocked(const std::string& i_worldPrefix);
	void UnlockHardLevel(const std::string& i_worldPrefix, int i_eventIndex);
	void LevelComplete(const std::string& i_worldPrefix, bool i_isHard, int i_eventIndex);
	WorldMapEventStatus  GetLevelStatus(const std::string& i_worldPrefix, bool i_isHard, int i_eventIndex);
	
	int GetLevelStarNumber(const std::string& i_worldPrefix, bool i_isHard, const class MapEventItem *i_event);

	std::vector<UnchartedModeLevelBonusData> GetLevelBonus(bool hard, int levelIndex);
	std::vector<UnchartedModeLevelBonusData> GetLevelFirstRewardBonus(bool hard, int levelIndex);
	std::vector<UnchartedModeLevelBonusData> GetLevelPreviewBonus(bool hard, int levelIndex);
	int GetCurrentLevelFirstReward(bool hard, int levelIndex);

	void OnObtainStarReward(const std::string& i_worldPrefix, int i_rewardIndex);
	std::vector<int> GetChallengeStatus(int levelIndex);

	void SetCurrentLevelIndex(int index) { m_currentLevelIndex = index; }
	int GetCurrentLevelIndex() const;
	void SetCurrentLevel(std::string name) { m_currentLevel = name; }
	std::string GetCurrentLevel() const { return m_currentLevel; }

	void ShowUnlockHardEvent(const class MapEventItem *i_event);
	void ShowUnlockAnniversarySelectLevel(const class MapEventItem *i_event);
	void ConfirmUnlock(class UIMessageBox* box, int buttonID);

	void SetLevelEnd(bool end) { m_levelEnd = end; }
	bool GetLevelEnd() { return m_levelEnd; }
	void SetSelectStarCount(int count) { m_selectStarCount = count; }
	int GetSelectStarCount() { return m_selectStarCount; }

	bool CheckAnniversaryBonus();
	bool HasAnniversaryBonus();
	void ShowAnniversaryBonus();
	void ClearAnniversaryVersionBonusInfo();

	void syncMainEntryInfo();

	std::vector<int> GetLevelThemes(int levelIndex, bool isHard);
	UnchartedModeBoostData GetBoostData(std::string worldName, bool isHard);
	UnchartedModeBoardRecord GetBoardRecord(std::string worldName, bool isHard);
	void SetBoardRecord(std::string worldName, bool isHard, UnchartedModeBoardRecord data);

	void SetStartBoardTime(pvztime_t time) { m_startBoardTime = time; }
	void SetElapseTime(pvztime_t time) { m_elapseTime = time; }
	pvztime_t GetElapseTime() const { return m_elapseTime - m_startBoardTime; }

private:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void syncWorldMapInfo();

private:
	bool m_requested;
	bool m_isHard;
	std::string m_prefixWorld;
	std::function<void()> m_afterRequest;
	UnchartedModeMainEntryData m_mainEntryData;
	UnchartedModeEndOfPlayData m_endPlayData;
	int m_currentLevelIndex;
	std::string m_currentLevel;

	std::vector<int> m_currentBoostCards;

	int m_unlockHardIndex;
	bool m_levelEnd;
	int m_selectStarCount;

	pvztime_t m_startBoardTime;
	pvztime_t m_elapseTime;
};

#define gUnchartedModeNetworkMgr (UnchartedModeNetworkMgr::GetInstancePtr())

///////////////////////////////////////////////
///  UnchartedModeSpringFestivalSeedBankModule
///////////////////////////////////////////////
class UnchartedModeSpringFestivalSeedBankModule : public SeedBankModule
{
public:
	RT_CLASS_DEFINE(UnchartedModeSpringFestivalSeedBankModule, SeedBankModule, RtClass);

protected:
	virtual void			initializeModule() override;
};

////////////////////////////////////////////////////
///  UnchartedModeSpringFestivalSeedBankProperties
////////////////////////////////////////////////////
class UnchartedModeSpringFestivalSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(UnchartedModeSpringFestivalSeedBankProperties, SeedBankProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return UnchartedModeSpringFestivalSeedBankModule::StaticGetClass();
	}
};


////////////////////////////////////////////////////
///  UnchartedModeSpringFestivalModule
////////////////////////////////////////////////////
class UnchartedModeSpringFestivalModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(UnchartedModeSpringFestivalModule, LevelModule, RtClass);

    UnchartedModeSpringFestivalModule();
	virtual ~UnchartedModeSpringFestivalModule();

protected:
    virtual void registerForEvents() override;
	virtual void postInitialize() override;

	void onGameplayEnded();
};

////////////////////////////////////////////////////
///  UnchartedModeSpringFestivalModuleProperties
////////////////////////////////////////////////////
class UnchartedModeSpringFestivalModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(UnchartedModeSpringFestivalModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return UnchartedModeSpringFestivalModule::StaticGetClass();
	}
};

///
/// UIPVZ1ModeHowToPlayButton
///
class UIPVZ2UnchartedHowToPlayButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UIPVZ2UnchartedHowToPlayButton, UIEasyButtonWidget, RtClass);

    UIPVZ2UnchartedHowToPlayButton();

    virtual void OnClick();

protected:
};
#endif
