//
//  JoustPropertySheet
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/15/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__JoustPropertySheet__
#define __PlantsVersusZombies2__JoustPropertySheet__

#include "PropertySheetBase.h"

#include "AdaptorJoustHowToPlayScreen.h"

struct PredefinedLoadoutEntry
{
    std::string     PlantType;
    int             PlantLevel = 0;
    bool            IsImitater = false;
};

class JoustPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(JoustPropertySheet, PropertySheetBase, RtClass);
	
	JoustPropertySheet()
	{
		ReplayRecordEventBasePeriodSecondsMin = 2.f;
		ReplayRecordEventBasePeriodSecondsMax = 4.f;
		FreePlayRechargeTimeSeconds = 3600;
		PlantsRequiredToUnlock = 999;
		NetworkTimeoutSeconds = 5;
		MinGeneratedScore = 500;
		MaxGeneratedScore = 2000;
		MaxAvatarName = 0;
		MaxAvatarIcon = 0;
    }
	
	float	ReplayRecordEventBasePeriodSecondsMin;
	float	ReplayRecordEventBasePeriodSecondsMax;
	float	FreePlayRechargeTimeSeconds;
	float	NetworkTimeoutSeconds;
	float	MinGeneratedScore;
	float	MaxGeneratedScore;
	int		MaxAvatarName;
	int		MaxAvatarIcon;
	std::string AvatarNamePattern;
	std::string AvatarIconPattern;
	std::vector<std::string>	LeagueIcons;
	std::vector<std::string>	LeagueNames;
	std::vector<std::string>	ShortLeagueNames;
    std::vector<std::vector<PredefinedLoadoutEntry>> PredefinedLoadouts;
	JoustHowToPlayScreenData	HowToPlayData;
	int		PlantsRequiredToUnlock;
	
public:
	static JoustPropertySheet* GetProperties();
};

#endif /* defined(__PlantsVersusZombies2__JoustPropertySheet__) */
