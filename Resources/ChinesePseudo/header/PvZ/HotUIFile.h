//
//  HotUIFile.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIFile__
#define __PlantsVersusZombies2__HotUIFile__

#include <string>
#include <utility>
#include <vector>

#include "HotUIWidget.h"

namespace Sexy {
class Widget;
class WidgetContainer;
}  // namespace Sexy

struct WidgetHotSwapData
{
public:
	WidgetHotSwapData()
	{
		FullName = "";
		Widget = HotUIWidgetPtr();
		Properties = HotUIWidgetPropertiesPtr();
	}
	
	WidgetHotSwapData(const std::string& i_fullWidgetName, HotUIWidgetPtr i_widget, HotUIWidgetPropertiesPtr i_properties)
	{
		FullName = i_fullWidgetName;
		Widget = i_widget;
		Properties = i_properties;
	}
	
	std::string					FullName;
	HotUIWidgetPtr				Widget;
	HotUIWidgetPropertiesPtr	Properties;
};

struct ComponentHotSwapData
{
public:
    ComponentHotSwapData()
    {
        
    }
    
    ComponentHotSwapData(HotUIComponentPtr i_component, HotUIComponentPropertiesPtr i_properties)
    {
        Component = i_component;
        Properties = i_properties;
    }
    
    HotUIComponentPtr           Component;
    HotUIComponentPropertiesPtr Properties;
};

class HotUIFile
{
public:
	
	HotUIFile(const std::string& i_fileName)
	{
		m_fileName = i_fileName;
	};
	
	virtual ~HotUIFile()
	{

	};
	
	const std::string&					GetFileName();
    
	const std::vector<WidgetHotSwapData>&		GetWidgetHotSwapData();
    const std::vector<ComponentHotSwapData>&    GetComponentHotSwapData();
    
	void								AddWidget(const std::string& i_fullWidgetName, HotUIWidgetPtr i_widget, HotUIWidgetPropertiesPtr i_properties);
    void                                AddComponent(HotUIComponentPtr i_component, HotUIComponentPropertiesPtr i_properties);
    
	bool								HasWidgetByName(const std::string& i_widgetName);
	HotUIWidget*						GetWidgetByName(const std::string& i_widgetName);
	template<class T> T*				GetWidgetByName(const std::string& i_widgetName)
	{
		HotUIWidget* widget = GetWidgetByName(i_widgetName);
		return widget->CastChecked<T>();
	};
	HotUIWidget*						GetWidgetByType(const RtClass* i_widgetType);
    
	const WidgetHotSwapData*			FindHotSwapDataByWidget(HotUIWidgetPtr i_widgetPtr);

	void								AddWidgetToApp(Widget* i_widget, WidgetContainer* i_parent);
	void								RemoveWidgetsFromApp();
    
	HotUIWidget*						GetEntryPointWidget();

private:

	std::string											m_fileName;
	std::vector<WidgetHotSwapData>					    m_widgetHotSwapData;
    std::vector<ComponentHotSwapData>                   m_componentHotSwapData;
	std::vector<std::pair<Widget*, WidgetContainer*>>	m_widgetsAddedToApp;
};

#endif /* defined(__PlantsVersusZombies2__HotUIFile__) */
