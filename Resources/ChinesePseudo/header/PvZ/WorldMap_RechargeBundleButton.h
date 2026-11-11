//
//  WorldMap_RechargeBundleButton.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/12/8.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef WorldMap_RechargeBundleButton_h
#define WorldMap_RechargeBundleButton_h

#include "RtObject.h"
#include "UIEasyButtonWidget.h"
#include "PVZ2UIButton.h"

class WorldMap_RechargeBundleButton : public UIEasyButtonWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_RechargeBundleButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_RechargeBundleButton();
    virtual ~WorldMap_RechargeBundleButton();
    
    // Public Interface (Inheritable)
    
    virtual void		Draw(Graphics* i_g) override;
    
    static bool         CheckVisibility(bool i_init = false);
    
    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);

};


class WorldMap_RechargeBundleButtonExtra : public PVZ2UIButton
{
public:
    WorldMap_RechargeBundleButtonExtra(int id, Sexy::ButtonListener* listener);

    virtual void Draw(Graphics* i_g) override;
};


#endif /* WorldMap_RechargeBundleButton_h */
