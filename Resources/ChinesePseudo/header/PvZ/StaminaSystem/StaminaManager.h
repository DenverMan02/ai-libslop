//
//  StaminaManager.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-12-6.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StaminaManager__
#define __PlantsVersusZombies2__StaminaManager__

#include <iostream>
#include "ServerTime.h"
#include "../Singleton.h"
#include "TimeMgr.h"

#define MAX_REFRESH_STAMINA_COUNT       5
#define REFRESH_STAMINA_SECONDS         600


struct StaminaData
{
    uint32      lastServerTime;
    uint64      startLocalTime;
    uint64      lastLocalTime;
    int         leftSeconds;
    int         totalStamina;
    bool        isTrust;
    
    StaminaData()
    {
        startLocalTime = 0;
        lastLocalTime = 0;
        lastServerTime = 0;
        leftSeconds = 0;
        totalStamina = MAX_REFRESH_STAMINA_COUNT;
        isTrust = false;
    }
};

class StaminaManager : public LazySingleton<StaminaManager>
{
public:
    StaminaManager();
    ~StaminaManager();

    bool init();
    
    void update();
    
    ///return total stamina, include out of normal range 5.
    int     getCurrentStamina();
    void    addStamina(int count);

    
    ///return 1-600 seconds.
    ///return 0 means the stamina is to max.
    int     getLeftSeconds();

    bool    consumeStamina(int count=1);
    
    bool    isTrustTime();

protected:
    void    verifyServerTime(long serverTime);
    uint64  getLocalSeconds();
};









#endif /* defined(__PlantsVersusZombies2__StaminaManager__) */
