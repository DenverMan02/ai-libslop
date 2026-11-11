//
//  WorldMap_ActivityLevelsButton.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/18.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_RechargeGiftButton_h
#define PlantsVersusZombies2_WorldMap_RechargeGiftButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_RechargeGiftButton : public UIWidget
{
    
public:
	RT_CLASS_DEFINE(WorldMap_RechargeGiftButton, UIWidget, RtClass);
    
	WorldMap_RechargeGiftButton();
	virtual ~WorldMap_RechargeGiftButton();
    
    virtual void			onUpdate() override;
    
	// Public Interface (Inheritable)
    
	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;

	void						CheckActivated();
protected:
	// Protected Interface (Inheritable)  
	virtual void			initLoadingResourcesGroupList() override;

private:
	// Private Interface (Core)
	virtual void			updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

	void						onButtonClicked();
	void						onPlantLevelUp(const std::string& type, int level);
	void						onWorldLoaded();

private:
};

#endif
