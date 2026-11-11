//
//  WorldMap_WelfareButton.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-8-29.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_WelfareButton_h
#define PlantsVersusZombies2_WorldMap_WelfareButton_h

#include "UIEasyButtonWidget.h"

class WorldMap_WelfareButton : public UIEasyButtonWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_WelfareButton, UIEasyButtonWidget, RtClass);
	
	WorldMap_WelfareButton();
	virtual ~WorldMap_WelfareButton();
    
    void Draw(Sexy::Graphics* i_g) override;
    
protected:
    
    // Protected Interface (Inheritable)
    
    virtual void			initLoadingResourcesGroupList() override;
    
private:
    void OnKillChooseDialog(UIWidget* pButton);
    void KillChooseDialog();
};

#endif
