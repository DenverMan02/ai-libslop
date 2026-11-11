/*
 * DynamicLevelMgr.h
 *
 *  Created on: 2021-11-22
 *      Author: admin
 */

#ifndef DYNAMICLEVELMGR_H_
#define DYNAMICLEVELMGR_H_

#include "Singleton.h"
#include "CustomLevelConfig.h"
#include "CustomLevelCreator.h"
#include "CustomLevelDataCreator.h"
#include "GameStateMgr.h"
#include "NetworkServiceManager.h"
#include "NetworkData.h"
#include "CustomLevelDownloadMgr.h"
#include "TGALogMgr.h"
#include "map"

//***************V303***********************
struct CustomNetworkAppraiseData
{
	int ID;
	std::string MSG;
};

class CustomNetworkExtraData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkExtraData, INetworkData, Sexy::RtClass);

	std::vector<CustomNetworkAppraiseData> AppraiseTagList;
	std::string PhoneNumber;
	std::string RelinkTimeStamp;
	std::vector<S2C_BonusInfo> RewardPreview;
	int CertState;
	std::string PlatformUrl;
	int AdsSwitch;
	int PlatformSwitch;
};

//***************V720***********************
class CustomNetworkUploadData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkUploadData, INetworkData, Sexy::RtClass);

public:
    int LevelID;
    std::string LevelName;
    int World;
    int LevelMode;
    bool EnableDownload;
    int Likes;
    int Dislikes;
    int PlayedCount;
    int Suggested;
    std::string LevelUrl;
    int AuthorID;
    int AuthorHeadshotID;
    std::string AuthorName;
    std::string Version;
    std::string UploadedTime;
    std::string UpdatedTime;
    std::string LocalLevelID;
    std::string BestRecord;
    int RateResult;
    bool isVersionCompatible;
	int PlayCoinState;
	int Reported;
	std::map<std::string,int> Appraise;
	int Certified = 0;
	std::string LevelAdsConfig;
};

class NetworkCustomLevelData : public RtObject
{
public:
    RT_CLASS_DEFINE(NetworkCustomLevelData, RtObject, RtClass);
    NetworkCustomLevelData() {}
public:
    CustomLevelWorldParams m_params;

    bool SerializeJson(const std::string &i_json);
    std::string SerializeObj();
};

//***************V720***********************

//***************V721***********************
struct CustomLevelEndBonusInfo
{
	CustomLevelEndBonusInfo()
	{
		Id = 0;
		Quantity = 0;
	}
	int Id;
	int Quantity;
};

class CustomNetworkEndPlayData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkEndPlayData, INetworkData, Sexy::RtClass);

public:
    int PlayTime;
	int Error;
	int CurrentCurrency;
	int MaxCurrency;
    std::vector<CustomLevelEndBonusInfo> Rewards;
};

//***************V722***********************
class CustomNetworkLikeDislikeData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkLikeDislikeData, INetworkData, Sexy::RtClass);

public:
    int SelfPerformedResult;
    int TotalLikes;
    int TotalDislikes;
};
//***************V722***********************

//***************V730***********************
class CustomNetworkPlayCountData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkPlayCountData, INetworkData, Sexy::RtClass);

public:
    int PlayCount;
    int TotalLikes;
};
//***************V730***********************

//***************V727,V733,V731***********************
class CustomNetworkResponseData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkResponseData, INetworkData, Sexy::RtClass);

public:
    bool Success;
};
//*************V727,V733,V731*************************

//*************V728*************************
class CustomNetworkFavouriteResponseData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkFavouriteResponseData, INetworkData, Sexy::RtClass);

public:
    bool Success;
    int Id;// level id
    int Op;// 0 = cancel favour, 1 = favour
};
//***************V728***********************

//***************V723,V724,V725***********************

struct CustomNetworkPreviewData
{
	int LevelID;
	std::string LevelName;
	int World;
	int Likes;
	int Dislikes;
	int PlayedCount;
	int Suggested;
	int AuthorHeadshotID;
	std::string AuthorName;
	int LevelMode;
	std::string LevelUrl;
	std::string LocalLevelID;
	int Certified = 0;
};

class CustomNetworkListData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomNetworkListData, INetworkData, Sexy::RtClass);

public:
    std::vector<CustomNetworkPreviewData> PreviewList;
    int Type;// 0 = mostplay 1 = mostlike 2 = favourite
};
//***************V723,V724,V725***********************


