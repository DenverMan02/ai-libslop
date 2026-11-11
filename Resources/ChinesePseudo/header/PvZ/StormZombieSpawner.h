//
//  StormZombieSpawner.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 12/5/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StormZombieSpawner__
#define __PlantsVersusZombies2__StormZombieSpawner__

#include <set>
#include <string>
#include <vector>

#include "RtObject.h"
#include "StateMachine.h"
#include "WaveActionSpawnZombies.h"

class ZombieType;

/// Storm types for storm entrances
enum StormType
{
	PVZ_BEGIN_ENUM(STORMTYPE_),
	STORMTYPE_SANDSTORM,
	STORMTYPE_SNOWSTORM,
	STORMTYPE_EXCOLDSTORM,
	PVZ_END_ENUM(STORMTYPE_),
};

// Spawn zombies X many at a time with Y seconds in between.
// If the wave ends, or the full spawn timer expires it spawns
// all remaining zombies.
struct StormZombieInstruction
{
	StormZombieInstruction()
	: HasPlantfood(false)
	{
		// Do nothing.
	}
	
	ZombieTypePtr Type;
	bool HasPlantfood;
};

class StormZombieSpawner : public ZombieSpawnerAction
{
	RT_CLASS_DEFINE(StormZombieSpawner, ZombieSpawnerAction, RtClass);
public:
	StormZombieSpawner()
	: m_nextZombieIndex(0)
	, m_nextGroupTime(PVZ_EOT())
	, m_fullSpawnTime(PVZ_EOT())
	{
		// Do nothing.
	}
	
	virtual void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand &i_random) override;
	virtual void WaveUpdate(int i_waveNumber, MTRand &i_random) override;
	virtual void WaveEnd(int i_waveNumber, MTRand &i_random) override;
	
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	virtual void GetZombies(std::vector<const ZombieType*> &o_zombies) override;
	virtual void SetLoot(const std::vector<Loot> &i_loot) override;
	
private:
	virtual void initializeAction(MTRand &i_random, int i_waveNumber) override;
	void createZombies(int i_waveNumber, MTRand &i_random, int i_startIndex, int i_stopIndex);
	void spawnGroup(int i_count, int i_waveNumber, MTRand &i_random);
	void spawnAllTheThings(int i_waveNumber, MTRand &i_random);
	
	std::vector<Loot> m_zombieLoot;
	std::vector<Sexy::Point> m_stormTargets;
	int m_nextZombieIndex;
	pvztime_t m_nextGroupTime;
	pvztime_t m_fullSpawnTime;
};

class StormZombieSpawnerProps : public ZombieSpawnerActionProps
{
	RT_CLASS_DEFINE(StormZombieSpawnerProps, ZombieSpawnerActionProps, RtClass);
public:
	
	StormZombieSpawnerProps()
	: AdditionalPlantfood(0)
	, GroupSize(1)
	, TimeBetweenGroups(1.0f)
	, TimeBeforeFullSpawn(PVZ_EOT())
	, ColumnStart(5)
	, ColumnEnd(8)
	, Type(STORMTYPE_SANDSTORM)
	{
		// Do nothing.
	}
	
	virtual RtClass* GetActionClass() const override
	{
		return StormZombieSpawner::StaticGetClass();
	}
	
	virtual void GatherSpawnedZombieTypes(std::set<const class ZombieType*> &o_zombies) override;
	
	std::vector<StormZombieInstruction> Zombies;
	int AdditionalPlantfood;
	int GroupSize;
	pvztime_t TimeBetweenGroups;
	pvztime_t TimeBeforeFullSpawn;
	int ColumnStart;
	int ColumnEnd;
	StormType Type;
};

#endif /* defined(__PlantsVersusZombies2__StormZombieSpawner__) */
