/*
 * CustomLevelConfig.h
 *
 *  Created on: 2021-11-23
 *      Author: admin
 */

#ifndef CUSTOMLEVELCONFIG_H_
#define CUSTOMLEVELCONFIG_H_

#include "PropertySheetBase.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "BoardConstants.h"
#include "PowerTileSubsystem.h"

static const int CUSTOM_LEVEL_MAX_WAVE = 10;
static const int CUSTOM_LEVEL_MAX_ZOMBIE_PER_COL = 3;
static const int CUSTOM_LEVEL_MAX_ZOMBIE_PER_ROW = 5;
static const int CUSTOM_LEVEL_MAX_ZOMBIE_PER_WAVE = CUSTOM_LEVEL_MAX_ZOMBIE_PER_COL * CUSTOM_LEVEL_MAX_ZOMBIE_PER_ROW;
static const int CUSTOM_LEVEL_MAX_SANDSTORM_ZOMBIE = 8;
static const int CUSTOM_LEVEL_MAX_SEED_PACKETS = 8;
static const int CUSTOM_LEVEL_MAX_ZOMBIE_SEED_PACKETS = 8;

enum ViewLevelType
{
	Most_Played,
	Most_Likes,
	My_Favourite,
	Guess_Like,
	Search,
};

enum ViewRankType
{
	Total_Rank,
	Monthly_Rank,
	Weekly_Rank
};

struct DefaultWaveConfig
{
	DefaultWaveConfig()
	: ZombieTypeName("")
	, Weight(5)
	{

	}

	inline bool operator==(const DefaultWaveConfig& p) const
	{
		return ((p.ZombieTypeName == ZombieTypeName) && (p.Weight == Weight));
	}

	inline bool operator!=(const DefaultWaveConfig& p) const
	{
		return ((p.ZombieTypeName != ZombieTypeName) || (p.Weight != Weight));
	}

	std::string ZombieTypeName;
	int Weight;
};

struct DefaultWave
{
	DefaultWave()
	: PickCount(0)
	{

	}

	int PickCount;
	std::vector<DefaultWaveConfig> Configs;
};

struct ConstraintConfig
{
	std::map<std::string, std::vector<std::string>> StringMaps;
	std::map<std::string, float> ValueMaps;
};

struct ModuleConfig
{
	std::string StageModule;
	std::string LootModule;
	std::vector<std::string> DefaultModules;
	std::string World;
	std::vector<std::string> DefaultZombieList;
	std::vector<DefaultWave> DefaultWaveList;
};

struct WaveEventConfig
{
	std::map<std::string, float> ValueMaps;
	std::map<std::string, std::string> StringMaps;
};

class CustomLevelConfig : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CustomLevelConfig, PropertySheetBase, RtClass);

public:
	float GetCommonConfigValue(const std::string& i_key, float i_default) const;
	const ModuleConfig* GetDefaultModuleConfigByWorld(const std::string& i_world) const;

	template <typename T>
	T GetWaveEventConfigValue(const std::string& i_type, const std::string& i_key, T i_default) const;

public:
	std::map<std::string, float> CommonConfigs;
	std::map<std::string, ModuleConfig> ModuleConfigs;
	std::map<std::string, WaveEventConfig> WaveEventConfigs;

private:
	template <typename T>
	T GetEventConfigValue(const WaveEventConfig& i_config, const std::string& i_key, T i_default) const;

	template <typename T>
	T GetValue(const std::string& i_key, const std::map<std::string, T>& i_map, T i_default) const;

	const WaveEventConfig& GetWaveEventConfigByType(const std::string& i_type) const;
	float GetEventConfigValue(const WaveEventConfig& i_config, const std::string& i_key, float i_default) const;
	std::string GetEventConfigValue(const WaveEventConfig& i_config, const std::string& i_key, std::string i_default) const;
};

template <typename T>
T CustomLevelConfig::GetWaveEventConfigValue(const std::string& i_type, const std::string& i_key, T i_default) const
{
	return GetEventConfigValue(GetWaveEventConfigByType(i_type), i_key, i_default);
}

