//
//  GrowthStates.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 5/23/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef GrowthStates_h
#define GrowthStates_h

#include "RtObject.h"
#include "Core.h"
#include "RtDb.h"

// Using this file to avoid circular references with includes in plant leveling.
// Started due to Sunshroom growth states.

//struct SunshroomGrowthStates
//{
//	float TimeToGrowInSeconds;
//	int Amount;
//	float MinSpread;
//};
//
//class GrowthStates : public RtObject
//{
//public:
//	RT_CLASS_DEFINE(GrowthStates, RtObject, RtClass);
//};

struct StingerLocationStateData
{
	std::string Location;
	int RightmostColumn;
	int Hitpoints;
};

class StingerLocationData : public RtObject
{
public:
	RT_CLASS_DEFINE(StingerLocationData, RtObject, RtClass);
};

#endif /* GrowthStates_h */