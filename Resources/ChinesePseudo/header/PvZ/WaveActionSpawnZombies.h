//
//  WaveActionSpawnZombies.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 4/22/14
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#include "GridItemGravestone.h"
#include "Wave.h"

#ifndef PlantsVersusZombies2_WaveActionSpawnZombies_h
#define PlantsVersusZombies2_WaveActionSpawnZombies_h

class ZombieSpawnerPattern : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ZombieSpawnerPattern, PropertySheetBase, RtClass);
	
	std::vector<int> RowStartOffset;
	std::vector<int> RowBetweenOffset;
};

// Adding a little bit of hierarchy here to make loot management feasible...
// Anything that spawns zombies as an action should use this.
class ZombieSpawnerAction : public WaveAction
{
	RT_CLASS_DEFINE(ZombieSpawnerAction, WaveAction, RtClass);
public:

	// If you want your zombies to get loot, you must implement these functions.
	virtual void GetZombies(std::vector<const ZombieType*> &o_zombies) {}
	virtual void SetLoot(const std::vector<Loot> &i_loot) {}
	virtual const std::vector<Loot> GetLoot() { return std::vector<Loot>(); }
};

class ZombieSpawnerActionProps : public WaveActionProperties
{
	RT_CLASS_DEFINE_ABSTRACT(ZombieSpawnerActionProps, WaveActionProperties, RtClass);
public:
	virtual void GatherSpawnedZombieTypes(std::set<const class ZombieType*> &o_zombies) = 0;
};

struct SpawnZombiesJitteredInstruction
{
	SpawnZombiesJitteredInstruction()
	: Row(RowSpawnInstruction::Random)
	, FriendZombie(false)
    , Level(1)
    , Color(-1)
	, Column(ColumnSpawnInstruction::ColumnInvalid)
	{
		// Do nothing.
	}

	ZombieTypePtr Type;
	RowSpawnInstruction::RowSpawnInstruction Row;
	ColumnSpawnInstruction::ColumnSpawnInstruction Column;
	bool FriendZombie;
    bool LeaderZombie = false;
    int Level;
    int Color;
};

class SpawnZombiesJitteredWaveAction : public ZombieSpawnerAction
{
	RT_CLASS_DEFINE(SpawnZombiesJitteredWaveAction, ZombieSpawnerAction, RtClass);
public:
	virtual void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, Sexy::MTRand &i_random) override;

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	virtual void GetZombies(std::vector<const ZombieType*> &o_zombies) override;
	virtual void SetLoot(const std::vector<Loot> &i_loot) override;
	virtual const std::vector<Loot> GetLoot() override { return m_zombieLoot; }

	virtual void onCreatedZombies(int i_waveNumber, std::vector<Zombie*> i_zombies) {}

	bool HasFriendZombie() const;

	std::vector<SpawnZombiesJitteredInstruction>& GetZombieConfigs() { return m_zombies; }

protected:
	virtual bool allowDynamicZombieCulling() const;
	std::vector<SpawnZombiesJitteredInstruction> m_zombies;

private:
	void createZombies(int i_waveNumber, Sexy::MTRand &i_random, std::vector<class Zombie*> &o_zombies);
	virtual void preCreateZombies() {};
	virtual void postCreateZombies() {};
	virtual void initializeAction(Sexy::MTRand &i_random, int i_waveNumber) override;
	virtual int getZombieCountToSpawn();

	virtual bool shouldRiseFromGround() { return false; }
	virtual float getZombieSpawnXPosition(Zombie* i_zombie, int i_zombieRow, MTRand &i_random);
	virtual SexyVector3 getZombieSpawnPosition(SpawnZombiesJitteredInstruction& i_spawnInstruction, Zombie* i_zombie, MTRand &i_random, int& io_lastRow);

	int getZombieRow(RowSpawnInstruction::RowSpawnInstruction i_rowType, ZombieTypePtr i_type, MTRand &i_random, int i_lastRow);
	int getZombieColumn(ColumnSpawnInstruction::ColumnSpawnInstruction i_columnType, ZombieTypePtr i_type, MTRand &i_random, int i_lastColumn);
	virtual void wavePositionZombies(std::vector<Zombie*> i_zombies, MTRand &i_random);

	std::vector<Loot> m_zombieLoot;
};

