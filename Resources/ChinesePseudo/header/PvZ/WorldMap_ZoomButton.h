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
#include "WorldMap_UniverseViewButton.h"
#include "GameEventMgr.h"

class WorldMap_ZoomButton : public WorldMap_UniverseViewButton
{
	
public:
	RT_CLASS_DEFINE(WorldMap_ZoomButton, WorldMap_UniverseViewButton, RtClass) {}

	WorldMap_ZoomButton();
	virtual ~WorldMap_ZoomButton();
	
	// Public Interface (Inheritable)
	
	virtual void		Draw(Graphics* i_g) override;

	// Public Interface (Core)
	
	inline void			SetZoomedOut(const bool i_isZoomedOut);
	
protected:
	
	OVERRIDE_STATE_ONENTER(WidgetState, Initializing)

	// Protected Interface (Inheritable)
	
	virtual void		initLoadingResourcesGroupList() override;

private:

	// Private Interface (Core)
	
	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed) override;

	// Private Members (serialized)
	
	// Private Members (not serialized)
	bool				m_zoomsIn;
};

inline void WorldMap_ZoomButton::SetZoomedOut(const bool i_isZoomedOut)
{
	m_zoomsIn = i_isZoomedOut;
}

#endif
