//
//  DangerRoomModule.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 3/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_DangerRoomModule_h
#define PlantsVersusZombies2_DangerRoomModule_h

#include <string>
#include <vector>

//#include "BoundedLine.h"
#include "LevelModule.h"
#include "PVZTypes.h"
#include "PlatformAutodetect.h"
#include "PlayerInfo.h"
#include "PropertySheetBase.h"
#include "RtDb.h"
#include "RtObject.h"
#include "dtypes.h"
#include "MacroStateMachine.h"
#include "StateMachine.h"
#include "ZombiePropertySheet.h"
#include "NetworkData.h"

class DangerRoomLevelDesigner;
namespace Sexy {
class MTRand;
}  // namespace Sexy

struct PlantFoodSetupData
{
	PlantFoodSetupData()
	{
		MinLevel = 1;
		MinPlantfoodPerFlagWave = 2;
		MaxPlantfoodPerFlagWave = 4;
	}
	
	uint8 MinLevel;
	uint8 MinPlantfoodPerFlagWave;
	uint8 MaxPlantfoodPerFlagWave;
};

struct FlagWaveSetupData
{
	FlagWaveSetupData()
	{
		MinLevel = 1;
		FlagCount = 1;
		MinWavesPerFlag = 12.0f;
		MaxWavesPerFlag = 12.0f;
	}
	
	uint8 MinLevel;
	uint8 FlagCount;
	float MinWavesPerFlag;
	float MaxWavesPerFlag;
};

struct DangerRoomLevelData
{
    DangerRoomLevelData()
	{
		MaxStagesPerLevel = 30;
        BonusRate = 1.0f;
        LevelName = "";
	}
    
    int32 MaxStagesPerLevel;
    std::vector<int32> StonePerLevel;
    float BonusRate;
    std::string LevelName;
};

// Rank details and rewards
struct DangerRoomRankData
{
    DangerRoomRankData()
    {
        HighestRank = 0;
        LowestRank = 0;
        RewardType = "";
        RewardValue = 0;
    }
    
    
    int HighestRank;
    int LowestRank;
    std::string RewardType;
    int RewardValue;
};

// Title details and rewards
struct DangerRoomTitleData
{
    DangerRoomTitleData()
    {
        HighestScore = 0;
        LowestScore = 0;
        TitleText = "";
        RewardType = "";
        RewardValue = 0;
    }    
    
    int HighestScore;
    int LowestScore;
    std::string TitleText;
    std::string RewardType;
    int RewardValue;
};

struct ZombieLevelPoolData
{
	ZombieLevelPoolData()
	{
		MinSpawnLevel = 0;

		MaxSpawnLevel = 0;
	}

	int MinSpawnLevel;

	int MaxSpawnLevel;

	ZombieTypePtr ZombieType;
};

class WorldSpecificDangerRoomProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(WorldSpecificDangerRoomProperties, PropertySheetBase, RtClass);
	
	std::vector<std::string>	StartingPlants;
    std::vector<std::string>	BlackList;
};

class DangerRoomPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(DangerRoomPropertySheet, PropertySheetBase, RtClass);
    void Copy(const DangerRoomPropertySheet& src);
    void CalcZombieLevel(int stageLevel, int& min, int& max, float& maxProbability) const;

	DangerRoomPropertySheet()
	{
		AssignMinPlantfoodPerFlagWave = 1;
		LevelsPerCheckpoint = 4;
		StartingLives = 3;
		MaxPlantfoodPurchases = 1;
		MaxPowerupPurchases = 1;

		RewardSmallMowerWeight = 20;
		RewardSmallSunWeight = 10;
		RewardSmallPlantfoodWeight = 5;
		
		CashOutRanks.clear();
		CashOutPerLevelAfterMax = 1000;
		
		ExtraCardCost = 1000;
        
        LifeCost.clear();
        
        MaxLife = 0;
        
        MaxBuyTime = 0;
        
        DangerRoomName = "";
        
        RankDisplayValue = 0;

        BaseScorePerLevel = 0;

        //MaxStagesPerLevel = 30;
	}
	
	std::vector<FlagWaveSetupData>	FlagWaveSetupList;
	std::vector<PlantFoodSetupData> PlantfoodSetupList;
	uint8							AssignMinPlantfoodPerFlagWave;
	uint8							LevelsPerCheckpoint;
	uint16							StartingLives;
	uint16							ExtraCardCost;
	int8							MaxPlantfoodPurchases;
	int8							MaxPowerupPurchases;
	int32							RewardSmallMowerWeight;
	int32							RewardSmallSunWeight;
	int32							RewardSmallPlantfoodWeight;
	int32							RewardPowerupWizardFingerWeight;
	int32							RewardPowerupFlickWeight;
	int32							RewardPowerupSnowballWeight;
	
	std::vector<uint16>				CashOutRanks;
	uint16							CashOutPerLevelAfterMax;
    //int32                           MaxStagesPerLevel;
    //std::vector<int32>              MaxStagesPerLevel;
    std::vector<DangerRoomLevelData> LevelDatas;
    std::vector<DangerRoomRankData> RankDatas;
    std::vector<DangerRoomTitleData> TitleDatas;
    std::vector<ZombieLevelStat>    ZombieLevelStats;
    std::vector<int32>              LifeCost;
    std::vector<int32>              PlantPacketStart;
    std::vector<int32>              PlantPacketLimit;
    std::vector<int32>              PlantPacketAddEachLevel;
    int                             MaxLife;
    int                             MaxBuyTime;
    std::string                     DangerRoomName;
    int								RankDisplayValue;

    int								BaseScorePerLevel;
    int                             MinWaveCount = 6;
    int                             MaxWaveCount = 15;
    int                             WaveAddEach  = 1;
    int                             WaveAddInterval = 5;
    
    int                             MinFlagWaveCount = 1;
    int                             MaxFlagWaveCount = 3;
    int                             MinLevelFlagWaveAdd = 10;
    float                           ZombieLevelBase = 0.9f;
    float                           ZombieLevelAdd = 0.1f;
    int                             ZombieTypeCount = 4;
    int                             BigZombieSureExistLevel = 50;
    int                             LeaderMinWaveCost = 100;
    float                           LeaderProbability = 0.4f;
    float                           LeaderStrengthenRate = 2.0f;
    float                           WealthGodProbability = 0.4f;
    int                             SunLimit   = 10000;
    int                             SunAddBase = 100;
    int                             SunAddEachLevel = 10;
    int                             SunAddBossBase  = 300;
    int                             SunAddBossEach  = 300;
    int                             BossInterval = 5;
    float                           BossHpBaseFactor = 0.2f;
    float                           BossHpAddFactor = 1.0f;
    int                             StartingPoints = 100;
    int                          	BasePointIncrementPerWave = 30;
    int                          	BasePointIncrementPerLevel = 5;
    PlantRestrictionSet             PlantStoredType;
    int								MaxSelectedPlant = 80;
};

