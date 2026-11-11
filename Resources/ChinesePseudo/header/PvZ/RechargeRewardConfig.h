//
//  RechargeRewardConfig.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/8/29.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef RechargeRewardConfig_h
#define RechargeRewardConfig_h

#include "RtObject.h"
#include "Precompile.h"
#include "NetworkData.h"

struct RechargeReward
{
    int32 objectId = 0;
    int32 quantity = 0;
    int32 weight = 0;
};

struct RechargeRewardContentConfig
{
    std::vector<RechargeReward> RewardList;
    SexyString RewardDescription;
    std::string BannerImage;
    std::string RewardImage;
    bool RandomReward = false;
    int RequiredAmount = 6;
    int ContentWidth = 0;
};


class RechargeRewardConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(RechargeRewardConfig, Sexy::RtObject, RtClass);
    
    void Init();
    const std::vector<RechargeRewardContentConfig>& getRewardContentList() { return m_rewardContent; }
    const std::vector<RechargeReward>& getFirstRechargeRewardContentList() { return m_firstRechargeRewardContent; }
    const std::string& getDefaultBanner() { return m_defaultBanner; }
    
    RechargeReward* pickRandomRewardFromConfig(int i_poolIdx);
    
    RechargeRewardContentConfig* getCurrentAvailableContent(const int& i_currRechargeAmount);
    RechargeRewardContentConfig* getNextAvailableContent(const int& i_currRechargeAmount);
    RechargeRewardContentConfig* getContentByIndex(const int& i_index);
    
private:
    //called by interface
    std::vector<RechargeRewardContentConfig>   m_rewardContent;
    
    std::vector<RechargeRewardContentConfig>   m_rewardContentIOS;
    std::vector<RechargeRewardContentConfig>   m_rewardContentAndroid;
    std::vector<RechargeReward>                m_firstRechargeRewardContent;
    std::string                         m_defaultBanner;
    int									m_startDate = 0;
    int									m_endDate = 0;
};

#endif /* RechargeRewardConfig_h */
