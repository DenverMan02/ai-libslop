//
//  WorldMap_TreasureButton.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-6-6.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_TreasureButton_h
#define PlantsVersusZombies2_WorldMap_TreasureButton_h

#include "UIEasyButtonWidget.h"
#include "Effect_PopAnim.h"

class WorldMap_TreasureButton : public UIEasyButtonWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_TreasureButton, UIEasyButtonWidget, RtClass);
	
	WorldMap_TreasureButton();
	virtual ~WorldMap_TreasureButton();
	
    void                    DoSubDialog();
    
    void WaitForTutorialClick()
	{
		m_clicked = false;
	}
	bool WasClickedForTutorial()
	{
		return m_clicked;
	}
    
private:
    bool m_clicked;
};

#endif
