//
//  WorldMap_ReconstructionButton.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-7-14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_ReconstructionButton__
#define __PlantsVersusZombies2__WorldMap_ReconstructionButton__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_ReconstructionButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_ReconstructionButton, UIWidget, RtClass);
	
	WorldMap_ReconstructionButton();
	virtual ~WorldMap_ReconstructionButton();
	
	// Public Interface (Inheritable)
	
	virtual void		Draw(Graphics* i_g) override;
    virtual void        onUpdate() override;
	virtual void        OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void        OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void		OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
protected:
	
	// Protected Interface (Inheritable)
	virtual void		initLoadingResourcesGroupList() override;
    
private:
    
	// Private Interface (Core)
	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_ReconstructionButton__) */
