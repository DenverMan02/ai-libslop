//
//  Throttles.h
//  PlantsVersusZombies2
//
//  Created by Matt McDonald on 4/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Throttles__
#define __PlantsVersusZombies2__Throttles__

#include <set>
#include <string>

#include "TimeMgr.h"

#define DEFAULT_DELTA_INTERVAL_S 30.f

class UserPrefsWrapper;

class Throttles
{
public:
    Throttles(UserPrefsWrapper& userPrefsWrapper);
    static Throttles& GetInstance();
    
    pvztime_t GetDeltaIntervalInS();
    std::string GetMinVersion();
    void SetMinVersion(std::string minVersion);
    void SetDeltaIntervalInMS(int interval);
    
//    bool IsOpenGraphReportingEnabled();
    
    bool WorldIsDisabled(const std::string &i_worldName);
    void SetWorldDisabled(const std::string &i_worldName, bool i_disabled);
    
    bool GetDataServiceDebugText() { return m_dataServiceDebugText; }
    void SetDataServiceDebugText(bool i_enabled) { m_dataServiceDebugText = i_enabled; }
    
private:
    UserPrefsWrapper&	m_userPrefsWrapper;
    std::string			m_minVersion;
    bool				m_reloadPropertySheets;
    bool				m_giftingEnabled;
    std::string			m_seasonalCostumeEnabled;
    bool				m_dataServiceDebugText;
    
    std::set<std::string> m_disabledWorlds;
};

#endif /* defined(__PlantsVersusZombies2__Throttles__) */

