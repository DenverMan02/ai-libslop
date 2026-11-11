//
//  WorldMap_CoinBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Displays the current coin currency that the player has
//  on the world map

#ifndef PlantsVersusZombies2_WorldMap_CoinBank_h
#define PlantsVersusZombies2_WorldMap_CoinBank_h

#include "core.h"
#include "RtObject.h"
#include "CoinBank.h"
//PVZ2_CHINESE_START
#include "Effect_PopAnim.h"
//PVZ2_CHINESE_END

class WorldMap_CoinBank : public CoinBank
{
	
public:
	RT_CLASS_DEFINE(WorldMap_CoinBank, CoinBank, RtClass);	
	
	WorldMap_CoinBank();
	virtual ~WorldMap_CoinBank();
	
	// Public Interface (Inheritable)
	//PVZ2_CHINESE_START
	virtual void            onUpdate() override;
	//PVZ2_CHINESE_END
	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    //PVZ2_CHINESE_BEGIN
    //virtual bool			IsMouseOver(const int i_mouseX, const int i_mouseY);
    virtual Sexy::Rect      CalcPlusButtonRect() override;
    //PVZ2_CHINESE_END
	
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
	//PVZ2_CHINESE_START
	Effect_PopAnim* m_popAnimEffect;
	//PVZ2_CHINESE_END
};

#endif