//***************V735***********************
class CustomLevelObtainPlayCoin : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomLevelObtainPlayCoin, INetworkData, Sexy::RtClass);

	int CurrentCoin;
	int MaxCoin;
	std::vector<S2C_BonusInfo> Award;
	bool IsFull;
};

//***************V735***********************


enum CustomLevelTutorialBtnID
{
	CUSTOM_LEVEL_TUTORIAL_BTN_SKIP
};

class CustomLevelTutorialSkipWidget : public Widget, public ButtonListener
{
public:
	CustomLevelTutorialSkipWidget();
	virtual ~CustomLevelTutorialSkipWidget();
    void ButtonDepress(int i_id) override;
    void Init();
    void SetCallBack(std::function<void()> i_callback) { m_callback = i_callback; }
private:
    class PVZ2UIButton* m_skipButton;
    std::function<void()> m_callback;
};

class CustomLevelMgr : public LazySingleton <CustomLevelMgr>
{
public:
	CustomLevelMgr();
    ~CustomLevelMgr();

    // Tests
    void TestSaveLevelData();
    void TestLoadLevelData();
    void TestDeleteLevelData();
    void TestCreateUIData();
    void TestLevelTemplate();
    CustomLevelWorldParams TestConstructLevelData();

    // Level Definition
    LevelDefinitionPtr TryLoadLevelDef(const std::string& i_levelName);
    void GenerateTemplateAndStart(const CustomLevelWorldParams& i_params, LevelSource i_levelSource);
	std::string GenerateTemplate(const CustomLevelWorldParams& i_params);

	void InitModules(const CustomLevelWorldParams& i_params);
	void ClearModules();

	const CustomLevelConfig* GetConfig() const;

	// Editor
	std::string GetWorldByWorldType(CustomLevelNetworkWorldType i_type);
	std::string GetStageByWorldType(CustomLevelNetworkWorldType i_type);
	std::string GetStageByCurrentWorldType();

	CustomLevelNetworkWorldType GetWorldTypeByWorld(const std::string& i_world);
	CustomLevelWorldInfo GetWorldInfoByWorldType(CustomLevelNetworkWorldType i_type);

	// Tutorial
	void CreateTutorialSkipMenu();
	bool CheckInTutorial();
	void Update(float dt);
	void TryResetTutorialSkipTimer();

	// UIs
//****************************************Outer*********************************************
	void StartLoadedLevel();
	void SaveCurrentLevel();
	const std::vector<CustomPreviewData> LoadLevelDatas();
	const CustomNetworkUploadData& LoadLevelData(int i_index);
	void UploadCurrentLevelData();
	const CustomNetworkUploadData& GetNetworkUploadedData() { return m_currentUploadedData; }
	const CustomNetworkUploadData& GetNetworkLevelDetails() { return m_currentLevelDetails; }
	const CustomNetworkListData& GetNetworkPreviewListData() { return m_currentPreviewListData; }
	const CustomNetworkLikeDislikeData& GetNetworkLikeDislikeData() { return m_currentLikeDislikeData; }
	const CustomNetworkFavouriteResponseData& GetNetworkFavouriteData() { return m_currentFavouriteData; }
	const CustomNetworkListData& GetNetworkUploadedListData() { return m_currentUploadedListData; }
	void SetCurrentSelfDownloadData(const CustomNetworkPreviewData& i_data) { m_currentSelfDownloadData = i_data; }
	bool IsCurrentNetworkLevelDownloaded();
	bool IsLevelDownloaded(const std::string& i_localLevelID);
	void FilterLevelName(std::string& i_levelName);

//****************************************Outer*********************************************
//****************************************Inner*********************************************
	// Level Pass
	void RecordFinishedLevel(pvztime_t i_playTime);
	bool HasFinishedLevel() { return m_currentLevelData.HasFinishedLevel; }
    void ResetFinishedLevel();
    bool IsCurrentLevelUploaded() { return m_currentLevelData.HasUploaded; }

    // Constraints
    void FilterGroup(const std::string& i_key, std::vector<std::string>& i_outerGroup);
    bool IsValueValid(const std::string& i_key, const std::string& i_value);
    bool IsValueValid(const std::string& i_key, float i_value, bool i_greater);
    float GetGroupValue(const std::string& i_key);

