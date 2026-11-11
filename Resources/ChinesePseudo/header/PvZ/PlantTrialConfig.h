//
//  PlantTrialConfig.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-11-4.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantTrialConfig_h
#define PlantsVersusZombies2_PlantTrialConfig_h


#include "RtObject.h"
#include "TimeMgr.h"

namespace PlantTrial {
    const  int LogTypeManualPopup           = 3;
    const  int LogTypeAutoPopupAfterBattle  = 4;
    const  int LogTypeBuySuccess            = 5;
    const  int LogTypeClickBuy              = 6;
    const  int LogTypeAutoPopupAfterLogin   = 7;
}

struct TrialData
{
    const static int Money = 0;
    const static int Gem = 1;
    std::string strLevelName;
    std::string strPlant;
    std::string strZombie;
    std::string strPlantDesc;
    std::string strZombieDesc;
    std::string strSKU;
    std::string strKeysWorld;
    std::string Android_SKU;
    std::string IOS_SKU;
    int         iDesPlantLv;
    int         iBuyType;   //0 rmb, 1 gem
    int         iBuyValue;
    int         iSpawnZombieWave;
    int         iStillSecond;
    int         iPlantFood;
    int         iExtraKey;
    int         iExtraMoney;
    int         iDiscount;
    
    TrialData()
    : strKeysWorld("egypt")
    , iDesPlantLv(1)
    , iSpawnZombieWave(1)
    , iStillSecond(3600)
    , iPlantFood(0)
    , iExtraKey(3)
    , iExtraMoney(10000)
    , iDiscount(8)
    , iBuyType(Money)
    , iBuyValue(0) {}
};

struct TrialLogData
{
    std::string strLevelName;
    std::string strPlant;
};

class PlantTrialConfig : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(PlantTrialConfig, Sexy::RtObject, RtClass);
    
    PlantTrialConfig();
    
    const std::vector<TrialData> & GetData() { return m_vTrialData; }
    const std::vector<TrialLogData> & GetLog() { return m_logData; }
    void InitTableDate();
    
    const TrialLogData* GetLogDataByLevel(const std::string& Level);
    TrialData* GetTrialDataByLevelName(std::string strLevelName);
    TrialData* GetTrialDataByPlantName(std::string strPlantName);
    RtWeakPtr<class PlantTrialProperties> GetPlantTrialProperties() { return m_ptrPlantTrialProperties; }
    TrialData& GetTrialDataCache() { return m_stTrialDataCache; }
    void       SetTrialDataCache(TrialData& data) { m_stTrialDataCache = data; }
    
    TrialData* GetTrialDataBySku(std::string sku);

#ifdef HOST_IPHONEOS
    void        SetPlantTrialPaying(bool i_paying) { m_isPlantTrialPaying = i_paying; }
    bool        IsPlantTrialPaying()  { return m_isPlantTrialPaying; }
#endif
    
private:
    void UpdateSkuData();
	std::vector<TrialData> m_vTrialData;
    std::vector<TrialLogData> m_logData;
    TrialData              m_stTrialDataCache;
    RtWeakPtr<class PlantTrialProperties> m_ptrPlantTrialProperties;
    
#ifdef HOST_IPHONEOS
    bool m_isPlantTrialPaying;
#endif
};


#endif
