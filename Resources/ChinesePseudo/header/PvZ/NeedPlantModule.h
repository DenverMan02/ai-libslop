//
//  NeedPlantModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_NeedPlantModule_h
#define PlantsVersusZombies2_NeedPlantModule_h

#include "LevelModule.h"
#include "Core.h"
#include "PvZ2IDs.h"
#include "GameEventMgr.h"
#include "Plant.h"
#include "ProtectThePlantChallenge.h"

class NeedPlantModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(NeedPlantModule, LevelModule, RtClass);

};

class NeedPlantProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(NeedPlantProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return NeedPlantModule::StaticGetClass();
	}
	
	NeedPlantProperties()
	{
		PlantTypes.clear();
	}
    
    std::string CheckNeedPlants(const std::vector<PlantTypePtr>& i_seedList);

	std::vector<std::string> PlantTypes;
};

#endif
