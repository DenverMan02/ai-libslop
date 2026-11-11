//
//  UIMetrics.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 12/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UIMetrics__
#define __PlantsVersusZombies2__UIMetrics__

#include <string>
#include <vector>

namespace UIMetrics
{
	class UIEventInfo
	{
	public:
		std::string Menu;
		std::string Action;
		std::string ContextData1;
		std::string ContextData2;
		
		UIEventInfo(std::string& i_Menu, std::string& i_Action)
		{
			Menu = i_Menu;
			Action = i_Action;
		}

		UIEventInfo(std::string& i_Menu, std::string& i_Action, std::string& i_data1, std::string& i_data2)
		{
			Menu = i_Menu;
			Action = i_Action;
			ContextData1 = i_data1;
			ContextData2 = i_data2;
		}
	};
	
	extern void BroadcastUIEvent(std::string i_Menu, std::string i_Action);
	extern void BroadcastUIEvent(std::string i_Menu, std::string i_Action, std::string i_data1, std::string i_data2);
}

namespace Message
{
	void UIEvent(UIMetrics::UIEventInfo& uiEvent);
}

#endif /* defined(__PlantsVersusZombies2__UIMetrics__) */
