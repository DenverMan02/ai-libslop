//
//  WorldMap_AnniversaryButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_AnniversaryButton__
#define __PlantsVersusZombies2__WorldMap_AnniversaryButton__

#include "UIEasyButtonWidget.h"

class WorldMap_AnniversaryButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_AnniversaryButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_AnniversaryButton();
    virtual ~WorldMap_AnniversaryButton();
    
    
    bool CheckActivated();
    void OnLuaNotify(const std::string& rLuaEvent);
    void showOpenErrorDialog();


private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();
    void onNotifyBackFromRift();
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_AnniversaryButton__) */
