//
//  WorldMap_ZMatchTicketBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Displays the current coin currency that the player has
//  on the world map

#ifndef PlantsVersusZombies2_WorldMap_ZMatchTicketBank_h
#define PlantsVersusZombies2_WorldMap_ZMatchTicketBank_h

#include "core.h"
#include "RtObject.h"
#include "ZMatchTicketBank.h"

class WorldMap_ZMatchTicketBank : public ZMatchTicketBank
{
	
public:
	RT_CLASS_DEFINE(WorldMap_ZMatchTicketBank, ZMatchTicketBank, RtClass);	
	
	WorldMap_ZMatchTicketBank();
	virtual ~WorldMap_ZMatchTicketBank();
	
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	//virtual bool			IsMouseOver(const int i_mouseX, const int i_mouseY);
    virtual Sexy::Rect		CalcPlusButtonRect() override;
	
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
	
	virtual void			updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
	
	bool	m_clicked;
	
};

#endif
