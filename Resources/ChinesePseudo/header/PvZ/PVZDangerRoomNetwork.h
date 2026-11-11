//
//  PVZDangerRoomNetwork.h
//  PlantsVersusZombies2
//
//  Created by ZYM on 14-12-12.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZDangerRoomNetwork_h
#define PlantsVersusZombies2_PVZDangerRoomNetwork_h

#include "NetworkServiceManager.h"
#ifdef HOST_IPHONEOS
#include "iosNetworkMsgProcess.h"
#endif
#include "PVZDB.h"
#include "PVZVersion.h"

namespace Message
{
	void RequestRankComplete(bool i_success);
}

enum DangerRoomType
{
    TYPE_ACTIVITY,
    TYPE_REWARD,
    TYPE_ACTIVITY_AND_REWARD,
};

enum FailedStartGameReason
{
    Reason_Ok,
    Reason_Not_In_Activity_Date,
    Reason_Not_Enough_Life,
    Reason_Not_Connect_Internet,
};

struct RewardInfo
{
    RewardInfo()
    {
        Type = "";
        Value = 0;
    }
    
    std::string Type;
    int Value;
};

struct ValidateInfo
{
    ValidateInfo()
    {
        Weight = 0;
        CurrentLevel = 0;
        CurrentWave = 0;
        Result = 0;
        LevelTime = 0;
        CurrentScore = 0;
    }
    
    int Weight;
    int CurrentLevel;
    int CurrentWave;
    int Result;
    int LevelTime;
    int CurrentScore;
};

class PVZDangerRoomNetwork
{
public:
	PVZDangerRoomNetwork();
	~PVZDangerRoomNetwork();
	void RequestForRank(int i_retries = 0, bool i_isUpload = false, int i_preRank = 0);
    void TryRequest(bool i_isUpload, int i_preRank);
    //void OnRequestFinished(std::string i_json);   
	void RequestRankUpdate();
    
    std::string GetUpdateUrl();
    
    // Rank and score functions
    RewardInfo GetTitleReward(int i_score);
    int GetLastRewardLevel(int i_score);
    std::string GetTitleText(int i_score);
    // Used for get player rank
    int GetTotalHighestScore();
    RewardInfo GetCurrentReward(int i_rank, bool i_PreScore);
    RewardInfo GetCurrentReward(int i_rank);
    RewardInfo GetLastReward(int i_lastrank);
    bool CanPickReward();
    
    void SetHasPickedReward(bool i_picked);
    
    void ValidateEvent();
    void SetDangerRoomLife(DangerRoomLifeData i_life);
    void SetDangerRoomRank(int i_rank);
    void SetDangerRoomScore(int i_score);
    void OnRequestFinished(bool i_success, int i_rank);
    
    void OnRequestFailed();
    
    int GetActiveRank();
    
    int GetLeftDangerRoomDays(bool i_reward);
    
    bool CanBuyLife();
    
    int GetCurrentLife();
    
    void ConsumeLife();
    
    bool CanStartDangerRoom();
    void OnScoreUpdated(bool i_success);
    void BuyLifeNew();
    void OnBuyDangerRoomLife(const bool& isSuccess);
    void OnLifeCost(bool i_success, bool i_noLife = false);
    //bool CanStartGame();
    FailedStartGameReason GetGameStatus(DangerRoomLevelType i_type);
    void OnCloseDialog();
    bool IsCurrentProgressDifferent(DangerRoomLevelType i_type);
    
    void ResetCurrentDangerRoom();
    
    bool IsCurrentDangerRoomFinished();
    
    int GetCurrentLifeCost();
    
    void SetValidateInfo(ValidateInfo& i_info) { m_validateInfo = i_info; }
    
    bool NeedResetLifeTimeCheck();
    
    void ResetAllDangerRoomInfo(bool i_eventRestart);
    
    void ResetPreHighestScore();
    
    int  GetPreHighestScore();
    
    void SaveCurrentProgress();
    
    bool IsInCurrentProgress();
    
    bool IsInCurrentProgress(DangerRoomLevelType i_type);
    
private:      
    
    bool NeedResetLife();   
    
    int         m_retriesLeft;
    std::string m_updateUrl;
    
    int         m_rank;
    
    ValidateInfo m_validateInfo;
};

#endif
