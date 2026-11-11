//
//  HotUIMessageBar.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 12/2/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIMessageBar__
#define __PlantsVersusZombies2__HotUIMessageBar__

#include "HotUIWidget.h"

#include "MessageWidgetEnums.h"

class HotUIMessageBar: public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIMessageBar, HotUIWidget, RtClass);
	
	HotUIMessageBar();
	
	virtual ~HotUIMessageBar();
	
	// Widget management
	void			ShowMessage(const SexyString& i_messageText, MessageStyle i_messageStyle);
	void			HideMessage();
	
protected:
	
	void			onDraw(Sexy::Graphics* i_graphics) override;
	void			onUpdate() override;
	
	// Serialized
	
	// Not serialized
	class MessageWidget*	m_messageBarWidget;
};

class HotUIMessageBarProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIMessageBarProperties, HotUIWidgetProperties, RtClass);
	
	HotUIMessageBarProperties()
	{}
	
	RtClass* GetWidgetClass() const override
	{
		return HotUIMessageBar::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__HotUIMessageBar__) */
