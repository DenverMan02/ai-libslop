//
//  RebateRewardConfig.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-12-16.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_RebateRewardConfig_h
#define PlantsVersusZombies2_RebateRewardConfig_h

#include "Precompile.h"
#include "RtObject.h"

struct WorldReward
{
    std::string strWorldName;
    std::vector<int> vObjectID;
};

struct RewardCondition
{
    int iCharge;
    int iQuantity;
    bool bWithDress;
};

class RebateRewardConfig : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(RebateRewardConfig, Sexy::RtObject, RtClass);
    
    RebateRewardConfig();
    
    void InitDate();
    
    std::vector<WorldReward>& GetWorldReward() { return m_vWorldReward; }
    
    std::vector<RewardCondition>& GetRewardCondition() { return m_vRewardCondition; }
    
    int GetStartDate() { return m_iEventStartDate; }
    
    int GetEndDate() { return m_iEventEndDate; }
    
private:
    
    int m_iEventStartDate;
    int m_iEventEndDate;
    std::vector<WorldReward> m_vWorldReward;
    std::vector<RewardCondition> m_vRewardCondition;
};


class RebateDateMgr
{
    
public:
    
   static RebateDateMgr& GetInstance();
    
    RewardCondition& GetRewardConditionWithIndex(int iIndex);
    
    std::string GetPlantNameWithWorldName(std::string& strWorldName);
    int GetPLantIDWithWorldName(std::string& strWorldName);
    
    std::string GetMaxWorldName();
    
    Image* GetPlantPieceImage(std::string& strPlantName);
    
    SexyString GetItemName(std::string& strPlantName, bool bAvatar = false);
    
    bool IsValidTime();
    
    bool IsAnyRewardRemain();
    
private:
    
    bool IsPlantValid(std::string& strPlantName);
    
    bool IsTodayReward(std::string& strPlantName);
    
    bool IsPlantOverLevel(std::string& strPlantName);
    
    std::string GetPlantNameFromPool(std::vector<int>& vPool);
    
    int GetPlantIDFromPool(std::vector<int>& vPool);
    
    bool IsWorldRewardValid(std::string& strWorldName);
    
    WorldReward* GetWorldRewardByWorldName(std::string& strWorldName);
    
};

#endif
