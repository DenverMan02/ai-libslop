#ifndef __WAVEGENERATOR_H__
#define __WAVEGENERATOR_H__

#include "PVZTypes.h"
#include "Loot.h"
#include "Effect_PopAnim.h"


using namespace Sexy;

// FIX - Move these to level properties? Make configurable somehow for sure!
const int MAX_ZOMBIE_WAVES = 100;
const int MAX_ZOMBIES_IN_WAVE = 50;
const int MAX_ZOMBIE_TYPES = 100;

const int MAX_EVENT_ZOMBIES_PER_WAVE = 50;
const int MAX_EVENT_ZOMBIE_SPAWN_WAVES = 10;

const pvztime_t FLAG_RAISE_TIME_SECS = 1.0f;
const pvztime_t ZOMBIE_COUNTDOWN_FIRST_WAVE_SECS = 18.0f;
const pvztime_t ZOMBIE_COUNTDOWN_FIRST_WAVE_CONVEYOR_SECS = 5.0f;
const pvztime_t ZOMBIE_COUNTDOWN_SECS = 20.0f;
const pvztime_t ZOMBIE_COUNTDOWN_RANGE_SECS = 5.0f;
const pvztime_t ZOMBIE_COUNTDOWN_BEFORE_FLAG_SECS = 35.0f;
const pvztime_t ZOMBIE_COUNTDOWN_SECS_NEW_PVP = 25.0F;
const pvztime_t ZOMBIE_COUNTDOWN_MIN_SECS = 4.0f;
const pvztime_t ZOMBIE_COUNTDOWN_SPAWN_DELAY_AFTER_HEALTH_TRIGGER_SECS = 2.0f;
const pvztime_t ZOMBIE_COUNTDOWN_HUGE_WAVE_DELAY = 7.5f;
const pvztime_t ZOMBIE_COUNTDOWN_BLACK_HOLE_DELAY = 8.f;
const pvztime_t FINAL_WAVE_SOUND_DELAY_SECS = 0.6f;

class WaveGeneratorProperties;
class WaveDefinition;
struct WaveDefinition;
struct WaveEventData;

namespace WaveType
{
	enum WaveType
	{
		Unknown,
		Normal,
		Huge,
	};
}


struct GravestoneSetupData
{
	GravestoneSetupData()
	{
		MinGravestoneCount = 0;
		BaseGravestoneCountPerLevel = 2.0f;
		MaxGeneratedGravestones = 20;
		MinStartingGravestoneSpawnCol = 2;
		MaxStartingGravestoneSpawnCol = 9;
		MaxStartingGravestoneSpawnColOffsetPerLevel = -0.5f;
		MinEndingGravestoneSpawnCol = 9;
		MaxEndingGravestoneSpawnCol = 9;
		MaxEndingGravestoneSpawnColOffsetPerLevel = 0.0f;
	}
	
	uint8 MinGravestoneCount;
	float BaseGravestoneCountPerLevel;
	uint8 MaxGeneratedGravestones;
	uint8 MinStartingGravestoneSpawnCol;
	uint8 MaxStartingGravestoneSpawnCol;
	float MaxStartingGravestoneSpawnColOffsetPerLevel;
	uint8 MinEndingGravestoneSpawnCol;
	uint8 MaxEndingGravestoneSpawnCol;
	float MaxEndingGravestoneSpawnColOffsetPerLevel;
};

struct MinecartSetupData
{
	MinecartSetupData()
	{
		BaseMinecartCount = 1;
		BaseMinecartCountPerLevel = 0.5f;
		MaxGeneratedMinecarts = 7;
	}

	uint8						BaseMinecartCount;
	float						BaseMinecartCountPerLevel;
	uint8						MaxGeneratedMinecarts;
	std::vector<std::string>	Layouts;
	
};

