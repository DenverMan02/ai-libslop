//
//  WorldMap_TopBar.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_TopBar_h
#define PlantsVersusZombies2_WorldMap_TopBar_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_TopBar : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_TopBar, UIWidget, RtClass);	
	
	WorldMap_TopBar();
	virtual ~WorldMap_TopBar();
	
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;

};


#endif
