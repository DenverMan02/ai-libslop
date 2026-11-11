//
//  InitialPlantPlacer.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/9/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__InitialPlantPlacer__
#define __PlantsVersusZombies2__InitialPlantPlacer__

#include "Plant.h"
#include "LevelModule.h"

/**
 ** Level Module Class
 **/

class InitialPlantPlacer : public LevelModule
{
public:
	RT_CLASS_DEFINE(InitialPlantPlacer, LevelModule, RtClass);
	
protected:
	virtual void registerForEvents() override;
	
private:
	void onLoadComplete();
	void onGameplayStarted();

	std::vector<PlantPtr> m_plantedPlants;
};

/**
 ** Properties
 **/

struct PlantPlacementProperties
{
	PlantPlacementProperties()
	{
		GridX = -1;
		GridY = -1;
		Condition = PCONDITION_Invalid;
		Level = -1;
	}
	
	std::string		TypeName;
	int				GridX;
	int				GridY;
	PlantConditions	Condition;
	int				Level;
};

class InitialPlantProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(InitialPlantProperties, LevelModuleProperties, RtClass);

	InitialPlantProperties()
	{
		IsInitialIntensiveCarrotPlacements = false;
	}
	
	virtual RtClass* GetModuleClass() const override
	{
		return InitialPlantPlacer::StaticGetClass();
	}
	
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<PlantPlacementProperties>	InitialPlantPlacements;
	bool									IsInitialIntensiveCarrotPlacements;
};

#endif /* defined(__PlantsVersusZombies2__InitialPlantPlacer__) */