struct EgyptSetupData
{
	EgyptSetupData()
	{
		BaseSandstormCount = 0;
		BaseSandstormCountPerLevel = 0.5f;
		MaxSandstormsPerFlagWave = 4.0f;
		BaseSandstormZombiesCount = 1;
		BaseSandstormZombiesCountPerLevel = 1.0f;
		MaxSandstormZombies = 20;
		MinStartingSandstormSpawnCol = 2;
		MaxStartingSandstormSpawnCol = 9;
		MaxStartingSandstormSpawnColOffsetPerLevel = -0.5f;
		MinEndingSandstormSpawnCol = 5;
		MaxEndingSandstormSpawnCol = 9;
		MaxEndingSandstormSpawnColOffsetPerLevel = -0.2f;
		BaseSandstormStartWave = 3;
	}
	uint8 BaseSandstormCount;
	float BaseSandstormCountPerLevel;
	float MaxSandstormsPerFlagWave;
	uint8 BaseSandstormZombiesCount;
	float BaseSandstormZombiesCountPerLevel;
	uint8 MaxSandstormZombies;
	uint8 MinStartingSandstormSpawnCol;
	uint8 MaxStartingSandstormSpawnCol;
	float MaxStartingSandstormSpawnColOffsetPerLevel;
	uint8 MinEndingSandstormSpawnCol;
	uint8 MaxEndingSandstormSpawnCol;
	float MaxEndingSandstormSpawnColOffsetPerLevel;
	uint8 BaseSandstormStartWave;
	 
	GravestoneSetupData			GravestoneData;
	std::vector<std::string>	BlackList;
	
};

struct PirateSetupData
{
	PirateSetupData()
	{
		BasePartyCount = 0;
		BasePartyCountPerLevel = 0.5f;
		BasePartyZombiesCount = 1;
		BasePartyZombiesCountPerLevel = 0.5f;
		MaxPartyZombies = 10;
		MaxPartyCount = 8;
		BasePartyStartWave = 3;
	}
	uint8 BasePartyCount;
	float BasePartyCountPerLevel;
	uint8 BasePartyZombiesCount;
	float BasePartyZombiesCountPerLevel;
	uint8 MaxPartyZombies;
	uint8 MaxPartyCount;
	uint8 BasePartyStartWave;
	
	std::vector<std::string>	PlankLayouts;
	std::vector<std::string>	BlackList;
};

struct CowboySetupData
{
	MinecartSetupData			MinecartData;
	std::vector<std::string>	BlackList;
};


enum EventType
{
	EVENTTYPE_NONE,
	EVENTTYPE_SANDSTORM,
	EVENTTYPE_RAIDINGPARTY,
	EVENTTYPE_SPIDERRAIN
};

enum RowSpawnType
{
	ROWSPAWN_ROW1,
	ROWSPAWN_ROW2,
	ROWSPAWN_ROW3,
	ROWSPAWN_ROW4,
	ROWSPAWN_ROW5,
	ROWSPAWN_ROW6,
	ROWSPAWN_RANDOM,
	ROWSPAWN_PREVIOUS,
};

class BlackHole : public GameObject
{
public:
	RT_CLASS_DEFINE(BlackHole, GameObject, RtClass);

	BlackHole();
	virtual ~BlackHole(){}

	void dragPlantsToblackHoleDirection(int i_colNumPlantIsDragged, const SexyVector2& i_blackHolePosition);
	void setPlantingStatus(bool isDisabled) const;
	void SetColNumToDragPlants(int colNumToDragPlants){ m_colNumToDragPlants = colNumToDragPlants; }
	void InitBlackHoleEffectPam(std::string pam);

protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;

	void onBlackHoleInAnimCompleted(StandaloneEffect *i_effect);
	void onBlackHoleAbsorbAnimCompleted(StandaloneEffect *i_effect);
	void onBlackHoleOutAnimCompleted(StandaloneEffect *i_effect);

private:
	RtWeakPtr<Effect_PopAnim> m_blackHoleEffect;

	int m_colNumToDragPlants;
	SexyVector2 m_position;
};
typedef RtWeakPtr<BlackHole> BlackHolePtr;

class ZombiePicker
{
public:
	int m_zombieCount;
	int m_zombiePoints;
	std::map<ZombieTypePtr, int> m_zombieTypeCount;
	std::map<ZombieTypePtr, int> m_allWavesZombieTypeCount;

	void Init();
	void InitForWave();
};

class ZombiePoolItem
{
public:
	ZombiePoolItem();
	~ZombiePoolItem() {};

