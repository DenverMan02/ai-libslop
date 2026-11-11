//
//  WorldMap_TwoYearButton.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-29.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_TwoYearButton__
#define __PlantsVersusZombies2__WorldMap_TwoYearButton__

#include <stdio.h>
#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_TwoYearButton : public UIWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_TwoYearButton, UIWidget, RtClass);
    
    WorldMap_TwoYearButton();
    virtual ~WorldMap_TwoYearButton();
    
    // Public Interface (Inheritable)
    
    virtual void		Draw(Graphics* i_g) override;
    virtual void		OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    virtual void		OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void		OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
protected:
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
    
    // Protected Interface (Inheritable)
    
    virtual void		initLoadingResourcesGroupList() override;
    
    virtual void		onUpdate() override;
    
private:
    
    // Private Interface (Core)
    
    virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
    void                DoPressButton();
    
    bool                IsNeedTips();
    
private:
    
    bool                m_bShowTips;
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_TwoYearButton__) */
