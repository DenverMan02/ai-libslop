//
//  DangerRoomLevelDesigner.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 8/28/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomLevelDesigner__
#define __PlantsVersusZombies2__DangerRoomLevelDesigner__

#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "Utils.h"

class GravestoneModule;
class WaveManagerProperties;


//
// A type that can generate procedural level content for a danger room.
// Has hooks for gathering resources, controlling setup, and adding/modifying waves
// A danger room may have may of these, and they aren't run in a particular order
// but the individual steps are - wave generation always happens before event generation, etc.
//
class DangerRoomLevelDesigner : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(DangerRoomLevelDesigner, PropertySheetBase, RtClass);
	virtual ~DangerRoomLevelDesigner() {}
	
	// Some designers may need to load resources, like gravestones
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
	
	// The following methods are called in order during setup, on each designer.  So all designers get to
	//   generate waves, then all designers get to generate events, then all designers get to do setup...
	virtual void ModifyBoardLayout(const int i_level, Sexy::MTRand& io_rand) const {}
	virtual void GenerateWaves(const int i_level, Sexy::MTRand& io_rand, WaveManagerProperties* io_props) const {}
	virtual void GenerateEvents(const int i_level, Sexy::MTRand& io_rand, WaveManagerProperties* io_props) const {}
	virtual void GenerateInitialBoardEntities(const int i_level, Sexy::MTRand& io_rand) const {}
	virtual void GenerateExtraModules(const int i_level, Sexy::MTRand& io_rand, class LevelModuleManager* i_levelModuleMgr) const {}
	
};



#pragma mark - Jittered Wave Generator

struct ZombiePoolConfig
{
	ZombiePoolConfig()
	{
		MinSpawnLevel = 1;
		MaxSpawnLevel = 99;
        Level = 1;
	}

	int MinSpawnLevel;
	int MaxSpawnLevel;
	//std::vector<ZombieTypePtr> ZombiePool;
	ZombieTypePtr ZombieType;
    int Level;
};

//
// Creates a level-full of zombie waves for danger room,
//
class DangerRoomJitteredWaveGenerator : public DangerRoomLevelDesigner
{
public:
	RT_CLASS_DEFINE(DangerRoomJitteredWaveGenerator, DangerRoomLevelDesigner, RtClass);
	DangerRoomJitteredWaveGenerator()
	: StartingPoints(100)
	, BasePointIncrementPerWave(30)
	, BasePointIncrementPerLevel(5)
	{ }
	virtual ~DangerRoomJitteredWaveGenerator() {}
	
	void GenerateWaves(const int i_level, Sexy::MTRand& io_rand, WaveManagerProperties* io_props) const override;
	
	uint16	StartingPoints;
	uint16	BasePointIncrementPerWave;
	uint16	BasePointIncrementPerLevel;
	std::vector<ZombieTypePtr> ZombiePool;
	
private:
	void configureJitteredWaves(int i_level, Sexy::MTRand& io_rand, struct DanggerRoomWaveConfig* io_config) const;
    void EnsureBigZombieExist(Sexy::MTRand& io_rand, std::vector<const ZombieType*>& dest, const std::vector<ZombieTypePtr>& pool) const;
    int CalcWaveCount(int level) const;
    int CalcFlagCount(int level, int waveCount, Sexy::MTRand &io_rand) const;
};



#pragma mark - Gravestone Generator

//
// Places initial gravestones for the danger room level
//
class DangerRoomGravestoneGenerator : public DangerRoomLevelDesigner
{
public:
	RT_CLASS_DEFINE(DangerRoomGravestoneGenerator, DangerRoomLevelDesigner, RtClass);
	DangerRoomGravestoneGenerator()
	: MinGravestoneCount(0)
	, BaseGravestoneCountPerLevel(2.0f)
	, MaxGeneratedGravestones(20)
	, MinStartingGravestoneSpawnCol(2)
	, MaxStartingGravestoneSpawnCol(9)
	, MaxStartingGravestoneSpawnColOffsetPerLevel(-0.5f)
	, MinEndingGravestoneSpawnCol(9)
	, MaxEndingGravestoneSpawnCol(9)
	, MaxEndingGravestoneSpawnColOffsetPerLevel(0.0f)
	{ }
	virtual ~DangerRoomGravestoneGenerator() {}
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void GenerateInitialBoardEntities(const int i_level, Sexy::MTRand& io_rand) const override;
	
	uint8 MinGravestoneCount;
	float BaseGravestoneCountPerLevel;
	uint8 MaxGeneratedGravestones;
	uint8 MinStartingGravestoneSpawnCol;
	uint8 MaxStartingGravestoneSpawnCol;
	float MaxStartingGravestoneSpawnColOffsetPerLevel;
	uint8 MinEndingGravestoneSpawnCol;
	uint8 MaxEndingGravestoneSpawnCol;
	float MaxEndingGravestoneSpawnColOffsetPerLevel;
	
private:
	GravestoneModule* tryGetGravestoneModule() const;
};



#pragma mark - DangerRoomLevelDesigner Helpers

namespace DangerRoomLevelDesignerHelpers
{
	class WavePool
	{
	public:
		void Add(const int i_waveID);
		void AddRange(const int i_startWaveID, const int i_endWaveID); // Inclusive bounds
		
		int Remove(const int i_value);
		int RemoveFirstWave();
		void RemoveFirstHalf();
		
		int PickRandom(Sexy::MTRand& io_random) const;
		bool Contains(const int i_value) const;
		bool IsEmpty() const { return m_pool.empty(); }
		
	private:
		std::vector<int> m_pool;
	};
	
	struct FlagWavePool
	{
		FlagWavePool(int i_flagWaveIndex)
		: Index(i_flagWaveIndex)
		{}
		
		int Index;
		WavePool Pool;
	};
	
	std::vector<FlagWavePool> GenerateFlagWavePools(const int i_numberOfWaves, const int i_flagInterval);
    int CalculateLevelValue(float i_pointInLevelSequence, const ValueRange& i_minRange, const ValueRange& i_maxRange);
}

#endif /* defined(__PlantsVersusZombies2__DangerRoomLevelDesigner__) */
