//
//  WorldMap_ActivityLevelsButton.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-8-29.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_ActivityLevelsButton_h
#define PlantsVersusZombies2_WorldMap_ActivityLevelsButton_h

#include "UIEasyButtonWidget.h"

class WorldMap_ActivityLevelsButton : public UIEasyButtonWidget
{
    
public:
	RT_CLASS_DEFINE(WorldMap_ActivityLevelsButton, UIEasyButtonWidget, RtClass);
    
	WorldMap_ActivityLevelsButton();
	virtual ~WorldMap_ActivityLevelsButton();

    void Draw(Graphics* i_g) override;
    
	void WaitForTutorialClick()
	{
		m_clicked = false;
	}
	bool WasClickedForTutorial()
	{
		return m_clicked;
	}
    
private:
    
    void updateNoticeState();
    
    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);
    
    bool	m_clicked = false;
};

#endif
