//
//  HotUIButtonList.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/21/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIButtonList__
#define __PlantsVersusZombies2__HotUIButtonList__

#include "HotUILayoutList.h"

namespace Sexy {
class Widget;
}  // namespace Sexy

typedef RtWeakPtr<class HotUIButtonList> HotUIButtonListPtr;
typedef RtWeakPtr<class HotUIButtonListProperties> HotUIButtonListPropertiesPtr;

class HotUIButton;

class HotUIButtonList: public HotUILayoutList
{
public:

	RT_CLASS_DEFINE(HotUIButtonList, HotUILayoutList, RtClass);
	
	HotUIButtonList()
	{}
	
	virtual ~HotUIButtonList()
	{}

	// Buttons
	std::vector<HotUIButton*>	GetButtons();
	
protected:
	
	// Widget layout
	void						onLayoutFinalized() override;
	
private:

	// Widget layout
    void						normalizeFonts();
};

class HotUIButtonListProperties : public HotUILayoutListProperties
{
public:
	RT_CLASS_DEFINE(HotUIButtonListProperties, HotUILayoutListProperties, RtClass);

	HotUIButtonListProperties()
	{}

	RtClass* GetWidgetClass() const override
	{	
		return HotUIButtonList::StaticGetClass();
	}
	
};

#endif /* defined(__PlantsVersusZombies2__HotUIButtonList__) */
