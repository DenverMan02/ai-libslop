//
//  WorldMap_LevelofDay.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/4/13.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef WorldMap_LevelofDay_h
#define WorldMap_LevelofDay_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "EffectAnim_UIAnim.h"
//#include "StarConvertConfig.h"
#include "Image.h"

class WorldMap_LevelofDay : public UIWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_LevelofDay, UIWidget, RtClass);
    
    WorldMap_LevelofDay();
    virtual ~WorldMap_LevelofDay();
    
    virtual void    onUpdate() override;
    
    virtual void    Draw(Graphics* i_g) override;
    virtual void    OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    virtual void    OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void    OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
    void            CheckActivated();
    void            OnLevelofDayOpening(bool i_success);
    void            OnWorldLoaded();
    
protected:
    virtual void    initLoadingResourcesGroupList() override;
    
private:
    virtual void    updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
    void            OnButtonClicked();
    
private:
};

#endif /* WorldMap_LevelofDay_h */
