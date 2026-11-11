//
//  WorldMap_SalesButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/3/12.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef WorldMap_SalesButton_h
#define WorldMap_SalesButton_h

#include "UIEasyButtonWidget.h"

class WorldMap_SalesButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_SalesButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_SalesButton();
    virtual ~WorldMap_SalesButton();
    
    bool            CheckActivated();
    
private:
    void            onButtonClicked();
    void            onWorldLoaded();
};

#endif /* WorldMap_SalesButton_h */