class SpawnZombiesJitteredWaveActionProps : public ZombieSpawnerActionProps
{
	RT_CLASS_DEFINE(SpawnZombiesJitteredWaveActionProps, ZombieSpawnerActionProps, RtClass);
public:
	
	SpawnZombiesJitteredWaveActionProps()
	{
		AdditionalPlantfood = 0;
		HighlightZombies = false;
		FixedOffset = 0.0f;
	}
	
	virtual RtClass* GetActionClass() const override
	{
		return SpawnZombiesJitteredWaveAction::StaticGetClass();
	}
	
	virtual void GatherSpawnedZombieTypes(std::set<const class ZombieType*> &o_zombies) override;
	
	std::vector<SpawnZombiesJitteredInstruction> Zombies;
	int AdditionalPlantfood;
	std::vector<int> DynamicPlantfood;
	bool HighlightZombies;
	RtWeakPtr<class ZombieJitterOffsets> JitterOffsets;
	std::string	ZombieSpawnPattern;
	float FixedOffset;
};

//Spawn Zombies From Ground
class SpawnZombiesMirrorWaveAction : public SpawnZombiesJitteredWaveAction
{
	RT_CLASS_DEFINE(SpawnZombiesMirrorWaveAction, SpawnZombiesJitteredWaveAction, RtClass);
public:
	SpawnZombiesMirrorWaveAction()
	{
		// Do nothing extra.
	}

	void onCreatedZombies(int i_waveNumber, std::vector<Zombie*> i_zombies) override;
};

class SpawnZombiesMirrorWaveActionProps : public SpawnZombiesJitteredWaveActionProps
{
	RT_CLASS_DEFINE(SpawnZombiesMirrorWaveActionProps, SpawnZombiesJitteredWaveActionProps, RtClass);
public:

	SpawnZombiesMirrorWaveActionProps()
	{
		// Do nothing.
	}

	virtual RtClass* GetActionClass() const override
	{
		return SpawnZombiesMirrorWaveAction::StaticGetClass();
	}
};

class ZombieJitterOffsets : public RtObject
{
public:
	RT_CLASS_DEFINE(ZombieJitterOffsets, RtObject, Sexy::RtClass);

	ZombieJitterOffsets()
	{
		ZombieSpawningOffsetIncrement = 80;
		ZombieSpawningRandomJitter = 30;
	}

	int ZombieSpawningOffsetIncrement;
	int ZombieSpawningRandomJitter;
};

//Spawn Zombies From Ground
class SpawnZombiesFromGroundWaveAction : public SpawnZombiesJitteredWaveAction
{
	RT_CLASS_DEFINE(SpawnZombiesFromGroundWaveAction, SpawnZombiesJitteredWaveAction, RtClass);
public:
	SpawnZombiesFromGroundWaveAction()
	{
		// Do nothing extra.
	}

private:
	virtual bool shouldRiseFromGround() override { return true; }
	virtual float getZombieSpawnXPosition(Zombie* i_zombie, int i_zombieRow, MTRand &i_random) override;
};

class SpawnZombiesFromGroundSpawnerProps : public SpawnZombiesJitteredWaveActionProps
{
	RT_CLASS_DEFINE(SpawnZombiesFromGroundSpawnerProps, SpawnZombiesJitteredWaveActionProps, RtClass);
public:

	SpawnZombiesFromGroundSpawnerProps()
	: ColumnStart(2)
	, ColumnEnd(9)
	{
		// Do nothing.
	}

	virtual RtClass* GetActionClass() const override
	{
		return SpawnZombiesFromGroundWaveAction::StaticGetClass();
	}

	int ColumnStart;
	int ColumnEnd;
};

//Spawn Zombies From Graves
class SpawnZombiesFromGridItemWaveAction : public SpawnZombiesJitteredWaveAction
{
	RT_CLASS_DEFINE(SpawnZombiesFromGridItemWaveAction, SpawnZombiesJitteredWaveAction, RtClass);
public:
	SpawnZombiesFromGridItemWaveAction()
	{
		m_timeToSpawnZombies = PVZ_EOT();
	}

	virtual void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, Sexy::MTRand &i_random) override;
	virtual void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;