template <typename T>
T CustomLevelConfig::GetValue(const std::string& i_key, const std::map<std::string, T>& i_map, T i_default) const
{
	auto foundIter = i_map.find(i_key);
	if (foundIter != i_map.end())
	{
		return foundIter->second;
	}

	return i_default;
}

//***************Waves***********************
enum CustomWaveEventType
{
	CWET_None,
	CWET_SandStorm,
	CWET_Thunder,
	CWET_ZombiePotion
};

struct CustomWaveZombie
{
	CustomWaveZombie()
	: ZombieType("")
	, ZombiePlaceRow(-1)
	, Level(1)
	{

	}

	CustomWaveZombie(const std::string& i_typeName, int i_row, int i_level)
	: ZombieType(i_typeName)
	, ZombiePlaceRow(i_row)
	, Level(i_level)
	{

	}

	std::string ZombieType;
	int ZombiePlaceRow;
	int Level;
};

struct CustomWaveEventSandStorm
{
	CustomWaveEventSandStorm()
	: ColumnEnd(0)
	, ColumnStart(0)
	, Type(0)
	{
		Zombies.resize(CUSTOM_LEVEL_MAX_SANDSTORM_ZOMBIE);
	}

	int ColumnEnd;
	int ColumnStart;
	std::vector<std::string> Zombies;
	int Type;
};

struct CustomWaveEventSpiderRain
{
	CustomWaveEventSpiderRain()
	: ColumnEnd(0)
	, ColumnStart(0)
	, SpiderCount(0)
	, SpiderZombieName("")
	{

	}

	int ColumnEnd;
	int ColumnStart;
	int SpiderCount;
	std::string SpiderZombieName;
};

struct CustomWaveEventParachuteRain
{
	CustomWaveEventParachuteRain()
	: ColumnEnd(-1)
	{

	}

	int ColumnEnd;
};

struct CustomWaveEventBlackHole
{
	CustomWaveEventBlackHole()
	: ColNumPlantIsDragged(-1)
	{

	}

	int ColNumPlantIsDragged;
};

struct CustomWaveEventPortal
{
	CustomWaveEventPortal()
	: PortalColumn(0)
	, PortalRow(0)
	, PortalType("")
	{

	}

	int PortalColumn;
	int PortalRow;
	std::string PortalType;
};

struct CustomWaveEventDinoRun
{
	CustomWaveEventDinoRun()
	: DinoRow(-1)
	, TimeInterval(0)
	{

	}

	int DinoRow;
	float TimeInterval;
};

struct CustomWaveEventRaidingParty
{
	CustomWaveEventRaidingParty()
	: SwashbucklerCount(-1)
	{

	}

	int SwashbucklerCount;
};

struct CustomWaveWind
{
	CustomWaveWind(int i_row)
	: Row(i_row)
	{

	}

	CustomWaveWind()
	: Row(-1)
	{

	}

	int Row;
};

struct CustomWaveEventFrostWind
{
	CustomWaveEventFrostWind()
	{

	}

	std::vector<CustomWaveWind> Winds;
};

struct CustomWaveEvent
{
	CustomWaveEvent()
	{

	}

	CustomWaveEventSandStorm SandStorm;
	CustomWaveEventSpiderRain SpiderRain;
	CustomWaveEventPortal Portal;
	CustomWaveEventDinoRun DinoRun;
	CustomWaveEventRaidingParty RaidingParty;
	CustomWaveEventFrostWind FrostWind;
	CustomWaveEventParachuteRain ParachuteRain;
	CustomWaveEventBlackHole BlackHole;
};

struct CustomWave
{
	CustomWave()
	: EventType(CWET_None)
	, AdditionalPlantfood(0)
	{
		Zombies.resize(CUSTOM_LEVEL_MAX_ZOMBIE_PER_WAVE);
	}

	CustomWaveEventType EventType;
	std::vector<CustomWaveZombie> Zombies;
	int AdditionalPlantfood;
	CustomWaveEvent Event;
};

struct CustomWaveData
{
	CustomWaveData()
	: SpawnColEnd(0)
	, SpawnColStart(0)
	, WaveSpendingPointIncrement(0)
	, WaveSpendingPoints(0)
	{
		Waves.resize(CUSTOM_LEVEL_MAX_WAVE);
	}

