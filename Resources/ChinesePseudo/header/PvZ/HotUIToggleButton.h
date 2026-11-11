//
//  HotUICheckBoxButton.h
//  PlantsVersusZombies2
//
//  Created by Albert Lai on 11/12/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUICheckBoxButton__
#define __PlantsVersusZombies2__HotUICheckBoxButton__

#include "HotUIButton.h"
#include "RtObject.h"

class HotUIToggleButton: public HotUIButton
{
public:

	RT_CLASS_DEFINE(HotUIToggleButton, HotUIButton, RtClass);
	bool IsButtonSelected();
	bool ToggleButtonAndReturnState();
	void SetSelectedState(bool i_selected);

protected:
	// Widget initialization
	void onInitializeWidget() override;
};

class HotUIToggleButtonProperties : public HotUIButtonProperties
{
public:
	RT_CLASS_DEFINE(HotUIToggleButtonProperties, HotUIButtonProperties, RtClass);

	HotUIToggleButtonProperties()
	{
		ToggleOnPress = false;
	}

	RtClass* GetWidgetClass() const override
	{
		return HotUIToggleButton::StaticGetClass();
	}

	bool	ToggleOnPress;
};

#endif