protected:
	bool allowDynamicZombieCulling() const override;
	
	virtual std::vector<BoardEntity*> getTargetGridItems();

private:
	virtual bool shouldRiseFromGround() override { return true; }
	virtual void preCreateZombies() override;
	virtual void postCreateZombies() override;
	virtual SexyVector3 getZombieSpawnPosition(SpawnZombiesJitteredInstruction& i_spawnInstruction, Zombie* i_zombie, MTRand &i_random, int& io_lastRow) override;
	virtual int getZombieCountToSpawn() override;
	bool testGridTypesMatch(GridItemTypePtr i_entityToMatch);

	std::vector<BoardEntity*> m_entitiesToSpawnFrom;
	pvztime_t m_timeToSpawnZombies;
};

class SpawnZombiesFromGridItemSpawnerProps : public SpawnZombiesJitteredWaveActionProps
{
	RT_CLASS_DEFINE(SpawnZombiesFromGridItemSpawnerProps, SpawnZombiesJitteredWaveActionProps, RtClass);
public:

	SpawnZombiesFromGridItemSpawnerProps()
	{
		WaveStartMessage = "[WARNING_GRAVESTONE_SPAWN]";
		ZombieSpawnWaitTime = 0.0f;
		SuppressActionIfNoGridItemsFound = true;
	}

	virtual RtClass* GetActionClass() const override
	{
		return SpawnZombiesFromGridItemWaveAction::StaticGetClass();
	}

	SexyString GetWaveStartMessage() const;

	std::vector<GridItemTypePtr>		GridTypes;
	std::string WaveStartMessage;
	pvztime_t ZombieSpawnWaitTime;
	bool SuppressActionIfNoGridItemsFound;
};


class ZombieRainSpawner : public ZombieSpawnerAction
{
	RT_CLASS_DEFINE(ZombieRainSpawner, ZombieSpawnerAction, RtClass);
public:
	ZombieRainSpawner()
	{
		// Do nothing.
	}
	
	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand &i_random) override;
	void WaveUpdate(int i_waveNumber, MTRand &i_random) override;
	void WaveEnd(int i_waveNumber, MTRand &i_random) override;
	
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	void GetZombies(std::vector<const ZombieType*> &o_zombies) override;
	void SetLoot(const std::vector<Loot> &i_loot) override;
	
	virtual void PostSpawnZombieSetup(Zombie* i_zombie, SexyVector3 i_destination, float i_fallDuration, float i_startHeight) {};
	
private:
	void initializeAction(MTRand &i_random, int i_waveNumber) override;
	void spawnZombies(int i_count, int i_waveNumber, MTRand &i_random);
	int calculateNextRowToSpawnIn();
	
	std::vector<Loot> m_zombieLoot;
	pvztime_t m_nextGroupTime = PVZ_EOT();
	pvztime_t m_fullSpawnTime = PVZ_EOT();
	int m_zombiesSpawned = 0;
	int m_nextRowToSpawnIn = 0;
};

class ZombieRainSpawnerProps : public ZombieSpawnerActionProps
{
	RT_CLASS_DEFINE(ZombieRainSpawnerProps, ZombieSpawnerActionProps, RtClass);
public:
	
	ZombieRainSpawnerProps()
	: GroupSize(1)
	, ZombieCount(1)
	, TimeBetweenGroups(1.0f)
	, TimeBeforeFullSpawn(PVZ_EOT())
	, ColumnStart(5)
	, ColumnEnd(8)
	, ZombieFallTime(1.5f)
	{
	}
	
	RtClass* GetActionClass() const override
	{
		return ZombieRainSpawnerProps::StaticGetClass();
	}
	
	void GatherSpawnedZombieTypes(std::set<const class ZombieType*> &o_zombies) override;
	
	std::string GetZombieName() const;
	void SetZombieName(std::string& i_name) { ZombieName = i_name; }
	SexyString GetWaveStartMessage() const;
	
	int GroupSize;
	int ZombieCount;
	pvztime_t TimeBetweenGroups;
	pvztime_t TimeBeforeFullSpawn;
	pvztime_t ZombieFallTime;
	int ColumnStart;
	int ColumnEnd;
	std::string WaveStartMessage;
	std::string ZombieName;
};

#endif

