//
//  WorldMap_AdsRewardButton.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/8/25.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef WorldMap_AdsRewardButton_h
#define WorldMap_AdsRewardButton_h

#include "UIEasyButtonWidget.h"
#include "EASquared.h"

class WorldMap_AdsRewardButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_AdsRewardButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_AdsRewardButton();
    virtual ~WorldMap_AdsRewardButton();
    
    void checkVisiable();
    
    void onGetReward(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    
    void onEASquaredAdsAvailableChanged();
    
    void changeAvailable();
    
    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);
    
    void onNotifyAdsReward(const class S2C_ADSReward& reward);

protected:
    virtual void onLoadComplete() override;
};

#endif /* WorldMap_AdsRewardButton_h */
