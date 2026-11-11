//
//  NetworkHelper.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-4-30.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NetworkHelper__
#define __PlantsVersusZombies2__NetworkHelper__

#include <iostream>
#include "NetworkData.h"

class NetworkHelper
{
public:
    static bool shallUpdateChargeReward(int totalCharge);
    static int getFirstChargeRewardIndex();
    static int getGachaActId(int inputId);
    static void pushDrawResult(const std::vector<S2C_BonusInfo>&  bonusList);
    static SexyString getObjectNameByActId(int i_actId);
    static std::string getObjectTypeStringByActId(int i_actId);
    static void checkNameMapperValid();
};


#endif /* defined(__PlantsVersusZombies2__iosNetworkHelper__) */
