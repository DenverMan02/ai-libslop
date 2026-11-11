//
//  WorldMap_ConsumptionButton.h
//  PlantsVersusZombies2
//
//  Created by Lang, Nan on 15-5-27.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_ConsumptionButton__
#define __PlantsVersusZombies2__WorldMap_ConsumptionButton__

#include <stdio.h>
#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_ConsumptionButton : public UIWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_ConsumptionButton, UIWidget, RtClass);
    
    WorldMap_ConsumptionButton();
    virtual ~WorldMap_ConsumptionButton();
    
    // Public Interface (Inheritable)
    
    virtual void		Draw(Graphics* i_g) override;
    virtual void		OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    virtual void		OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void		OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
    void                OngetConsumptionRewardStat(bool i_success);
    
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
    void                onCloseDialog();
    
private:
    
    std::string    m_strImageButton;
    
    bool           m_bShowTips;
    
    // Private Members (serialized)
    
    // Private Members (not serialized)
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_RedPackButton__) */
