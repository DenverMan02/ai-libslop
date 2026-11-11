//
//  WorldMap_AuthenticationButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_AuthenticationButton__
#define __PlantsVersusZombies2__WorldMap_AuthenticationButton__

#include "UIEasyButtonWidget.h"
#include "LawnAppEnums.h"

class WorldMap_AuthenticationButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_AuthenticationButton, UIEasyButtonWidget, RtClass);
    
	WorldMap_AuthenticationButton();
    virtual ~WorldMap_AuthenticationButton();
    
    void OnNotyAuthenticationSuc(bool i_success);
    void BackToMap();
    
    bool CheckActivated();

    static bool IsVisible();// check visible
    
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();

    std::vector<PlatformType> blacklistChannels;

    static bool _isVisible;// if this button is visible
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_AuthenticationButton__) */