	int SpawnColEnd;
	int SpawnColStart;
	int WaveSpendingPointIncrement;
	int WaveSpendingPoints;
	std::vector<CustomWave> Waves;
};
//***************Waves***********************


//***************SeedBanks***********************
enum CustomSeedBankType
{
	CustomSeedBank_Normal,
	CustomSeedBank_Conveyor
};

struct CustomConveyorData
{
	CustomConveyorData()
	: PlantTypeName("")
	, Weight(0)
	, Level(-1)
	{

	}

	CustomConveyorData(const std::string& i_plantTypeName, int i_weight, int i_level)
	: PlantTypeName(i_plantTypeName)
	, Weight(i_weight)
	, Level(i_level)
	{

	}

	std::string PlantTypeName;
	int Weight;
	int Level;
};

struct CustomSeedBankData
{
	CustomSeedBankData()
	: Type(CustomSeedBank_Normal)
	, GlobalLevel(-1)
	{
		PresetList.resize(CUSTOM_LEVEL_MAX_SEED_PACKETS);
		ConveyorList.resize(CUSTOM_LEVEL_MAX_SEED_PACKETS);
	}

	std::vector<std::string> BlackList;
	std::vector<std::string> PresetList;
	CustomSeedBankType Type;
	// conveyor
	std::vector<CustomConveyorData> ConveyorList;
	int GlobalLevel;
};
//***************SeedBanks***********************

//***************Challenges***********************

// LastStand
struct CustomChallengeLastStand
{
	CustomChallengeLastStand()
	: StartingPlantfood(-1)
	, StartingSun(0)
	{

	}

	int StartingPlantfood;
	int StartingSun;
};

// Molds
struct CustomChallengeMolds
{
	CustomChallengeMolds()
	{
		MoldGrids.resize(BoardConstants::NUMBER_OF_ROWS());
		for (size_t i = 0; i < MoldGrids.size(); i++)
		{
			MoldGrids[i].resize(BoardConstants::NUMBER_OF_COLUMNS());
		}
	}
	std::vector<std::vector<uint32> > MoldGrids;
};

// Tower Defend
struct TowerDefendTreeInfo
{
	TowerDefendTreeInfo()
	: Cost(0)
	, PlantName("")
	{

	}

	TowerDefendTreeInfo(int i_cost, const std::string& i_typeName)
	: Cost(i_cost)
	, PlantName(i_typeName)
	{

	}

	int Cost;
	std::string PlantName;
};

struct TowerDefendTree
{
	std::vector<TowerDefendTreeInfo> TreeInfos;
};

struct TowerDefendRoadInfo
{
	TowerDefendRoadInfo()
	: GridX(0)
	, GridY(0)
	, Img("")
	{

	}

	TowerDefendRoadInfo(int i_x, int i_y, const std::string& i_img)
	: GridX(i_x)
	, GridY(i_y)
	, Img(i_img)
	{

	}

	int GridX;
	int GridY;
	std::string Img;
};

struct TowerDefendWaveZombie
{
	TowerDefendWaveZombie()
	: ZombieType("")
	, ZombiePlaceRow(-1)
	{

	}

	TowerDefendWaveZombie(const std::string& i_typeName, int i_row)
	: ZombieType(i_typeName)
	, ZombiePlaceRow(i_row)
	{

	}

	std::string ZombieType;
	int ZombiePlaceRow;
};

struct TowerDefendWave
{
	TowerDefendWave()
	{
		Zombies.resize(CUSTOM_LEVEL_MAX_ZOMBIE_PER_WAVE);
	}

	std::vector<TowerDefendWaveZombie> Zombies;
};

struct TowerDefendWaveData
{
	TowerDefendWaveData()
	{
		Waves.resize(CUSTOM_LEVEL_MAX_WAVE);
	}

	std::vector<TowerDefendWave> Waves;
};

struct CustomChallengeTowerDefend
{
	CustomChallengeTowerDefend()
	{
		PresetPlantList.resize(CUSTOM_LEVEL_MAX_SEED_PACKETS);
	}

	std::vector<std::string> PresetPlantList;
	std::vector<TowerDefendTree> TreeList;
	TowerDefendWaveData WaveData;
	std::vector<TowerDefendRoadInfo> Roads;
};

