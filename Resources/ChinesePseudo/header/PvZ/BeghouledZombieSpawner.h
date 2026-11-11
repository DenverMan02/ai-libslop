//
//  BeghouledZombieSpawner.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 6/25/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BeghouledZombieSpawner__
#define __PlantsVersusZombies2__BeghouledZombieSpawner__

#include "SimpleZombieSpawner.h"

struct MatchStageMap
{
	int StageNumber;
	int MatchCount;
};

class BeghouledZombieSpawnerModule : public SimpleZombieSpawnerModule
{
public:
	RT_CLASS_DEFINE(BeghouledZombieSpawnerModule, SimpleZombieSpawnerModule, RtClass);

protected:
	void registerForEvents() override;
	
	void onUpdate() override;
	void startSpawner() override;
	void stopSpawner() override;
};

class BeghouledZombieSpawnerProperties : public SimpleZombieSpawnerProperties
{
public:
	RT_CLASS_DEFINE(BeghouledZombieSpawnerProperties, SimpleZombieSpawnerProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return BeghouledZombieSpawnerModule::StaticGetClass();
	}
	
	std::vector<MatchStageMap> MatchCountsToStageAdvance;
};

#endif /* defined(__PlantsVersusZombies2__BeghouledZombieSpawner__) */
