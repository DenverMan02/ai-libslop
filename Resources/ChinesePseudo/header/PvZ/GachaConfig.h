//
//  GachaConfig.h
//  PlantsVersusZombies2
//
//  Created by Rain Chen on 14-05-18.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GachaConfig__
#define __PlantsVersusZombies2__GachaConfig__

#include "PVZDB.h"
#include "ProfileMgr.h"
#include "Color.h"

struct GachaReward
{
    std::string strSku;
    std::string iType;
    int         iCount;
    int         iProbability;
    
    
    GachaReward()
    {
        iType = "";
        strSku = "";
        iCount = 0;
        iProbability = 0;
    }
};

//-----------------------------------------------

class GachaConfig : public Sexy::RtObject
{
public:
    
	RT_CLASS_DEFINE(GachaConfig, Sexy::RtObject, Sexy::RtClass);
    
    int GetGeneralRefreshTime() { return iGeneralRefreshTime; }
    int GetSpecialRefreshTime() { return iSpecialRefreshTime; }
    int GetSingleDrawPrice() {return iSingleDrawPrice; }
    int GetRepeatedDrawTimes() { return iRepeatedDrawTimes; }
    double GetRepeatedDrawDiscount() { return fRepeatedDrawDiscount; }
    std::vector<GachaReward>& GetGachaGlobalRewardList() { return GachaGlobalRewardList; }
    std::vector<GachaReward>& GetGachaPlantRewardList() { return GachaPlantRewardList; }
    std::vector<GachaReward>& GetGachaFreeRewardList() { return GachaFreeRewardList; }
    
    std::string GetGachaRewardType(const std::string &i_rewardSku);
    
private:
    int     iSingleDrawPrice;
    int     iRepeatedDrawTimes;
    float  fRepeatedDrawDiscount;
    int     iGeneralRefreshTime;
    int     iSpecialRefreshTime;
    std::vector<GachaReward> GachaGlobalRewardList;
    std::vector<GachaReward> GachaPlantRewardList;
    std::vector<GachaReward> GachaFreeRewardList;
    
};

#endif /* defined(__PlantsVersusZombies2__GachaConfig__) */
