//
//  WorldMap_NewerButton.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-8-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_NewerButton__
#define __PlantsVersusZombies2__WorldMap_NewerButton__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_NewerButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_NewerButton, UIWidget, RtClass);
    
	WorldMap_NewerButton();
	virtual ~WorldMap_NewerButton();
	
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

#endif /* defined(__PlantsVersusZombies2__WorldMap_NewerButton__) */
