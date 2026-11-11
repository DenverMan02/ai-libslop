//
//  InitialPlantModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_InitialPlantModule_h
#define PlantsVersusZombies2_InitialPlantModule_h

#include "LevelModule.h"
#include "Core.h"
#include "PvZ2IDs.h"
#include "GameEventMgr.h"
#include "Plant.h"

class InitialPlantModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(InitialPlantModule, LevelModule, RtClass);
    
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
	void onLoadComplete();
};

struct InitialPlantEntry
{
	InitialPlantEntry()
	{
		GridX = 0;
        GridY = 0;
		Level = -1;
		Avatar = false;
	}
    
    std::vector<std::string> PlantTypes;
    
	int GridX;
	int GridY;
	int Level;
	bool Avatar;
};

class InitialPlantEntryProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(InitialPlantEntryProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return InitialPlantModule::StaticGetClass();
	}
	
	InitialPlantEntryProperties()
	{
		Plants.clear();
	}
	
	std::vector<InitialPlantEntry> Plants;
};

#endif
