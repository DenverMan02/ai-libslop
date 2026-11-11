//
//  WorldMap_FuelBank.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery 7/19/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_FuelBank__
#define __PlantsVersusZombies2__WorldMap_FuelBank__

#include "RtObject.h"
#include "UIWidget.h"
#include "FuelBank.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class WorldMap_FuelBank : public FuelBank
{
public:
	RT_CLASS_DEFINE(WorldMap_FuelBank, FuelBank, RtClass);
	
    void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    void OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	void OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	
private:
    void updateButtonStates(const int i_screenX, const int i_screenY, const bool i_isPressed) override;
};

#endif
