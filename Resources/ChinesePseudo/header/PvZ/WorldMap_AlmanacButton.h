//
//  WorldMap_AlmanacButton.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_AlmanacButton_h
#define PlantsVersusZombies2_WorldMap_AlmanacButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "WorldData.h"

class WorldMap_AlmanacButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_AlmanacButton, UIWidget, RtClass);	
	
	WorldMap_AlmanacButton();
	virtual ~WorldMap_AlmanacButton();
	
	// Public Interface (Inheritable)
    void                    OnWorldMapWorldLoaded();
    void                    OnUniverseMapOpened();
	
	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;

	void WaitForTutorialClick()
	{
		m_clicked = false;
	}
	bool WasClickedForTutorial()
	{
		return m_clicked;
	}

protected:
	
	// Protected Interface (Inheritable)
	OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
	virtual void			initLoadingResourcesGroupList() override;

private:
	
	// Private Interface (Core)
	
	virtual void			updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

	// Used for tutorial tracking purposes.
	bool m_clicked;
	
};

#endif
