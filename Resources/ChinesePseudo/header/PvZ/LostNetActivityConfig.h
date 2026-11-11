//
//  LostNetActivityConfig.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 2016/12/30.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef LostNetActivityConfig_h
#define LostNetActivityConfig_h

#include "Precompile.h"
#include "RtObject.h"

class LostNetActivityConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(LostNetActivityConfig, Sexy::RtObject, RtClass);
    
    LostNetActivityConfig();
    ~LostNetActivityConfig();
    
    void Refresh();
    
    bool IsActivity();
    int GetCurrentBonus();
    time_t GetTodaySec();
    
public:
    int OrgPrice = 98;
    int Price = 30;
    int Coins = 30000;
    int Gems = 300;
    int TargetLevel = 2;
    int LimitLevel = -1;
    std::vector<int> RewardPool;
    
private:
    bool m_inited = false;
    
    int StartDate = 0;
    int EndDate = 0;
};

#endif /* LostNetActivityConfig_h */
