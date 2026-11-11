//
//  PVPManager.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.29
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVPManager__
#define __PlantsVersusZombies2__PVPManager__

#include "Singleton.h"
#include "RtDb.h"
#include "GameObject.h"
#include "PVZTypes.h"
#include "ArenaPrecompile.h"
#include "NetWorkData.h"
#include "PVPDatas.h"
#include "PVPShopConfigData.h"
#include "PlaybackData.h"

namespace Message
{
    void NotifyBattleEndingNetworkError();
    void NotifyPreviewModeBegin();
    void PVPCurrencyChanged();
	void NotifyArenaFinish();
    void NotifyAddOtherUserZbList(int64 profileId);
}

struct PVPZoneServerData
{
    int zoneId;
    int unlockPrice;
    bool isLock;
    PVPZoneServerData()
    : zoneId(0)
    , unlockPrice(0)
    , isLock(true)
    {
    }
};

struct NameEffectStruct
{
    int profileId;
    int zoneId;
    int houseId;
    std::wstring oldNmae;
    NameEffectStruct()
    : profileId(0)
    , zoneId(0)
    , houseId(0)
    {
    }
};

enum ServerPlantType
{
    Server_Plant_None,
    Server_Plant_Battle,
    Server_Plant_PVP_Edit,
    Server_Plant_Occupy_Edit
};

const int PVPMapHouseNum = 20;
const int PVPMapZoneNum = 6;

const int PVPPingStateInDefenseSetting  = 1;
const int PVPPingStateInBattle          = 2;
const int PVPPingStateEndDefenseSetting = 3;
const int PVPPingStateEndBattle         = 4;

#define RANK_MAX_COUNT      100
#define PER_RANKINFO_TO_GET 10

//-----------------------------------------------------------
class PVPManager : public LazySingleton<PVPManager>
{
public:
    PVPManager();
    ~PVPManager();
    void                    Initialise();
    void                    Reset();
    void                    Update();
    void                    Login();
    bool                    IsActivated();
    
    void                    SetPVPCoin(int iVal);
    int                     GetPVPCoin() const { return m_PVPCoin; }
    int                     GetPVPCoinMax();
    
    void                    SetPVPMedal(int iVal);
    int                     GetPVPMedal() const { return m_PVPMedal; }
    int                     GetPVPMedalMax();
  
    int                     GetPVPSunMax();
    
    void                    SetPVPCup(int iVal);
    int                     GetPVPCup() const { return m_PVPCup; }
    int                     GetPVPCupMax() const; 
    
    void                    SetGemToday(int iVal);
    int                     GetGemToday();
    void                    SetLeagueId(int iVal);
    int                     GetLeagueId() const { return m_leagueId; }
    
    void                    SetConfigData(const S2C_PVP_Entry& data);
    std::string             GetProductVersion();
    
    // zombie data
    class TrainingCamp*     GetZombieCamp();
    PVPZombieData*          AddZombieData(const PVPZombieData& data);
    PVPZombieData*          GetZombieData(const std::string& i_zombie);
    const MapZombieDatas&    GetZombieDatas() const { return m_ZombieDatas; }
    void                    GetZombieDatas(VecZombieDatas& o_Datas);
    void                    ClearZombieDatas() { m_ZombieDatas.clear(); }
    
    // skill data
    PVPSkillData*         AddSkillData(const PVPZombieData& data);
    PVPSkillData*          GetSkillData(const std::string& i_skill);
    const MapSkillDatas&    GetSkillDatas() const { return m_SkillDatas; }
    void                    ClearSkillDatas() { m_SkillDatas.clear(); }
    
    // pvp lab data
    PVPLabData&             GetLabData() { return m_labData; }
    void                    SetEndTimeTraining(float fVal) { m_endTimeTraining = fVal; }
    float                   GetEndTimeTraining() const { return m_endTimeTraining; }
    void                    SetEndTimeLab(float fVal) { m_endTimeLab = fVal; }
    float                   GetEndTimeLab() const { return m_endTimeLab; }
    void                    InitUpgradeConfig();
    PVPUpgradeData*          GetUpgradeConfig() { return m_upgradeConfig; }
    void                    SetAchievementTrain(int i_space, int i_cost);
    void                    SetAchievementMoney(int i_coin, int i_metal, int i_cup, bool bRent = false);
    