struct SingleHandedPlantInfo
{
	SingleHandedPlantInfo()
	: KillNum(0)
	, PlantType("")
	{

	}

	SingleHandedPlantInfo(int i_killNum, const std::string& i_type)
	: KillNum(i_killNum)
	, PlantType(i_type)
	{

	}

	int KillNum;
	std::string PlantType;
};

struct SingleHandedWaveZombie
{
	SingleHandedWaveZombie()
	: ZombieType("")
	, ZombiePlaceRow(-1)
	{

	}

	SingleHandedWaveZombie(const std::string& i_typeName, int i_row)
	: ZombieType(i_typeName)
	, ZombiePlaceRow(i_row)
	{

	}

	std::string ZombieType;
	int ZombiePlaceRow;
};

struct SingleHandedWave
{
	SingleHandedWave()
	{
		HasPlantfood = false;
		Zombies.resize(CUSTOM_LEVEL_MAX_ZOMBIE_PER_WAVE);
	}

	std::vector<SingleHandedWaveZombie> Zombies;
	bool HasPlantfood;
};

struct SingleHandedWaveData
{
	SingleHandedWaveData()
	{
		Waves.resize(CUSTOM_LEVEL_MAX_WAVE);
	}

	std::vector<SingleHandedWave> Waves;
};

struct CustomChallengeSingleHanded
{
	CustomChallengeSingleHanded()
	: StartingPlantType("")
	{
		//PlantInfos.resize(CUSTOM_LEVEL_MAX_SEED_PACKETS - 1);
	}

	std::vector<SingleHandedPlantInfo> PlantInfos;
	SingleHandedWaveData WaveData;
	std::string StartingPlantType;
};

// Vase Breaker
enum VaseType
{
	VaseType_Plant,
	VaseType_Zombie
};

struct VaseBreakerVaseEntry
{
	VaseBreakerVaseEntry()
	: Type(VaseType_Plant)
	, TypeName("")
	, Count(0)
	{

	}

	VaseType Type;
	std::string TypeName;
	int Count;
};

struct CustomChallengeVaseBreaker
{
	CustomChallengeVaseBreaker()
	: MinColumnIndex(-1)
	, MaxColumnIndex(-1)
	{
		VaseInfos.resize(CUSTOM_LEVEL_MAX_SEED_PACKETS);
	}

	int MinColumnIndex;
	int MaxColumnIndex;
	std::vector<VaseBreakerVaseEntry> VaseInfos;
};

// Evil Dave
struct EvilDavePlantEntry
{
	EvilDavePlantEntry()
	: GridX(0)
	, GridY(0)
	, TypeName("")
	{

	}

	EvilDavePlantEntry(int i_x, int i_y, const std::string& i_typeName)
	: GridX(i_x)
	, GridY(i_y)
	, TypeName(i_typeName)
	{

	}

	int GridX;
	int GridY;
	std::string TypeName;
};

struct CustomChallengeEvilDave
{
	CustomChallengeEvilDave()
	: StartingSun(0)
	, PlantDistance(0)
	{
		ZombieInfos.resize(CUSTOM_LEVEL_MAX_ZOMBIE_SEED_PACKETS);
	}

	int StartingSun;
	float PlantDistance;
	std::vector<EvilDavePlantEntry> PlantEntries;
	std::vector<std::string> ZombieInfos;
};

// Statue Maze
struct StatueMazeMatrix
{
	StatueMazeMatrix()
	: ClockWise(true)
	, WaitTime(0)
	, RotateTime(0)
	{

	}

	StatueMazeMatrix(bool i_clockWise, float i_waitTime, float i_rorateTime)
	: ClockWise(i_clockWise)
	, WaitTime(i_waitTime)
	, RotateTime(i_rorateTime)
	{

	}

	bool ClockWise;
	float WaitTime;
	float RotateTime;
};

struct StatueMazeSet
{
	StatueMazeSet()
	: MatrixSize(0)
	, DisplayTime(0)
	, TargetNum(0)
	, BonusLife(0)
	{

	}