	// Worlds
	CustomLevelNetworkWorldType GetWorldType();

	void SetWorld(CustomLevelNetworkWorldType i_type);
	void SetMode(CustomLevelNetworkLevelMode i_mode);
	CustomLevelNetworkLevelMode GetMode() { return m_currentLevelData.NetworkLevelMode; }
	const std::vector<std::string>& GetDefaultZombieListByCurrentWorld();
	void SetLevelName(const std::string& i_levelName);
	const std::string& GetLevelName();

	//encourage
	void SetCanBuySunmoney(bool i_flag);
	bool GetCanBuySunmoney();
	void SetCanBuyPlantfood(bool i_flag);
	bool GetCanBuyPlantfood();
	void SetCanBuyMower(bool i_flag);
	bool GetCanBuyMower();
	
	// Starting Sun
	int GetStartingSun();

	void SetStartingSun(int i_count);
	// Elements
	bool GetPlantGrid(int i_x, int i_y, std::string& i_typeName, int& i_level);
	bool GetGridItemGrid(int i_x, int i_y, std::string& i_typeName);
	bool GetMoldGrid(int i_x, int i_y);
	bool GetRailGrid(int i_x, int i_y);

	void UpdatePlantGrid(const std::string& i_typeName, int i_x, int i_y, int i_level = 1, bool i_add = true);
	void UpdateGridItemGrid(const std::string& i_typeName, int i_x, int i_y, int i_level = 1, bool i_add = true);
	void UpdateMoldGrid(int i_x, int i_y, bool i_add = true);
	void UpdateRails(int i_x, int i_y, bool i_add = true);

	bool GetPowerTile(int i_x, int i_y, PowerTileClass& i_type);
	void RemovePowerTile(int i_x, int i_y);
	void UpdatePowerTile(PowerTileClass i_type, int i_x, int i_y);

	// SeedBank Normal
	CustomSeedBankType GetSeedBankType();

	void SetSeedBankType(CustomSeedBankType i_type);
	void SetSeedBankGlobalLevel(int i_level);
	int GetSeedBankGlobalLevel();
	void AddSeedBankPlantBlackList(const std::string& i_typeName);
	void RemoveSeedBankPlantBlackList(const std::string& i_typeName);
	void ClearSeedBankPlantBlackList();
	const std::vector<std::string>& GetSeedBankPlantBlackList();
	// SeedBank Preset
	void AddPresetSeedBankPlant(const std::string& i_typeName, int i_index);
	void RemovePresetSeedBankPlant(int i_index);
	std::string GetPresetSeedBankPlant(int i_index);
	const std::vector<std::string>& GetPresetSeedBankPlants();
	// SeedBank Conveyor
	bool IsConveyorValid();
	void AddConveyorSeedBankPlant(const std::string& i_typeName, int i_weight, int i_level, int i_index);
	void UpdateConveyorSeedBankPlant(int i_weight, int i_level, int i_index);
	void RemoveConveyorSeedBankPlant(int i_index);
	CustomConveyorData GetConveyorSeedBankPlantData(int i_index);
	const std::vector<CustomConveyorData>& GetConveyorSeedBankPlants();

	// Zombies
	void GetWaveRowZombies(int i_waveIndex, int i_row, std::vector<std::string>& i_zombieList);
	CustomWaveZombie GetWaveZombie(int i_waveIndex, int i_row, int i_col);

	void AddRandomZombies();
	void AddWaveZombie(int i_waveIndex, const std::string& i_typeName, int i_row, int i_col, int i_level = 1);
	bool UpdateWaveZombie(int i_waveIndex, int i_row, int i_col, int i_level);
	bool RemoveWaveZombie(int i_waveIndex, int i_row, int i_col);
	void SetAllZombiesLevel(int i_level);
	void RemoveAllZombies();

	int GetWaveAdditionalPlantfood(int i_waveIndex);
	void SetWaveAdditionalPlantfood(int i_waveIndex, int i_num = 1);