    // For save (In Battle)
    void                    SetPlayerPlantPositionInfo(const std::vector<ArenaPlantPositionData>& i_info);
    void                    SetPlayerPlantInfo(const std::vector<ArenaPlantInfoData>& i_info);
    void                    SetPlayerPlantInfoVersion(int i_ver);
    float                   GetTargetZombieAwakenScaledLevel(ZombieTypePtr i_type);
    void                    RequestSavePlayerProfile(int i_occupyId, int i_type);
    void                    AddPVPMapData(S2C_PVP_BigMapInfo& data);
    std::vector<S2C_PVP_BigMapInfo>& GetPVPMapDataList() { return m_PVPMapDataList; }
    S2C_PVP_BigMapInfo      GetPVPMapData(int zoneId, int houseId);
    
    void                    AddPVPMapPVPData(S2C_PVP_BigMapPVPInfo& data);
    std::vector<S2C_PVP_BigMapPVPInfo>& GetPVPMapPVPDataList() { return m_PVPMapPVPDataList; }
    S2C_PVP_BigMapMainInfo& GetPVPMapMainData() { return m_mainInfo;}
    const S2C_PVP_BigMapPVPInfo* GetPVPMapPVPData(int nZoneId, int nHouseId) const;
    
    void                    SetEvilDavidMaxChallengingTimes(int nCount);
    int                     GetEvilDavidMaxChallengingTimes(void) const;
    
    void                    SetEvilDavidStatus(int iStatus) { m_iEvilDavidStatus = iStatus; }
    int                     GetEvilDavidStatus() { return m_iEvilDavidStatus; }
    
    void                    SetEvilDavidResult(int iResult) { m_iEvilDavidResult = iResult; }
    int                     GetEvilDavidResult() { return m_iEvilDavidResult; }
    
    bool                    IsInBattle();
    bool                    IsEvilDavidBattle();
    int                     GetAttackCost();
    
    void                    AddPVPMapZoneData(PVPZoneServerData& data);
    std::vector<PVPZoneServerData>& GetPVPMapZoneDataList() { return m_PVPMapZoneDataLise; }
    void                    SetPVPCost(int iVal) { m_PVPGoldCost = iVal; }
    int                     GetPVPCost() const { return m_PVPGoldCost; }
    void                    SetPVPNeedCup(int iVal) { m_PVPCupNeed = iVal; }
    int                     GetPVPNeedCup() const { return m_PVPCupNeed; }
    void                    SetBattlePingInterval(int interval) { m_battlePingInterval = interval; }
    int                     GetBattlePingInterval() { return m_battlePingInterval; }
    void                    SetDefensePingInterval(int interval)  { m_defensePingInterval = interval; }
    int                     GetDefensePingInterval() { return m_defensePingInterval; }
    
