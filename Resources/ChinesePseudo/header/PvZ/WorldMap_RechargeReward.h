//
//  WorldMap_RechargeReward.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_RechargeReward__
#define __PlantsVersusZombies2__WorldMap_RechargeReward__

#include "UIEasyButtonWidget.h"

class WorldMap_RechargeReward : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_RechargeReward, UIEasyButtonWidget, RtClass);
    
    WorldMap_RechargeReward();
    virtual ~WorldMap_RechargeReward();
    
    bool CheckActivated();
    void                onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void showOpenErrorDialog();
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_RechargeReward__) */
