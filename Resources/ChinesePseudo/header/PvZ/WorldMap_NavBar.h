//
//  WorldMap_NavBar.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 1/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_NavBar_h
#define PlantsVersusZombies2_WorldMap_NavBar_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class UniverseWorldButton;
class MapEventItem;

class WorldMap_NavBar : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_NavBar, UIWidget, RtClass) {}

	WorldMap_NavBar();
	virtual ~WorldMap_NavBar();
	
	// Public Interface (Inheritable)
	
	virtual void                Draw(Graphics* i_g) override;
	virtual void                OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void                OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void                OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	virtual bool                IsMouseOver(const int i_mouseX, const int i_mouseY) override;
    virtual UniverseWorldButton* GetButtonForWorld(std::string i_worldName);
    virtual std::vector<UniverseWorldButton*> GetButtons();
	
	Rect				GetButtonRect(const int i_buttonIdx);
	
protected:
	
	OVERRIDE_STATE_ONENTER(WidgetState, Initializing)

	// Protected Interface (Inheritable)
	
	virtual void		initLoadingResourcesGroupList() override;

	virtual void		onUpdate() override;
	
private:

	// Private Interface (Core)
	
	void				updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
	void				syncButtonStates();

	void				onUnlockedStarGate(const MapEventItem* i_item);
	
	// Private Members (serialized)
	
	// Private Members (not serialized)

	std::vector<UniverseWorldButton*>	m_worldButtons;
};


#endif