    // For load (In Battle)
    void                    RequestGetPlayerProfile(int i_occupyId, int i_type, BattleID battle_id = 0);
    void                    RequestChangePlayer(int i_cid);
    void                    RequestGetEditPlant(int i_cid, int i_occupyId, int i_type);
    bool                    SetPlayerData(const std::string& i_data);
	bool                    SetPlayerData(const PlayerPlantData& i_data);
    PlayerPlantData         GetPlayerData() { return m_playerData; }
    const std::vector<ArenaPlantPositionData>& GetPlayerPlantPositionInfo() { return m_playerData.m_positionInfos; }
    const std::vector<ArenaPlantInfoData>& GetPlayerPlantInfo() { return m_playerData.m_plantInfos; }
    int                     GetTargetPlantLevel(PlantTypePtr i_type);
    bool                    GetTargetPlantAvatar(PlantTypePtr i_type);
    std::string             GetTargetPlantAccessory(int i_plantId);
    float                   GetTargetPlantAwakenDamage(PlantTypePtr i_type);
    void                    RequestBattleEnding(int i_result, int i_occupyId, int i_type, const std::vector<ZombieRecord>& loseZombies);
    bool                    SendPVP_Ping(int state);
    void                    RequestBuyPvpCoin(int item);
    void                    SetCurrentPVPType(ArenaType i_type) { m_currentPVPType = i_type; }
    ArenaType               GetCurrentPVPType() { return m_currentPVPType; }
    void                    SetPlayerCurrency(int i_num) { m_currentPlayerCurrency.m_PVPCoin = i_num; }
    void                    SetPlayerMedal(int i_num) { m_currentPlayerCurrency.m_PVPMedal = i_num; }
    void                    SetPlayerCup(int i_num) { m_currentPlayerCurrency.m_PVPCup = i_num; }
    void                    SetPlayerLeagueCurrency(int i_num) { m_currentLeagueCurrency.m_PVPCoin = i_num; }
    void                    SetPlayerLeagueMetal(int i_num) { m_currentLeagueCurrency.m_PVPMedal = i_num; }
    void                    SetPlayerLeagueCup(int i_num) { m_currentLeagueCurrency.m_PVPCup = i_num; }
    int                     GetPlayerCurrency() { return m_currentPlayerCurrency.m_PVPCoin; }
    int                     GetPlayerMedal() { return m_currentPlayerCurrency.m_PVPMedal; }
    int                     GetPlayerCup() { return m_currentPlayerCurrency.m_PVPCup; }
    int                     GetPlayerLeagueCurrency() { return m_currentLeagueCurrency.m_PVPCoin; }
    int                     GetPlayerLeagueCup() { return m_currentLeagueCurrency.m_PVPCup; }
    int                     GetPlayerLeagueMetal() { return m_currentLeagueCurrency.m_PVPMedal; }
    void                    SetCurrentDefenderInfo(DefenderInfo i_info) { m_currentDefenderInfo = i_info; }
    DefenderInfo            GetCurrentDefenderInfo() { return m_currentDefenderInfo; }
    int                     GetCurrentDefenderId() { return m_currentDefenderInfo.m_profileId; }
    std::string             GetCurrentLevelName() { return m_playerData.m_levelName; }
    std::string             GetCurrentEditLevelName() { return m_playerData.m_editLevelName; }
    void                    ResetPlayerData();
    ServerPlantType         IsLoadServerPlantData();
    bool                    IsLoadServerZombieData();
    bool                    IsInPlaybackMode();
    void                    SetCurrentOccupyId(int i_occupyId) { m_currentOccupyId = i_occupyId; }
    int                     GetCurrentOccupyId() { return m_currentOccupyId; }
    void                    SetCurrentHouseId(int i_houseId) { m_currentHouseId = i_houseId; }
    int                     GetCurrentHouseId() { return m_currentHouseId; }
    void                    SetCurrentZoneId(int i_zoneId) { m_currentZoneId = i_zoneId; }
    int                     GetCurrentZoneId() { return m_currentZoneId; }
    void                    SetIsOccupyPrepare(bool i_prepare) { m_isOccupyPrepare = i_prepare; }
    bool                    GetIsOccupyPrepare() { return m_isOccupyPrepare; }
    void                    SetStartFromOccupyPrepare(bool i_prepare) { m_startFromOccupyPrepare = i_prepare; }
    bool                    GetStartFromOccupyPrepare() { return m_startFromOccupyPrepare; }
    void                    SetIsPVPPrepare(bool i_prepare) { m_isPVPPrepare = i_prepare; }
    bool                    GetIsPVPPrepare() { return m_isPVPPrepare; }
    void                    SetStartFromPVPPrepare(bool i_prepare) { m_startFromPVPPrepare = i_prepare; }
    bool                    GetStartFromPVPPrepare() { return m_startFromPVPPrepare; }
    void                    SetChangerPlayerCooldown(int i_cooldown) { m_changePlayerCooldown = i_cooldown; }
    int                     GetChangerPlayerCooldown() { return m_changePlayerCooldown; }
    void                    SetCurrentDefenderPlayerId(int i_id) { m_defenderId = i_id; }
    int                     GetCurrentDefenderPlayerId() { return m_defenderId; }
    int                     GetCurrentVersion() { return m_playerData.m_version; }
    
