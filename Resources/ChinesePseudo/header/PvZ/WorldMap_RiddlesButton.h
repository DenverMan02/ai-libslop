//
//  WorldMap_RiddlesButton.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 15-5-22.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_RiddlesButton_h
#define PlantsVersusZombies2_WorldMap_RiddlesButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "Effect_PopAnim.h"

class WorldMap_RiddlesButton : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_RiddlesButton, UIWidget, RtClass);
	
	WorldMap_RiddlesButton();
	virtual ~WorldMap_RiddlesButton();
	
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
    virtual void            onUpdate() override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    void                    DoSubDialog();
    
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
    
    void                KillChooseDialog();
    void                OnKillChooseDialog(UIWidget* pButton);
    
    void                DrawTips(Graphics* i_g);
    
    //anim
    Effect_PopAnim* m_popAnimEffect;
    bool m_bAnimActivated;
    
    bool m_clicked;
};

#endif
