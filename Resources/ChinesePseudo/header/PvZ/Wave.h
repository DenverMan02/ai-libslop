//
//  Wave.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/22/13
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Wave_h
#define PlantsVersusZombies2_Wave_h

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "GameObject.h"
#include "LevelModule.h"
#include "Loot.h"
#include "PVZDB.h"
#include "PVZTypes.h"
#include "PropertySheetBase.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "SexyAppFramework/MTRand.h"
#include "TimeMgr.h"
#include "TodDebug.h"
#include "WaveGenerator.h"

class DynamicZombiesInstruction;
class WaveManagerProperties;
class ZombieType;
//class WaveGenerator;

//
// Old WaveGenerator Cruft
//
//enum EventType
//{
//	EVENTTYPE_NONE,
//	EVENTTYPE_SANDSTORM,
//	EVENTTYPE_RAIDINGPARTY,
//	EVENTTYPE_SPIDERRAIN
//};
//
//const pvztime_t ZOMBIE_COUNTDOWN_SECS = 25.0f;
//const pvztime_t ZOMBIE_COUNTDOWN_RANGE_SECS = 6.0f;
//const pvztime_t ZOMBIE_COUNTDOWN_BEFORE_FLAG_SECS = 45.0f;
//const pvztime_t ZOMBIE_COUNTDOWN_MIN_SECS = 4.0f;

//
// Scaffolding
//

//namespace WaveType
//{
//	enum WaveType
//	{
//		Unknown,
//		Normal,
//		Huge,
//	};
//}
namespace Sexy
{
	RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(WaveType::WaveType);
}
//RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(WaveType::WaveType);



// Allows for the description/instantiation of WaveActions from json.
class WaveActionProperties : public PropertySheetBase
{
	RT_CLASS_DEFINE_ABSTRACT(WaveActionProperties, PropertySheetBase, RtClass);
public:

	virtual RtClass* GetActionClass() const = 0;
	std::vector<std::string>    ResourceGroupNames;
    std::vector<std::string>	NotificationEvents;
};
typedef RtWeakPtr<WaveActionProperties> WaveActionPropertiesPtr;


// Instanced based off of WaveActionProperties specified in json.
class WaveAction : public GameObject
{
	RT_CLASS_DEFINE(WaveAction, GameObject, RtClass);
public:

	void InitializeAction(WaveActionPropertiesPtr i_properties, Sexy::MTRand &i_random, int i_waveNumber);

	virtual void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, Sexy::MTRand &i_random) {}
	virtual void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) {}
	virtual void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) {}

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) {}

	template <typename T> const T* GetProps() const
	{
		DBG_ASSERT(m_propertySheetPtr.IsValid());
		return m_propertySheetPtr->CastChecked<const T>();
	}

protected:
	virtual void initializeAction(Sexy::MTRand &i_random, int i_waveNumber) {}
    void notifyWaveEvents();

private:
	RtWeakPtr<WaveActionProperties> m_propertySheetPtr;
};
typedef RtWeakPtr<WaveAction> WaveActionPtr;

struct Wave
{
	Wave()
	: Type(WaveType::Normal)
	{
		// Do nothing.
	}

	WaveType::WaveType Type;
	std::vector<WaveActionPtr> Actions;
};

// Manages wave progression.
class WaveManager : public RtObject
{
	RT_CLASS_DEFINE(WaveManager, RtObject, RtClass);
public:
	WaveManager();
	~WaveManager();
	
	void Initialize(RtWeakPtr<class WaveManagerProperties> i_props, LootConfig *i_lootConfig, bool i_hasDynamicZombies);
	void AddResourceRequirements(std::set<std::string> &io_resGroupNames) const;

	void Update();

	void SetPause(bool i_paused);
	bool IsPaused() const;
	void SetNextWaveTime(pvztime_t i_time);
	bool IsDone(void) const;
	bool IsRiftTimedEvent() const;
	bool HasSpawnedFinalWave() const;

	void GetZombies(std::vector<const ZombieType*> &o_zombies) const;
	void GetZombiesForWave(int i_wave, std::vector<const ZombieType*> &o_zombies) const;
    
    void GetCreatures(std::vector<const CreatureType*> &o_creatures) const;
    void GetCreaturesForWave(int i_wave, std::vector<const CreatureType*> &o_creatures) const;
	
	int GetWaveCount() const;
	int GetCurrentWave() const { return m_currentWave; }

	Wave* GetCurrentWaveData() const;

	void ReseedRandomness(unsigned i_seed);

	const WaveManagerProperties *GetProps() const;

	void SetForceSpawnMode(bool i_enabled);
	void ForceSpawnWave();

	bool ShouldCullZombiesForWave(int i_wave) const;
    bool ShouldFreeCapturedZombies();

	bool WaveHasFriendZombie(int i_wave) const;
    bool AnyWaveHasDynamicZombies() const { return m_hasDynamicZombies; }

    Wave GetWaveByIndex(int i_index);

    void setIsHasShowOppoTips(bool isHasShowOppoTips);
    bool getIsHasShowOppoTips() const;

