//
//  PVZLiveConfig.h
//  PlantsVersusZombies2
//
//  Created by David Siems 4/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PVZLIVECONFIG_H__
#define __PVZLIVECONFIG_H__

#include "PropertySheetBase.h"

struct Toggle
{
public:
	std::string Key;
	bool Enabled;
	std::string DisplayName;
	std::string Category;
};

class PVZLiveConfig : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PVZLiveConfig, PropertySheetBase, RtClass);
	
	PVZLiveConfig()
	{
		ContentRefreshMinutes = 60;
        EASquaredAwaitAdRewardTimeout = 0.5f;
	}

	int ContentRefreshMinutes;
	std::vector<Toggle> Toggles;
    
    float EASquaredAwaitAdRewardTimeout;
};

namespace LiveConfig 
{
	const PVZLiveConfig& Get();
}

#endif
