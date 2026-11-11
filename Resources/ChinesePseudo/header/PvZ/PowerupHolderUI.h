//
//  PowerupHolderUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/14/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupHolderUI__
#define __PlantsVersusZombies2__PowerupHolderUI__

#include "UIWidget.h"
#include "PowerupType.h"

class PowerupHolderUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(PowerupHolderUI, UIWidget, RtClass) {}

	virtual void Draw(Graphics* i_g) override;
    
    void AddPowerup(PowerupTypePtr i_powerupType, bool i_isLocked);
    
private:
    float m_offset_x;
};

#endif /* defined(__PlantsVersusZombies2__PowerupHolderUI__) */
