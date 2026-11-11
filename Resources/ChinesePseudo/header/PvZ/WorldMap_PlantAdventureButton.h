//
//  WorldMap_PlantAdventureButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_PlantAdventureButton__
#define __PlantsVersusZombies2__WorldMap_PlantAdventureButton__

#include "UIEasyButtonWidget.h"

class WorldMap_PlantAdventureButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_PlantAdventureButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_PlantAdventureButton();
    virtual ~WorldMap_PlantAdventureButton();
    
    void OnGotExploreTeamStatus(bool i_success);
    void BackToMap();
    
    bool CheckActivated();
    void                onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void showOpenErrorDialog();
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_PlantAdventureButton__) */
