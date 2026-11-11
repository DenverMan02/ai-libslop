//
//  FutureStage.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_FutureStage_h
#define PlantsVersusZombies2_FutureStage_h

#include "StageModule.h"
#include "TimeLine.h"
#include "WaveActionSpawnZombies.h"

#define USE_CONNECTOR_DOTS	(1)

enum LinkedTileClass
{
	PVZ_BEGIN_ENUM(LINKEDTILE_),
	LINKEDTILE_ALPHA,
	LINKEDTILE_BETA,
	LINKEDTILE_GAMMA,
	LINKEDTILE_DELTA,
	LINKEDTILE_EPSILON,
	PVZ_END_ENUM(LINKEDTILE_)
};

struct LinkedTileEntry
{
	LinkedTileEntry()
	{
		Group = LINKEDTILE_Invalid;
		PropagationDelay = 0.f;
		LocationCycleTimer = 1000.f;
	}
	
	Sexy::Point	 		Location;
	LinkedTileClass 	Group;
	float				LocationCycleTimer;
	float				PropagationDelay;
};

struct LinkedTileInstanceData
{
	LinkedTileInstanceData()
	{
		IsPlantfoodActive = false;
	}
	RtWeakPtr<class EffectAnimRig_LinkedTile> 	AnimRigPtr;
	bool										IsPlantfoodActive;
};

#if USE_CONNECTOR_DOTS
struct LinkedTilePropagation_ConnectingDotHandler
{
	LinkedTilePropagation_ConnectingDotHandler()
	{
		Done = false;
	}

	void CreateRig();
	void DestroyRig();
	
	void FadeIn(pvztime_t i_atTime);
	void FadeOut(pvztime_t i_atTime);

	void Update();
	void Draw(Graphics* i_g);
	
	void OnFadeOutDone(const std::string& i_animLabel);
	
	
	RtWeakPtr<class EffectAnimRig_LinkedTileConnect> RigPtr;
	SexyVector2			BoardLocation;
	Color				TintColor;
	bool				Done;
};
#endif

struct LinkedTilePropagationInfo
{
	LinkedTilePropagationInfo()
	{
		Timer = 0.f;
		IsBossPropagation = false;
	}
	
	void BuildTileGlows(class FutureStage* i_stage, const Color& i_tint);
	void DestroyTileGlows();
	
	bool IsDone();
	
	Sexy::Point 		SourceLocation;
	Sexy::Point			TargetLocation;
	LinkedTileClass 	Group;
	float				TotalTime;
	float				Timer;
	bool 				IsBossPropagation;

#if USE_CONNECTOR_DOTS
	std::vector<LinkedTilePropagation_ConnectingDotHandler*> Dots;
	TimeLine					DotTimeLine;
#endif
};

struct FactoryArmStatus
{
	enum FactoryArmState
	{
		ARMSTATE_INIT,
		ARMSTATE_DROPPING,
		ARMSTATE_GRABBING,
		ARMSTATE_RISING,
		ARMSTATE_DONE
	};
	
	FactoryArmStatus();
	void Draw(Graphics* i_g);
	void Update(const class FutureStageProperties* i_props);
	void TapTest(int i_mouseX, int i_mouseY);
	
	int					CoinDropsLeft;
	float				CoinDropChance;
	pvztime_t			LastTapGameTime;
	pvztime_t 			Timer;
	pvztime_t			StateEndTime;
	SexyVector3 		TargetLocation;
	FactoryArmState 	State;
};

class FutureStage : public StageModule
{
public:
	RT_CLASS_DEFINE(FutureStage, StageModule, RtClass);
	
	void SetLinkedTiles(const std::vector<LinkedTileEntry>& i_linkedTiles);
	
	Color GetLinkedTileColor(LinkedTileClass i_class);
	LinkedTileClass GetLinkedTileClassAt(const Sexy::Point& i_gridLoc);
	
	Sexy::Point GetRandomLinkedTileLocation() const;

	virtual bool CanZombieSpawnInRow(int i_row, ZombieTypePtr i_type) override;
	virtual bool UseToolAt(const std::string& i_toolName, int i_mouseX, int i_mouseY, int i_clickCount) override;
	virtual int GetPlantedPacketCount(const std::string& i_packetType) override;
	
	virtual void DestroyLinkedTileAt(const Sexy::Point& i_gridLoc);
	virtual void DestroyLinkedNetworkAt(const Sexy::Point& i_gridLoc);
    