	//Wave Events
	void RemoveAllEvents(int i_waveIndex);
	// Sandstrom
	bool IsWaveEventSandStormVaild(int i_waveIndex);
	int GetSandStormColumnEnd(int i_waveIndex);
	int GetSandStormColumnStart(int i_waveIndex);
	std::string GetWaveEventSandStormZombie(int i_waveIndex, int i_index);
	int GetSandStormType(int i_waveIndex);
	void SetSandStormType(int i_waveIndex, int i_type);
	void SetSandStormColumnEnd(int i_waveIndex, int i_colEnd);
	void SetSandStormColumnStart(int i_waveIndex, int i_colStart);
	void AddWaveEventSandStorm(int i_waveIndex, int i_index, const std::string& i_typeName);
	void RemoveWaveEventSandStorm(int i_waveIndex, int i_index);
	// Spider Storm
	bool IsWaveEventSpiderStormValid(int i_waveIndex);
	void SetSpiderStormColumnStartEnd(int i_waveIndex, int i_col);
	void SetSpiderStormZombieCount(int i_waveIndex, int i_count);
	void RemoveWaveEventSpiderStorm(int i_waveIndex);
	int GetSpiderStormColumnStartEnd(int i_waveIndex);
	int GetSpiderStormZombieCount(int i_waveIndex);
	// Raiding Party
	bool IsWaveEventRaidingPartyValid(int i_waveIndex);
	void SetRaidingPartySwashbucklerCount(int i_waveIndex, int i_count);
	int GetRaidingPartySwashbucklerCount(int i_waveIndex);
	// Parachute Rain
	bool IsWaveEventParachuteRainValid(int i_waveIndex);
	void SetParachuteRainColumnEnd(int i_waveIndex, int i_col);
	int GetParachuteRainColumnEnd(int i_waveIndex);
	// Black Hole
	bool IsWaveEventBlackHoleValid(int i_waveIndex);
	void SetBlackHoleColumnEnd(int i_waveIndex, int i_col);
	int GetBlackHoleColumnEnd(int i_waveIndex);
	// Portal
	bool IsWaveEventPortalValid(int i_waveIndex);
	void SetPortalColumn(int i_waveIndex, int i_col);
	void SetPortalRow(int i_waveIndex, int i_row);
	void SetPortalType(int i_waveIndex, const std::string& i_worldName);
	int GetPortalColumn(int i_waveIndex);
	int GetPortalRow(int i_waveIndex);
	const std::string& GetPortalType(int i_waveIndex);
	// Dino
	bool IsWaveEventDinoValid(int i_waveIndex);
	void SetDinoRow(int i_waveIndex, int i_row);
	void SetDinoTimeInterval(int i_waveIndex, float i_time);
	int GetDinoRow(int i_waveIndex);
	float GetDinoTimeInterval(int i_waveIndex);
	// Frost Wind
	void AddWaveEventFrostWind(int i_waveIndex, int i_row);
	void UpdateWaveEventFrostWind(int i_waveIndex, int i_index, int i_row);
	void RemoveWaveEventFrostWind(int i_waveIndex, int i_index);