    void                    SetChangedCurrency(const PVPCurrencyData& data) { m_changedCurrency = data; }
    const PVPCurrencyData&  GetChangedCurrency() const { return m_changedCurrency; }
    
    int32                   GetPVPProfileId();
    // For check ending (In Battle)
    bool                    GetIsInGameEnding() { return m_isInGameEnding; }
    void                    SetIsInGameEnding(bool i_ending) { m_isInGameEnding = i_ending; }
	void                    EndArenaBattle(bool bForceQuit = false);
    
    bool                    IsPreviewMode() { return m_isPreviewMode; }
    void                    SetPreviewMode(bool i_preivew) { m_isPreviewMode = i_preivew; }
    
    void                    RefreshTrainingDatas(class S2C_PVP_TrainingZombie* pDatas);
    
    //FOR Rank
    void                    RequestRankList(int rankType);
    void                    AddRankInfo(S2C_PvPRankInfo& data);
    const std::vector<S2C_PVP_RankInfo>& GetRankList(int rankType);
    int                     GetRankMaxCount(int rankType);
    int                     GetLeagueRewardCount() {return m_leagueRewardTime;}
    int                     GetLeagueTotalRewardCount() {return m_leagueTotalRewardTime;}
    const std::vector<S2C_PVP_LeagueInfo>& GetLeagueInfoList() {return m_leagueInfoList;}
    const std::vector<S2C_PVP_GardenRewardInfo>& GetGardenRewardInfoList() {return m_gardenRewardInfoList;}
    const std::vector<S2C_PVP_PreGardenRankInfo>& GetPreGardenRankInfoList() {return m_preGardenRankInfoList;}
    const S2C_PVP_RankInfo& GetMainRankInfo() { return m_mainRankInfo; }
    void                    AddOtherUserZbList(int64 profileId, const std::vector<S2C_PVP_ZombieInfo>& zbList);
    bool                    GetOtherUserZbList(int64 profileId, std::vector<S2C_PVP_ZombieInfo>& zbList);
    void                    RequestOtherUserZbList(int64 profileId);
    void                    ClearRankList();
    void                    SetRankMonthReward(const PvPRankMonthReward& i_data) { m_rankMonthReward = i_data; }
    const PvPRankMonthReward& GetRankMonthReward() const { return m_rankMonthReward; }
    
    //For pvp shop
    PVPShopConfigData&      GetPVPShopConfigData() {return m_pvpShopConfigData;}
    // home system
    int                     GetHomeLevel();
    const std::string&      CreateLogArenaID();
    const std::string&      GetLogArenaID();
    void                    SetPvpRequestStartTime(time_t time);
    time_t                  GetPvpRequestStartTime();
    bool                    HasNameChanged() { return m_nameChanged; }
    void                    nameChanged( bool flag ) { m_nameChanged = flag; }
    NameEffectStruct        GetOldNameStatus() { return m_oldNameStatus; }
    void                    SetOldNameStatus(NameEffectStruct old) { m_oldNameStatus = old; }
    
    void                    SetPVPMapType(PVPMapType i_type) { m_mapType = i_type; }
    bool                    IsInPVPMap();
    PVPMapType              GetPVPMapType() { return m_mapType; }
    
    int                     TimeToGem(int seconds);
    
    // playback
    void                    StartBattleReplay(BattleID battle_id);
    void                    SetRevengeID(BattleID battle_id) { m_revengeID = battle_id; }
    BattleID                GetRevengeID() const { return m_revengeID; }
    void                    RefreshBattleDataTo(class PlaybackData* pPlayback);
    void                    RefreshBattleDataFrom(class PlaybackData* pPlayback);
protected:
    
