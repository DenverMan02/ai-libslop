//
//  WorldMap_UpdateProgressButton.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-5-15.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_UpdateProgressButton__
#define __PlantsVersusZombies2__WorldMap_UpdateProgressButton__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

enum UpdaterType
{
    Updater_Type_None,
    Updater_Type_Tip,
    Updater_Type_DownLoading,
	Updater_Type_Finished,
	Updater_Type_Count
};

class WorldMap_UpdateProgressButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_UpdateProgressButton, UIWidget, RtClass) {}
    
	WorldMap_UpdateProgressButton();
	virtual ~WorldMap_UpdateProgressButton();
    
    void SetUpdaterType(UpdaterType i_type);
	
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
    
    UpdaterType  m_nType;
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_UpdateProgressButton__) */
