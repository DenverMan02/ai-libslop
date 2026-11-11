//
//  GachaConfig.h
//  PlantsVersusZombies2
//
//  Created by Rain Chen on 14-05-18.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TreasureConfig__
#define __PlantsVersusZombies2__TreasureConfig__

#include "PVZDB.h"
#include "ProfileMgr.h"
#include "Color.h"

struct TreasureReward
{
    std::string strSku;
    std::string iType;
    int         iCount;
    int         iProbability;
    std::string mapName;
    int         iLeaf;
    
    
    TreasureReward()
    {
        iType = "";
        strSku = "";
        iCount = 0;
        iProbability = 0;
        mapName = "";
        iLeaf = 0;
    }
};

struct TreasurePool
{
    std::string mapName;
    int         iPrice;
    std::string stPurchase;
    int         iActId;
    int         iActTenId;
    std::string strImg;
    std::string strTitleImg;
    std::string strbkImg;
    
    TreasurePool():iPrice(0),iActId(0), iActTenId(0)
    {
        
    }
};
//-----------------------------------------------

class TreasureConfig : public Sexy::RtObject
{
public:
    
	RT_CLASS_DEFINE(TreasureConfig, Sexy::RtObject, Sexy::RtClass);
    
    
    typedef std::vector<TreasureReward>   VECTREASURES;
 
    
    VECTREASURES* GetTreasureRewardsByWorld(const std::string &strWorld);
    
    TreasurePool* GetTreasurePool(std::string& strMapname);
    
    std::vector<TreasurePool>& GetTreasurePools(){return TreasurePools;}
    
    TreasureReward* GetTreasureRewardBySku(std::string strSku);
    
private:
    
    std::vector<TreasureReward> TreasureRewardList;
    
    std::vector<TreasurePool>   TreasurePools;
   
    std::map<std::string,VECTREASURES>   m_mapTreasureReward;
};



#endif /* defined(__PlantsVersusZombies2__GachaConfig__) */
