//
//  HotUIVerticalList.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 4/24/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIVerticalList__
#define __PlantsVersusZombies2__HotUIVerticalList__

#include "HotUIWidget.h"
#include "RtObject.h"
#include "Curve.h"

// A HotUI widget that ignores its own height and the y-offsets of its children,
// instead stacking them vertically in the order they were added, then adjusting its own height
// to match.
// Current use case: First widget interior to a vertical scroll area.  Automatically sizes for nice scrolling boundaries.
class HotUIVerticalList : public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIVerticalList, HotUIWidget, RtClass);

	HotUIVerticalList()
	: m_childToRemove(nullptr)
	, m_nextChild(nullptr)
	{}
	virtual ~HotUIVerticalList();

	void Update() override;
	void Draw(Graphics* i_g) override;

	void RepositionChildrenAndResize();
	void RepositionChildrenAndResizeCheckVisible();
	void ReplaceChild(Widget* i_childWidget, Widget* i_replacementWidget);
	void RemoveChildSmoothly(Widget* i_childWidget, const float i_duration);
    
    virtual void RemoveWidget(Widget* i_widget) override;
protected:
	void	onLayoutFinalized() override;
	int		getMinHeight();

private:

	void finishSmoothlyRemovingChild();

	FloatCurve m_smoothRemovalCurve;
	Widget* m_childToRemove;
	Widget* m_nextChild;
};

class HotUIHorizontalList : public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIHorizontalList, HotUIWidget, RtClass);
	virtual ~HotUIHorizontalList() {};

	void RepositionChildrenAndResize();

protected:
	void	onLayoutFinalized() override;
	int		getMinWidth();
};

class HotUIVerticalListProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIVerticalListProperties, HotUIWidgetProperties, RtClass);

	HotUIVerticalListProperties()
	: NumColumns(1)
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIVerticalList::StaticGetClass();
	}

	DynamicSizeData SpaceBetweenWidgets;
	int				NumColumns;
};

class HotUIHorizontalListProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIHorizontalListProperties, HotUIWidgetProperties, RtClass);

	HotUIHorizontalListProperties()
	: NumRows(1)
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIHorizontalList::StaticGetClass();
	}

	DynamicSizeData SpaceBetweenWidgets;
	int				NumRows;
};

class HotUIVerticalButtonList : public HotUIVerticalList
{
public:
	RT_CLASS_DEFINE(HotUIVerticalButtonList, HotUIVerticalList, RtClass);

	HotUIVerticalButtonList()
	{}
	virtual ~HotUIVerticalButtonList() {}

	void AddWidget(Widget* i_widget) override;
	void RemoveWidget(Widget* i_widget) override;

	std::vector<class HotUIButton*> GetButtons();

private:
	std::vector<HotUIWidget*>	m_childLayouts;
};

class HotUIVerticalButtonListProperties : public HotUIVerticalListProperties
{
public:
	RT_CLASS_DEFINE(HotUIVerticalButtonListProperties, HotUIVerticalListProperties, RtClass);

	HotUIVerticalButtonListProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIVerticalButtonList::StaticGetClass();
	}
};

namespace Message
{
	void ChildRemovedSmoothlyFromVerticalList();
}

#endif /* defined(__PlantsVersusZombies2__HotUIVerticalList__) */
