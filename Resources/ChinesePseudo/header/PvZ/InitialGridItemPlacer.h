//
//  InitialGridItemPlacer.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 6/26/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__InitialGridItemPlacer__
#define __PlantsVersusZombies2__InitialGridItemPlacer__

#include "LevelModule.h"

/**
 ** Level Module Clas
 **/

class InitialGridItemPlacer : public LevelModule
{
public:
	RT_CLASS_DEFINE(InitialGridItemPlacer, LevelModule, RtClass);
    
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void			registerForEvents() override;
	
private:
	void onLoadComplete();
};

/**
 ** Properties
 **/

struct GridItemPlacementProperties
{
	GridItemPlacementProperties()
	{
		GridX = -1;
		GridY = -1;
	}
	
	std::string		TypeName;
	int				GridX;
	int				GridY;
};

class InitialGridItemProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(InitialGridItemProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return InitialGridItemPlacer::StaticGetClass();
	}
	
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<GridItemPlacementProperties>	InitialGridItemPlacements;
};

#endif /* defined(__PlantsVersusZombies2__InitialGridItemPlacer__) */