	void SetCycleSpawnMode(int i_startIndex);
	bool IsInCycleMode() const { return m_cycleStartIdx != -1; };
	void CommonUpdateWave();
	void SetFinish() { setState(Finished); }
private:
	enum WaveState {
		Uninitialized,
		Running,
		DelayedForHugeWave,
		ForceSpawnMode,
		RiftTimedEventMode,
		CycleMode,
		Finished,
	};

	void updateActions();

	void adjustTimeForZombieHealth();
	void sendProgressUpdates();
	void spawnNextWave();
	void assignLoot(class LootConfig *i_lootConfig);
	void updateLootStats(Loot i_loot);

	void setState(WaveState i_state);
	void onExit(WaveState i_state);
	void onEnter(WaveState i_state);

	void onWaveEnded(int i_waveIndex);
	void onWaveStarted(int i_waveIndex);

	void onGameplayEnded();
	
	bool nextWaveIsHugeWave() const;
	bool shouldSpawnWave() const;
	bool isFinalWave(int i_wave) const;
	void backToNormal();

	// Serialized
	RtWeakPtr<WaveManagerProperties> m_props;
	std::vector<Wave> m_waves;
	int m_currentWave;
	pvztime_t m_nextWaveTime;
	pvztime_t m_lastWaveTime;
    pvztime_t m_zombieWaveSpawnTimeInterval;
	int m_currentWaveTotalHealth;
	int m_nextWaveHealthThreshold;
	WaveState m_state;
	bool m_paused;
	bool m_forceSpawnNextWave;
	bool m_hasDynamicZombies;

	// Not serialized.
	Sexy::MTRand m_waveRNG;
	bool m_bIsHasShowOppoTips;
	int m_cycleStartIdx;
};

// Configures the WaveManager via json.
class WaveManagerProperties : public PropertySheetBase
{
	RT_CLASS_DEFINE(WaveManagerProperties, PropertySheetBase, RtClass);
public:
	WaveManagerProperties()
	: FlagWaveInterval(10)
	, WaveCount(0)
	, SuppressFlagZombie(false)
	, MinNextWaveHealthPercentage(0.70f)
	, MaxNextWaveHealthPercentage(0.85f)
	, ZombieCountdownFirstWaveSecs(12.0f)
	, ZombieCountdownFirstWaveConveyorSecs(5.0f)
	, ZombieCountdownHugeWaveDelay(5.0f)
	, LevelJam("")
	, Description("")
	, DescriptionName("")
	{
		WaveManagerProperties* defaults = PVZDB::GetInstance().FindObjectByAlias<WaveManagerProperties>(PVZDB::TABLE_PROPERTYSHEETS, L"DefaultWaveManagerProperties");
		if (defaults)
		{
			defaults->ShallowCopyInto(this);
		}
	}

	void ShallowCopyInto(WaveManagerProperties *o_props) const
	{
		o_props->Waves = Waves;
		o_props->FlagWaveInterval = FlagWaveInterval;
		o_props->WaveCount = WaveCount;
		o_props->SuppressFlagZombie = SuppressFlagZombie;
        o_props->MinNextWaveHealthPercentage = MinNextWaveHealthPercentage;
        o_props->MaxNextWaveHealthPercentage = MaxNextWaveHealthPercentage;
		o_props->ZombieCountdownFirstWaveConveyorSecs = ZombieCountdownFirstWaveConveyorSecs;
		o_props->ZombieCountdownFirstWaveSecs = ZombieCountdownFirstWaveSecs;
		o_props->ZombieCountdownHugeWaveDelay = ZombieCountdownHugeWaveDelay;
		o_props->SuppressedDynamicZombieWaves = SuppressedDynamicZombieWaves;
		o_props->Description = Description;
		o_props->DescriptionName = DescriptionName;
	}

	RtClass* GetModuleClass();
	SexyString GetDescription();
	SexyString GetDescriptionName();

	std::vector<std::vector<WaveActionPropertiesPtr> > Waves;
	int FlagWaveInterval;
	int WaveCount;
	bool SuppressFlagZombie;
	std::vector<int> SuppressedDynamicZombieWaves;

	float MinNextWaveHealthPercentage;
	float MaxNextWaveHealthPercentage;
	
	pvztime_t ZombieCountdownFirstWaveSecs;
	pvztime_t ZombieCountdownFirstWaveConveyorSecs;
	pvztime_t ZombieCountdownHugeWaveDelay;

	std::string LevelJam;

	std::string Description;
	std::string DescriptionName;
};


//
// WaveManagerModule
//
class WaveManagerModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(WaveManagerModule, LevelModule, RtClass);
	
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
	bool IsDone() const;

	WaveManager &GetWaveManager() { return m_waveManager; }
	const DynamicZombiesInstruction* GetDifficultyProps();
    
    static short GetProfileDifficultyIndex();

protected:
	virtual void postInitialize() override;
	virtual void registerForEvents() override;

private:
	void onLevelInit();
	void onGameplayStarted();	
	void onUpdate();
	
	void injectDynamicZombies(WaveManagerProperties *o_props);
	
	WaveManager m_waveManager;
};


