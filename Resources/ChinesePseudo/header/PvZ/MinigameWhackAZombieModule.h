//
//  MinigameWhackAZombieModule.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 11/19/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MinigameWhackAZombieModule__
#define __PlantsVersusZombies2__MinigameWhackAZombieModule__

#include "GridItemWhackPuddle.h"
#include "LevelModule.h"
#include "WaveActionSpawnZombies.h"
#include "Utils.h"

namespace Message
{
	void PuddleSpawned(BoardEntity* i_entity);
}

class MinigameWhackAZombieModule : public LevelModule
{
public:
	enum HammerStatus
	{
		WHACK_HAMMER_STATUS_USELESS,
		WHACK_HAMMER_STATUS_BROKEN,
		WHACK_HAMMER_STATUS_NORMAL,
		WHACK_HAMMER_STATUS_SUPER,
	};
	
public:
	RT_CLASS_DEFINE(MinigameWhackAZombieModule, LevelModule, RtClass);

public:
	void ReserveNewZombiePuddles();
	const std::vector<BoardEntityPtr>& GetCurrentAvailableZombiePuddles();
	
	std::vector<GridItemWhackPuddle*> GetAvailablePuddles();
	
	HammerStatus GetHammerStatus();
	float GetHammerHitValue();
	
	void OnWhackOccurred(bool i_hitZombie);
	
protected:
	void initializeModule() override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	bool onTouchEvent(const Sexy::Touch& i_touch);
	
	void OnZombieAddedToBoard(Zombie* i_zombie);
	
private:
	void onUpdate();
	void onLevelLoaded();
	void gameplayStarted();

	void findPuddles();
	void onPuddleSpawned(BoardEntity* i_entity);
	
	void ensureMinimumPuddles();
	void openPuddles(int numToOpen);
	void reserveNewPuddle();

	std::vector<BoardEntityPtr>		m_Puddles;
	std::vector<BoardEntityPtr>		m_ReservedPuddles;
	
	HammerStatus	m_HammerState;
	int				m_HammerStateTapCount;
	
};

class MinigameWhackAZombieModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(MinigameWhackAZombieModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return MinigameWhackAZombieModule::StaticGetClass();
	}
	MinigameWhackAZombieModuleProperties()
	{
		PuddleCountReservedForModifiers = 1;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	int PuddleCountReservedForModifiers;
	
	std::vector<int> HammerTapsToDecay;
	std::vector<float> HammerHitValue;
};




// Spawn zombies X many at a time with Y seconds in between.
// If the wave ends, or the full spawn timer expires it spawns
// all remaining zombies.
//
// This is nearly functional but may need additional work.
// My intention was to isolate the special WhackAZombie code.
//
// In addition, it would be nice to unify it with the parent code,
// however much of this code actually game from a different wave
// spawner module that supported groups.

class SpawnZombiesDelayedFromGridItemsWaveAction : public SpawnZombiesFromGridItemWaveAction
{
	RT_CLASS_DEFINE(SpawnZombiesDelayedFromGridItemsWaveAction, SpawnZombiesFromGridItemWaveAction, RtClass);
public:
	SpawnZombiesDelayedFromGridItemsWaveAction()
	{
		m_nextGroupTime = PVZ_EOT();
		m_fullSpawnTime = PVZ_EOT();
	}
	
	virtual void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, Sexy::MTRand &i_random) override;
	virtual void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
	virtual void WaveEnd(int i_waveNumber, MTRand &i_random) override;
	
protected:
	virtual void spawnZombieFromGridItem(BoardEntity* i_gridItem, Zombie* i_zombie);
	
private:

	void spawnGroup(int i_count, int i_waveNumber, MTRand &i_random);
	void spawnRemainder(int i_waveNumber, MTRand &i_random);
	void createZombies(int i_waveNumber, MTRand &i_random, int i_startIndex, int i_stopIndex);

	int m_nextZombieIndex;
	pvztime_t m_nextGroupTime;
	pvztime_t m_fullSpawnTime;
	RtId m_lastSpawnObjectID;
};

class SpawnZombiesDelayedFromGridItemsProps : public SpawnZombiesFromGridItemSpawnerProps
{
	RT_CLASS_DEFINE(SpawnZombiesDelayedFromGridItemsProps, SpawnZombiesFromGridItemSpawnerProps, RtClass);
public:
	
	SpawnZombiesDelayedFromGridItemsProps()
	: GroupSize(1)
	, TimeBetweenGroups(1.0f)
	, TimeBeforeFullSpawn(PVZ_EOT())
	, ZombieCondition(ZCONDITION_Invalid)
	{
		WaveStartMessage = "";
	}
	
	virtual RtClass* GetActionClass() const override
	{
		return SpawnZombiesDelayedFromGridItemsWaveAction::StaticGetClass();
	}
	
	int GroupSize;
	pvztime_t TimeBetweenGroups;
	pvztime_t TimeBeforeFullSpawn;
	ZombieConditions ZombieCondition;
};



class SpawnWhackAZombiesAction : public SpawnZombiesDelayedFromGridItemsWaveAction
{
	RT_CLASS_DEFINE(SpawnWhackAZombiesAction, SpawnZombiesDelayedFromGridItemsWaveAction, RtClass);
public:
	SpawnWhackAZombiesAction()
	{
	}
	
protected:
	std::vector<BoardEntity*> getTargetGridItems() override;
	
private:
	
	void spawnZombieFromGridItem(BoardEntity* i_gridItem, Zombie* i_zombie) override;
};

class SpawnWhackAZombiesProps : public SpawnZombiesDelayedFromGridItemsProps
{
	RT_CLASS_DEFINE(SpawnWhackAZombiesProps, SpawnZombiesDelayedFromGridItemsProps, RtClass);
	
public:
	virtual RtClass* GetActionClass() const override
	{
		return SpawnWhackAZombiesAction::StaticGetClass();
	}
};


#endif