	int					m_zombieCost;
	int					m_zombieWeight;
	bool				m_zombieOverridden;
	ZombieTypePtr		m_zombieType;
};

class WaveSpawnItem
{
public:
	WaveSpawnItem();
	~WaveSpawnItem() {};

	RowSpawnType		m_rowInfo;
	bool				m_hasPlantfood;
	Loot 				m_loot;
	std::string			m_presentType;
	int					m_level;
    
    int                 m_rise_x;
	int                 m_rise_y;
    
    int                 m_sunDrop;
    int                 m_besiegeHit;
    float               m_zombieRate;
    float               m_zombieScale;
    
    pvztime_t           m_targetValidTime;
	
	ZombieTypePtr		m_zombieType;
};

struct EventZombieData
{

public:

	ZombieTypePtr	m_zombieTypePtr;
	int				m_row;
	int				m_column;
	bool			m_active;
	bool			m_hasPlantfood;
};

class EventZombieWaveData
{

public:
	
	EventZombieWaveData()
	{
		m_eventType = EVENTTYPE_NONE;
		m_count = 0;
		m_timerInterval = 0;
		m_timerEndTime = 0;
		m_eventZombieDataIndex = 0;
		m_eventZombieFreeIndex = 0;
		m_eventZombieData.clear();
	}

	void							ZombieAdd(ZombieTypePtr i_zombieType, int i_spawnInRow, int i_spawnInColumn, bool i_hasPlantfood);
	void							ZombieClear();
	void							ZombieSpawn(class Board* i_board, int spawnCount = 1);
	
	EventType						m_eventType;
	int								m_count;
	pvztime_t						m_timerInterval;
	pvztime_t						m_timerEndTime;
	std::vector<EventZombieData>	m_eventZombieData;
	int								m_eventZombieDataIndex;
	int								m_eventZombieFreeIndex;
	
};

typedef std::pair<ZombieTypePtr, bool> ZombiePtrBoolPair;
typedef std::pair<ZombieTypePtr, std::vector<ZombiePoolItem> > ZombiePtrPoolItemVectorPair;

class WaveGenerator: public RtObject
{
	RT_CLASS_DEFINE(WaveGenerator, RtObject, RtClass);
	
public:

	WaveGenerator();
	virtual ~WaveGenerator() {}

	// Public Interface (Inheritable)
	
	// Public Interface (Core)
	
	void						Initialize(const WaveGeneratorProperties* i_properties);
	void						InitZombieWaves(LootConfigPtr i_lootConfig);
	void						InitZombieWavesForCurrentLevel();
	void						InitDangerRoomZombieWavesForCurrentLevel();
	void						InitZombieSpawnForWaves();

	bool						CanZombieSpawnOnLevel(ZombieTypePtr i_zombieType);
	
	int							GetFlagWavesTriggered(int i_waveNumber);
	int							GetTotalFlagWaves();
	const WaveDefinition*	GetWaveDefinition(int i_waveNum);
	int							GetNumberZombiesInWave(int i_waveIndex);
	int							GetTotalZombiesHealthInWave(int i_waveIndex);

	inline int					GetNumWavesPerFlag() const;
	inline int					GetCurrentWave() const;
	inline int					GetNumWaves() const;
	inline pvztime_t			GetHugeWaveTime() const;
	inline pvztime_t			GetZombieWaveSpawnTime() const;
	inline pvztime_t			GetZombieWaveStartTime() const;
	inline int					GetZombieHealthToNextWave() const;
	inline int					GetZombieHealthWaveStart() const;
	inline ZombieTypePtr		GetZombieTypeInWaveByIndex(const int i_waveIndex, const int i_index);
	inline int					GetZombieLevelInWaveByIndex(const int i_waveIndex, const int i_index);
	inline int					GetDangerRoomLevel() const;

	inline const WaveGeneratorProperties* GetProps() const;

	inline void					SetZombieWaveSpawningPaused(const bool i_isPaused);
	inline void					SetHugeWaveTime(const pvztime_t i_time);
	inline void					SetDangerRoomLevel(const int i_levelNumber);
    