struct DynamicZombiesInstruction
{
	DynamicZombiesInstruction()
	: StartingPoints(0)
	, PointIncrementPerWave(0)
	, StartingWave(0)
	{
		// Do nothing.
	}

	int StartingPoints;
	int PointIncrementPerWave;
	int StartingWave;
	std::vector<ZombieTypePtr> ZombiePool;
    std::vector<int>           ZombieLevel;
};

// Configures the WaveManagerModule via json.
class WaveManagerModuleProperties : public LevelModuleProperties
{
	RT_CLASS_DEFINE(WaveManagerModuleProperties, LevelModuleProperties, RtClass);
public:
	WaveManagerModuleProperties()
	: ManualStartup(false)
	, HasWinCondition(true)
	{
		// Do nothing.
	}

	virtual RtClass* GetModuleClass() const override
	{
		return WaveManagerModule::StaticGetClass();
	}

	RtWeakPtr<WaveManagerProperties> WaveManagerProps;
	bool ManualStartup;

	std::vector<DynamicZombiesInstruction> DynamicZombies;
	std::vector<RtWeakPtr<WaveManagerProperties>> WaveManagerPropsVector;
	bool HasWinCondition;
};


//
// Actions
//
namespace RowSpawnInstruction
{
	enum RowSpawnInstruction 
	{
		RowOne,
		RowTwo,
		RowThree,
		RowFour,
		RowFive,
		Random,
		Previous,
		None,
	};
}

namespace ColumnSpawnInstruction
{
	enum ColumnSpawnInstruction
	{
		ColumnInvalid,
		ColumnOne,
		ColumnTwo,
		ColumnThree,
		ColumnFour,
		ColumnFive,
		ColumnSix,
		ColumnSeven,
		ColumnEight,
		ColumnNine,
		Random,
		Previous,
		None,
	};
}

struct ZombieLootApplicant
{
	ZombieLootApplicant()
	: OwningAction(NULL)
	{
		// Do nothing.
	}

	class ZombieSpawnerAction *OwningAction;
	std::vector<const ZombieType*> Zombies;
	std::vector<Loot> Loots;
};

//
// Random Jittered Waves
//
struct RandomJitteredWaveInstruction
{
	RandomJitteredWaveInstruction()
	: WaveNumber(0)
	, AdditionalPlantfood(0)
	, DisableZombieSpawning(false)
	{
		// Do nothing.
	}

	int WaveNumber;
	std::vector<const ZombieType*> AddZombiesToPool;
	std::vector<const ZombieType*> RemoveZombiesFromPool;
	int AdditionalPlantfood;
	bool DisableZombieSpawning;
};

struct DrZomibeLevelData
{
    DrZomibeLevelData()    
    {
        Level = 1;
    }
    ZombieTypePtr ZombieType;
    int Level;
};


struct RandomJitteredWaveConfig
{
	RandomJitteredWaveConfig()
	: StartingWave(0)
	, WaveCount(0)
	, FlagWaveInterval(10)
	, StartingPoints(0)
	, PointIncrementPerWave(0)
	, RandomSeed(0)
	{
		// Do nothing.
	}

	RandomJitteredWaveInstruction &EnsureInstructionForWave(int i_wave); // Do not hold onto references across calls to the function, as it can resize the array it's keeping the instructions in.
	const RandomJitteredWaveInstruction *GetInstructionForWave(int i_wave) const;

	int StartingWave;
	int WaveCount;
	int FlagWaveInterval;
	int StartingPoints;
	int PointIncrementPerWave;
	int RandomSeed;
	std::vector<RandomJitteredWaveInstruction> WaveInstructions;
    std::vector<DrZomibeLevelData> ZombieDatas;
};

struct DanggerRoomWaveConfig : public RandomJitteredWaveConfig
{
    int level = 1;
    int MinZombieLevel = 1;
    int MaxZombieLevel = 1;
    float MaxLevelProbability = 1.0f;
    int LeaderMinWaveCost = 100;
    float  LeaderProbability = 0.0f;
    float  WealthGodProbability = 0.0f;
};

namespace WaveHelpers
{
	void PickZombiesFromPool(int i_pointBalance, const std::set<const ZombieType*> &i_pool, MTRand &i_random, std::vector<const ZombieType*> &o_pickedZombies);
	void PickZombiesFromPool(int i_pointBalance, const std::set<ZombieTypePtr> &i_pool, MTRand &i_random, std::vector<ZombieTypePtr> &o_pickedZombies);
	void GenerateRandomJitteredWaves(const RandomJitteredWaveConfig &i_config, WaveManagerProperties *o_props);
    void GenerateDangerRoomWaves(const DanggerRoomWaveConfig &i_config, WaveManagerProperties *o_props);
}

//
// Messages
//
namespace Message
{
	void SendWaveNotificationEvents(const std::vector<std::string>& i_waveNotificationEvents);
	void PreWaveInitialization(WaveManagerProperties *i_waveProps);
}

#endif
