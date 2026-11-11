/*
 * PVZ1ModePropertySheet.h
 *
 *  Created on: 2021-7-16
 *      Author: zhousen
 */

#ifndef PVZ1MODEPROPERTYSHEET_H_
#define PVZ1MODEPROPERTYSHEET_H_

#include "AdaptorHowToPlayScreen.h"
#include "PropertySheetBase.h"
#include "Utils.h"
#include "PVZ1ModePropertySheet.h"


class PVZ1ModePropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PVZ1ModePropertySheet, PropertySheetBase, RtClass);

	PVZ1ModePropertySheet()
	{
    }

	HowToPlayScreenData	HowToPlayData1;
	HowToPlayScreenData	HowToPlayData2;
	HowToPlayScreenData	HowToPlayData3;
	HowToPlayScreenData NewPvPHowToPlayData;
	HowToPlayScreenData NewPvPArmyHowToPlayData;
	HowToPlayScreenData UnchartedHowToPlayData;

	std::vector<std::string> PlantBannedList;
	std::vector<std::string> PvZ1PlantList;

public:
	static PVZ1ModePropertySheet* GetProperties();
};



#endif /* PVZ1MODEPROPERTYSHEET_H_ */