    inline void					SetIsNextWave();    //PVZ2_CHINESE Next_Wave

	inline bool					IsZombieWaveSpawningPaused() const;

	bool						IsFlagWave(int i_waveNumber);
	void						VerifyZombieWaveDistribution();

	int							PickRowForNewZombie(ZombieTypePtr i_zombieType);
	ZombieTypePtr				PickZombieType(int i_zombiePoints, int i_waveIndex, bool i_spawnPlantfood);
	void						PickZombieWaves();
	void						PutInMissingZombies(int i_waveNumber, ZombiePicker *i_zombiePicker);
	void						PutZombieInWave(ZombieTypePtr zombieType, int waveNumber, ZombiePicker *zombiePicker, bool zombieHasPlantfood = false, RowSpawnType i_row = ROWSPAWN_RANDOM, int level = 1, int i_x = 0, int i_y = 0, pvztime_t i_targetValidTime = 1.5f, int i_sunDrop = 0, float i_rate = 0.f, float i_scale = 1.f, int i_hit = 1);
	void						SpawnWave();
	void						SpawnZombieWave();
	void						SpawnZombiesFromSandStorm(const WaveEventData* i_eventData);
	void						SpawnZombiesFromRaidingParty(const WaveEventData* i_eventData);
	void						SpawnZombiesFromEvent(const WaveEventData* i_eventData, EventType i_eventType, int i_colStart, int i_colEnd, bool useUniqueRows, ZombieTypePtr i_zombieType, bool i_zombiesCanHavePlantfood);

	void						PauseNextWave(bool i_paused);
	void						SpawnNextWaveIn(pvztime_t i_delay);
	
	void						OnLevelStarted();
	void						OnSandStormSpawned();
	void						OnSandStormDestroyed();

	void						Update();
	void						UpdateZombieSpawning();
	
	bool 						PreSerialize(const bool i_isReading);
	bool						PostSerialize(const bool i_isReading);
    
private:
	
	void updateLootStats(Loot i_loot);

	// Private Interface (Inheritable)

	// Private Interface (Core)
	
	void						nextWaveComing();
	void						addDefinedZombiesToWaves(int i_waveIndex, ZombiePicker* i_picker, int i_plantfoodLeft);
	void						assignLoot(LootConfigPtr i_lootConfig);
	WaveSpawnItem*				pickLootZombie(int i_pointPool, int *o_zombieCost);
	void						resetDataVectors();

	// Private Members (serialized)
	int							m_dangerRoomLevel;
	int							m_flagWaveInterval;
	int							m_activeSandStorms;

	int							m_zombieCurrency;
	int							m_zombieCurrencyIncrement;
	int							m_oldZombieCurrency;

	int							m_currentWave;
	int							m_numWaves;
	int							m_totalSpawnedWaves;
	
	pvztime_t					m_finalWaveSoundTime;
	pvztime_t					m_flagRaiseTime;
	pvztime_t					m_hugeWaveTime;
	pvztime_t					m_zombieWaveSpawnTime;
	pvztime_t					m_zombieWaveStartTime;
    
    pvztime_t					m_zombieWaveSpawnTimeInterval;  //PVZ2_CHINESE Next_Wave
	
	bool						m_playedHugeWaveSound;
	bool						m_zombieWaveSpawningPaused;
    bool                        m_isNextWave;                   //PVZ2_CHINESE Next_Wave
	
	int							m_spawnColStart;
	int							m_spawnColEnd;
	int							m_spawnCount;
	int							m_spawnWavesPerEvent;
	int							m_eventTimeSpread;
	
	int							m_zombieHealthWaveStart;
	int							m_zombieHealthToNextWave;
	int							m_plantfoodToSpawnCount;

	std::vector<std::vector<WaveSpawnItem> >	m_zombiesInWave; //[MAX_ZOMBIE_WAVES][MAX_ZOMBIES_IN_WAVE];
	std::vector<uint8>							m_eventZombiesSpawnDuringWave; //[MAX_ZOMBIE_WAVES];
	std::vector<EventZombieWaveData>			m_eventZombieWaveData; //[MAX_EVENT_ZOMBIE_SPAWN_WAVES];
	
