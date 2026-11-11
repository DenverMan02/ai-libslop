//
//  WorldMap_FirstRechargeButton.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/9/2.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef WorldMap_FirstRechargeButton_h
#define WorldMap_FirstRechargeButton_h

#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_FirstRechargeButton : public UIWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_FirstRechargeButton, UIWidget, RtClass);
    
    WorldMap_FirstRechargeButton();
    virtual ~WorldMap_FirstRechargeButton();
    
    // Public Interface (Inheritable)
    
    virtual void		Draw(Graphics* i_g) override;
    virtual void		OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    virtual void		OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void		OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
    static bool         CheckVisibility();
    
protected:
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
    
    // Protected Interface (Inheritable)
    
    virtual void		initLoadingResourcesGroupList() override;
    
    virtual void		onUpdate() override;
    
private:
    
    // Private Interface (Core)
    
    virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
    // Private Members (serialized)
    
    // Private Members (not serialized)
};


#endif /* WorldMap_FirstRechargeButton_h */
