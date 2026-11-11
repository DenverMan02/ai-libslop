//
//  WorldMap_LimitGachaButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_LimitGachaButton__
#define __PlantsVersusZombies2__WorldMap_LimitGachaButton__

#include "UIEasyButtonWidget.h"

class WorldMap_LimitGachaButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_LimitGachaButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_LimitGachaButton();
    virtual ~WorldMap_LimitGachaButton();
    
    bool CheckActivated();
    void                onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void showOpenErrorDialog();
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();
    void onNotifyBackFromRift();
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_LimitGachaButton__) */