    // message handle
    void                    onEditPlayerPlant(bool i_success, int i_errorCode);
    void                    onGetPVPPlayerInfo(bool i_success, int i_errorCode);
    void                    onApplyData(int i_errorCode);
    void                    OnCloseDialog();
    void                    OnNetworkErrorCloseDialog();
    void                    onNetworkError(int erroId);
    void                    onDoChangePlayer();
    
protected:
    int                     m_PVPCoin;
    int                     m_PVPMedal;
    int                     m_PVPCup;

    int                     m_gemToday;
    int                     m_leagueId;
    PVPMapType              m_mapType;
    bool                    m_bFirstLogin;
    bool                    m_bInitialised;
    
    class TrainingCamp*     m_pZombieCamp;
    MapZombieDatas          m_ZombieDatas;
    MapSkillDatas          m_SkillDatas;
    PVPLabData              m_labData;
    float                   m_endTimeTraining;
    float                   m_endTimeLab;
    // (In Battle)
    PlayerPlantData         m_playerData;
    ArenaType               m_currentPVPType;
    PVPCurrencyData         m_currentPlayerCurrency;
    PVPCurrencyData         m_currentLeagueCurrency;
    PVPCurrencyData         m_changedCurrency;
    DefenderInfo            m_currentDefenderInfo;
    int                     m_currentOccupyId;
    int                     m_currentHouseId;
    int                     m_currentZoneId;
    bool                    m_isOccupyPrepare;
    bool                    m_startFromOccupyPrepare;
    
    bool                    m_isPVPPrepare;
    bool                    m_startFromPVPPrepare;
    
    int                     m_defenderId;
    BattleID                m_revengeID = 0;
    
    std::vector<S2C_PVP_BigMapInfo>     m_PVPMapDataList;
    std::vector<PVPZoneServerData>      m_PVPMapZoneDataLise;
    std::vector<S2C_PVP_BigMapPVPInfo>  m_PVPMapPVPDataList;
    S2C_PVP_BigMapMainInfo              m_mainInfo;
    int                     m_iEvilDavidMaxChallengingTimes;
    int                     m_iEvilDavidStatus;
    int                     m_iEvilDavidResult; //-1 into from map, 0 fail, 1 success
    
    int                     m_PVPGoldCost;
    int                     m_PVPCupNeed;
    int                     m_battlePingInterval;
    int                     m_defensePingInterval;
    std::string             m_strLogArenaID;
    time_t                  m_pvpRequestStartTime;
    
    bool                    m_isInGameEnding;
    
    bool                    m_isPreviewMode;
    int                     m_changePlayerCooldown;
    
    float                             m_rankCacheTime;
    std::vector<S2C_PVP_RankInfo>     m_leagueRankInfoList;
    int                               m_leagueMaxCount;
    int                               m_leagueRewardTime;
    int                               m_leagueTotalRewardTime;
    std::vector<S2C_PVP_RankInfo>     m_gardenRankInfoList;
    int                               m_gardenMaxCount;
    std::vector<S2C_PVP_LeagueInfo>   m_leagueInfoList;
    std::vector<S2C_PVP_GardenRewardInfo>   m_gardenRewardInfoList;
    std::vector<S2C_PVP_PreGardenRankInfo>   m_preGardenRankInfoList;
    S2C_PVP_RankInfo                    m_mainRankInfo;
    PvPRankMonthReward                      m_rankMonthReward;
    
    std::map<int64, std::vector<S2C_PVP_ZombieInfo>> m_otherZbList;
    
    bool                    m_nameChanged;
    NameEffectStruct        m_oldNameStatus;
    
    PVPShopConfigData       m_pvpShopConfigData;
    PVPUpgradeData*         m_upgradeConfig;
    bool                    m_doChangePlayer;
public:
    bool                    m_PingDisabled;
public: // static
    static const std::string    GetLevelIconString(int i_level);  // <=0 means disabled
    static const std::string PacketsZombiePrefix;
    static const std::string PacketsZombieBigPrefix;
    static const std::string PacketsSkillPrefix;
};

#define gPVPManager (PVPManager::GetInstancePtr())


#endif /* defined(__PlantsVersusZombies2__PVPManager__) */