	StatueMazeSet(int i_matrixSize, int i_targetNum, float i_displayTime, int i_bounsLife)
	: MatrixSize(i_matrixSize)
	, DisplayTime(i_displayTime)
	, TargetNum(i_targetNum)
	, BonusLife(i_bounsLife)
	{

	}

	int MatrixSize;
	float DisplayTime;
	int TargetNum;
	int BonusLife;
	std::vector<StatueMazeMatrix> MatrixInfos;
};

struct CustomChallengeStatueMaze
{
	std::vector<StatueMazeSet> SetInfos;
};

struct CustomChallengeData
{
	CustomChallengeLastStand LastStand;
	CustomChallengeMolds Molds;
	CustomChallengeStatueMaze StatueMaze;
	CustomChallengeEvilDave EvilDave;
	CustomChallengeTowerDefend TowerDefend;
	CustomChallengeSingleHanded SingleHanded;
	CustomChallengeVaseBreaker VaseBreaker;
};

struct CustomChallenge
{
	CustomChallenge()
	: Description("")
	, DescriptiveName("")
	{

	}

	CustomChallenge(const std::string& i_description, const std::string& i_descriptiveName)
	: Description(i_description)
	, DescriptiveName(i_descriptiveName)
	{

	}

	bool HasAnyChallenge() const;
	bool HasLastStand() const;
	bool HasMolds() const;
	bool HasStatueMaze() const;
	bool HasEvilDave() const;
	bool HasTowerDefend() const;
	bool HasSingleHanded() const;
	bool HasVaseBreaker() const;

	std::string Description;
	std::string DescriptiveName;
	CustomChallengeData ChallengeData;
};
//***************Challenges***********************

//***************Elements***********************
// Rails
struct PlacementInfo
{
	PlacementInfo()
	: GridX(0)
	, GridY(0)
	, Level(0)
	, TypeName("")
	{

	}

	PlacementInfo(int i_x, int i_y, int i_level, const std::string& i_typeName)
	: GridX(i_x)
	, GridY(i_y)
	, Level(i_level)
	, TypeName(i_typeName)
	{

	}

	int GridX;
	int GridY;
	int Level;
	std::string TypeName;
};

struct RailCartInfo
{
	RailCartInfo()
	: Column(0)
	, Row(0)
	{

	}

	RailCartInfo(int i_col, int i_row)
	: Column(i_col)
	, Row(i_row)
	{

	}

	int Column;
	int Row;
};

struct RailInfo
{
	RailInfo()
	: Column(0)
	, RowEnd(0)
	, RowStart(0)
	{

	}

	RailInfo(int i_col, int i_rowEnd, int i_rowStart)
	: Column(i_col)
	, RowEnd(i_rowEnd)
	, RowStart(i_rowStart)
	{

	}

	int Column;
	int RowEnd;
	int RowStart;
};

struct CustomRailInfo
{
	CustomRailInfo()
	: RailcartType("railcart_cowboy")
	{

	}

	CustomRailInfo(const std::string& i_typeName)
	: RailcartType(i_typeName)
	{

	}

	std::string RailcartType;
	std::vector<RailCartInfo> RailCartInfos;
	std::vector<RailInfo> RailInfos;
};

struct CustomPowerTileInfo
{
	CustomPowerTileInfo()
	: Type(POWERTILE_Invalid)
	, GridX(0)
	, GridY(0)
	{

	}

	CustomPowerTileInfo(PowerTileClass i_type, int i_x, int i_y)
	: Type(i_type)
	, GridX(i_x)
	, GridY(i_y)
	{

	}

	PowerTileClass Type;
	int GridX;
	int GridY;
};

struct CustomLevelElements
{
	CustomLevelElements()
	{

	}

	std::vector<PlacementInfo> PlantInfos;
	std::vector<PlacementInfo> GridItemInfos;
	std::vector<PlacementInfo> ZombieInfos;
	CustomRailInfo RailInfo;
	std::vector<CustomPowerTileInfo> PowerTileInfos;
};

struct CustomLevelEncourage
{
	CustomLevelEncourage()
	:BuySunmoney(true),
	BuyPlantfood(true),
	BuyMower(true),
	IsEncourage(false)
	{

	}

