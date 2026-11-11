//
//  DangerRoomManager.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.10.27
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _DangerRoomManager_h_
#define _DangerRoomManager_h_

#include "Singleton.h"
#include "Widget.h"
#include "NetworkData.h"
#include "EASquared.h"

namespace Lua {
    class CUIDialog;
}

namespace Message
{
	void DangerRoomSelectListSaved();
}

enum DangerRoomType
{
	DangerRoom_Normal,
	DangerRoom_Training
};

class DangerRoomInfo;

class NetworkSelectPlantListInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkSelectPlantListInfo, INetworkData, RtClass);

public:
	std::vector<S2C_DangerRoomPlantNum> m_plantList;
};

class NetworkADRefreshInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkADRefreshInfo, INetworkData, RtClass);

public:
	int m_watchedCount;
};

class DangerRoomManager : public LazySingleton<DangerRoomManager>
{
public:
    const static int LevetUninitilize = -1;
    static DangerRoomManager* GetPtr() { return DangerRoomManager::GetInstancePtr(); }
public:
    DangerRoomManager();
    ~DangerRoomManager();
    void Reset();
    Lua::CUIDialog*     ShowMainDialog();
    Lua::CUIDialog*     GetMainDialog();
    void                CloseMainDialog();
    void				SetMainDialogVisible(bool i_visible);
    bool                IsOpened();
    
    void                StartLevel();
    void                EnterLevel(bool i_training);
    
    void                ShowEndLevel(bool i_msgError);
    
    // set/get
    void                SetRecord(const S2C_DangerRoomRecord& i_record);
    const S2C_DangerRoomRecord& GetRecord() const { return m_record; }
    void                SetMedal(int i_value);
    int                 GetMedal() const { return m_record.m_medal; }
    void                SetCurrentLevel(int i_value);
    int                 GetCurrentLevel() const;
    int                 GetNextLevel() const;
    void                SetMaxLevel(int i_value);
    int                 GetMaxLevel() const;
    void                SetMaxLastWeekLevel(int i_value);
    int                 GetMaxLastWeekLevel() const;
    const DangerRoomInfo& GetDangerRoomInfo(bool i_training = false) const;
    void                SetDangerRoomInfo(const DangerRoomInfo& i_dangerRoomInfo, bool i_training = false);
    int                 GetPlantfoodNum() const;
    int                 GetSunNum() const;
    int                 GetDayScore() const;
    
    int                 GetPlantNum(const std::string& i_plantName) const;
    int                 GetPlantNum(int i_id) const;
    bool                IsHavePlant(int i_id) const;
    void                SetPlantOnBoard(const std::string& i_plantName);    
    void                SetPlantOnBoard(const std::string& i_plantName, int count);
    const std::vector<S2C_DangerRoomPlantNum>& GetPlantNumList() const { return m_record.m_plantNumList; }
    void				SetPlantNumList(const std::vector<S2C_DangerRoomPlantNum>& i_list) { m_record.m_plantNumList = i_list; }
    void				SetCachePlantNumList(const std::vector<S2C_DangerRoomPlantNum>& i_list) { m_cachePlantNumList = i_list; }
    const std::vector<S2C_DangerRoomPlantNum>& GetCachePlantNumList() const { return m_cachePlantNumList; }
    
    std::string         GetWorldName() const { return m_worldName; }
    float               GetBossHp() const { return m_bossHp; }
    
    int                 GetSkipGemCost() const { return m_record.m_jumpCost; }
    int                 GetSkipLevelNum() const { return m_record.m_jumpLevel; }
    int                 GetMowerNum() const;
    void                SetHaveMower(int i_row, bool have);
    bool                IsHaveMower(int i_row);
    void                SetFailed(bool i_value) { m_bFailed = i_value; }
    bool                IsFailed() const { return m_bFailed; }
    
    void                SetLevelScore(int i_value) { m_levelScore = i_value; }
    int                 GetLevelScore() const;
    void                SetLevelMedal(int i_value) { m_levelMedal = i_value; }
    int                 GetLevelMedal() const;
    void                SetLevelSunAdd(int i_value) { m_levelSunAdd = i_value; }
    int                 GetLevelSunAdd() const { return m_levelSunAdd; }
    int                 GetRankPredict() const { return m_record.m_rankPredict; }
    int                 GetScorePredict() const { return m_record.m_scorePredict; }
    void                SetLevelPlantsAdd(const std::vector<S2C_DangerRoomPlantNum>& i_list) { m_levelPlantsAdd = i_list; }
    const std::vector<S2C_DangerRoomPlantNum>& GetLevelPlantsAdd() const { return m_levelPlantsAdd; }
    
    void                SetActionPopup(int i_value) { m_iActionPopup = i_value; }
    int                 GetActionPopup() const { return m_iActionPopup; }
    void                SetCukeCount(int i_value);
    int                 GetCukeCount() const;
    int                 GetCukeUsedCount() const;
    // ----- message -------
    void                OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void                OnBuyItemFinish(class MsgResultInfo* io_result, const class S2C_ICloud_GetConsumeGemInfo* pInfo, const class S2C_PlayerInfo* pGemChanged);
    void                OnNotifySkipDangerRoom(int result, const S2C_DangerRoomSkipLevel* data, const class S2C_PlayerInfo* pGemChanged);
    void                OnNotifyChallengeReward(const std::string& i_jsonStr);
    
