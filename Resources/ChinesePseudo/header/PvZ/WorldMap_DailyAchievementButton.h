//
//  WorldMap_DailyAchievementButton.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/9/21.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_DailyAchievementButton__
#define __PlantsVersusZombies2__WorldMap_DailyAchievementButton__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "WorldData.h"

class WorldMap_DailyAchievementButton : public UIWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_DailyAchievementButton, UIWidget, RtClass);
    
    WorldMap_DailyAchievementButton();
    virtual ~WorldMap_DailyAchievementButton();
    
    // Public Interface (Inheritable)
    
    virtual void			Draw(Graphics* i_g) override;
    virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
    void                CheckActivited();
    
protected:
    
    // Protected Interface (Inheritable)
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
    virtual void			initLoadingResourcesGroupList() override;
    
    void                onWorldLoaded();
    void                onNotifyAchievementConfigChanged();
    
private:
    
    // Private Interface (Core)
    
    virtual void			updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
    bool                    canGetDailyAchievementReward();
    
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_DailyAchievementButton__) */
