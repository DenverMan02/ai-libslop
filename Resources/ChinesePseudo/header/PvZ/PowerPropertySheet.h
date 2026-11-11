//
//  PowerPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 3/14/16.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __POWERPROPERTYSHEET_H__
#define __POWERPROPERTYSHEET_H__

#include <string>
#include <vector>

#include "BoardEntity.h"
#include "ComponentDamageRadius.h"
#include "ComponentWarmingRadius.h"
#include "GrowthStates.h"
#include "PlantEnums.h"
#include "PlatformAutodetect.h"
#include "Point.h"
#include "PlantBoostPropertySheet.h"
#include "ProjectilePropertySheet.h"
#include "PropertySheetBase.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TargetInfoProps.h"
#include "TimeMgr.h"

//  Generic Powers

class DuplicatableProps
{
public:
	DuplicatableProps()
	: NumberOfDuplicates(0)
	{}
	
	int NumberOfDuplicates;
	std::vector<std::map<std::string, int>> PlantingRanges;
};

class PowerPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PowerPropertySheet, PropertySheetBase, RtClass);
	
	std::string	TypeName;
};

class PowerPropsSunProducer : public PowerPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPropsSunProducer, PowerPropertySheet, RtClass);
	
	PowerPropsSunProducer()
	{
		Amount = 0;
		MinSpread = 0.f;
	}
	
	PowerPropsSunProducer(const PowerPropsSunProducer &obj)
	{
		Amount = obj.Amount;
		MinSpread = obj.MinSpread;
	}
	
	PowerPropsSunProducer(const int i_amount, const float i_minSpread)
	{
		Amount = i_amount;
		MinSpread = i_minSpread;
	}
	
	int Amount;
	float MinSpread;
};

class PowerPropsShield : public PowerPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPropsShield, PowerPropertySheet, RtClass);
	
	PowerPropsShield()
	{
		Health = 0;
	}
	
	PowerPropsShield(const PowerPropsShield &obj)
	{
		Health = obj.Health;
	}
	
	int Health;
};

class PowerPropsWarmingRadius : public PowerPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPropsWarmingRadius, PowerPropertySheet, RtClass);
	
	PowerPropsWarmingRadius()
	{
		WarmingRadius = ComponentWarmingRadiusProps();
	}
	
	PowerPropsWarmingRadius(const PowerPropsWarmingRadius &obj)
	{
		WarmingRadius = obj.WarmingRadius;
	}
	
	ComponentWarmingRadiusProps WarmingRadius;
};

class PowerPropsDamageRadius : public PowerPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPropsDamageRadius, PowerPropertySheet, RtClass);
	
	PowerPropsDamageRadius()
	{
		DamageRadius = ComponentDamageRadiusProps();
	}
	
	PowerPropsDamageRadius(const PowerPropsDamageRadius &obj)
	{
		DamageRadius = obj.DamageRadius;
	}
	
	ComponentDamageRadiusProps DamageRadius;
};

class PowerPropsDuplicator : public PowerPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPropsDuplicator, PowerPropertySheet, RtClass);
	
	PowerPropsDuplicator()
	{
		DuplicationProps = DuplicatableProps();
	}
	
	PowerPropsDuplicator(const PowerPropsDuplicator &obj)
	{
		DuplicationProps = obj.DuplicationProps;
	}
	
	DuplicatableProps DuplicationProps;
};

//  Plant-specific Powers

//class PowerPropsSunshroomGrowth : public PowerPropertySheet
//{
//public:
//	RT_CLASS_DEFINE(PowerPropsSunshroomGrowth, PowerPropertySheet, RtClass);
//	
//	PowerPropsSunshroomGrowth()
//	{
//	}
//	
//	PowerPropsSunshroomGrowth(const PowerPropsSunshroomGrowth &obj)
//	{
//		GrowthStages = obj.GrowthStages;
//	}
//	
//	std::vector<SunshroomGrowthStates> GrowthStages;
//};

class PowerPropsRedStingerLocationData : public PowerPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPropsRedStingerLocationData, PowerPropertySheet, RtClass);
	
	PowerPropsRedStingerLocationData()
	{
	}
	
	PowerPropsRedStingerLocationData(const PowerPropsRedStingerLocationData &obj)
	{
		LocationData = obj.LocationData;
	}
	
	std::vector<StingerLocationStateData> LocationData;
};

class PowerPropsStrawburstGrowth : public PowerPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPropsStrawburstGrowth, PowerPropertySheet, RtClass);
	
	PowerPropsStrawburstGrowth()
	{
	}
	
	PowerPropsStrawburstGrowth(const PowerPropsStrawburstGrowth &obj)
	{
		GrowthTimes = obj.GrowthTimes;
	}
	
	std::vector<pvztime_t> GrowthTimes;
};

#endif
