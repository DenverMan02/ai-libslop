//
//  UtilityActions.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 5/5/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UtilityActions__
#define __PlantsVersusZombies2__UtilityActions__

#include "RunnableAction.h"
#include "TimeMgr.h"

// Enables or disables mouse/touch input on the specified WidgetContainer
// Can be used on gLawnApp->mWidgetManager to disable input to all widgets.
// See helper classes for readability below: DisableWidgetInputAction and EnableWidgetInputAction
class SetWidgetInputEnabledAction : public RunnableAction
{
public:
	SetWidgetInputEnabledAction(Sexy::WidgetContainer* i_widget, bool i_enabled);
	void onBegin() override;
	
private:
	Sexy::WidgetContainer* m_widget;
	bool m_enabled;
};

class DisableWidgetInputAction : public SetWidgetInputEnabledAction
{
public:
	DisableWidgetInputAction(Sexy::WidgetContainer* i_widget) : SetWidgetInputEnabledAction(i_widget, false) {}
};

class EnableWidgetInputAction : public SetWidgetInputEnabledAction
{
public:
	EnableWidgetInputAction(Sexy::WidgetContainer* i_widget) : SetWidgetInputEnabledAction(i_widget, true) {}
};

// Action that blocks for a certain number of seconds
class WaitAction : public RunnableAction
{
public:
	WaitAction(pvztime_t i_waitDurationSeconds);
	void onBegin() override;
	void onUpdate() override;
	
private:
	pvztime_t m_startTime;
	pvztime_t m_duration;
};

#endif /* defined(__PlantsVersusZombies2__UtilityActions__) */
