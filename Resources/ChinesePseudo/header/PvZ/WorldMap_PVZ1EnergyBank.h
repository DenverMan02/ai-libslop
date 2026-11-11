/*
 * WorldMap_PVZ1EnergyBank.h
 *
 *  Created on: 2021-8-16
 *      Author: admin
 */

#ifndef WORLDMAP_PVZ1ENERGYBANK_H_
#define WORLDMAP_PVZ1ENERGYBANK_H_

#include "RtObject.h"
#include "UIWidget.h"
#include "FuelBank.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class WorldMap_PVZ1EnergyBank : public FuelBank
{
public:
	RT_CLASS_DEFINE(WorldMap_PVZ1EnergyBank, FuelBank, RtClass);

    void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    void OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	void OnMouseDown(const int i_mouseX, const int i_mouseY) override;

private:
    void updateButtonStates(const int i_screenX, const int i_screenY, const bool i_isPressed) override;
};


#endif /* WORLDMAP_PVZ1ENERGYBANK_H_ */
