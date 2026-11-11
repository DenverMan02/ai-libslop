//
//  WorldMap_ZoomOutButton.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 1/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_ZoomOutButton_h
#define PlantsVersusZombies2_WorldMap_ZoomOutButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "WorldMap_ZoomInButton.h"
#include "GameEventMgr.h"

class WorldMap_ZoomOutButton : public WorldMap_ZoomInButton
{
	
public:
	RT_CLASS_DEFINE(WorldMap_ZoomOutButton, WorldMap_ZoomInButton, RtClass) {}

	WorldMap_ZoomOutButton();
	virtual ~WorldMap_ZoomOutButton();
	
	// Public Interface (Inheritable)
	
	virtual void		Draw(Graphics* i_g);
	
protected:
	
	OVERRIDE_STATE_ONENTER(WidgetState, Initializing)

	// Protected Interface (Inheritable)
	
	virtual void		initLoadingResourcesGroupList();

private:

	// Private Interface (Core)
	
	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

	// Private Members (serialized)
	
	// Private Members (not serialized)
};

#endif