	// Challenges
	// Last Stand
	bool IsLastStandValid();
	void SetLastStandStartingSun(int i_count);
	void SetLastStandPlantfood(int i_count);
	int GetLastStandPlantfood();
	void RemoveLastStand();
	// Statue Maze
	const StatueMazeSet& GetSet(int i_index);
	int GetSetSize();
	void AddSet(int i_matrixSize, int i_targetNum, float i_displayTime, float i_bonusLife);
	void UpdateSet(int i_index, int i_matrixSize, int i_targetNum, float i_displayTime, float i_bonusLife);
	void RemoveSet(int i_index);
	void SetSetRotateAndWaitTime(int i_setIndex, float i_rotateTime, float i_waitTime);
	const StatueMazeMatrix& GetSetMatrix(int i_setIndex, int i_matrixIndex);
	int GetSetMatrixSize(int i_setIndex);
	void AddSetMatrix(int i_setIndex, bool i_clockWise);
	void UpdateSetMatrix(int i_setIndex, int i_matrixIndex, bool i_clockWise);
	void RemoveSetMatrix(int i_setIndex, int i_matrixIndex);
	// Evil Dave
	bool IsEvilDaveValid();
	void SetEvilDaveStartingSun(int i_count);
	int GetEvilDaveStartingSun();
	void SetEvilDavePlantDistance(float i_distance);
	float GetEvilDavePlantDistance();
	void AddEvilDavePlant(int i_x, int i_y, const std::string& i_typeName);
	void RemoveEvilDavePlant(int i_x, int i_y);
	void AddEvilDaveZombie(int i_index, const std::string& i_typeName);
	void RemoveEvilDaveZombie(int i_index);
	bool GetEvilDavePlantGrid(int i_x, int i_y, std::string& i_typeName);
	const std::string& GetEvilDaveZombieTypeName(int i_index);
	// Tower Defend
	void SetTowerDefendStartingSun(int i_count);
	int  GetTowerDefendStartingSun();
	void SetTowerDefendPlantfood(int i_count);
	void AddTowerDefendRoad(int i_x, int i_y, const std::string& i_imgName);
	void RemoveTowerDefendRoad(int i_x, int i_y);
	bool GetTowerDefendRoad(int i_x, int i_y, std::string& i_typeName);
	void AddTowerDefendPresetSeedBankPlant(const std::string& i_typeName, int i_index);
	const std::string& GetTowerDefendPresetSeedBankPlant(int i_index);
	void RemoveTowerDefendPresetSeedBankPlant(int i_index);
	void AddUpgradeTree(int i_index, const std::string& i_upgradeTypeName, int i_cost);
	void GetUpgradeTree(int i_index, std::string& i_upgradeTypeName, int& i_cost);
	void AddTowerDefendWaveZombie(int i_waveIndex, const std::string& i_typeName, int i_row, int i_col);
	bool RemoveTowerDefendWaveZombie(int i_waveIndex, int i_row, int i_col);
	void GetTowerDefendWaveRowZombies(int i_waveIndex, int i_row, std::vector<std::string>& i_zombieList);
	TowerDefendWaveZombie GetTowerDefendWaveZombie(int i_waveIndex, int i_row, int i_col);

	// Single Handed
	void AddStartingPlant(const std::string& i_typeName);
	void RemoveStartingPlant();
	const std::string& GetStartingPlant();
	void AddUpgradePlant(int i_index, const std::string& i_srcTypeName, const std::string& i_upgradeTypeName, int i_killNum);
	void GetUpgradePlant(int i_index, std::string& i_upgradeTypeName, int& i_killNum);
	void RemoveUpgradePlant(int i_index);
	void AddSingleHandedWaveZombie(int i_waveIndex, const std::string& i_typeName, int i_row, int i_col);
	bool RemoveSingleHandedWaveZombie(int i_waveIndex, int i_row, int i_col);
	void GetSingleHandedWaveRowZombies(int i_waveIndex, int i_row, std::vector<std::string>& i_zombieList);
	SingleHandedWaveZombie GetSingleHandedWaveZombie(int i_waveIndex, int i_row, int i_col);
	void SetSingleHandedWavePlantfood(int i_waveIndex, bool i_plantfood);
	bool GetSingleHandedWavePlantfood(int i_waveIndex);

	// Vase Breaker
	void SetVaseBreakerMinMaxColumn(int i_min, int i_max);
	void GetVaseBreakerMinMaxColumn(int& i_min, int& i_max);
	void SetVaseBreakerContent(int i_index, VaseType i_type, const std::string& i_typeName, int i_count);
	void GetVaseBreakerContent(int i_index, VaseType& i_type, std::string& i_typeName, int& i_count);
	void RemoveVaseBreakerContent(int i_index);
	void SetVaseBreakerCount(int i_count);
	int GetVaseBreakerCount();

//****************************************Inner*********************************************
	// Networks

	void RequestUploadLevelData(const CustomLevelWorldParams& i_params);
	void RequestDeleteLevelData();
	void RequestGetNetworkLevelDetails(int i_networkLevelID);
	void RequestGetFilterPreviewList(int i_index = 0, int i_count = 0);
	void RequestGetViewPreviewList(std::vector<CustomLevelNetworkWorldType> i_worldTypeList,
			std::vector<CustomLevelNetworkLevelMode> i_modeList, ViewLevelType i_type, ViewRankType i_rankType, int i_index, int i_count, bool refresh = false);
	void RequestGetSearchPreviewList(int i_networkLevelID, std::vector<CustomLevelNetworkWorldType> i_worldTypeList = std::vector<CustomLevelNetworkWorldType>(),
			std::vector<CustomLevelNetworkLevelMode> i_modeList = std::vector<CustomLevelNetworkLevelMode>());
	void RequestPerformLikeDislike(bool i_like);
	void RequestStartLevel();
	void RequestUpdateFavourite(bool i_add);
	void RequestUpdateLevelName(const std::string& i_levelName);
	void RequestGetPlayCount();
	void RequestChangeDownloadable(bool i_enabled);
	void RequestAuthorLevels(int i_networkLevelID);
	void SetExtraData(CustomNetworkExtraData& i_data);
	const CustomNetworkExtraData& GetExtraData();
	std::string GetAppraiseTagInfo(int i_id);

