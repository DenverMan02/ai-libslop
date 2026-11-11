//
//  PlantCooldownModifierModule.h
//  PlantsVersusZombies2
//
//  Created by Erik Rydeman on 9/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantCooldownModifierModule_h
#define PlantsVersusZombies2_PlantCooldownModifierModule_h

#include <string>

#include "LevelModule.h"
#include "PVZTypes.h"
#include "RtObject.h"

class PlantCooldownModifierModule : public LevelModule
{ 
public:
	RT_CLASS_DEFINE(PlantCooldownModifierModule, LevelModule, RtClass) {}
	
	float GetCooldownMultiplier(PlantTypePtr plantType);
};

class PlantCooldownModifierProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PlantCooldownModifierProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return PlantCooldownModifierModule::StaticGetClass();
	}
	
	PlantCooldownModifierProperties()
	{
		HomeworldToExcludeFromOverride = "";
		CooldownMultiplier = 1.0f;
	}
	
	std::string HomeworldToExcludeFromOverride;
	float CooldownMultiplier;
};

#endif
