//
//  InitialZombiePlacer.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/9/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__InitialZombiePlacer__
#define __PlantsVersusZombies2__InitialZombiePlacer__

#include "Zombie.h"
#include "LevelModule.h"

/**
 ** Level Module Class
 **/

class InitialZombiePlacer : public LevelModule
{
public:
	RT_CLASS_DEFINE(InitialZombiePlacer, LevelModule, RtClass);
	
protected:
	virtual void registerForEvents() override;
	
private:
	void onLoadComplete();
};

/**
 ** Properties
 **/

struct ZombiePlacementProperties
{
	ZombiePlacementProperties()
	{
        Level = 1;
		GridX = -1;
		GridY = -1;
		Condition = ZCONDITION_Invalid;
	}
	
	std::string			TypeName;
    int                 Level;
	int					GridX;
	int					GridY;
	ZombieConditions	Condition;
};

class InitialZombieProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(InitialZombieProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return InitialZombiePlacer::StaticGetClass();
	}
	
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<ZombiePlacementProperties>	InitialZombiePlacements;
};

#endif /* defined(__PlantsVersusZombies2__InitialZombiePlacer__) */