	bool IsEncourage;
	bool BuySunmoney;
	bool BuyPlantfood;
	bool BuyMower;
};

//***************Elements***********************

//***************Level includes***********************
struct CustomLevelParams
{
	CustomLevelParams()
		: Title("")
		, Description("")
		, LevelNumber(0)
		, StartingSun(200)
	{}

	std::string Title;
	std::string Description;
	int LevelNumber;
	int StartingSun;
	CustomWaveData WaveData;
	CustomSeedBankData SeedBankData;
	CustomChallenge Challenge;
	CustomLevelElements Elements;
	CustomLevelEncourage Encourage;
};
//***************Level includes***********************

//***************Construct Data***********************
enum CustomLevelNetworkWorldType
{
	WorldType_Egypt,
	WorldType_Pirate,
	WorldType_Cowboy,
	WorldType_Kongfu,
	WorldType_Future,
	WorldType_Eightes,
	WorldType_Dark,
	WorldType_Beach,
	WorldType_Dino,
	WorldType_Iceage,
	WorldType_Lostcity,
	WorldType_Modern,
	WorldType_Steam,
	WorldType_Renai,
	WorldType_heain,
	WorldType_Statue,
	WorldType_EvilDave,
	WorldType_TowerDefend,
	WorldType_SingleHanded,
	WorldType_VaseBreaker,
	//WorldType_FairyTale,
	WorldType_Max,
};

struct CustomLevelWorldInfo
{
	CustomLevelWorldInfo()
	: World("")
	, Stage("")
	{

	}

	CustomLevelWorldInfo(const std::string& i_world, const std::string& i_stage)
	: World(i_world)
	, Stage(i_stage)
	{

	}

	std::string World;
	std::string Stage;
};

enum CustomLevelNetworkLevelMode
{
	LevelMode_Normal,
	LevelMode_Conveyor,
	LevelMode_LastStand,
	LevelMode_StatueMaze,
	LevelMode_CrazyBoss,
	LevelMode_TowerDefence,
	LevelMode_SingleHanded,
	LevelMode_VaseBreaker,
	LevelMode_Max,
};

struct CustomLevelWorldParams
{
	CustomLevelWorldParams()
	: World("egypt")
	, LevelID("")
	, NetworkLevelID(0)
	, NetworkLevelName("")
	, NetworkWorldType(WorldType_Egypt)
	, NetworkLevelMode(LevelMode_Normal)
	, NetworkEnableDownload(true)
	, NetworkAuthorName("")
	, NetworkAuthorHeadshotID(0)
	, NetworkUploadedTime("")
	, NetworkUpdatedTime("")
    , LevelIndex(0)
	, HasFinishedLevel(false)
    , HasUploaded(false)
    , LocalUpdatedTime(0)
	, PlayTime(0)
	{

	}

	// Levels
	std::string World;
	std::string LevelID;
	CustomLevelParams LevelParams;
	// Networks
	int NetworkLevelID;
	std::string NetworkLevelName;
	CustomLevelNetworkWorldType NetworkWorldType;
	CustomLevelNetworkLevelMode NetworkLevelMode;
	bool NetworkEnableDownload;
	std::string NetworkAuthorName;
	int NetworkAuthorHeadshotID;
	std::string NetworkUploadedTime;
	std::string NetworkUpdatedTime;
    int LevelIndex;
    bool HasFinishedLevel;
    bool HasUploaded;
    time_t LocalUpdatedTime;
    pvztime_t PlayTime;

};
//***************Construct Data***********************

//***************Local Preview Data***********************
struct CustomPreviewData
{
	CustomPreviewData()
	: LevelName("")
	, World("")
	, HasUploaded(false)
	, LevelMode(LevelMode_Normal)
	, LevelID(0)
	{

	}

	std::string LevelName;
	std::string World;
	bool HasUploaded;
	CustomLevelNetworkLevelMode LevelMode;
	int LevelID;
};
//***************Local Preview Data***********************

//***************Save/Load***********************
class CustomLevelData : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CustomLevelData, PropertySheetBase, RtClass);

public:
	CustomLevelWorldParams WorldParams;
};
//***************Save/Load***********************

#endif /* CUSTOMLEVELCONFIG_H_ */