	std::string					m_waveRNGSerializeString;
	std::string					m_dangerRNGSerializeString;
	
	std::vector<ZombiePtrPoolItemVectorPair> m_zombieInWaveZombiePoolSerialized;
	std::vector<ZombiePtrBoolPair> m_zombiesInLevelSerialized;

	// Private Members (not serialized)

	// Built after serialization, no need to serialize
	MTRand						m_waveRNG;
	MTRand						m_dangerRNG;

	//RtWeakPtr<DangerRoomPropertySheet>	m_dangerRoomPropsPtr;
	
	// MF - While these are not serialized in their current states, there are serialized
	// std::vector versions of the maps and strings for the MTRand so that they will
	// function properly

	std::map<ZombieTypePtr, std::vector<ZombiePoolItem> > m_zombieInWaveZombiePool;
	std::map<ZombieTypePtr, bool> m_zombiesInLevel;
	
	const WaveGeneratorProperties* m_properties;

	BlackHolePtr	m_blackHole;
	bool			m_hasWaitedAllZombiesDie;
};

namespace Message
{
	void NewWaveStarting(int i_waveIndex, const WaveDefinition* i_currentDefinition);
	void FlagWaveTriggered(int i_flagsTriggered);
	void ProgressMeterSetFlagCount(int i_flagCount);
	void SetMoonWaveNum(int i_moon_wave);
	void SetTotalWaveCount(int i_total_wave);
	void HugeWave();
	void FinalWave();
	void WaveStarted(int i_wave, WaveType::WaveType i_type, bool i_isFinal);
	void WaveEnded(int i_wave, WaveType::WaveType i_type, bool i_isFinal);
	void HugeWaveComing(bool i_isFinal, int i_wave);
    void WaveStartCreatZombieEnd();
}

inline void WaveGenerator::SetDangerRoomLevel(const int i_levelNumber)
{
	m_dangerRoomLevel = i_levelNumber;
}

inline int WaveGenerator::GetDangerRoomLevel() const
{
	return m_dangerRoomLevel;
}

inline const WaveGeneratorProperties* WaveGenerator::GetProps() const
{
	return m_properties;
}

inline pvztime_t WaveGenerator::GetHugeWaveTime() const
{
	return m_hugeWaveTime;
}

inline void WaveGenerator::SetHugeWaveTime(const pvztime_t i_time)
{
	m_hugeWaveTime = i_time;
}

inline bool WaveGenerator::IsZombieWaveSpawningPaused() const
{
	return m_zombieWaveSpawningPaused;
}

inline void WaveGenerator::SetZombieWaveSpawningPaused(const bool i_isPaused)
{
	m_zombieWaveSpawningPaused = i_isPaused;
}

//PVZ2_CHINESE_START Next_Wave
inline void	WaveGenerator::SetIsNextWave()
{
    m_isNextWave = true;
}
//PVZ2_CHINESE_END

inline int WaveGenerator::GetNumWavesPerFlag() const
{
	return m_flagWaveInterval;
}

inline int WaveGenerator::GetCurrentWave() const
{
	return m_currentWave;
}

inline int WaveGenerator::GetNumWaves() const
{
	return m_numWaves;
}

inline pvztime_t WaveGenerator::GetZombieWaveSpawnTime() const
{
	return m_zombieWaveSpawnTime;
}

inline pvztime_t WaveGenerator::GetZombieWaveStartTime() const
{
	return m_zombieWaveStartTime;
}

inline int WaveGenerator::GetZombieHealthToNextWave() const
{
	return m_zombieHealthToNextWave;
}

inline int WaveGenerator::GetZombieHealthWaveStart() const
{
	return m_zombieHealthWaveStart;
}

inline ZombieTypePtr WaveGenerator::GetZombieTypeInWaveByIndex(const int i_waveIndex, const int i_index)
{
	return m_zombiesInWave[i_waveIndex][i_index].m_zombieType;
}

inline int WaveGenerator::GetZombieLevelInWaveByIndex(const int i_waveIndex, const int i_index)
{
	return m_zombiesInWave[i_waveIndex][i_index].m_level;
}

#endif // __WAVEGENERATOR_H__



