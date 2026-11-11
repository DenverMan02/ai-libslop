//
//  WorldMap_CommonButton.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-1.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_CommonButton__
#define __PlantsVersusZombies2__WorldMap_CommonButton__

#include <stdio.h>
#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_CommonButton : public UIWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_CommonButton, UIWidget, RtClass);
    
    WorldMap_CommonButton();
    virtual ~WorldMap_CommonButton();
    
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
    
    virtual void        DoPressButton() {}
    
private:
    
    // Private Interface (Core)
    
    virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
    bool                IsNeedTips();
    
private:
    
    bool                m_bShowTips;
    
    // Private Members (serialized)
    
    // Private Members (not serialized)
};

//////////////////////////

class WorldMap_ChristmasButton : public WorldMap_CommonButton
{
    
public:
    RT_CLASS_DEFINE(WorldMap_ChristmasButton, WorldMap_CommonButton, RtClass);
  
protected:
    
    void DoPressButton() override;
};

//////////////////////////

class WorldMap_ActivityCenterButton : public WorldMap_CommonButton
{
    
public:
    RT_CLASS_DEFINE(WorldMap_ActivityCenterButton, WorldMap_CommonButton, RtClass);
    
protected:
    
    void DoPressButton() override;
};




#endif /* defined(__PlantsVersusZombies2__WorldMap_CommonButton__) */
