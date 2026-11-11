//
//  SimpleZombieSpawner.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/23/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SimpleZombieSpawner_h
#define PlantsVersusZombies2_SimpleZombieSpawner_h

#include "LevelModule.h"
#include "TimeMgr.h"
#include "Zombie.h"
 
class SimpleZombieSpawnerModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(SimpleZombieSpawnerModule, LevelModule, RtClass);
	
	void PauseSpawning();
	void ResumeSpawning(float i_delay);
	void SetActiveStage(int i_newStage);
	const int GetActiveStage() { return m_activeStage; }

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;

	virtual void onUpdate();
	virtual void startSpawner();
	virtual void stopSpawner();
	
	Zombie* spawnZombie();

	bool getIsDoneSpawning();
	
	pvztime_t m_nextSpawnTime;
	int m_nextPlantFoodZombie;
	int m_remainingZombies;
	
	int m_activeStage;
	
	std::vector<std::vector<ZombieTypePtr> > m_chosenZombieTypes;
};


struct ZombieSpawnerEntry
{
public:
	ZombieSpawnerEntry()
	{
		Weight = 10;
	}
	std::string 	ZombieType;
	int				Weight;
};

struct ZSEntryList
{
public:
	ZSEntryList()
	{
		SpawnCount = -1;
		SpawnDelay = 10.0f;
		PlantFoodInterval = -1;
	}
	
	std::vector<ZombieSpawnerEntry> Types;
	int SpawnCount;
	float SpawnDelay;
	int PlantFoodInterval;
};
 
class SimpleZombieSpawnerProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(SimpleZombieSpawnerProperties, LevelModuleProperties, RtClass);
     
    virtual RtClass* GetModuleClass() const override
    {
        return SimpleZombieSpawnerModule::StaticGetClass();
    }
 	
	std::vector<ZSEntryList> Stages;
};

#endif
