//
//  DailyAchievementInfo.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/9/11.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DailyAchievementInfo__
#define __PlantsVersusZombies2__DailyAchievementInfo__

#include "RtObject.h"
#include "Precompile.h"

namespace Message
{
    void DailyAchievementReceived(int i_actId, int i_targetNum);
}

enum AchievementType
{
    AchievementType_Start = 10200,
    AchievementType_GetPlantPiece,
    AchievementType_GetPendantPiece,
    AchievementType_Gacha,
    AchievementType_GetAvatarPiece,
    AchievementType_CrazyYeti,
    AchievementType_GargantuarCrisis,
    AchievementType_DevilInvade,
    AchievementType_Star,
    AchievementType_PVP_BattleWin = 10209,
    AchievementType_PVP_TrainSpace = 10210,
    AchievementType_PVP_Rent = 10211,
    AchievementType_PVP_TrainCost = 10212,
    AchievementType_PVP_CupAdd = 10213,
    AchievementType_PVP_MedalAdd = 10214,
    AchievementType_PVP_CoinAdd = 10215,
    AchievementType_ThreeBossChallenge = 10216,
    AchievementType_WinLevel = 10217,
    AchievementType_VaseBreaker = 10872,
    AchievementType_Last,   //keep last!
};

struct AchievementConfig
{
    std::vector<int> m_contents;
    std::string m_tips;
    int m_activatedDate = 0;
    
    //no reflection part
    bool m_bServer;
    
    AchievementConfig()
    : m_bServer(false)
    {
        
    }
};

struct RewardContent
{
    std::string m_rewardName;
    std::string m_rewardType;
    std::string m_rewardImage;
    int         m_count;
    int         m_pieceCount;
    
    RewardContent()
    {
        m_count = 0;
        m_pieceCount = 0;
    }
};

struct NetworkRewardContent
{
    std::string m_rewardName;
    std::string m_rewardType;
    std::string m_rewardImage;
    int         m_count;
    int         m_pieceCount;
    int			m_objectId;

    NetworkRewardContent()
    {
        m_count = 0;
        m_pieceCount = 0;
        m_objectId = 0;
    }
};

struct AchievementItem
{
    std::vector<RewardContent> m_rewardContent;
    std::vector<int> m_targetNum;
    std::string m_description;
    int m_actId = 0;
    
    AchievementItem()
    {
        
    }
};

struct PoolContent
{
    std::string m_sku;

    int m_count;
    int m_weight;
    PoolContent()
    {
        m_sku = "";
        m_count = 0;
        m_weight = 0;
    }
};

//================================= No Reflection Part ===================================
struct PoolResult
{
    std::string m_sku;
    int m_minRate = 0;
    int m_maxRate = 0;
    int m_count = 0;
    PoolResult()
    {
        
    }
};

struct FinalPool
{
    std::vector<PoolResult> m_pool;
    int m_maxRate;
    FinalPool()
    {
        m_pool.clear();
        m_maxRate = 0;
    }
};

class NetworkAchievementItem : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkAchievementItem, Sexy::RtObject, Sexy::RtClass);

public:
	std::vector<NetworkRewardContent> m_rewardContent;
	std::vector<int> m_targetNum;
	std::string m_description;
	int m_actId = 0;
};

//========================================================================================

class DailyAchievementInfo : public Sexy::RtObject
{
public:
    
    RT_CLASS_DEFINE(DailyAchievementInfo, Sexy::RtObject, RtClass);
    
    DailyAchievementInfo();
    
    void InitDate();
    
    AchievementConfig*    getAchievementConfigByDate(int i_date);
    AchievementItem*      getAchievementItemById(int i_actId);
    void                  getRewardByConfig(int i_actId, int i_targetNum, const std::string& i_specficSku = "", const int& i_specificCount = 0, const std::string& i_rewardName = "");
    PoolResult            getRewardSkuByCertainPool(FinalPool& i_pool, const std::string& i_type);
    void                  initPool();
    
    const FinalPool& getSpecificAvatarPool() { return m_specificAvatarPool; }
    const FinalPool& getSpecificPlantPool() { return m_specificPlantPool; }
    
    void                  AddAchievementConfig(const AchievementConfig& achConfig);
    
private:
    void                  initSpecificAvatarPool();
    void                  initSpecificPlantPool();
    
    void                  initBoxAvatarPool();
    void                  initBoxPlantPool();
    
    void                  initBoxAccessoryPool();
    
private:
    std::vector<AchievementItem> m_achievementItem;
    std::vector<AchievementConfig> m_achievementConfig;
    std::vector<PoolContent> m_avatarRewardPool;
    std::vector<PoolContent> m_plantRewardPool;
    std::vector<PoolContent> m_avatarRewardBoxPool;
    std::vector<PoolContent> m_plantRewardBoxPool;
    std::vector<PoolContent> m_accessoryRewardBoxPool;
    
    //no reflection part
private:
    FinalPool m_specificAvatarPool;
    FinalPool m_specificPlantPool;
    
    FinalPool m_boxAvatarPool;
    FinalPool m_boxPlantPool;
    
    FinalPool m_boxAccessoryPool;
};



#endif /* defined(__PlantsVersusZombies2__DailyAchievementInfo__) */
