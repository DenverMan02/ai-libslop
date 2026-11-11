//
//  OakArrowHolderUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-11-3.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__OakArrowHolderUI__
#define __PlantsVersusZombies2__OakArrowHolderUI__

#include "UIWidget.h"

class OakArrowHolderUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(OakArrowHolderUI, UIWidget, RtClass) {}
    
	virtual void Draw(Graphics* i_g) override;
};

#endif /* defined(__PlantsVersusZombies2__OakArrowHolderUI__) */
