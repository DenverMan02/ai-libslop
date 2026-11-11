//
//  WorldMap_PlantAdventureButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_DaveClubButton__
#define __PlantsVersusZombies2__WorldMap_DaveClubButton__

#include "UIEasyButtonWidget.h"

class WorldMap_DaveClubButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_DaveClubButton, UIEasyButtonWidget, RtClass);
    
	WorldMap_DaveClubButton();
    virtual ~WorldMap_DaveClubButton();
    
    void OnGotExploreTeamStatus(bool i_success);
    void BackToMap();
    
    bool CheckActivated();
	void OnNotifyRefresh(bool i_success, const std::set<int>& changeList);
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_PlantAdventureButton__) */