	bool IsReported();
	bool IsPlayCoinObtained();
	bool IsSupported();
	bool IsNotSupported();
	bool IsNoAppraise();

	void RequestDownloadLevelData(const std::string& i_serverUrl, int i_retries = 0, bool i_save = true, bool i_self = false);
	bool CreateNetworkLevelData(std::string i_json, bool i_save, bool i_self);
	void SetTutorialDownloadURL(const std::string& i_serverUrl) { m_tutorialURL = i_serverUrl; }
	const std::string& GetTutorialDownloadURL() { return m_tutorialURL; }

	// my favourite levels check
	bool IsMyFavourite(int levelID);
	void UpdateMyFavourite(int levelID, bool favourite);
	void FillFavouriteLevelMap(std::vector<CustomNetworkPreviewData> list);
	int GetFavouriteTotalCount();

	void SetLogData(const TGACustomLevelData& i_data) { m_logData = i_data; }
	const TGACustomLevelData& GetLogData() { return m_logData; }

private:
	// Levels
	const CustomLevelConfig* getConfig() const;
	void initializeDefaultModules();
	void initOtherModules(const CustomLevelWorldParams& i_params);
	bool IsCustomLevel(const std::string& i_levelName);
	void Reset();

	// Networks
	std::string ConstructNetworkLevelData(const CustomLevelWorldParams& i_params);
	bool SaveNetworkLevelData(const std::string& i_json, bool i_save, bool i_self);
	void OnDownloadedFinish(bool i_save, bool i_success);
	void SyncUploadedDataToLocal();
	void SyncLocalLevelDataToLocalLevelDetails();

	// Editor
	std::string GetValueByWorldType(CustomLevelNetworkWorldType i_type, bool i_world);
	bool FindGridInfo(const std::vector<PlacementInfo>& i_infos, const std::string& i_typeName);
	void UpdateGridInfo(std::vector<PlacementInfo>& i_infos, const std::string& i_typeName, int i_x, int i_y, int i_level = 1);
	void RemoveGridInfo(std::vector<PlacementInfo>& i_infos, int i_x, int i_y);

	void UpdateRailInfo(std::vector<RailInfo>& i_infos, int i_x, int i_y);
	void RemoveRailInfo(std::vector<RailInfo>& i_infos, int i_x, int i_y);

	void ProcessDefaultWave(const DefaultWave& i_wave, int i_index);
	void AddWaveZombie(int i_waveIndex, int i_index, const std::string& i_typeName, int i_row, int i_level = 1);

private:
	// Levels
	std::vector<class CustomLevelTemplate*> m_modules;
	CustomLevelCreator m_creator;
	CustomLevelDataCreator m_dataCreator;
	CustomLevelDownloadMgr m_downloadMgr;
	CustomLevelWorldParams m_currentLevelData;
	CustomLevelWorldParams m_tempDownloadedData;

	// Networks
	CustomNetworkUploadData m_currentUploadedData;
	CustomNetworkUploadData m_currentLevelDetails;
	CustomNetworkListData m_currentPreviewListData;
	CustomNetworkLikeDislikeData m_currentLikeDislikeData;
	CustomNetworkPlayCountData m_currentPlayCountData;
	CustomNetworkFavouriteResponseData m_currentFavouriteData;
	std::string	m_tutorialURL;
	CustomNetworkListData m_currentUploadedListData;
	bool m_hasRequestUploadedList;
	CustomNetworkPreviewData m_currentSelfDownloadData;
	CustomNetworkExtraData m_activityExtraData;

	// Tutorial
	float         m_skipTutorialTimer;

	static std::map<int, CustomLevelWorldInfo> g_worldTypeMaps;
	std::map<int, int> m_favouriteLevelList;// my favourite list

	// Log
	TGACustomLevelData m_logData;
};

#define gCustomLevelMgr CustomLevelMgr::GetInstancePtr()

#endif /* DYNAMICLEVELMGR_H_ */
