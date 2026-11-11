//
//  WorldMap_SocialButton.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 2/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_SocialButton_h
#define PlantsVersusZombies2_WorldMap_SocialButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_SocialButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_SocialButton, UIWidget, RtClass);	
	
	WorldMap_SocialButton();
	virtual ~WorldMap_SocialButton();
	
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;

protected:
	
	// Protected Interface (Inheritable)
	
	virtual void			initLoadingResourcesGroupList() override;

private:

	// Private Interface (Core)
	
	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
	
};

#endif
