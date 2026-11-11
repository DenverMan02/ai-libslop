//
//  HotUIPurchaseButton.h
//  PlantsVersusZombies2
//
//  Created by Alex Gelles on 7/19/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIPurchaseButton__
#define __PlantsVersusZombies2__HotUIPurchaseButton__

#include <string>

#include "HotUIButton.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyString.h"
#include "Core.h"


class HotUIPurchaseButton : public HotUIButton
{
public:

	RT_CLASS_DEFINE(HotUIPurchaseButton, HotUIButton, RtClass);
	
	HotUIPurchaseButton();
	virtual ~HotUIPurchaseButton();
	
	void SetCostLabel(const SexyString& i_label);
	void ClearCostLabel();
};

class HotUIPurchaseButtonProperties : public HotUIButtonProperties
{
public:
	RT_CLASS_DEFINE(HotUIPurchaseButtonProperties, HotUIButtonProperties, RtClass);

	HotUIPurchaseButtonProperties()
	{
		
	};

	RtClass* GetWidgetClass() const override
	{	
		return HotUIPurchaseButton::StaticGetClass();
	}
	
	std::string	CostLabel;
	int	CostLabelX = 25;
	int	CostLabelY = 0;
	int CostLabelMaxWidth = 50;
};

#endif
