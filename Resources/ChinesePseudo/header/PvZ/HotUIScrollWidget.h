//
//  HotUIScrollWidget.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 11/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __HOT_UI_SCROLL_WIDGET_H__
#define __HOT_UI_SCROLL_WIDGET_H__

#include "HotUIWidget.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

enum UIScrollMode
{
	UISCROLL_MODE_DISABLED,
	UISCROLL_MODE_HORIZONTAL,
	UISCROLL_MODE_VERTICAL,
	UISCROLL_MODE_BOTH,
};

class HotUIScrollWidget: public HotUIWidget, public Sexy::ScrollWidgetListener
{
public:

	RT_CLASS_DEFINE(HotUIScrollWidget, HotUIWidget, RtClass);
	
	HotUIScrollWidget();
	virtual ~HotUIScrollWidget();
	
	void AddWidget(Widget* i_widget) override;
	void RemoveWidget(Widget* i_widget) override;

	void ScrollerMoved(Sexy::ScrollWidget* i_scrollWidget) override;
	void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) override;
	void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) override;
	
	void SetScrollListener(Sexy::ScrollWidgetListener* i_listener);
	
	ScrollWidget* GetScrollWidget() const { return m_scrollWidget; }
	
protected:
	
	void			onLayoutFinalized() override;
	void			onUpdate() override;

private:
	ScrollWidget::ScrollMode getScrollMode();
	
	ScrollWidget*			m_scrollWidget;
	ScrollWidgetListener*	m_scrollListener;
};

class HotUIScrollWidgetProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIScrollWidgetProperties, HotUIWidgetProperties, RtClass);

	HotUIScrollWidgetProperties()
	{
		ScrollMode = UISCROLL_MODE_BOTH;
		UsingTimeDt = false;
	}

	RtClass* GetWidgetClass() const override
	{	
		return HotUIScrollWidget::StaticGetClass();
	}
	
	UIScrollMode	ScrollMode;
	bool			UsingTimeDt;
};

#endif /* defined(__HOT_UI_SCROLL_WIDGET_H__) */
