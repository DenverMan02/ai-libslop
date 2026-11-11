//
//  Toggles.h
//  PlantsVersusZombies2
//
//  Created by Matt Westhoff on 9/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Toggles__
#define __PlantsVersusZombies2__Toggles__

#include "Precompile.h"

#include <map>
#include <string>
#include <vector>

struct Toggle;

namespace Message
{
	void ToggleOverrideSet(const std::string& i_toggleName, bool i_newToggleValue);
};

class LiveConfigToggleGetter
{
public:
	virtual ~LiveConfigToggleGetter() {}
	static LiveConfigToggleGetter& GetInstance();
	virtual std::vector<Toggle> GetLiveConfigToggles();
};

class Toggles
{
public:
	Toggles(LiveConfigToggleGetter& i_liveConfigToggleGetter);
	static Toggles& GetInstance();
	
	void OverrideToggle(const std::string& key, bool enabled);
	void SwrveToggle(const std::string& key, bool enabled);
	bool IsEnabled(const std::string& key);
	
private:	
	LiveConfigToggleGetter& m_toggleGetter;
	std::map<std::string, bool> m_overrides;
	std::map<std::string, bool> m_swrvedToggles;
};

#endif /* defined(__PlantsVersusZombies2__Toggles__) */