	void SetIsBossFight(bool i_isBossFight);
	
protected:
	virtual void initializeModule() override;
	virtual void onLevelEnded();
	virtual void registerForEvents() override;
	virtual void renderBackground(Graphics* i_g) override;
	
	void addLinkedTile(const LinkedTileEntry& i_newTile);
	void destroyLinkedTileAtIndex(const int i_index);
	
private:
	void onUpdate();
    void onToolAppliedPlantFood(class PlantGroup* i_plant);
	void onPlantPlantfooded(class Plant* i_plant);
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void addToRenderQueue(class RenderQueue* i_queue);
	void onPlantPlanted(class Plant* i_plant);
	void onPlantDied(class Plant* i_plant);
	
	void propagateFromTile(const LinkedTileEntry* i_fromTile, bool i_isBossPropagation);
    
    void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	
	/// Linked tiles
	std::vector<LinkedTileEntry> 			m_linkedTiles;
	std::vector<LinkedTilePropagationInfo> 	m_linkedTilePropagations;
	std::vector<LinkedTileInstanceData> 	m_linkedTileInstances;
	
	/// Factory arm mechanic
	std::vector<FactoryArmStatus> 	m_factoryArms;
	std::vector<ZombieTypePtr>		m_factoryArmZombieTypes;
		
	bool m_isBossFight;
};

class FutureStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(FutureStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return FutureStage::StaticGetClass();
	}
	
	FutureStageProperties()
	{
		LinkedTileColors[0] = Color::Green;
		LinkedTileColors[1] = Color::Red;
		LinkedTileColors[2] = Color::Yellow;
		LinkedTileColors[3] = Color::Purple;
		LinkedTileColors[4] = Color::Cyan;
		
		FactoryArmDropTime = 2.5f;
		FactoryArmGrabTime = 1.0f;
		FactoryArmRiseTime = 2.5f;
		
		FactoryArmCoinDropChance = 0.5f;
		FactoryArmCoinDropCount = 5;
		LinkedTilePropagationAlpha = 0.5f;
	}
	
	Color LinkedTileColors[5];
	
	std::vector<std::string> FactoryArmZombieTypes;
	
	float FactoryArmDropTime;
	float FactoryArmGrabTime;
	float FactoryArmRiseTime;
	
	float FactoryArmCoinDropChance;
	float FactoryArmCoinDropCount;
	
	float LinkedTilePropagationAlpha;
};

class SpiderRainZombieSpawner : public ZombieSpawnerAction
{
	RT_CLASS_DEFINE(SpiderRainZombieSpawner, ZombieSpawnerAction, RtClass);
public:
	SpiderRainZombieSpawner()
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
	void spawnSpiders(int i_count, int i_waveNumber, MTRand &i_random);
	int calculateNextRowToSpawnIn();

	std::vector<Loot> m_zombieLoot;
	pvztime_t m_nextGroupTime;
	pvztime_t m_fullSpawnTime;
	int m_spidersSpawned;
	int m_nextRowToSpawnIn;
};

class SpiderRainZombieSpawnerProps : public ZombieSpawnerActionProps
{
	RT_CLASS_DEFINE(SpiderRainZombieSpawnerProps, ZombieSpawnerActionProps, RtClass);
public:

	SpiderRainZombieSpawnerProps()
	: GroupSize(1)
	, SpiderCount(1)
	, TimeBetweenGroups(1.0f)
	, TimeBeforeFullSpawn(PVZ_EOT())
	, ColumnStart(5)
	, ColumnEnd(8)
	, ZombieFallTime(1.5f)
	{
		WaveStartMessage = "[WARNING_SPIDERRAIN]";
	}

	virtual RtClass* GetActionClass() const override
	{
		return SpiderRainZombieSpawner::StaticGetClass();
	}

	virtual void GatherSpawnedZombieTypes(std::set<const class ZombieType*> &o_zombies) override;

	std::string GetZombieName() const;
	SexyString GetWaveStartMessage() const;

	int GroupSize;
	int SpiderCount;
	pvztime_t TimeBetweenGroups;
	pvztime_t TimeBeforeFullSpawn;
	pvztime_t ZombieFallTime;
	int ColumnStart;
	int ColumnEnd;
	//for diy use
//private:
	std::string SpiderZombieName;
	std::string WaveStartMessage;
};

#endif
