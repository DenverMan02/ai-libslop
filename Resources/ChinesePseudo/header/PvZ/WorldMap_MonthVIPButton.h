//
//  WorldMap_MonthVIPButton.h
//  PlantsVersusZombies2
//
//  Created by xuzh on 17/03/15.
//  Copyright © 2017年 PopCap Games. All rights reserved.
//

#ifndef WorldMap_MonthVIP_Button_h
#define WorldMap_MonthVIP_Button_h

#include "UIEasyButtonWidget.h"
#include "EASquared.h"

class WorldMap_MonthVIPButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_MonthVIPButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_MonthVIPButton();
    virtual ~WorldMap_MonthVIPButton();
    
    void checkVisiable();
    
    void onShowVIPWnd();
};

#endif /* WorldMap_MonthVIP_Button_h */
