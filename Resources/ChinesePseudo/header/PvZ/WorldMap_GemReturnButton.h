//
//  WorldMap_TreasureButton.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-6-6.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_GemreturnButton_h
#define PlantsVersusZombies2_WorldMap_GemreturnButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_GemreturnButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_GemreturnButton, UIWidget, RtClass);
	
	WorldMap_GemreturnButton();
	virtual ~WorldMap_GemreturnButton();
	
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
    virtual void            onUpdate() override;
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
	virtual void			initLoadingResourcesGroupList() override;
    
private:
    
	// Private Interface (Core)
	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
#ifdef HOST_ANDROID
    void OnButtonClicked();
    void OnConfirmReward();
    
private:
    int m_gemSum = 0;
#endif
    
    bool m_clicked;
};

#endif
