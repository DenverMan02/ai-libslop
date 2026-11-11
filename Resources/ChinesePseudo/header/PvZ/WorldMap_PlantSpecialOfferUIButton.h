//
//  WorldMap_PlantSpecialOfferUIButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_PlantSpecialOfferUIButton__
#define __PlantsVersusZombies2__WorldMap_PlantSpecialOfferUIButton__

#include "UIEasyButtonWidget.h"

class WorldMap_PlantSpecialOfferUIButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_PlantSpecialOfferUIButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_PlantSpecialOfferUIButton();
    virtual ~WorldMap_PlantSpecialOfferUIButton();
    
    bool CheckActivated();
    void                onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void showOpenErrorDialog();
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();
    void onNotifyBackFromRift();
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_PlantSpecialOfferUIButton__) */
