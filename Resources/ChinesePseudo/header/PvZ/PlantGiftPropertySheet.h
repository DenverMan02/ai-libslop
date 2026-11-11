/*
 * PlantGiftPropertySheet.h
 *
 *  Created on: 2015-4-9
 *      Author: jianglc
 */

#ifndef PLANTGIFTPROPERTYSHEET_H_
#define PLANTGIFTPROPERTYSHEET_H_

#include "RtDb.h"
#include "PropertySheetBase.h"

struct PlantGiftBaseData
{
	PlantGiftBaseData()
	{
		PlantName = "";
		Weight = 0;
	}

	std::string PlantName;
	int Weight;
};

typedef RtWeakPtr<class PlantGiftPropertySheet> PlantGiftPropertySheetPtr;

class PlantGiftPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlantGiftPropertySheet, PropertySheetBase, RtClass);

	PlantGiftPropertySheet()
	{

	}

	std::vector<PlantGiftBaseData> GiftDatas;
};


#endif /* PLANTGIFTPROPERTYSHEET_H_ */
