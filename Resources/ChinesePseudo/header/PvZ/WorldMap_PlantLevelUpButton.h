//
//  WorldMap_PlantLevelUpButton.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-5-19.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_PlantLevelUpButton_h
#define PlantsVersusZombies2_WorldMap_PlantLevelUpButton_h

#include "UIEasyButtonWidget.h"

class WorldMap_PlantLevelUpButton : public UIEasyButtonWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_PlantLevelUpButton, UIEasyButtonWidget, RtClass);
	
	WorldMap_PlantLevelUpButton();
    virtual ~WorldMap_PlantLevelUpButton();

    void OnTouch();

	void WaitForTutorialClick()
	{
		m_clicked = false;
	}
	bool WasClickedForTutorial()
	{
		return m_clicked;
	}

protected:
    virtual void onLoadComplete() override;
    
private:
    void updateNotice();
    
    void OnKillChooseDialog(UIWidget* pButton);
    void KillChooseDialog();
    
    bool ShowTheNoticeAboutPlantLevelUp();
    bool ShowTheNoticeAboutAvatar();

	bool	m_clicked;
};

#endif
