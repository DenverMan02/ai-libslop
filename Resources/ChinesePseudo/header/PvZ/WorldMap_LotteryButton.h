//
//  WorldMap_LotteryButton.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 13-8-23.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_LotteryButton_h
#define PlantsVersusZombies2_WorldMap_LotteryButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_LotteryButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_LotteryButton, UIWidget, RtClass);
    
	WorldMap_LotteryButton();
	virtual ~WorldMap_LotteryButton();
	
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
    
	// Private Members (serialized)
	
	// Private Members (not serialized)
};


#endif