STATE_ENUM_BASE_BEGIN(DangerRoomState)
DRS_CardSelect,
DRS_Ready,
STATE_ENUM_END(DangerRoomState);

class DangerRoomModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(DangerRoomModule, LevelModule, RtClass);

	DangerRoomModule();
	virtual ~DangerRoomModule();

	static const DangerRoomPropertySheet* GetDangerRoomPropertySheet();
	static RtWeakPtr<WorldSpecificDangerRoomProperties> GetWorldSpecificPropertySheetByWorldName(const std::string& i_worldName);
    static std::string GetBossLevel(const std::string& normalLevel);
    static void StartDangerRoomLevel(const std::string& world, bool i_training = false);
    static int CalcSunAdd(int level);
    static int CalcSunAdd(int startLevel, int SkipLevelCount);
    static void AddPacketCount(int SkipLevel);
    static std::string GetLevelName(const std::string& world, int level);
	const RtWeakPtr<WorldSpecificDangerRoomProperties> GetWorldSpecificPropertySheet() const;
	
	DangerRoomState GetState();
    void SkipLevel(int count);
    void OnBoostEnd(void);

	// Public Interface (Inheritable)

	// Public Interface (Core)
	
protected:
	
	// Protected Interface (Inheritable)

    virtual void initializeModule() override;
	virtual void postInitialize() override;
    virtual void registerForEvents() override;

	// Protected Interface (Core)
	
	DECLARE_FSM_HANDLER_BASE(DangerRoomState);
    
protected:
    void onNetworkError(int erroId, const std::string& requestID);
    
private:
	
	// Private Interface (Inheritable)

	// Private Interface (Core)
	void onLoadComplete();
	void onGameplayStarted();
	void onGameplayEnded();
	void onLevelEnded();

	void onMowerTriggered(class LawnMower* i_mower);
	void onMowerCreated(class LawnMower* i_mower);
    void onPlantAdded(class Plant* i_plant);
    void onPlantfoodUsed(class PlantGroup* plant);
    void onLaunchCuke(bool success, int i_gemCost, int freeGem);
    void onDangerRoomEnd(int result, const class S2C_DangerRoomEndLevel* data);
	void setupMowerInformation();

	void checkInvalidPlants();
	void initGamePlay();
    void initStoredPlants(DangerRoomInfo& i_info);
    int GetBossStage();
    int GetBossRetreatColumn();
    int GetPlantFoodBuyCount();
    DangerRoomNewPlantInfos StoredPlantInfos();
    bool CheckCheating(const DangerRoomNewPlantInfos& infos);

    void Update();

	// Private members (serialized)

	DangerRoomInfo		m_cachedDangerRoomInfo;
	std::vector<uint8>	m_lawnMowerInRow;
    S2C_DangerRoomConsumeData m_consume;
	DECLARE_FSM_STATE_VALUE(DangerRoomState);

	pvztime_t m_nextRequestTime;
	int m_requestCount;
	bool m_hasWon;
	int m_waveNum;
	bool m_cheat;
};

class DangerRoomModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(DangerRoomModuleProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return DangerRoomModule::StaticGetClass();
	}
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	RtWeakPtr<WorldSpecificDangerRoomProperties> WorldSpecificProperties;
	std::vector<RtWeakPtr<DangerRoomLevelDesigner> > LevelDesigners;
};

namespace Message
{
    void DangerRoomLevelEnded(const DangerRoomInfo& i_dangerRoomInfo);
    void DangerRoomSkipLevel(int i_skipLevel);
    void DangerRoomBoostEnd();
}

#endif