    void                RequestResetFree();
    void                OnResetDangerRoom();     // free & cost
    const class DangerRoomPropertySheet* GetProps();
    void                InitProps(const class S2C_DangerRoomPropertySheet* props);
    std::string         CheckPlantList(bool i_init);
    int                 PickupZombieLevelForCurrentLevel();
    bool                IsPropsInit() const { return m_bPropInit; }
    void                SetPropsInit(bool value) { m_bPropInit = value; }
    int                 GetLevelLimit() const { return m_levelLimit; }
    void                SetPlantFoodBuyCount(int count);
    int                 GetPlantFoodBuyCount();
    const std::vector<int>& GetPlantFoodPrice();
    void				SetArtifactLeftTimes(int count);
    int					GetArtifactLeftTimes();
    void				SetArtifactMaxTimes(int count);
    int					GetArtifactMaxTimes();
    int					GetArtifactUsedTimes();

    //DangerRoom Select Screen
    int					GetMaxSelectedPlant();
    void				GetInitPlantList(std::vector<int>& i_list);
    void				GetSelectedPlantList(std::vector<int>& i_list);
    void				SaveSelectedPlantList(std::vector<int>& i_list);
    void				GetFavoritePlantList(std::vector<int>& i_list);
    void				RebuildPlantNumList(const std::vector<int>& i_list);
    void				RebuildNewPlantNumList(const std::vector<int>& i_list);
    const std::vector<S2C_DangerRoomPlantNum>& GetCurrentPlantNumList() const;
    bool				PlayerReachRequiredPlantNum();
    void				LoadPlantNumList();
    std::string         CheckSelectPlantList();
    void				SendSelectPlantList();

    // for ads - endless shop refresh
	void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
	bool IsAdvertisementEnable();
    void PlayAds();
    void ShowAD(int i_type);
    int GetLeftADWatchCount(int i_type);
    bool CanWatchAD(int i_type);
    void SetADWatchCount(int i_type, int i_count);
    void onADFinished(int i_type);

    // for ads - challenge time buy reset
    void onAdsFinish_ChallengeTimeReset(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    bool IsAdvertisementEnable_ChallengeTimeReset();
    void PlayAds_ChallengeTimeReset();

    void RequestAds_Reset(int id);// for ads reset btn
    void RequestSpecialOfferExtraUI();

    // Training Room
    void SetCurrentTrainingWorld(const std::string& i_world);
    std::string GetCurrentTrainingWorld();
    std::vector<std::string> GetTrainingWorldList() { return m_trainingWorldList; }
    int GetHighestTrainingRecord(const std::string& i_world);

    void SetDangerRoomType(DangerRoomType i_type) { m_type = i_type; }
    DangerRoomType GetDangerRoomType() const { return m_type; }
    int GetNextTrainingLevel() const;
    int GetCurrentTrainingLevel() const;
    void SetCurrentTrainingLevel(int i_value);

    const DangerRoomInfo& GetCurrentDangerRoomInfo() const;
    int                   GetCurrentNextLevel() const;
    bool IsTrainingMode() const { return GetDangerRoomType() == DangerRoom_Training; }
    void HandleLevelEnd(DangerRoomInfo& i_cacheInfo);
    bool HasTrainingInfo();
    int  GetCurrentTrainingCount() { return m_currentTrainingCount; }
    void SetCurrentTrainingCount(int i_count) { m_currentTrainingCount = i_count; }

private:
    void                OnNarrationFinished();
    void                OnResetCallback(class UIMessageBox* pBox, int buttonID);
    int                 GetResetGemCost();
protected:
    std::string         m_worldName;
    float               m_bossHp = 1.0f;
    S2C_DangerRoomRecord    m_record;
    bool                m_bFailed = false;      // means the whole dangerroom failed.(need start over.)
    int                 m_levelScore = 0;
    int                 m_levelMedal = 0;
    int                 m_levelSunAdd = 0;
    int                 m_levelLimit = 0;
    std::vector<S2C_DangerRoomPlantNum> m_levelPlantsAdd;
    int                 m_iActionPopup = 0;
    class DangerRoomPropertySheet* m_props = nullptr;
    S2C_DangerRoomPropertySheet m_s2c_props;
    bool                m_bReward = false;
    bool                m_bPropInit = false;
    std::set<int>       m_initedPlants;
    std::vector<int>    m_plantfoodPrice;
    std::vector<S2C_DangerRoomPlantNum> m_currentPlantNumList;
    std::vector<S2C_DangerRoomPlantNum> m_cachePlantNumList;

    // Training Room
    std::vector<std::string> m_trainingWorldList;
    std::string m_currentTrainingWorld = "";
    DangerRoomType m_type = DangerRoom_Normal;
    int m_currentTrainingCount = 0;
};

#define gDangerRoomMgr (DangerRoomManager::GetInstancePtr())

//------------------------------------------------
// DangerRoomRuleAwardItem
//------------------------------------------------
class DangerRoomRuleAwardItem : public Sexy::Widget
{
public:
    virtual void    Draw(Sexy::Graphics* i_g) override;
    void            Refresh();
public:
    SexyString      m_strDesc;
    SexyString      m_strAward;
    Sexy::Image*    m_pAwardImage = nullptr;
    int             m_headID = -1;
};


//------------------------------------------------
// MiniGameRuleAwardItem
//------------------------------------------------
class MiniGameRuleAwardItem : public Sexy::Widget
{
public:
	MiniGameRuleAwardItem();
	virtual void    Draw(Sexy::Graphics* i_g) override;
public:
	SexyString      m_strDesc;
	SexyString      m_strAward[3];
	Sexy::Image*    m_pAwardImage[3];
};


#endif
