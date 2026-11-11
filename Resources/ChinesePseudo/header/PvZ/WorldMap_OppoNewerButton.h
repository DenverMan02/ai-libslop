//
//  WorldMap_NewerButton.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-8-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_OppoNewerButton__
#define __PlantsVersusZombies2__WorldMap_OppoNewerButton__

#include "core.h"
#include "RtObject.h"
#include "UIEasyButtonWidget.h"
#include "GameEventMgr.h"

class WorldMap_OppoNewerButton : public UIEasyButtonWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_OppoNewerButton, UIWidget, RtClass);
    
	WorldMap_OppoNewerButton();
	virtual ~WorldMap_OppoNewerButton();
	
	void CheckActivated();

private:
	void onButtonClicked();
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_NewerButton__) */
