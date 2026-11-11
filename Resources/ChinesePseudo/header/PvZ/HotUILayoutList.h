//
//  HotUILayoutList.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUILayoutList__
#define __PlantsVersusZombies2__HotUILayoutList__

#include "HotUIWidget.h"
#include "RtDb.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

typedef RtWeakPtr<class HotUILabel> HotUILayoutListPtr;
typedef RtWeakPtr<class HotUILabelProperties> HotUILayoutListPropertiesPtr;

class HotUILayoutList: public HotUIWidget
{
public:

	RT_CLASS_DEFINE(HotUILayoutList, HotUIWidget, RtClass);
	
	HotUILayoutList()
	{}
	
	virtual ~HotUILayoutList()
	{}
	
	// Widget management
	void						AddWidget(Widget* i_widget) override;
	void						RemoveWidget(Widget* i_widget) override;

protected:

	// Widget layout
	void						onLayoutFinalized() override;
    void						performLayout();
	SexyVector2					calculateGapsBetweenChildren(std::vector<HotUIWidget*>& i_childLayouts, int i_maxWidth, int i_maxHeight) const;
	
	// Not Serialized
	std::vector<HotUIWidget*>	m_childLayouts;
};

class HotUILayoutListProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUILayoutListProperties, HotUIWidgetProperties, RtClass);

	HotUILayoutListProperties()
	{
		IgnoreMouseInput = true;
	};

	RtClass* GetWidgetClass() const override
	{	
		return HotUILayoutList::StaticGetClass();
	}
	
};

#endif /* defined(__PlantsVersusZombies2__HotUILayoutList__) */
