//
//  EASquaredPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquaredPropertySheet__
#define __PlantsVersusZombies2__EASquaredPropertySheet__

#include "PropertySheetBase.h"

class EASquaredPropertySheet : public PropertySheetBase
{
	public:
	RT_CLASS_DEFINE(EASquaredPropertySheet, PropertySheetBase, RtClass);
	
	EASquaredPropertySheet()
	{
		MonetizerType = "";
		MinimumDaysSinceInstall = 0;
		MaximumCoinBalance = std::numeric_limits<int>::max();
        EnableSuperSonic = true;
		ShowButtonInFullStore = true;
		AutoplayOnQuickCoinStoreClosed = false;
    }
	
	std::string MonetizerType;
	int MinimumDaysSinceInstall;
	int MaximumCoinBalance;
    bool EnableSuperSonic;
	bool ShowButtonInFullStore;
	bool AutoplayOnQuickCoinStoreClosed;
    
    std::string SuperSonicAppKey;
    std::string AdColonyAppID;
    std::string AdColonyZoneID;
    std::string VungleAppID;
    std::string UnityAdsGameID;
    std::string UnityAdsZoneID;
};

#endif /* defined(__PlantsVersusZombies2__EASquaredPropertySheet__) */
