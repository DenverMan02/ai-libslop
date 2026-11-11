//
//  WorldMap_RedPackButton.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15-1-17.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_RedPackButton__
#define __PlantsVersusZombies2__WorldMap_RedPackButton__

#include <stdio.h>
#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_RedPackButton : public UIWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_RedPackButton, UIWidget, RtClass);
    
    WorldMap_RedPackButton();
    virtual ~WorldMap_RedPackButton();
    
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
    
    void                DoPressRedPacketButton();
    
    // Private Members (serialized)
    
    // Private Members (not serialized)
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_RedPackButton__) */
