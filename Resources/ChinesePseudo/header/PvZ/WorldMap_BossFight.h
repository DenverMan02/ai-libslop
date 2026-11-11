//
//  WorldMap_BossFight.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/9/9.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_BossFight__
#define __PlantsVersusZombies2__WorldMap_BossFight__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_BossFightButton : public UIWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_BossFightButton, UIWidget, RtClass);
    
    WorldMap_BossFightButton();
    virtual ~WorldMap_BossFightButton();
    
    virtual void    onUpdate() override;
    
    // Public Interface (Inheritable)
    
    virtual void    Draw(Graphics* i_g) override;
    virtual void    OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    virtual void    OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void    OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
    void            CheckActivated();
protected:
    // Protected Interface (Inheritable)
    virtual void    initLoadingResourcesGroupList() override;
    
private:
    // Private Interface (Core)
    virtual void    updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
    void            onButtonClicked();
    void            onWorldLoaded();
    
private:
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_BossFight__) */
