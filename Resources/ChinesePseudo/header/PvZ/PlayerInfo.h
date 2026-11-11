#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__


#include "SexyAppFramework/SexyAppBase.h"
#include "core.h"
#include "PVZTypes.h"
#include "WorldData.h"
#include "MagentoService.h"
#include "ZombieAlmanac.h"
#include "LawnKeyField.h"
//#include "CollectableSpring.h"
#include "PlantEnums.h"
#include "DangerRoomInfo.h"
//#include "PlantBoostMgr.h"
#include "PlantAccessoryMgr.h"
#include "PlantFamilyMgr.h"
#include "ProbabilitySet.h"
#include "ArenaInfo.h"
#include "StarConvertConfig.h"
//#include "ActivityManager.h"
#include "LocalSaveDataEnums.h"

#include <map>

#ifdef HOST_ANDROID
#include "ACNetworkData.h"
#endif

class ArcadeLastPlayData;
struct RichmanBattleEventSaveData;

struct ZombieWarning
{
	ZombieWarning()
	{
		Level = 0;
	}

	ZombieTypePtr Type;
	int Level;
	//bool IsWarned;
};

typedef std::vector<ZombieWarning> ZombieStoredMarks;

// PlayerInfo
// - PI is managed by the ProfileMgr, do not new or make copies of this class.
//

typedef int32 PlayerProfileIndex;
typedef unsigned int NameHash;
const PlayerProfileIndex INVALID_PLAYER_PROFILE_INDEX = 0;

#ifdef HOST_ANDROID
	const int g_purchase_gem_bomb = 306;
	const int g_purchase_gem_recharge = 98;
#else
	const int g_purchase_gem_bomb = 772;
	const int g_purchase_gem_recharge = 1;
#endif

const std::string g_reward_plant_type = "cherry_bomb";

enum DangerRoomLevelType
{
    DR_LEVEL_ONE,
    DR_LEVEL_TWO,
    DR_LEVEL_THREE,
    DR_LEVEL_FOUR,
    DR_LEVEL_ENDLESS,
    DR_LEVEL_COUNT,
};

enum GemReturnButtonState
{
    GMS_NoInfo = -1,
    GMS_Unavailable = 0,
    GMS_Available = 1,
    GMS_Obtained = 2,
};

enum eDayEvtRec
{
    eDayEvtRec_GemReturn    = 0x01,
    eDayEvtRec_SpringGift   = 0x02,
    eDayEvtRec_SpringGiftGet= 0x04,
};

enum eMonthlyCardType
{
	E_MC_MAKE_UP = 0x01,
	E_MC_CLASSICAL = 0x02,
	E_MC_SUPER = 0x04,
	E_MC_CHINA_MOBILE = 0x08,
};

struct AccessoryPiece
{
	AccessoryPiece()
	{
		Type     = "";
		PieceCount  = 0;
	}

	std::string Type;
	int PieceCount;
};

struct DailyAchievementRecord
{
    std::vector<int> targetFinished;
    std::string specificSku;
    int actId;
    int targetCount;
    
    DailyAchievementRecord()
    {
        specificSku = "";
        targetFinished.clear();
        actId = 0;
        targetCount = 0;
    }
};

struct BattleArrayComponent
{
    BattleArrayComponent()
    {
        BattleType = BattleArrayType_Default;
        BattleList.clear();
    }
    
    BattleArrayType BattleType;
    std::vector<int> BattleList;
};

struct ReconstructionComponent
{
	ReconstructionComponent()
	{
		ComponentType   = "";
		ComponentCount  = 0;
	}
    
	std::string ComponentType;
	int         ComponentCount;
};

enum eReconstructionType
{
    ReconstructionType_Cannon,
    ReconstructionType_Board
};

struct ReconstructionLevel
{
	ReconstructionLevel()
	{
		ReconstructionWorldName = "";
        CannonLevel             = 0;
        BoardLevel              = 0;
	}
    
	std::string ReconstructionWorldName;
	int         CannonLevel;
    int         BoardLevel;
};

struct SignRewardContent
{
    int32 itemId;
    int32 amount;
    SignRewardContent()
    {
        itemId = 0;
        amount = 0;
    }
};

struct PlantPieceRecord
{
    PlantPieceRecord()
    {
        PlantId     = -1;
        PieceCount  = 0;
    }
    
    int PlantId;
    int PieceCount;
};

struct RebateSingleRecord
{
    std::string strDate;
    std::string strPlantID;
};

struct PlantStarLevel
{
    int iCurrentPlantId;
    int iCurrentLevel;
    
    PlantStarLevel()
    {
        iCurrentPlantId = -1;
        iCurrentLevel = 0;
    }
};

struct ZombieStarLevel
{
	int iZombieId;
	int iCurrentLevel;

	ZombieStarLevel()
	{
		iZombieId = -1;
		iCurrentLevel = 0;
	}
};

struct OnlineEventInfo
{
	OnlineEventInfo();
	bool RefreshEventInfo();
    
#ifdef HOST_IPHONEOS
    int								    RefreshOnlineEventTime;
#else
    time_t								RefreshOnlineEventTime;
#endif
    
	LawnKeyField						TodayYetiLeftCount;		//How many times today can kill yeti
	LawnKeyField						TodayMiniGameLeftCount;	//How many times today can play minigame event
    
    LawnKeyField						TodayCrazyYetiLeftCount;
    LawnKeyField						TodayGargantuarCrisisLeftCount;
    LawnKeyField						ToadyDevilInvadeLeftCount;
    
    LawnKeyField                        yetiCountPerDay;
    LawnKeyField                        yetiCountPerDayVersion;
    bool                                ToturialPlayered;       //is the yeti toturial played before
    
    LawnKeyField                        SpringbossLeftCount;
    
    static const int32 yetiCount = 5;	//QZY changed: to make it compile on Android.
	static const int32 minigameCount = 2; //QZY changed: to make it compile on Android.
    static const int32 springFestivalCount = 3;
    static const int32 springFestivalDevilCount = 1;
};

struct PurchaseInfo
{
    PurchaseInfo(){
        receiptId = "";
        receipt = "";
        productId = "";
        objectId = 0;
    }
    std::string receiptId;
    std::string receipt;
    std::string productId;
    int objectId;
};

struct GameRankItem
{
    GameRankItem()
    {
        levelIndex = -1;
        star = -1;
        time = -1;
    }
    int levelIndex;
    int star;
    std::string formation;
    int time;
};

enum RechargeNode
{
	RECHARGE_DOUBLE_COIN = 2,
    RECHARGE_DOUBLE_LOTTERY = 6,
    RECHARGE_PLANT_PACKAGE = 10,
	RECHARGE_DOUBLE_SPEED = 20,
	RECHARGE_BOMB = 30
};

struct LevelScoreItem
{
    LevelScoreItem()
    {
        mark = 0;
        level_name = "";
    }
    
    int mark;
    std::string level_name;
};

struct PowerupRecord
{
	PowerupRecord()
	: Inventory(0)
	{}
	
	std::string Name;
	int Inventory;
};

struct ZombieGift
{
	std::string TypeName;
	std::string Sender;
};

struct PlantTrialCD
{
    std::string PlantName;
    time_t      CDTime;
};

struct BirthZRecord
{
    BirthZRecord() {}
    BirthZRecord(std::string& strd, int iCount)
    : iGetCount(iCount), strDay(strd) {}
    
    std::string strDay;
    int         iGetCount;
};

struct SavedWorldMapEventData
{
	SavedWorldMapEventData()
	: WorldId(0)
	, EventId(0) 
	, Status(EVENTSTATUS_UNDISCOVERED)
	, StarCompletion(0)
	, CompletionCount(0)
	, PlayCount(0)
	{}
	
	const std::string& GetName();

	// Serialized
	uint8 					WorldId;
	uint16					EventId;
	WorldMapEventStatus		Status;
	int						StarCompletion;
	int						CompletionCount;
	int 					PlayCount;
	
	bool operator==(SavedWorldMapEventData& i_compareTo)
	{
		return (WorldId == i_compareTo.WorldId) && (EventId == i_compareTo.EventId) && (i_compareTo.Status == Status) && (i_compareTo.StarCompletion == StarCompletion) && (i_compareTo.CompletionCount == CompletionCount) && (i_compareTo.PlayCount == PlayCount);
	}

private:
	// Not serialized
	std::string				m_name;
};

struct WorldEventCompletionData
{
    WorldEventCompletionData()
    : EventId(0)
    , PassHard(0)
    {}
    
    uint16 EventId;
    uint8 PassHard;
};

struct WorldCompletionData
{
    WorldCompletionData()
    : WorldId(0)
    , ReceivedWorldKey(false)
    {}
    
    uint8 WorldId;
    std::vector<WorldEventCompletionData> Events;
    bool ReceivedWorldKey;
};

template<typename T>
class IArcadeProgressData
{
public:
	virtual ~IArcadeProgressData() {}
	IArcadeProgressData()
	: IDHash(0)
	{}

	NameHash IDHash;

	virtual bool	IsEqual(const T& i_otherData) const = 0;
	virtual T		MakeDelta(const T& i_newData) const = 0;
};

class ArcadeLevelProgress : public IArcadeProgressData<ArcadeLevelProgress>
{
public:
	ArcadeLevelProgress()
	: Progress(0)
	, State(0)
	{}

	// Two uint32's to be filled out however you'd like
	// Use the ArcadeSaveDataEncoder to encapsulate reading and writing these values
	uint32 Progress;	// For endless mode, this contains both current wave and high score (bitpacked)
	uint32 State;

	bool				IsEqual(const ArcadeLevelProgress& i_otherLevel) const override;
	ArcadeLevelProgress	MakeDelta(const ArcadeLevelProgress& i_newLevel) const override;
};

class ArcadePackProgress : public IArcadeProgressData<ArcadePackProgress>
{
public:
	ArcadePackProgress() {}

	std::vector<ArcadeLevelProgress> LevelProgress;

	bool				IsEqual(const ArcadePackProgress& i_otherPack) const override;
	ArcadePackProgress	MakeDelta(const ArcadePackProgress& i_newPack) const override;
};

class PowerUpProgress : public IArcadeProgressData<PowerUpProgress>
{
public:
	PowerUpProgress()
	: Progress(0)
	{}

	// One uint32 indicating "upgrades" to the particular power-up, whether that's discounts or
	// additional power.  Yet to be determined, could be used differently per power-up.
	uint32 Progress;

	bool				IsEqual(const PowerUpProgress& i_otherPowerUp) const override;
	PowerUpProgress		MakeDelta(const PowerUpProgress& i_newPowerUp) const override;
};

class PowerUpCollectionProgress : public IArcadeProgressData<PowerUpCollectionProgress>
{
public:
	PowerUpCollectionProgress() {}

	std::vector<PowerUpProgress> UnlockedPowerups;

	bool						IsEqual(const PowerUpCollectionProgress& i_otherPack) const override;
	PowerUpCollectionProgress	MakeDelta(const PowerUpCollectionProgress& i_newPack) const override;
};

struct PresentRecord
{
	PresentRecord()
	{
		TimeAwarded = 0;
		TimeOpened = 0;
		Seed = 0;
	}
	
	std::string PresentTableName;
	uint32 Seed;
	uint32 TimeAwarded;
	uint32 TimeOpened;
};

struct WorldSpecificKeys
{
	std::string WorldName;
	KeyCurrency KeyCount;
};

struct FirstRechargeAwardData
{
    std::string sSku;
    bool        bHas;
    
    FirstRechargeAwardData()
    {
        sSku = "";
        bHas = false;
    }
};


struct TreasureYetiInfo
{
	TreasureYetiInfo()
	: LastSpawnTime(-1)
	, NextSpawnTime(-1)
	, WorldMapLocation("none")
	{}

	std::string WorldMapLocation;
	time_t LastSpawnTime;
	time_t NextSpawnTime;
	
	TreasureYetiInfo& operator=(const TreasureYetiInfo& theInfo)
	{
		WorldMapLocation = theInfo.WorldMapLocation;
		LastSpawnTime = theInfo.LastSpawnTime;
		NextSpawnTime = theInfo.NextSpawnTime;
		
		return *this;
	}
};

struct StoredDangerRoomEventData
{
    int  CurrentPeriod;
    int  ServerPeriod;
    int  RewardStartDate;
    int  RewardEndDate;
    bool IsPickedReward;
    bool HasResetDangerRoom;
    bool HasResetPickedReward;
    int  PreHighestScore;
    time_t	 LastPeriod;
    
    StoredDangerRoomEventData()
    {
        CurrentPeriod = 0;
        ServerPeriod = 0;
        RewardStartDate = 0;
        RewardEndDate = 0;
        IsPickedReward = false;
        HasResetDangerRoom = false;
        HasResetPickedReward = false;
        PreHighestScore = 0;
        LastPeriod = 0;
    }
};

// Training Room
struct DangerRoomTrainingRecord
{
	DangerRoomTrainingRecord()
	{
		WorldName = "";
		HighestLevel = 0;
	}

	std::string WorldName;
	int HighestLevel;
};
    
struct DangerRoomLifeData
{
    int CurrentLife;
    int BoughtTime;
    
    DangerRoomLifeData()
    {
        CurrentLife = 0;
        BoughtTime = 0;        
    }
};

struct PlayerFlagInfo
{
    bool flag;
    std::string flagType;
};

struct PlayerStorageData
{
    std::string DataName;
    int DataNumber = 0;
};

struct WorldCupInfo
{
    std::string worldName;
    bool starCupUnlocked;
    bool bossCupUnlocked;
    bool plantCupUnlocked;
    
    WorldCupInfo()
    {
        worldName = "";
        starCupUnlocked = false;
        bossCupUnlocked = false;
        plantCupUnlocked = false;
    }
};

struct BundleDisplay
{
    int bundleTypeId = 0;
    int objectId = 0;
    time_t expireTime = 0;
    int buyTimes = 0;
};

struct BundleQueueCondition
{
    std::vector<std::string> levelList;
    std::string condition = "";
    int bundleTypeId = 0;
};

struct NationalShopItem
{
	int objectId = 0;
	int buyTimes = 0;
};

struct FestivalShopItem
{
	int objectId = 0;
	int buyTimes = 0;
};

struct bundleItemInfo
{
	int itemId;
	int quantity;
};

struct PurchasedBundleInfo
{
	std::string sku;
	int index = 0;
	std::vector<bundleItemInfo> itemList;
};

enum FunnelEvent
{
	FUNNEL_Start = 0,					//Initialization value, not reported
	
	FUNNEL_GameInstalled = 1,			//1 Not Implemented
	FUNNEL_CreatedLoginName,			//2 MainMenu.cpp
	FUNNEL_PressesStart,				//3 MainMenu.cpp
	FUNNEL_DoesTutorial,				//4 TutorialLevel1.cpp
	FUNNEL_SkipsTutorial,				//5 TutorialLevel1.cpp
	
	FUNNEL_StartsModernDay1,			//6 TutorialLevel1.cpp
	FUNNEL_PlantsFirstPeashooter,		//7 TutorialLevel1.cpp
	FUNNEL_GrabsFirstSun,				//8 TutorialLevel1.cpp
	FUNNEL_WinsModernDay1,				//9 TutorialLevel1.cpp
	
	FUNNEL_PickupSunflower,				//10 VictoryOutro.cpp
	FUNNEL_SunflowerDialogContinue,		//11 VictoryOutro.cpp
	
	FUNNEL_StartsModernDay2,			//12 Tutorial2.cpp
	FUNNEL_PlantsFirstSunflower,		//13 Tutorial2.cpp
	FUNNEL_WinsModernDay2,				//14 Tutorial2.cpp
	
	FUNNEL_PickupWallnut,				//15 VictoryOutro.cpp
	FUNNEL_WallnutDialogContinue,		//16 VictoryOutro.cpp
	
	FUNNEL_StartsModernDay3,			//17 TutorialLevel3.cpp
	FUNNEL_TapsShovel,					//18 TutorialLevel3.cpp
	FUNNEL_ShovelsPeashooter,			//19 TutorialLevel3.cpp
	FUNNEL_WinsModernDay3,				//20 TutorialLevel3.cpp
	
	FUNNEL_PickupPotatoMine,			//21 VictoryOutro.cpp
	FUNNEL_PotatoMineDialogContinue,	//22 VictoryOutro.cpp
	
	FUNNEL_StartsModernDay4,			//23 TutorialLevel4.cpp
	FUNNEL_TapFirstCoin,				//24 PickupCollectableTutorialModule.cpp
	FUNNEL_WinsModernDay4,				//25 TutorialLevel4.cpp
	
	FUNNEL_PickupHotSauce,				//26 VictoryOutro.cpp
	
	FUNNEL_StartsEgyptDay1,				//27 EgyptStage.cpp
	FUNNEL_WinsEgyptDay1,				//28 EgyptStage.cpp
	
	FUNNEL_PickupMap,					//29 VictoryOutro.cpp
	
	FUNNEL_StartsEgyptDay2,				//30 EgyptStage.cpp
	FUNNEL_UsePlantFood,				//31 PlantfoodTutorialIntro.cpp
	FUNNEL_WinsEgyptDay2,				//32 EgyptStage.cpp
	
	FUNNEL_LastEvent = FUNNEL_WinsEgyptDay2, //So we know when we're done with the funnel.
	
	FUNNEL_Complete,					//Cap value, not reported
	
	FUNNEL_MAX = FUNNEL_Complete
};
	
typedef std::vector<SavedWorldMapEventData> MapEventList;

enum PlayerProfileVersion
{
	PVZ_BEGIN_ENUM(PLAYERPROFILEVER_),
	PLAYERPROFILEVER_Initial = 0,								// First rev of profiles used this version
	PLAYERPROFILEVER_AddedInitialPlantList = 1,					// Initial plant list must be added to any profile < this version
	PLAYERPROFILEVER_NewWorldMapAug16 = 2,						// New world map added. We nuke all previous profiles
	PLAYERPROFILEVER_AddedRandomSeed = 3,						// Added random seed, must generate a new one for all profiles
	PLAYERPROFILEVER_NewWorldMapDec21_2012 = 4,					// New world map added, we must nuke everything.
	PLAYERPROFILEVER_WorldMapZoomPersistance_Jan16_2013 = 5,	// Player remembers their zoom level on the world map
	PLAYERPROFILEVER_DangerRoomProfileHooks_Feb13_2013 = 6,		// Danger room profile addition for danger room progress
	PLAYERPROFILEVER_PrimaryAndChildProfile_Mar27_2013 = 7,		// Primary and child profile addition
	PLAYERPROFILEVER_NewDangerRoomDataHandling_May21_2013 = 8,	// Converts the Danger Room lives into mowers left per row. Just giving everyone 5 mowers.
	PLAYERPROFILEVER_MarkForChineseVersion_June25_2013    = 9,  // Mark for Chinese version
    PLAYERPROFILEVER_HotFixForChineseVersion_Aug05_2013   = 10, // Hot fix some issue for Chinese version first launch.
	PLAYERPROFILEVER_AddDeltaDataForServer             	  = 11,
	PLAYERPROFILEVER_UsingiCloudServer					  = 12,
	PLAYERPROFILEVER_HotFixForChineseVersion_Nov18_2013 = 13,
    PLAYERPROFILEVER_KongFu_Dec18_2013					  = 14,
    PLAYERPROFILEVER_YetiRemove_Mar24_2014				  = 15,
    PLAYERPROFILEVER_ACTIVITYUPDATE_JUN11_2014			  = 16,
#ifdef HOST_ANDROID
    PLAYERPROFILEVER_HotFixForStarPlant_July08_2014       = 17,
    PLAYERPROFILEVER_MoreAvatarCompen_Aug07_2014          = 18,
    PLAYERPROFILEVER_DailyRewardCompen_Sep03_2014         = 19,
    PLAYERPROFILEVER_HotFixRepeatData_Aug15_2016          = 20,
    PLAYERPROFILEVER_NMTWorld_Sep15_2016                  = 21,
#else
	PLAYERPROFILEVER_ICloud_April_2014					  = 17,
	PLAYERPROFILEVER_HotFixForStarPlant_July08_2014       = 18,
    PLAYERPROFILEVER_MoreAvatarCompen_Aug07_2014          = 19,
	PLAYERPROFILEVER_DailyRewardCompen_Sep03_2014         = 20,
    PLAYERPROFILEVER_DarkAge_Oct25_2014                   = 21,
    PLAYERPROFILEVER_DragonBoat_June18_2015               = 22,
    PLAYERPROFILEVER_Skycity_Aug8_2015                    = 23,
    PLAYERPROFILEVER_HotFixForInvaild_April07_2016        = 24,
    PLAYERPROFILEVER_HotFixForErrorWorld_July07_2016      = 25,
    PLAYERPROFILEVER_HotFixRepeatData_Aug15_2016          = 26,
    PLAYERPROFILEVER_NMTWorld_Sep15_2016                  = 27,
#endif
    PVZ_END_ENUM(PLAYERPROFILEVER_)
};
//PVZ2_CHINESE_BEGIN
struct DeltaWorldMapEventInfo
{
	std::vector<int>		eventInfo;
};

class DeltaPlayerProfileInfo: public RtObject
{
	public:
		RT_CLASS_DEFINE(DeltaPlayerProfileInfo, RtObject, RtClass);

		PlayerProfileVersion 				version;
		uint32 								randomSeed;
		uint32 								coins;
		std::vector<int> 					unlockedPlants;
		std::vector<DeltaWorldMapEventInfo>	worldMapEventList;
		std::string 						level;
		std::vector<GameFeature> 			unlockedGameFeatures;
		MapTutorialState 					tutorialProgress;
		std::vector<int> 					completedNarrationEvents;
		std::vector<WorldSpecificKeys>		worldSpecificKeys;
		std::vector<PlantPieceRecord> 		plantPieceRecords;

		DeltaPlayerProfileInfo()
		{
			version 			= PLAYERPROFILEVER_Last;
			randomSeed 			= 0;
			coins 				= 0;
			tutorialProgress 	= TUTORIAL_NONE;
		}
};

class DeltaInfoSummary: public RtObject
{
	public:
		RT_CLASS_DEFINE(DeltaInfoSummary, RtObject, RtClass);

		uint32								days;
		uint32 								gems;
		uint32								coins;
		uint32								egystars;
		uint32								cowstars;
		uint32								piratestars;
		uint32								kongfustars;
        uint32                              futurestars;
        uint32                              darkstars;
		std::string							level;
		uint32								unlockedplantsize;
		uint32								unlockedavatarsize;
		uint32								totalplantlevel;

		DeltaInfoSummary()
		{
			days 		= 0;
			gems 		= 0;
			coins		= 0;
			egystars	= 0;
			cowstars	= 0;
			piratestars	= 0;
			kongfustars = 0;
            darkstars = 0;
			unlockedplantsize = 0;
			unlockedavatarsize = 0;
			totalplantlevel = 0;
            futurestars = 0;
		}
};

struct PlantAvatarInfo
{
	PlantAvatarInfo()
	{
		iPlantID = 0;
		eAvatar = E_AVATAR_NONE;
		vecAvatarUnlocked.resize(E_AVATAR_ALL);
	}
	int iPlantID;
	PlantAvatarType eAvatar;
	std::vector<uint8> vecAvatarUnlocked;
};

enum WhichAvatarType
{
    NOT_AN_AVATAR_TYPE,
    OLD_AVATAR_TYPE,
    NEW_AVATAR_TYPE,
};

struct PlantNewAvatarInfo
{
    PlantNewAvatarInfo()
    {
        iPlantID = 0;
        vecNewAvatarUnlockedID.clear();
    }
    int iPlantID;
    std::vector<int> vecNewAvatarUnlockedID;
};

struct PlantAvatarPiecesInfo
{
	PlantAvatarPiecesInfo()
	{
		iPlantID = 0;
		vecAvatarPiecesCount.resize(E_AVATAR_ALL);
	}
	int iPlantID;
	std::vector<int> vecAvatarPiecesCount;
};

struct PlantNewAvatarPiecesInfo
{
    PlantNewAvatarPiecesInfo()
    {
        iPlantNewPiecesID = 0;
        iPiecesCount = 0;
    }
    int iPlantNewPiecesID;
    int iPiecesCount;
};

struct CollectionInfo
{
    CollectionInfo()
    {
        CollectionID = 0;
        Rare = 0;
        State = 1;
    }
    int CollectionID;
    int Rare;
    int State;
};

struct CardInfo
{
    CardInfo()
    {
        CardID = 0;
    }

    int CardID;
};

struct PlantEquipAvatarInfo
{
    PlantEquipAvatarInfo()
    {
        iPlantID = 0;
        iAvatarID = 0;
    }
    int iPlantID;
    int iAvatarID;
};

struct ArtifactBoostInfo
{
	ArtifactBoostInfo()
	: BoostId(-1)
	, Value(0.0f)
	{

	}

	int BoostId;
	float Value;
};

struct ArtifactInfo
{
    ArtifactInfo()
    {
        ArtifactID = 0;
        Rank = 0;
        Level = 0;
    }
    int ArtifactID;
    int Rank;
    int Level;
    std::vector<ArtifactBoostInfo> BoostInfos;
    std::vector<ArtifactBoostInfo> UnsavedBoostInfos;
};

struct PlantGeneInfo
{
    PlantGeneInfo()
    {
        GeneID = 0;
        Level = 0;
        LockState = 0; //0 is unlock, other normal 1 is lock
    }
    int GeneID;
    int Level;
    int LockState;
};

struct PlantGeneEssenceInfo
{
    PlantGeneEssenceInfo()
    {
        GeneEssenceID = 0;
        Number = 0;
    }
    int GeneEssenceID;
    int Number;
};

struct FestivalPlantRandomIndex
{
    FestivalGameMode    eGameMode;
    FestivalGameLevel   eGameLevel;
    time_t              NormalPlantRandomIndex;
    time_t              FewPlantRandomIndex;
    time_t              RarePlantRandomIndex;
    
    FestivalPlantRandomIndex()
    {
        eGameMode = FestivalGameMode_None;
        eGameLevel = FestivalGameLevel_Count;
        NormalPlantRandomIndex = -1;
        FewPlantRandomIndex = -1;
        RarePlantRandomIndex = -1;
    }
};

struct LevelLostInfo
{
	LevelLostInfo()
	{
		iTimes = 0;
		strLevelName = "";
	}
	std::string		strLevelName;
	int					iTimes;
};

enum DungeonState
{
    DS_None = 0,
    DS_Ready,
    DS_InAdventure,
    DS_Finished,
    DS_AdventuredOut,
    DS_Closed,
};

struct PlantAdventureStates
{
    int dungeonId;
    int state;
    int times;
    int addChanceCount;
    
    PlantAdventureStates()
    {
        dungeonId = -1;
        state = -1;
        times = -1;
        addChanceCount = -1;
    }
};

struct PlantAdventureInfo
{
    bool inited;
    bool hasSurprise;
    int dungeonId;
    int coinBonus;
    int plantChipId;
    int plantChipQuantity;
    int surpriseObjectId;
    int surprisePrice;
    int surpriseQuantity;
    int itemBonus;
    uint32 surpriseShowTime;
    uint32 endTime;
    std::vector<int> plantIdList;
    
    PlantAdventureInfo()
    {
        inited = false;
        hasSurprise = false;
        dungeonId = -1;
        coinBonus = 0;
        itemBonus = 0;
        plantChipId = -1;
        plantChipQuantity = 0;
        surpriseObjectId = 0;
        surprisePrice = 0;
        surpriseQuantity = 0;
        surpriseShowTime = 0;
        endTime = 0;
    }
};

struct AdventurePlants
{
    int plantId;
    uint32 endTime;
    
    AdventurePlants()
    {
        plantId = -1;
        endTime = 0;
    }
};

enum ACUI_Type
{
    ACUI_None = 0,
    ACUI_Free,
    ACUI_Coin,
    ACUI_Gem,
};

struct ChristmasAccessoryInfo
{
    bool inited;
    int freeChances;
    int coinChances;
    int gemChances;
    uint32 lastRefreshTime;
    std::vector<int>  freeIndex;
    std::vector<int>  coinIndex;
    std::vector<int>  gemIndex;
    
    ChristmasAccessoryInfo()
    {
        inited = false;
        lastRefreshTime = 0;
        freeChances = 0;
        coinChances = 0;
        gemChances = 0;
        freeIndex.clear();
        coinIndex.clear();
        gemIndex.clear();
    }
};

enum CGE_Stat
{
    CGE_None = 0,
    CGE_Ready,
    CGE_Opened,
};

struct GoldenEggInfo
{
    bool inited;
    int ObjectId;
    int hammers;
    int hammersLeft;
    int dailyReward;
    int dailyHammerAmount;
    float dailyChargeAmount;
    uint32 lastRefreshTime;
    std::vector<int>  eggsStat;
    std::vector<int>  openedInfo;
    
    GoldenEggInfo()
    {
        inited = false;
        ObjectId = 0;
        hammers = 0;
        hammersLeft = 0;
        dailyReward = 0;
        lastRefreshTime = 0;
        dailyHammerAmount = 0;
        dailyChargeAmount = 0.f;
        eggsStat.clear();
        openedInfo.clear();
    }
};

struct PvpShopInfo
{
    int32               refreshTimes;
    int32               lastGotTimeDay;
    std::vector<int>    sellObjIds;
    std::vector<int>    buyObjIds;
    
    PvpShopInfo()
    {
        refreshTimes = 0;
        lastGotTimeDay = 0;
    }
    
    bool hasBuyed(int objId)
    {
        std::vector<int>::iterator ite = buyObjIds.begin();
        while (ite != buyObjIds.end())
        {
            if((*ite) == objId)
            {
                return true;
            }
            ++ite;
        }
        
        return false;
    }
};

struct SalesPriceList
{
    int pieces;
    int price;
};

struct CurrentSalesInfo
{
    bool newArrival;
    bool opening;
    int ObjectId;
    uint32 refreshTimes;
    std::string configName;
    std::vector<SalesPriceList> priceList;
    
    CurrentSalesInfo()
    {
        newArrival = false;
        opening = false;
        ObjectId = -1;
        refreshTimes = 0;
        configName = "";
        priceList.clear();
    }
};

struct SalesObject
{
    int newArrival;
    int ObjectId;
    uint32 refreshTimes;
    
    SalesObject()
    {
        newArrival = 0;
        ObjectId = -1;
        refreshTimes = 0;
    }
};

struct ServerSalesInfo
{
    bool fromServer;
    bool opening;
    std::string configName;
    std::vector<SalesObject> salesList;
    std::vector<SalesPriceList> priceList;
    
    ServerSalesInfo()
    {
        fromServer = false;
        opening = false;
        configName = "";
        salesList.clear();
        priceList.clear();
    }
};

struct LevelofTheDayActiveInfo
{
    int currentDay;
    int currentChance;
    int remainDays;
    
    LevelofTheDayActiveInfo()
    {
        currentDay = 0;
        currentChance = 0;
        remainDays = 0;
    }
};

struct ServerLevelOfTheDayInfo
{
    bool fromServer;
    bool opening;
//    std::string configName;
    LevelofTheDayActiveInfo activeStates;
    
    ServerLevelOfTheDayInfo()
    {
        fromServer = false;
        opening = false;
//        configName = "";
    }
};

class BossKillTimeChallengeInfo : public RtObject
{
public:
    RT_CLASS_DEFINE(BossKillTimeChallengeInfo, RtObject, RtClass);
public:
    int id         = 0;
    float killTime = 0;
    float life     = 0;
    int  kill     = 0;
    std::string version;
};

#ifdef HOST_ANDROID

struct GeilivableLotteryInfo
{
    LawnKeyField totalChances = 0;
    LawnKeyField remainChances = 0;
    std::string configName = "";
};

class MaterialInfo : public RtObject
{
public:
    RT_CLASS_DEFINE(MaterialInfo, RtObject, RtClass);
public:
    int32 id    = 0;
    LawnKeyField count = 0;
};

struct SynInfo
{
    time_t timestamp;
    int id;
};

#endif

//PVZ2_CHINESE_END

// These values should be in chronological order
enum PlayerProfileMapConversionState
{
    PVZ_BEGIN_ENUM(MAPCONVERSION_),
    MAPCONVERSION_None = 0,
    MAPCONVERSION_ProgressConverted,
    MAPCONVERSION_RewardsPresented,
    MAPCONVERSION_NotNeeded,
    PVZ_END_ENUM(MAPCONVERSION_)
};

struct ProfileConversionResults
{
    struct LevelChange
    {
        LevelChange(const std::string i_oldName, const std::string i_newName)
        : OldLevelName(i_oldName), NewLevelName(i_newName) {}
        std::string OldLevelName;
        std::string NewLevelName;
    };
    
    ProfileConversionResults()
    {
        Calculated = false;
        TotalCoinsAwarded = 0;
        TotalCostumesAwardedFromKeys = 0;
        TotalCostumesAwardedFromStars = 0;
        TotalWorldKeysAwarded = 0;
    }
    bool Calculated;
    int TotalCoinsAwarded;
    int TotalCostumesAwardedFromKeys;
    int TotalCostumesAwardedFromStars;
    int TotalWorldKeysAwarded;
    std::vector<std::string> CostumesAwarded;
    std::vector<std::string> UpgradesAwarded;
    std::vector<std::string> PlantsAwarded;
    std::vector<LevelChange> LevelChanges;
};

struct WorldPackInfo
{
	std::string sku;
	std::string world;
};

struct DailyRechargeCurrency
{
    int date;
    LawnKeyField rechargeCurrency;
};

struct NextPopData
{
    time_t nextTime;
    std::string typeIndex;
};

struct EventTimesRecord
{
    time_t theTime;
    int record;
    std::string signName;
};

struct TravelLogTaskSaveInfo
{
    int ID;
    int GroupID;
    int Progress;
    int32 State;
    time_t Creation;
};

struct PvZ1LevelCompleteInfo
{
    int LevelIndex = -1;
    bool OnlyPvZ1Plant = false;
    bool BeatEliteZombie = false;
    int CurrentStage;
    std::vector<int> ThemeList;
};

struct AdvertisementWatchTimeInfo
{
    time_t FreeChestNormal;
    time_t FreeChestRare;
    time_t PlantAdventureSkip;
    time_t Challenge1;
    time_t Challenge2;
    time_t Challenge3;
    time_t DailySign;
    time_t Endlevel;
    time_t DangerRoomShopRefresh;
    time_t DangerRoomChallengeReset;
    time_t WorldMapADLottery;

    AdvertisementWatchTimeInfo() {
        FreeChestNormal = 0;
        FreeChestRare = 0;
        PlantAdventureSkip = 0;
        Challenge1 = 0;
        Challenge2 = 0;
        Challenge3 = 0;
        DailySign = 0;
        Endlevel = 0;
        DangerRoomShopRefresh = 0;
        DangerRoomChallengeReset = 0;
        WorldMapADLottery = 0;
    }
};

struct AdvertisementWatchCountInfo
{
    int EndlessCount;

    AdvertisementWatchCountInfo() { 
        EndlessCount = 0;
    }
};

enum AdvertisementTimeType {
    ADS_TIME_INVALID = -1,
    ADS_TIME_FREE_CHEST_NORMAL,
    ADS_TIME_FREE_CHEST_RARE,
    ADS_TIME_PLANT_ADVENTURE_SKIP,
    ADS_TIME_CHALLENGE_1,
    ADS_TIME_CHALLENGE_2,
    ADS_TIME_CHALLENGE_3,
    ADS_TIME_DAILYSIGN,
    ADS_TIME_ENDLEVEL,
    ADS_TIME_DANGERROOM_SHOP_REFRESH,
    ADS_TIME_DANGERROOM_CHALLENGE_RESET,
    ADS_TIME_WORLDMAP_LOTTERY,

    // maybe for future use
    ADS_TYPE_1,
    ADS_TYPE_2,
    ADS_TYPE_3,
    ADS_TYPE_4,
    ADS_TYPE_5,
    ADS_TYPE_6,
    ADS_TYPE_7,
};

///
/// battle event save data
///
struct RichmanItemInfo
{
    int _id;
    int _count;

    RichmanItemInfo() { 
        _id = 0;
        _count = 0;
    }
};

// in Board Endlevel func, we check if current event is a battle event
// if yes and win, we send protocol to server, in callback func, we save this eventdata into playerinfo
// after return to mainmap, when we click richman module
// we check battle event save data, if popup is true, we popup a UI tell player you get rewards.then make popup false;
// if player shutdown game, we can run the flow above again.
struct RichmanBattleEventSaveData
{
    bool _needPopup;// if should pop up a reward UI
    bool _battleWin;
    int _battleEventType;// RichmanTileEventType to Int
    std::string _levelName;
    int _rewardID;
    int _rewardCount;
    std::vector<RichmanItemInfo> _rewardItemList;
    std::vector<RichmanItemInfo> _rewardChestList;
    time_t _timeStamp;// data identify

    RichmanBattleEventSaveData() { 
        Reset();
    }

    void Reset() { 
        _needPopup = false;
        _battleWin = false;
        _battleEventType = -1;
        _levelName = "";
        _rewardID = 0;
        _rewardCount = 0;
        _rewardItemList.clear();
        _rewardChestList.clear();
        _timeStamp = 0;
    }
};

struct RichmanGameSaveData
{
    float _winRatio;// guess game ratio
    float _loseRatio;
    int _beansCount;

    RichmanGameSaveData() { 
        _winRatio = 0.3f;
        _loseRatio = 0.3f;
        _beansCount = 0;
    }
};

// danger room special offer save data
struct DangerRoomSpecialOfferSaveData
{
    bool _hasBought;// if bought current term special offer gift
    time_t _expiredTime;// current term special expired time
    int _popUpUICount;// if this count above 1, we should not to popup the gift UI
    bool _bCheck;// if is danger room end fail

    DangerRoomSpecialOfferSaveData() { 
        Reset();
    }

    void Reset() { 
        _hasBought = false;
        _expiredTime = 0;
        _popUpUICount = 0;
        _bCheck = false;
    }
}; 

// check for each normal world anniversary bonus.
struct UnchartedWorldAnniversaryBonusInfo
{
	UnchartedWorldAnniversaryBonusInfo() {
		HasAnniversaryBonus = false;
		AnniversaryVersion = 0;
	}

	bool HasAnniversaryBonus;
	int AnniversaryVersion;
};


class PlayerInfo : public RtObject
{
public:
    RT_CLASS_DEFINE(PlayerInfo, RtObject, RtClass);
	PlayerInfo();

    bool                            NeedSave() { return m_needSave; }
    void                            SetNeedSave(bool i_need) { m_needSave = i_need; }
    
	bool                            IsValid();
    void							SAVE_PROFILE();
	void							saveCurrentProfile();
	void							SetDelaySave(pvztime_t delay_time);
	bool							IsNeedDelaySave() const;

	//Zhred add
	void setIsAuthIDCard(bool isAuthIDCard);
	bool getIsAuthIDCard();

    void setLastZmatchShopRefrashTime(time_t lastZmatchShopRefrashTime);
	time_t getLastZmatchShopRefrashTime();
protected:
	pvztime_t                       m_timerDelaySave;

public:
    void SetCrashContext();
    
	PlayerProfileVersion			GetVersion() const;
	void							UpdateVersion();
    
    //PVZ2_CHINESE_START Copy Protection
    std::string                     GetSignUUID() const;
#ifdef HOST_ANDROID
    std::string						GetSaveSignUUID() const;
#endif
    bool                            GetLastOSVersonIsSeven() const;
    
    void                            UpdateUUIDAndOSVerson();
    
    void                            ResetALLSign();
    void                            SaveLastPurchaseReceiptMD5();
    std::string                     GetLastPurchaseReceiptMD5();

    void                            UpdateLawnKeyField();
    void							UpdateTotalRecharge();
	// Resets all saved values to those of a fresh, blank profile
	void							InitializeSavedValues();
	
	void							GenerateRandomSeed();
	unsigned long					GetRandomSeed() const;
    
    std::wstring					GetName() const;
    void							SetName(const std::wstring& i_name);

    CoinCurrency					GetNumCoins(bool i_check = false);
    void							AddCoins(const CoinCurrency i_amount); 
    int                             SubtractCoins(const CoinCurrency i_amount);
    
    StoneCurrency					GetNumStones(bool i_check = false);
    void							AddStones(const StoneCurrency i_amount);
    int                             SubtractStones(const StoneCurrency i_amount);
    
    RedPacketCurrency			    GetRedPacketCount(bool i_check = false);
    void							AddRedPacket(const RedPacketCurrency i_amount);
    int                             SubtractRedPacket(const RedPacketCurrency i_amount);
    
    int                             GetNumWorldKeys();
    void							AddWorldKeys(const int i_amount);
    int                             SubtractWorldKeys(const int i_amount);
    
    int 							GetDaysCount();
    void 							IncrementDaysCount();
    
    void                            UnlockRechargeNode(RechargeNode i_node);
    bool                            IsUnlockRechargeNode(RechargeNode i_node);
    
    void                            ObtainNewTotalRechargeReward(int i_node);
    bool                            HasObtainedNewTotalRechargeReward(int i_node);
    const std::vector<int>&         GetNewTotalRechargeRewardStatus() { return m_newTotalRechargeRewardStatus; }
    
    void                            SetCoins(const CoinCurrency i_amount);
    void							SetGems(const GemCurrency i_amount);
    void                            SetPlayerGems(const struct S2C_PlayerInfo& i_info);
    void                            SetRedPacket(const RedPacketCurrency i_amount);
    void                            SetLeafs(const LeafCurrency i_amount);
    int                             GetNumRechargeCurrency();
    void                            SetNumRechargeCurrency(int i_currency) { m_rechargeCurrency = i_currency; }
    const std::vector<std::string>& GetRechargeProductId() const { return m_todayRechargeProductId; }  
    bool                            IsNewTotalRechargeReward();
    
    int                             GetNumTotalRechargeCurrency();
    void 							AddRechargeCurrency(int i_currency);
    void                            AddRechargeProductId(const std::string& productID);
    GemCurrency 					GetNumTodayRechargeCurrency();
    GemCurrency                     GetNumRechargeCurrencyRecordedBetween(int from, int to);
    GemCurrency 					GetNumTodayMaxRechargeCurrency();
    GemCurrency 					GetNumMonthRechargeCurrency();
    
    GemCurrency                     GetActitiyDaysRechargeCurrency() { return m_iActitiyDaysRechargeCurrency; }
    void                            ResetActitiyDaysRechargeCurrency() { m_iActitiyDaysRechargeCurrency = 0; }

    GemCurrency                     GetNumGemConsumeRecordedBetween(int from, int to);
    
    void                            RefreshDisplayingBundle(BundleDisplay i_bundle);
    void                            SetDisplayingBundleBuyTimes(int objectId, int i_buyTimes);
    int                             GetDisplayingBundleBuyTimes(int objectId);
    void                            SetDisplayingBundleExpireTime(int objectId, int i_expireTime);
    time_t                          GetDisplayingBundleExpireTime(int objectId);
    const std::vector<BundleDisplay>& GetDisplayingBundleList() { return m_displayingBundle; }
    std::vector<BundleDisplay>      GetDisplayingBundleById(int i_bundleTypeId);
    bool                            IsBundleListDisplaying(int i_bundleTypeId);
    bool                            IsBundleDisplaying(int i_bundleTypeId, int i_objectId);
    bool                            IsDisplayingBundleExpired(int i_bundleTypeId, int i_objectId);
    void                            ClearExpiredDisplayingBundle();
    void                            SortDisplayingBundleByTime();
    void                            ClearAllDisplayingBundle();
    
    void							SetBundleInPurchase(const PurchasedBundleInfo& bundle);
    void							RemoveBundleInPurchase(const std::string& sku, int index = 0);
    bool							GetBundleInPurchase(const std::string& sku, PurchasedBundleInfo& bundleInfo, int index = 0);

    void                            AddBundleQueueCondition(const std::string& condition, const std::string& levelName, const int& bundleTypeId);
    int                             CheckBundleQueueCondition(const std::string& condition, const std::string& levelName);
    const std::vector<BundleQueueCondition>& GetBundleQueueConditionList() { return m_queuedBundleCondition; }
    
    void                            AddBundleToQueue(int bundleTypeId);
    bool                            HasQueueingBundle();
    const std::vector<int>&         GetBundleQueueingList() { return m_queuedBundles; }
    void                            ClearBundleQueueingList() { m_queuedBundles.clear(); }
    
    GemCurrency                     GetRechargeGems();
    GemCurrency                     GetGiveGems();
    GemCurrency						GetNumGems(bool i_check = false);
    void							AddGems(const GemCurrency i_amount, bool bRecharge=true);

    int                             SubtractGems(const GemCurrency i_amount, const int actid = -1, class ICloudRequestCallbackFunctionBase* fCallback = NULL, int sceneId = 1, bool wait = false);

    void                            SetGiveGems(const GemCurrency i_amount);
    void                            SetRechargeGems(const GemCurrency i_amount);
    void 							RefreshRechargeCurrency();

    bool							IsSingleRecharge(){ return m_bSingleRecharge; }
    bool 							CanEnjoyActivity();
    void 							RefreshActivityRecharge(bool bRecharge=false);
    void 							CompleteActivityLevel();
    
    void                            OnOK();
    void                            SetRecharge(bool i_recharge);
    bool                            IsRecharge();
    
    void                            SetFirstBuyPlant(bool i_first);
    bool                            IsFirstBuyPlant();
    
    void                            SetFirstBuyPlantBag(bool i_first);
    bool                            IsFirstBuyPlantBag();
    
    void                            SetNewerPresent(bool i_newerpresent);
    bool                            IsNewerPresent();
    
    void                            SetAdvanceNewerPresent(bool i_advancepresent);
    bool                            IsAdvanceNewerPresent();
    
    void                            SetFirstRechargeRewardStatus(bool i_hasGot);
    bool                            HasGotFirstRechargeReward();
    
    void                            SaveCurrentGemProductRechargeDouble(const std::string & sSku);
    bool                            IsGetRechargeDouble(const std::string & sSku) const;
    bool                            IsAllProductsRechargeDoubleGot(const MagentoCategoryPropsPtr& i_category) const;
    void                            ResetRechargeDoubleData();
    
    void                            SaveRechargePlantPieceReward();
    void                            ResetRechargePlantPieceReward();
    bool                            IsRechargePieceRewardHas() const { return m_bHasRechargePieceReward; }
    
    void                            SetShowRechargeDoubleDialog(bool i_showRechargeDoubleDialog);
    bool                            IsShowRechargeDoubleDialog();

	KeyCurrency						GetNumKeys(const std::string& i_forWorld, bool i_check = false);
	void							AddKeys(const std::string& i_forWorld, KeyCurrency i_amount);
	void							SubtractKeys(const std::string& i_forWorld, KeyCurrency i_amount);

	//Rift
	PennyFuelCurrency            	GetNumPennyFuel() const;
	void                            AddPennyFuel(const PennyFuelCurrency i_amount, const bool i_willBeBankedLater=false);
	void							SubtractPennyFuel(const PennyFuelCurrency i_amount);

	ZombossSignalCurrency			GetCurrentZombossSignal() const;
	void							AddZombossSignal(const ZombossSignalCurrency i_amount);
	void							SubtractZombossSignal(const ZombossSignalCurrency i_amount);
	void							SetZombossSignal(const ZombossSignalCurrency i_resetAmount);

	void                            SetRiftZombossWinField(int i_zombossWinField);
	int                             GetRiftZombossWinField();
	void                            SetRiftZombossAttemptCount(int i_count);
	int                             GetRiftZombossAttemptCount();
	void                            SetRiftZombossClearedCounter(int i_count);
	int                             GetRiftZombossClearedCounter();
	void                            AddRiftZombossAttemptDifficulty(int i_difficulty);
	int                             GetRiftZombossAttemptDifficulty(int i_attempt);
	void                            ClearRiftZombossAttemptDifficulty();
	bool							HasCompletedRiftLevel(int i_nodeIndex);
	bool							HasReceivedFirstClearReward(int i_nodeIndex, int i_difficulty);
	void							SetRiftLevelComplete(int i_nodeIndex, int i_difficulty);
	void							ClearRiftLevelProgress();

	PennyTechCurrency				GetNumPennyTech() const;
	void							AddPennyTech(const PennyTechCurrency i_amount);
	void							SubtractPennyTech(const PennyTechCurrency i_amount);
	void                            SetCurrentRiftID(const serializable_time_t i_riftID);
	serializable_time_t             GetCurrentRiftID();
	void                            SetCurrentRiftSubEventID(const serializable_time_t i_riftID);
	serializable_time_t             GetCurrentRiftSubEventID();
	serializable_time_t				GetZombossNextAvailableTime();
	void							SetZombossNextAvailableTime(const serializable_time_t i_nextAvailableTime);
	int								GetNumTimesZombossFought();
	void							IncrementZombossFightCount();
	void							ClearZombossFightCount();

	// PVZ1
	bool							HasCompletedPVZ1Level(int i_nodeIndex, bool i_hard);
	void							SetPVZ1LevelComplete(int i_nodeIndex, bool i_hard);
	void							ClearPVZ1LevelProgress(bool i_hard);

    bool							HasCompletedUnchartedLevel(int i_nodeIndex, bool i_hard);
	void							SetUnchartedLevelComplete(int i_nodeIndex, bool i_hard);
	void							ClearUnchartedLevelProgress(bool i_hard);

	bool							HasCompletedCardGameLevel(int i_nodeIndex, bool i_hard);
	void							SetCardGameLevelComplete(int i_nodeIndex, bool i_hard);
	void							ClearCardGameLevelProgress(bool i_hard);

    const StarCurrency				GetNumStars(int i_worldId = 0);
    const LeafCurrency				GetLeafCurrency();

	void							AddStars(const StarCurrency i_amount, int i_worldId = 0);
	void							SubtractStars(const StarCurrency i_amount, int i_worldId = 0);
    
    void                            ChangeLeafs(const LeafCurrency i_amount);

    void                            AddKillZombiesNum(const int i_amount);
    int                             GetKillZombiesNum();
    
    void                            SetDoLotteryTimes(const int i_num) {m_doLotteryTimes = i_num;}
    int                             GetDoLotteryTimes() {return m_doLotteryTimes;}
    
    void                            SetActivityLotteryTimesPerDay(const int i_num) {m_activityLotteryTimesPerDay = i_num;}
    int                             GetActivityLotteryTimesPerDay() {return m_activityLotteryTimesPerDay;}

    void                            SetLastLotteryDate(int i_date) {m_lastLotteryDate = i_date;}
    int                             GetLastLotteryDate() {return m_lastLotteryDate;}
    
    void                            SetLastLotteryYear(int i_year) {m_lastLotteryYear = i_year;}
    int                             GetLastLotteryYear() {return m_lastLotteryYear;}
    
    void                            SetTotalLoginDays(int i_days) {m_totalLoginDays = i_days;}
    int                             GetTotalLoginDays() {return m_totalLoginDays;}
    
    void                            ResetTotalLoginGotRewardDays();
    void                            SaveTotalLoginGotRewardDays();
    bool                            HasSavedTotalLoginGotRewardDays() { return m_bHasGotDailyReward; }

    void                            SetLastLoginTimeStamp(time_t i_time);
    time_t                          GetLastLoginTimeStamp() {return m_lastLoginTimeStamp;}

	//zhred add
	void							SetLastConsumGemsTime(time_t i_time);
	time_t							GetLastConsumGemsTime() const { return m_lastConsumGemsTime; }

    void                            SetLastRequestSignTimeStamp(time_t i_time) {m_lastRequestSignTimeStamp = i_time;}
    time_t                          GetLastRequestSignTimeStamp() {return m_lastRequestSignTimeStamp;}
    
    bool                            OnLuaNotify(const std::string& strJsonInfo);
    void                            OnLuaNotifyTag(const std::string& strTag);         // used for processing some specific tag
    std::string                     GetLuaShareData(void) const;
    Sexy::StructuredData            GetLuaShareJson(void) const;
    
    void                            SetHasDailySigned(bool i_signed) {m_hasDailySigned = i_signed;}
    bool	                        GetHasDailySigned() {return m_hasDailySigned;}
    
    void                            SetDailySignRewardSheet(int32 itemId, int32 amount);
    std::vector<SignRewardContent>&         GetDailySignRewardSheet() {return m_dailySignRewardSheet;}
    
    bool                            NeedRefreshDailySignSheet();
    
    void                            SetNeedShowRewardDialog(bool i_need) {m_needShowRewardDialog = i_need;}
    bool                            GetNeedShowRewardDialog() {return m_needShowRewardDialog;}
    
    void                            SetNeedShowRatingDialog(bool i_need) {m_needShowRatingDialog = i_need;}
    bool                            GetNeedShowRatingDialog() {return m_needShowRatingDialog;}

    void							UpdateLoginCount() { m_loginCount++; }
    int32							GetLoginCount(){ return m_loginCount; }

    void                            SetHasGotRewardList(int i_id, int i_value);
    const std::vector<int>&         GetHasGotRewardList() {return m_hasGotRewardList;}


    void                            SetRestorePurchaseInfo(PurchaseInfo &i_purchaseInfo);
    PurchaseInfo                    GetRestorePurchaseInfo();
    void                            ClearRestorePurchaseInfo();
    
    void                            SetDangerRoomEventData(StoredDangerRoomEventData &i_data);
    StoredDangerRoomEventData&      GetDangerRoomEventData();
    
    void                            DailyRefreshPlantAdventureTimes();
    bool                            RefreshPlantAdventureStates();
    void                            SetPlantAdventureState(int i_dungeonId, int i_state, int i_times, bool need_save = true, int i_addChance = 1);
    int                             GetPlantAdventureState(int i_dungeonId);
    int                             GetPlantAdventureTimes(int i_dungeonId);
    bool                            HasPlantAdventureChances(int i_dungeonId);
    bool 							HasPlantAdventureAddChances(int i_dungeonId);
    int 							GetPlantAdventureAddChances(int i_dungeonId);
    
    void                            FixPlantAdventureInfoByServer(int i_dungeonId, int i_state, int i_chances, bool i_hasSurprise, uint32 i_endTime, std::vector<int> i_pl, int i_addChance);
    bool                            IsPlantInAdventure(int i_plantId);
    bool                            HasPlantAdventureFinished();
    bool                            CanStartNewPlantAdventure();
    int                             GetPlantAdventureTeamCount();
    void                            SetPlantAdventureInfos(std::vector<PlantAdventureInfo> i_infos);
    void                            AddPlantAdventureInfo(PlantAdventureInfo i_info);
    void                            SetPlantAdventureInfo(int i_dungeonId, bool i_hasSurprise, uint32 i_endTime, std::vector<int> i_pl, bool need_save = true);
    void                            RemovePlantAdventureInfo(int i_dungeonId, uint32 i_now);
    PlantAdventureInfo              GetPlantAdventureInfo(int i_dungeonId);
    
    void                            AddPlantAdventureOpenInfo(std::string i_dungeonName);
    bool                            HasFirstPlantAdventureOpenInfo();
    std::string                     GetFirstPlantAdventureOpenInfo();
    void                            RemovePlantAdventureOpenInfo(std::string i_dungeonName);
    void                            RemoveAllPlantAdventureOpenInfo();
    
    bool                            HasRealLevelUpTo(std::string i_plantName, int i_level);
    bool                            IsSalesOpening();
    CurrentSalesInfo                GetCurrentSalesInfo();
    ServerSalesInfo                 GetServerSalesInfo();
    void                            SetCurrentSalesInfo(CurrentSalesInfo i_info);
    void                            SetServerSalesInfo(ServerSalesInfo i_info);
    void                            ClearServerSalesInfo();
    void                            ClearCurrentSalesInfo(bool i_init = false);
    bool                            IsServerSalesConfigValid();
    bool                            HasUsedServerSalesConfig();
    bool                            IsCurrentSalesNewArrival();
    uint32                          GetCurrentSalesRefreshTime();
    bool                            OverCurrentSalesRefreshTime();
    bool                            HasValidSales();
    void                            TryNextSales(bool i_fromFirst);
    void                            RefreshLocalSalesConfig(bool i_force);
    int                             GetCurrentSalesPricesCount();
    
#if true
    bool                            IsLevelOfTheDayOpening(int activityTypeId);
	bool                            IsLevelOfTheDayInfoValid(int activityTypeId);
	LevelofTheDayActiveInfo         GetLevelOfTheDayInfo(int activityTypeId);
	void                            SetLevelOfTheDayInfo(bool i_opening, LevelofTheDayActiveInfo i_info, int activityTypeId);
	void                            ClearLevelOfTheDayInfo();
	void							ClearLevelOfTheDayInfoByType(int activityTypeId);
	int                             GetLevelOfTheDayRemainDays(int activityTypeId);
	void                            RefreshLevelOfTheDayInfo(bool i_force, int activityTypeId);
	ServerLevelOfTheDayInfo         GetServerLevelOfTheDayInfo(int activityTypeId);
	bool							isActivityExist(int activityType) const;
#else
    bool                            IsLevelOfTheDayOpening(ActivityTypeID activityType = Activity_ChildrenDay2019);
    bool                            IsLevelOfTheDayInfoValid(ActivityTypeID activityType = Activity_ChildrenDay2019);
    LevelofTheDayActiveInfo         GetLevelOfTheDayInfo(ActivityTypeID activityType = Activity_ChildrenDay2019);
    void                            SetLevelOfTheDayInfo(bool i_opening, LevelofTheDayActiveInfo i_info, ActivityTypeID activityType = Activity_ChildrenDay2019);
    void                            ClearLevelOfTheDayInfo();
	void							ClearLevelOfTheDayInfoByType(ActivityTypeID activityType = Activity_ChildrenDay2019);
    int                             GetLevelOfTheDayRemainDays(ActivityTypeID activityType = Activity_ChildrenDay2019);
    void                            RefreshLevelOfTheDayInfo(bool i_force, ActivityTypeID activityType = Activity_ChildrenDay2019);
    ServerLevelOfTheDayInfo         GetServerLevelOfTheDayInfo(ActivityTypeID activityType = Activity_ChildrenDay2019);
	bool							isActivityExist(ActivityTypeID activityType) const;
#endif

    ConvertObject                   GetNextStarConvert();
    
    void                            RemoveAllAdventure(bool i_clearInfo, bool i_clearPlants, bool i_clearStates);
    void                            RemoveAllAdventurePlants(bool i_clearInfo = false);
    void                            RemoveAdventurePlants(int i_plantId);
    void                            RemoveInvalidAdventures();
    void                            Refresh(uint32 i_now);
    uint32                          GetAdventurePlantEndTime(int i_plantId);
    void                            AddAdventurePlantEndTime(int i_plantId, uint32 i_now, bool need_save = true);
    void                            SetAdventurePlantEndTime(int i_plantId, uint32 i_endTime, bool need_save = true);
    std::vector<AdventurePlants>    GetAdventurePlantsInfo();
    
    void                            ForceRefreshChristmasAccessoryInfo();
    void                            DailyRefreshChristmasAccessoryInfo();
    int                             GetChristmasAccessoryIndex(int i_type, int i_pos);
    void                            ResetChristmasAccessoryIndex(int i_type, std::vector<int> i_index, bool need_save = true);
    void                            SetChristmasAccessoryChances(int i_type, int i_chances, bool need_save = true);
    int                             GetChristmasAccessoryChances(int i_type);
    void                            SetChristmasAccessoryLastRefreshTime(uint32 i_time, bool need_save = true);
    uint32                          GetChristmasAccessoryLastRefreshTime();
    ChristmasAccessoryInfo          GetChristmasAccessoryInfo();
    void                            ClearChristmasAccessoryInfo();
    
    void                            ForceRefreshGoldenEggInfo();
    void                            DailyRefreshGoldenEggInfo();
    int                             ResetGoldenEggsObjectId();
    int                             TryToResetGoldenEggsObjectId();
    int                             GetGoldenEggsObjectId();
    std::vector<int>                GetGoldenEggsStat();
    int                             GetGoldenEggsStatByIndex(int i_index);
    void                            SetGoldenEggsStat(int i_index, int i_eggsStat, bool need_save = true);
    void                            ResetGoldenEggsStat(std::vector<int> i_eggsStat, bool need_save = true);
    void                            SetGoldenEggDailyChargeAmount(float i_amount, bool need_save = true);
    float                           GetGoldenEggDailyChargeAmount();
    void                            SetGoldenEggDailyHammerAmount(int i_amount, bool need_save = true);
    int                             GetGoldenEggDailyHammerAmount();
    void                            SetGoldenEggHammers(int i_hammers, bool need_save = true);
    int                             GetGoldenEggHammers();
    void                            SetGoldenEggHammersLeft(int i_hammersLeft, bool need_save = true);
    int                             GetGoldenEggHammersLeft();
    void                            SetGoldenEggDailyReward(int i_dailyReward, bool need_save = true);
    int                             GetGoldenEggDailyReward();
    void                            SetGoldenEggLastRefreshTime(uint32 i_time, bool need_save = true);
    uint32                          GetGoldenEggLastRefreshTime();
    void                            AddToGoldenEggOpenedInfo(int i_index, bool need_save = true);
    void                            ResetGoldenEggOpenedInfo(bool need_save = true);
    bool                            IsOpenedIndex(int i_index);
    GoldenEggInfo                   GetGoldenEggInfo();
    void                            ClearGoldenEggInfo();
    
    void							AddPurchasedWorldMapInfo(const std::string& sku, const std::string& world);
    const WorldPackInfo*			GetPurchasedWorldMapInfo(const std::string& sku);
    void							RemovePurchasedWorldMapInfo(const std::string& sku);

#ifdef HOST_ANDROID
    void                            ClearGLInfo(bool init = false);
    void                            CheckGLInfo();
    GeilivableLotteryInfo           GetGLInfo();
    void                            SetGLInfo(GeilivableLotteryInfo i_info);
    int                             GetGLTotalChances();
    int                             GetGLRemainChances();
    void                            AddGLChances(int i_addition);
    bool                            SubGLChances();

    // for anti cheat test
#ifndef RELEASEFINAL
	void							ChangeGemsForACLog(GemCurrency gems);
	void							UnlockPlantForACLog(int plantId);
	void							SetPlantLevelForACLog(int plantId, int level);
	void							ChangePlantPiecesForACLog(int plantId, int pieces);
	void							UnlockAvatarForACLog(int plantId);
	void							ChangeAvatarPiecesForACLog(int plantId, int pieces);
	void							ChangeAccessoryPiecesForACLog(const std::string& accessory, int pieces);
	void							ChangeMaterialForACLog(int material, int num);
#endif

#endif
    
	std::string						GetCurrentLevel() const;
    void							SetCurrentLevel(const std::string& i_levelName);
    
    std::string                     GetCurrentWorldName() const;

	bool							GetLevelCompleted(const std::string& i_levelName);
	void							SetLevelCompleted(const std::string& i_levelName, bool i_completed);
    
    bool							GetHardLevelCompleted(const std::string& i_levelName);
    void							SetHardLevelCompleted(const std::string& i_levelName, bool i_completed);

    WorldMapEventStatus				GetWorldMapEventStatus(const std::string& i_savedDataString) const;
	void							SetWorldMapEventStatus(const std::string& i_eventName, const std::string& i_savedDataString, const WorldMapEventStatus i_eventStatus, const bool i_firstCall = true);
    
    bool							SetWorldMapEventStatusNoConsequences(const std::string& i_eventName, const std::string& i_savedDataString, const WorldMapEventStatus i_eventStatus);
    
	void							SetWorldMapEventStatusForEgypt5(const WorldMapEventStatus i_eventStatus);
    
	std::vector<SavedWorldMapEventData> &GetSavedWorldMapEvents() { return m_worldMapEventList; }
    std::vector<WorldCompletionData> &GetEventCompletionList() { return m_worldMapEventData; }
	
	void							ClearWorldMapEventStatus(const std::string& i_savedDataString);
    void                            ClearWorldMapEventStatusById(const int i_worldId, const int i_eventId);
	
	int								GetWorldMapEventCompletionCount(const std::string& i_eventName);
	void							IncrementWorldMapEventCompletionCount(const std::string& i_eventName);
	
	void							SetWorldMapZoomData(const float i_zoomLevel, const bool i_isOnUniverseMap);
	float							GetLastWorldMapZoomLevel();
	bool							WasOnUniverseMapLast();
    
    void                            UpdataDayFirstPayFlag(int iIndex);
    bool                            GetDayFirstPayFlag(int iIndex);
    
    void                            AddPlantTrialObj(const std::string& strPlantName);
    void                            RemovePlantTrialObj(const std::string& strPlantName);
    bool                            IsPlantTrialObjExist(const std::string& strPlantName);
    PlantTrialCD*                   GetPlantTrialObjInfo(const std::string& strPlantName);
    std::vector<PlantTrialCD>&      GetPlantTrialRecord() { return m_vPlantTrialCD; }
    void                            AddPlantOnlyNameTrial(const std::string& strPlantName);
    bool                            IsPlantOnlyNameExist(const std::string& strPlantName);
    void							AddPurchasedPlantTrialObj(const std::string& strPlantName);
    const std::string*				GetPurchasedPlantTrialObj();
    void							RemovePurchasedPlantTrialObj(const std::string& strPlantName);
    void							ClearAllPurchaseRedeemInfo();

	// level lost info
	void							SetLevelLostInfo(const std::string& level_name, bool bWin);
	LevelLostInfo*                  GetLevelLostInfo(const std::string& level_name);
	
	PlantAvatarType					GetPlantAvatar(const std::string& i_plantTypeName, bool i_check = false);
	void							SetPlantAvatar(const std::string& i_plantTypeName, PlantAvatarType eType);
    bool                            IsPlantAvatarUnLocked(const std::string& i_plantTypeName, PlantAvatarType eType, bool i_check = false);
    void                            UnlockPlantAvatar(const std::string& i_plantTypeName, PlantAvatarType eType);
    void							AddAvatarPieces(const std::string& i_plantTypeName, PlantAvatarType eType,bool i_needsave = true);
    void							AddAvatarPiecesCount(const std::string& i_plantTypeName, PlantAvatarType eType, int i_count,bool i_needsave = true);
    void                            AddAvatarPieces(const std::string& i_plantTypeName, int count);
    void							SetAvatarPieces(const std::string& i_plantTypeName, PlantAvatarType eType, int count, bool i_needsave = true, bool i_needByDailyAchievement = true);
    int								GetAvatarPiecesCount(const std::string& i_plantTypeName, PlantAvatarType eType, bool i_check = false);
    bool							IsPlantAvatarPiecesFull(const std::string& i_plantTypeName, PlantAvatarType eType, bool i_check = false);
    bool                            IsPlantPiecesFull(const std::string& i_plantTypeName, bool i_check = false);

    //zxq add for new avatar
    WhichAvatarType                 GetWhichAvatarType(int i_avatarID);
    //Dangerous operation, used only to synchronize data
    void                            ClearNewAvatarInfo();
    void                            ClearNewAvatarPieceInfo();
    void                            ClearAvatarInfo();

    //for new avatar operation
    void                            UnlockNewAvatar(int i_newAvatarID);
    bool                            IsPlantNewAvatarUnLocked(int i_newAvatarID);
    PlantNewAvatarInfo              GetUnlockedPlantNewAvatar(int i_plantID);
    //for new avatar piece operation
    void                            AddNewAvatarPieces(int i_newPiecesID, int count);
    void                            SetNewAvatarPiecesCount(int i_newPiecesID, int count);
    int                             GetNewAvatarPiecesCount(int i_newPiecesID);
    //for equip avatar operation
    void                            CheckEquipAvatarInfo();
    void                            EquipAvatar(int i_avatarID);
    void                            UnEquipAvatar(int i_avatarID);
    bool                            IsEquipAvatar(int i_avatarID);
    int                             GetEquipAvatarID(const std::string& i_plantTypeName);

    //collection
    bool                            HasCollection(int i_collectionID);
    void                            AddCollection(int i_collectionID, int i_aid);
    void                            SetCollection(const CollectionInfo& i_info);
    CollectionInfo                  GetCollection(int i_collectionID);
    void                            SetCollectionRare(int i_collectionID, int rare);
    void                            SetCollectionState(int i_collectionID, bool i_equip);
    void                            RemoveCollection(int i_collectionID);
    void                            ClearCollection();
    const std::vector<CollectionInfo>& GetAllCollection();

    void                            AddCard(int i_cardID);
    const std::vector<CardInfo>&    GetAllCardList();

    //artifact
    int                             GetCurrentArtifact();
    int                             SetCurrentArtifact(int i_artifactID);
    bool                            IsArtifactUnlocked(int i_artifactID);
    void                            UnlockArtifact(int i_artifactID);
    ArtifactInfo                    GetArtifactInfoByID(int i_artfactID);
    void                            ArtifactLevelUp(int i_artifactID);
    void                            ArtifactRankUp(int i_artifactID);
    const std::vector<ArtifactInfo>&    GetUnlockedArtifactList();


    void                            SetArtifactInfo(const ArtifactInfo& i_info);
    void                            ClearArtifactInfo();
    void                            RemoveArtifact(int i_artifactID);
    void                            ResetArtifact(int i_artifactID);
    //gene
    void                            AddPlantGene(int i_geneID);
    void                            PlantGeneLevelUp(int i_geneID);
    void                            SetPlantGeneInfo(const PlantGeneInfo& i_info);
    void                            SetPlantGeneLevel(int i_geneID, int i_level);
    PlantGeneInfo                   GetPlantGeneInfoByID(int i_geneID);
    const std::vector<PlantGeneInfo>&   GetAllPlantGeneInfo();
    void                            ClearPlantGeneInfo();
    void                            PushPlantGeneInfo(const PlantGeneInfo& i_info);

    bool                            IsGeneLocked(int i_geneID);
    void                            SetGeneLockState(int i_geneID, bool i_flag);

    void                            AddGeneEssence(int i_geneEssenceId, int i_number);
    void                            SubGeneEssence(int i_geneEssenceId, int i_number);
    void                            SetGeneEssence(int i_geneEssenceId, int i_number);
    int                             GetGeneEssence(int i_geneEssenceId);
    void                            ClearPlantGeneEssenceInfo();


	bool							GetIsPlantUnlocked(const std::string& i_plantTypeName);
    void							LockPlant(const std::string& i_plantTypeName);
	void							UnlockPlant(const std::string& i_plantTypeName, bool i_silentUnlock = false);
	const std::vector<std::string>	GetUnlockedPlantList();
    
	void 							AddPlantStartLevel(const std::string& i_plantTypeName, int iLevel = 0);
    void                            PlantStarLevelUp(const std::string& i_plantTypeName, bool i_check = false);
    int                             GetPlantStarLevel(const std::string& i_plantTypeName, bool i_check = false);
    int                             GetPlantCount(int level, bool i_check = false);
    bool                            IsCurrentPlantLevelMax(const std::string& i_plantTypeName, bool i_check = false);
    void                            PlantLevelUpCurrentLevel(const std::string& i_plantTypeName, int iTargetLevel, bool i_check = false);

    void                            SetPlantStarLevel(const std::string& i_plantTypeName, int i_level, bool i_check = false, bool i_save = true);
    void                            CurrentPlantStarLevelUp(const std::string& i_plantTypeName, bool i_check = false);
    int                             GetCurrentPlantStarLevel(const std::string& i_plantTypeName, bool i_check = false);
    int                             CalcPlantStarWeight();
    void                            ClearPlantStarLevel();
    void							AddZombieStarLevel(const std::string& i_zombie, int iLevel);
    int								GetZombieStarLevel(const std::string& i_zombie);
    
    void                            AddPlantAwaken(const std::string& i_plantTypeName);
    bool							GetIsPlantAwaken(const std::string& i_plantTypeName);

    void                            AddRewardByTypeName(const std::string& i_typeName, const std::string& i_productName, int i_count = 1, bool i_tutorial = false);

    // AirMarshal...
    void							AM_SetName(const std::wstring);
    std::wstring					AM_GetName();

    void							AM_SetCoins(CoinCurrency); 
    CoinCurrency					AM_GetCoins(); // "Player's purser - must be in cheat mode to change.");
    
    void							AM_SetLevel(std::string);
    std::string						AM_GetLevel();// "Current level, or next level.");

    void							AM_SetGems(GemCurrency);
    GemCurrency						AM_GetGems(); // "Player's purser - must be in cheat mode to change.");
    
    void                            ResetStarTotal();
    void                            SetStarCompleted(const std::string& i_eventDataName, bool i_hard = false);
    int                             GetStarCompleted(const std::string& i_eventDataName);
	bool							IsStarCompletedByLevel(const std::string& level_name);
	
	int								GetStarsAvailableInWorld(const std::string& i_worldName);
	int								GetStarsCompletedInWorld(const std::string& i_worldName, bool i_check = false);

	void							SetKilledZombie(const std::string& i_zombieTypeName);
	bool							IsKilledZombie(const std::string& i_zombieTypeName);
	const std::vector<int>			GetKilledZombieList() const;
	
	void							SetPowerupUnlockState(const std::string& i_powerupName, bool i_state);
	bool							GetPowerupUnlockState(const std::string& i_powerupName) const;

	const std::vector<ArcadePackProgress>&	GetArcadeProgress() const { return m_arcadeProgress; }
	void									SetArcadeProgress(std::vector<ArcadePackProgress>& i_newProgress);

	const std::vector<PowerUpCollectionProgress>&	GetPowerUpProgress() const { return m_powerUpCollections; }
	void											SetPowerUpProgress(std::vector<PowerUpCollectionProgress>& i_newProgress);

	int								GetPowerupUsesLeft(const std::string& i_powerupName) const;
    void 							SetupPowerupUses(const std::string& i_powerupName, int i_num);
	void 							ModifyPowerupUses(const std::string& i_powerupName, int i_diff);
    int                             GetMonthlyCukeUsesLeft();

	const std::string&				GetTreasureYetiLocation() const;
	void							SetTreasureYetiLocation(const std::string& i_location);
	
	void							SetTreasureYetiTries(int i_tries);
	int 							GetTreasureYetiTries() const;

	void 							SetNextTreasureYetiTime(time_t i_time);
	time_t 							GetNextTreasureYetiTime() const;

	void 							SetLastTreasureYetiTime(time_t i_time);
	time_t 							GetLastTreasureYetiTime() const;

	const bool						HasDangerRoomInfo(const std::string& i_worldName);
	void							SetDangerRoomInfo(const std::string& i_worldName, const DangerRoomInfo& i_dangerRoomInfo);
	const DangerRoomInfo&			GetDangerRoomInfo(const std::string& i_worldName);

    void							SetVacationLevelInfo(const DangerRoomInfo& info);
    const DangerRoomInfo&           GetVacationLevelInfo();
    
	const ArenaInfo&				GetArenaInfo() { return m_arenaInfo; }
	void							SetArenaInfo(const ArenaInfo& i_arenaInfo);

	void							HandlePurchase(const std::string& i_purchaseSku, const std::vector<struct PaymentBundleInfo>& i_bundleInfos = {});
	void							HandlePurchaseFail(const std::string& i_purchaseSku);
#ifdef HOST_ANDROID
	bool							CheckIsGemSku(const std::string& i_purchaseSku);
	MagentoProductPropsPtr			GetGemProduct(const std::string& i_purchaseSku);
#endif
	bool							OwnsItemContainedInProps(const class MagentoProductProps* i_productProps);
	
	void							SetProfileIndex(PlayerProfileIndex i_index);
	inline PlayerProfileIndex		GetProfileIndex() const { return m_index; }
    
    void							SetProfileCreatedTime(time_t i_time) { m_profileCreatedTime = i_time; }
    inline time_t                   GetProfileCreatedTime() const { return m_profileCreatedTime; }

    void							SetProfileId(int32 number );
	inline int32                    GetProfileId() const { return m_profileId; }
    
    void							SetVersionNumber(int32 number );
	inline int32                    GetVersionNumber() const { return m_versionNumber; }

	void							MarkForDelete();
	bool							GetIsMarkedForDelete();
	
	void							MarkForKongfuUnlock();
	bool							GetIsMarkedForKongfuUnlock();

	const ZombieStoredMarks			GetZombieStoredMarks();
	void							AddZombieStoredMarks(ZombieWarning i_warning);

	void							UpdateForDelta(PlayerInfo &currInfo);

	void 							AddPlayCountToLevel(const std::string& i_levelName);
    int                             GetLevelPlayCount(const std::string& i_levelName);
	
	void							IncrementSessionCount();
	uint64							GetLifetimeSessionCount() const { return m_lifetimeSessionCount; }
	
	FunnelEvent						GetHighestTutorialEventReached() const { return (FunnelEvent)m_highestTutorialEventReached; }
	void							SetHighestTutorialEventReached(FunnelEvent i_funnelEvent);
	
	time_t							GetLastTutorialFunnelEventTime() const { return m_lastTutorialFunnelEventTime; }
	void							SetLastTutorialFunnelEventTime(time_t i_time);

	void							CompleteTutorial(MapTutorialState i_state);
	bool							PlayerHasCompletedTutorial(MapTutorialState i_state) const;
	MapTutorialState				GetCurrentTutorialState() const { return m_tutorialNewProgress; }
    void							ResetTutorialProgress(MapTutorialState i_state);
    void                            ConvertOldTutorialToNewTutorial();

	void							UnlockGameFeature(GameFeature i_feature);
	void							SetGameFeatureUnlockState(GameFeature i_feature, bool i_state);
	bool							GameFeatureIsUnlocked(GameFeature i_feature);

	void							CompleteNarrationEvent(const std::string& i_eventName);
	bool							GetNarrationEventCompleted(const std::string& i_eventName) const;

	void							UpdateArcadeLastPlayForMode(const std::string& i_modeID, const std::string& i_levelID, const LastPlayStatus i_status, int i_waveIndex);
	ArcadeLastPlayData*				GetArcadeLastPlayForMode(const std::string& i_modeID);

	void							ClearSavedProgress();

	// RtObject interface.
	virtual bool Serialize(const RtSerializeContext& inContext) override;

	void 							SetActiveTutorial(MapTutorialState i_state);
	MapTutorialState 				GetActiveTutorial() const { return m_activeTutorial; }
    
    // New world map conversion
    bool							GetHasBeenConvertedToNewMap() const;
    bool							GetHasBeenGivenConversionRewards() const;
    bool							DidProfileExistOnOldMap() const;
    
    PlayerProfileMapConversionState	GetMapConversionState() const;
    void							SetMapConversionState(PlayerProfileMapConversionState i_newState);
    
    void							SetProfileConversionResults(const ProfileConversionResults& i_results);
    const ProfileConversionResults&	GetProfileConversionResults() const;
    
    //Common Get Reward
    //    void                            AddCommonGachaReward(int i_objectid, int i_count);
    void                            AddCommonGachaRewardList(std::vector<class S2C_BonusInfo> bonusList, bool needSync = false);
    void                            AddCommonGachaReward(int32 objectId, int32 quantity, bool needSync = false, bool syncNow = true);
    
    // functions for calcurating items catagories count
    int                             GetPlantPieceCatagoryCount();
    int                             GetAvatarPieceCatagoryCount(int type = 0);// type = 0 : all avatar, type = 1 : old avatar, type = 2 : new avatar
    int                             GetAccessoryPieceCatagoryCount();
    int                             GetMaterialCatagoryCount();

    //[WuXJ] add the functions for plant piece feature
    void                            clearPlantPieceCount();
    int                             GetPlantPieceCount(const std::string& i_plantTypeName, bool i_check = false);

    bool                            AddPlantPieceCount(const std::string& i_plantTypeName, int i_pieceCount, bool i_needTellServer = true);

    bool                            SubPlantPieceCount(const std::string& i_plantTypeName, int i_pieceCount);
    bool                            ResetPlantPieceCount(const std::string& i_plantTypeName);

    void                            SetPlantPieceCount(const std::string& i_plantTypeName, int i_pieceCount, bool i_check = true, bool i_reset = true, bool i_needsave = true, bool i_needByDailyAchievement = true);

    bool                            HasPlantPiece();
    const std::pair<PlantTypePtr, int> GetPlantPieceCompletionEnable();
    bool							AddBonus(const std::string& i_bonusName, bool b_needAddPlant = true);
	// Accessory Pieces
    void                            ClearAccessoryPieceCount();
	int                             GetAccessoryPieceCount(const std::string& i_type, bool i_check = false );
	bool                            AddAccessoryPieceCount(const std::string& i_type, int i_pieceCount, bool i_save = true);
	bool                            SubAccessoryPieceCount(const std::string& i_type, int i_pieceCount);
    bool                            SetAccessoryPieceCount(const std::string& i_type, int i_pieceCount, bool i_save = true);
    bool                            HasAccessoryPiece(const std::string& i_type);
    
    int                             GetReconstructionComponentCount(const std::string& i_type);
	bool                            AddReconstructionComponentCount(const std::string& i_type, int i_pieceCount);
	bool                            SubReconstructionComponentCount(const std::string& i_type, int i_pieceCount);
	
    
    int                             GetReconstructionLevel(const std::string& i_world_name,eReconstructionType i_type);
	bool                            SetReconstructionLevel(const std::string& i_world_name,eReconstructionType i_type, int i_level);
    
    bool                            IsYetiTutorialPlayed();
    void                            SetYetiToturialEnd();
    int32                           GetPlayYetiLevelCount();
    void                            SubPlayYetiLevelCount();
    int                             GetCurPlayYetiNeedCoin();
    bool                            PayYeti();

    bool                            DoOnlineRefreshEventTime();
    void                            RefreshEvent();
    
    int32                           GetFestivalGameLeftCount(FestivalGameMode i_mode);
    void                            SubFestivalGameLeftCount(FestivalGameMode i_mode);
    void                            AddFestivalGameLeftCount(FestivalGameMode i_mode, int i_count);
    void                            SetFestivalGameLeftCount(FestivalGameMode i_mode, int i_count);
    
    std::vector<FestivalPlantRandomIndex> & GetFestivalPlantRandomIndexList() { return m_listFestivalPlantRandomIndexInfo; }
    void                            RefreshPlantRandomIndexList();
    bool                            RefreshOneOfPlantRandomIndexList(FestivalGameMode eGameMode, FestivalGameLevel eGameLevel);
    
    bool							GetIsWorldUnlocked(const std::string& i_worldName);
    void                            CheckWorldKeyValueWhenUpdate();
    void                            SetReturnWorldKeyValue(int i_returnWorldKeyValue);
    int                             GetReturnWorldKeyValue();
    
    void                            SetReturnGoldValue(int i_returnGoldValue);
    int                             GetReturnGoldValue();
    
    std::vector<int>&               GetUnlockPlantIdList(){ return m_unlockedPlants;};
    std::vector<int>&               GetExperiencePlants() { return m_vecExperiencePlants; };
    void                            addExperiencePlants(int plantID);
    void                            eraseExperiencePlants(int plantID);
    bool                            getIsExperiencePlantById(int plantID);
    bool                            getIsExperiencePlant(const std::string& i_plantTypeName);

    bool                            CheckGemFake();
    int                             GetUnlockBonusGemCount();
    int32                           GetUnlockPlantGemAndCoinCount();
	
	void 							UpdateDeltaDataFromServer(const std::string& i_json, const std::string& i_md5, uint32 i_saveTime);
    void                            UpdateDeltaDataSignFromServer(const std::string& i_md5, const std::string& i_summary, uint32 i_saveTime,uint32 i_profileId);

    void							UpdateDeltaDataSignFromServer(const std::string& i_md5, const std::string& i_summary, uint32 i_saveTime);
    void							UpdateDeltaDataForServer();
    void							UpdateDeltaDataOfflineSaveTime();
    void 							FinishUpdateDeltaDataForServer();
    bool							IsDiffDeltaDataBetweenServer();
    void							SyncOfflineDataFromOnlineData();
    bool							GetDeltaDataForServer(std::string& i_json, std::string& i_md5, std::string& i_summary);
    std::string						GetDeltaOfflineDataSign() { return m_deltaDataOffline_sign; }
    std::string						GetDeltaOnlineDataSign() { return m_deltaDataOnline_sign; }
    const DeltaInfoSummary&			GetDeltaOnlineSummary() { return m_deltaInfoOnlineSummary; }
    const DeltaInfoSummary&			GetDeltaOfflineSummary() { return m_deltaInfoOfflineSummary; }
    uint32							GetDeltaOfflineSaveTime() { return static_cast<uint32>(m_deltaDataOfflineSaveTime); }
    uint32							GetDeltaOnlineSaveTime() { return static_cast<uint32>(m_deltaDataOnlineSaveTime); }
    bool							IsOlderThanServerData();


    void                            AddGameRankRecord(GameRankItem& i_info);
    void                            GetGameRankRecord(GameRankItem& i_info, int i_levelNumber, int star);
    bool							HasGotNewPlayerPackage();
    void							SetGotNewPlayerPackage(bool i_got);
    int32							getTodayPayCount(){ return dayPayCount_;}
    void							setTodayPayCount( int32 count ){ dayPayCount_ = count;}

    const std::string&				getLastOrderId(){ return lastOrderId_;}
    void							setLastOrderId( const char* orderid ){ lastOrderId_ = orderid;}
    bool 							HasSyncDataWithServer() { return m_hasSyncDataWithServer; }
    void 							SetSyncDataWithServer(bool i_sync) { m_hasSyncDataWithServer = i_sync; }

    bool							HasRechargeInActivityDays(){ return m_bRechargeInActivityDays; }
    
    void                            setHeadshotId(int headshotId) {m_headshotId = headshotId;}
    int                             getHeadshotId()const {return m_headshotId;}
    
    //lzjseed added
    const std::vector<PlantAvatarPiecesInfo>& GetPlantAvatarPiecesInfo() const {return m_listPlantAvatarPiecesInfo;}
    const std::vector<PlantAvatarInfo>& GetPlantAvatarInfo() const {return m_listPlantAvatarsAvatarInfo;}
    const std::vector<PlantAvatarInfo>& GetExperiencePlantAvatarInfo() const {return m_listExperiencePlantAvatarsAvatarInfo;}
    const std::vector<PlantPieceRecord>& GetPlantPiecesInfo() const {return m_plantPieceRecords;}
    const std::vector<int>& GetPlantsInfo() const {return m_unlockedPlants;}
    const std::vector<PlantStarLevel>& GetPlantStarsInfo()const {return m_plantStarLevelArray;}
    const std::vector<PlantStarLevel>& GetPlantExperienceStarsInfo()const {return m_plantExperienceStarLevelArray;}
    const std::vector<AccessoryPiece>& GetAccessoryPiecesInfo() const{return m_accessoryPieces;}
#ifdef HOST_ANDROID
    const std::vector<MaterialInfo>& GetMaterialInfo() const { return m_materialList; }
#endif
    const std::vector<PlantNewAvatarInfo>& GetPlantNewAvatarInfo() const {return m_listPlantNewAvatarInfo;}
    const std::vector<PlantNewAvatarPiecesInfo>& GetPlantNewAvatarPiecesInfo() const {return m_listPlantNewAvatarPiecesInfo;}
    
    ///zxy added for config
    void                            forceRefreshYetiCount();
    
    bool    getAdviceEnergyGrid() const   {return canAdviceEnergyGrid;}
    bool    setAdviceEnergyGrid(bool can) {return canAdviceEnergyGrid = can;}
    
	//PVZ2_CHINESE_END
    
    // World Events
    bool							SetWorldMapEventStatusByIds(const uint8 i_worldId, const uint16 i_eventId, const WorldMapEventStatus i_worldMapEventStatus);
    const WorldMapEventStatus		GetWorldMapEventStatusByIds(const uint8 i_worldId, const uint16 i_eventId) const;
    bool							ClearMapEventStatusByIds(const uint8 i_worldId, const uint16 i_eventId);
    
    // Old world map mapping functions to access old data when the Map 1.0
    // world maps are gone (thus preventing name lookups)
    bool							SetOldMapEventStatusByIds(const uint8 i_worldId, const uint16 i_eventId, const WorldMapEventStatus i_worldMapEventStatus);
    const WorldMapEventStatus		GetOldMapEventStatusByIds(const uint8 i_worldId, const uint16 i_eventId) const;
    bool							ClearOldMapEventStatusByIds(const uint8 i_worldId, const uint16 i_eventId);
    void							SetOldMapObjectivesCompletedByIds(const uint8 i_worldId, const uint16 i_eventId, int i_index, bool i_state);
    void                            ClearOldMapEventStatus();
    
    void							SetWorldBeforeEvent(const std::string& i_worldName);
    std::string						GetWorldBeforeEvent() const { return m_worldBeforeEvent; }
    void							ClearWorldBeforeEvent() { m_worldBeforeEvent = ""; }
    
    
    const std::string&				GetLastWorldName();
    void                            SetLastWorldName(const std::string& i_world_name);
    
    bool							GetShowNoticeOnce(){ return m_bShowNoticeOnce; }
    void							CloseShowNoticeOnce(){ m_bShowNoticeOnce = false; }

    int                             GetLevelScore(std::string i_level);
    void                            SetLevelMaxScore(std::string i_level,int i_score);

    
    
    void                            resetChallengeCount();
    void                            resetChallengeCountSize();
    void                            increaseChallengeCount(int worldIndex,int levelIndex);
    int                             getChallengeCount(int worldIndex,int levelIndex) const;
    void							setChallengeCount(std::vector<int> i_challengeCount);
    std::vector<int>				getAllChallengeCount();

    uint64                          getLastFreeGachaTime();
    void                            setLastFreeGachaTime(int32 lastFreeGacha);
    bool                            canFreeGacha();
    time_t                          getFreeGachaLeftTime();
    // New gacha start
    uint64                          getLastFreeGachaTimeNew(int i_type);
    void                            setLastFreeGachaTimeNew(int i_type, int32 lastFreeGacha);
    bool                            canFreeGachaNew(int i_type);
    time_t                          getFreeGachaLeftTimeNew(int i_type);
    bool                            isFirstDiamondGachaNew(int i_type);
    void                            setFirstDiamondGachaNew(int i_type, bool bfirstGacha);
    // New gacha end
    time_t                          GetTimeStamp(const std::string& strDate, const std::string& strDateFormat = "%Y%m%d%H%S");
    bool                            getAvatarCompen();
    void                            setAvatarCompen(bool hasCompen);
    void							setAvatarAdvanceCompen(bool bAdvanceCompen);
    bool                            getGachaCompen();
    void                            setGachaCompen(bool hasCompen);
    bool                            getDailyRewardCompen();
    void                            setDailyRewardCompen(bool hasCompen);
    bool                            getiOSBugCompen();
    void                            setiOSBugCompen(bool hasCompen);
    bool                            getPlantStoreOpen();
    void                            setPlantStoreOpen(bool hasCompen);
    bool                            isFirstDiamondGacha();
    void                            setFirstDiamondGacha(bool bfirstGacha);
    uint32                          CalculateCompenDiamond();
    void                            DoUpdatePlantStarRewards();
    void							AddZombieGift(const std::string &from, const std::string &zombieType);
	std::vector<ZombieGift>&		GetZombieGifts(void) { return m_zombieGifts; }

    bool                            isPlantStarRewards(int plantId);
    void                            setPlantStarRewards(int plantId);

    const int                       getUploadKey(){return m_uploadKey;}
    void                            setUploadKey(const int count){m_uploadKey = count;}
    void                            increaseUploadKey(){++m_uploadKey;saveCurrentProfile();}
    
    const int                       getConfigVersion(){return m_configVersion;}
    void                            setConfigVersion(const int number){m_configVersion = number;}

	void							SetFakeCount(int count){ m_fakeCount = count; }
	int32							GetFakeCount(){ return m_fakeCount; }
    
    time_t                          GetStoneRefreshTime(){return m_iStoneStoreRefreshTime;}
    void                            SetStoneRefreshTime(time_t iTime){m_iStoneStoreRefreshTime = iTime;}
    std::vector<std::string>&       GetVecStoneStoreRec(){return m_vecStoneStoreRec;}
    std::vector<std::string>&       GetVecStoneStoreRecBuyed(){return m_vecStoneStoreRecBuyed;}
    void                            CheckStoneStoreRec(const std::string& strSku,bool& inRec,bool& inRecBuyed);
    void                            SetStoneBuyed(const std::string& strSku);
    
    const bool                      getPlayerHasRated() {return m_hasRated;}
    void                            setPlayerHasRated(bool i_hasRated) {m_hasRated = i_hasRated;}

    std::string                     getLastDiamondBonusName(){return m_lastDiamondBonusname;}
    void							FixProfileSize();
	void							OptimizeProfileSize(); // for mission status reduce
  
    //add shizf
    void                            FixRepeatData();
    void                            UniquePlantPieceCount();
    void                            UniquePlantStartLevel();
    void                            UniqueZombieStartLevel();
    //add shizf end
    
	bool                            getQihooLoginReward();
	void                            setQihooLoginReward(bool hasObtain);
    
    void                            SetCurrentDangerRoomLevel(DangerRoomLevelType i_type);
    DangerRoomLevelType             GetCurrentDangerRoomLevel();

    void                            SetEndlessRemainLife(int i_life);
 	void                            SetCurrentDangerRoomLife(DangerRoomLifeData& i_life);
    DangerRoomLifeData&             GetCurrentDangerRoomLife();
    
    void                            SetCurrentEndlessRankData(int i_rank);
    int                             GetCurrentEndlessRankData();
    
    void                            SetLastLifeResetTimeStamp(time_t i_time) {m_lastLifeResetTimeStamp = i_time;}
    time_t                          GetLastLifeResetTimeStamp() {return m_lastLifeResetTimeStamp;}
    
    void                            SetLastLevelResetTimeStamp(time_t i_time) {m_lastLevelResetTimeStamp = i_time;}
    time_t                          GetLastLevelResetTimeStamp() {return m_lastLevelResetTimeStamp;}
    
    void                            SetRiddlesGotToday(const std::vector<int>& i_riddles);
    std::vector<int>&               GetRiddlesGotToday() {return m_riddlesGotToday; }
    void                            RandomRiddlesForToday();
    time_t                          GetLoginDayTimeRec() {return m_iLoginDayTimeRec;}
    
    void                            AddRiddlesHasAnswered(int i_num);
    std::vector<int>&               GetRiddlesHasAnswered() {return m_riddlesHasAnswered;}
    int                             GetSpringBossCount();
    void                            DecSpringBossCount();

    int                             GetSpringGiftIndex();
    void                            SetSpringGiftIndex(int i_index);
    
    bool                            IsNeedShowSpringGift() const;
    void                            SetNeedShowSpringGift(bool setting);
	
    bool                            HasPopupOnceDay() const;
    void                            SetPopupOnceDay(bool i_PopupOnceDay);
    
    bool                            HasPopupPlantTrialToday() const;
    void                            SetPopupPlantTrialToday(bool popup);
    
    const int						GetAccessoryInfosSize();
    void							SortPlantAccessoryInfos();

    void                            SetRiddlesAnsweredToday(int i_num) {m_riddlesAnsweredToday = i_num;}
    int                             GetRiddlesAnsweredToday() {return m_riddlesAnsweredToday;}
    
    void                            SetRiddlesAnsweredDays(int i_num) {m_riddlesAnsweredDays = i_num;}
    int                             GetRiddlesAnsweredDays() {return m_riddlesAnsweredDays;}
    
    void                            SetRiddlesCorrectNum(int i_num) {m_riddlesCorrectNum = i_num;}
    int                             GetRiddlesCorrectNum() {return m_riddlesCorrectNum;}
    
    void                            SetRiddlesCorrectTotal(int i_num) {m_riddlesCorrectTotal = i_num;}
    int                             GetRiddlesCorrectTotal() {return m_riddlesCorrectTotal;}
    
    void                            SetLastRiddleTimeStamp(time_t i_time) {m_lastRiddleTimeStamp = i_time; }
    time_t                          GetLastRiddleTimeStamp() {return m_lastRiddleTimeStamp; }
    bool                            NeedResetRiddleInfo();
    bool                            CanRiddleToday();
    bool                            IsTodayRiddleTaskComplete();
    
    void                            SetRiddlesPrizeGotIndex(int i_num) {m_riddlesPrizeGotIndex = i_num;}
    int                             GetRiddlesPrizeGotIndex() {return m_riddlesPrizeGotIndex;}
    
    void                            SetRedPackRank(int i_num) {m_redPackRank = i_num;}
    int                             GetRedPackRank() {return m_redPackRank;}
    int                             GetGemReturnDays() { return m_iGemReturnDays;}
    void                            IncGemReturnDays();
    void                            EnableGemReturn();
    
#ifdef HOST_ANDROID
    bool                            StillRemainsGemsReturn();
    void                            SetCloseGemsReturn();
#endif
    void                            SetPaidForGemReturn(bool i_paid);
    bool                            HasPaidForGemReturn();
    bool                            HasGemReturnReward();
    bool                            IsGemReturnOpened();
    void                            SetGemReturnInfo(std::vector<int> i_infoVec);
    std::vector<int>                GetGemReturnInfo();
    GemReturnButtonState            GetGemReturnButtonInfo(int i_index);
    void                            SetReturnDailyHint(bool i_set) { m_gemReturnDailyHint = i_set; }
    bool                            GetReturnDailyHint() { return m_gemReturnDailyHint; }
	void                            SetRedPackOpenTotal(int i_num);
    int                             GetRedPackOpenTotal() {return m_redPackOpenTotal;}
    void                            AddRedPackOpenTotalCount(int iNum);
    void                            SetIsRedPackRankRewardGet(bool bGet);
    bool                            GetIsIsRedPackRankRewardGet() { return m_bRedPackRewardRankGet; }

	int								GetRechargeGiftTimes() const { return m_rechargeGiftTimes; }
	void							AddRechargeGiftTimes();
	void                            ResetRechargeGiftTimes();
	void							SetRechargeGiftCached(bool bCached);
	bool							IsRechargeGiftCached() const { return m_rechargeGiftCached > 0; }
    
    void							ResetBossFightLevels();
    bool                            IsInBossFightLevel() { return m_playingBossFightLevels; }
    void                            SetInBossFightLevel(bool i_fighting) { m_playingBossFightLevels = i_fighting; }
//    std::vector<int>&				GetBossFightLevels() { return m_bossFightLevels; }
    const int                       GetRandomBossLevelIndex();
    void                            RemoveLastBossFightLevel();
    void							SetTodayBossFightCompleted(bool i_finished) { m_bossFightToday = i_finished; }
    bool							IsTodayBossFightCompleted() const { return m_bossFightToday; }

	const int						GetLastUpdateRewardVersion() { return m_lastUpdateRewardVersion; }
	void							SetLastUpdateRewardVersion(int i_version) { m_lastUpdateRewardVersion = i_version; }

	bool							GetIsNewUpdate() { return m_isNewUpdate; }
	void							SetIsNewUpdate(bool i_new) { m_isNewUpdate = i_new; }
    
    // Plant Famliy infos
    std::vector<PlantFamilyInfo>&   GetPlantFamilyInfos();
    void                            SyncPlantFamilyInfos(const std::vector<struct S2C_PlantFamilyInfo>& netInfos, bool needClear = false);
    
	// Plant accessory infos
    std::vector<PlantAccessoryInfo>& GetPlantAccessoryInfos();
    int64                            GetPlantAccessoryUIdById(int id);
    int32                            GetPlantAccessoryIdByUId(int64 uid);
    bool                             HasPlantAccessoryInfos(std::string i_type, int64 accessoryId = 0);
    void							 AddPlantAccessoryInfos(std::string i_type, int64 accessoryId = 0, bool i_save = true);
    void							 SetPlantAccessoryInfos(int id, int i_plantId);
    void							 ClearPlantAccessoryInfos(int id);
    void							 RemovePlantAccessoryInfos(int id);
    void                             RemoveAllPlantAccessoryInfos();
    void                             RemoveAllUnusePlantAccessoryInfos();
    void                             RemoveUnKnowPlantAccessoryInfos(const std::vector<struct S2C_PlantPendantInfo>& netInfos);
    void 							 RemoveUnKnowPlantInfos(const std::vector<struct S2C_PlantListInfo>& netInfos);
    void 							 CheckAccessoryLegality();

    void                             CheckLoginDayTime();
    bool                             TestLoginDayEvt(eDayEvtRec e);
    void                             ClearLoginDayEvt(eDayEvtRec e);
    // Plant Super accessory infos
    int32                            GetPlantAccessoryLevelById(int64 uid);
    int32                            GetPlantSuperAccessoryLevel(int64 accessoryId);
    void                             SetPlantSuperAccessoryLevel(int64 accessoryId, int level);
    
    void                             ResetNeedResetSprintGiftIndex();
    bool                             IsNeedResetSprintGiftIndex();
    
    int								GetLastGateUnlocked() { return m_lastGateUnlocked; }
    void							SetLastGateUnlocked(int i_gate) { m_lastGateUnlocked = i_gate; }

    std::vector<std::string>&		GetWorldAnimPlayed() { return m_worldAnimPlayed; }
    void							AddWorldAnimPlayed(const std::string& i_world);
    bool							HasTargetWorldPlayedAnim(const std::string& i_world);
    
    void clearHeadShot();
    void setUnlockHeadshotId(int headshotId);
    bool isUnlockHeadshotId(int headshotId);
    
    void ClearRankAvatars();
    void SetUnlockRankAvatar(int i_id);
    bool IsUnlockRankAvatar(int i_id);
    int GetCurrentRankAvatar();
    void SetCurrentRankAvatar(int i_id);

	void                            RegainPlantPieceSign();

	void							ClearVaseBreakerData();
    
    void                            ClearAboutRiddlesData();
    void                            ClearRebateData();
    
    void							CheckAndUpdateVaseBreakerActId();
    void                            CheckAndUpdateActivityTopic();
    void                            CheckAndUpdateConsumptionTopic();
    int                             GetConsumptionRewardCount() { return m_iConsumptionRewardCount; }
    void                            SetConsumptionRewardCount(int i_node) { m_iConsumptionRewardCount = i_node; }
    void                            SetConsumptionGems(int i_gems);
    void                            AddConsumptionRewardCount(int iAdd = 1);
    void                            AddConsumptionGems(int iAdd);
    int                             GetConsumptionGems() { return m_iConsumptionGems; }
    
	void							SetLotteryConsumptionGems(int i_stones);
	void                            AddLotteryConsumptionGems(int iAdd);
	int								GetLotteryConsumptionGems() { return m_nLotteryConsumptionGems; }

	// for ConsumptionAndReceive Activity
    void                            CheckConsumptionActivityVersion(int serverVersion);
	void 							SetConsumptionActivityGems(int gems);
	void 							AddConsumptionActivityGems(int gems);
	void 							ResetConsumptionActivityGems(bool save = false);
	int 							GetConsumptionActivityGems()  { return m_ConsumptionActivityGems; }

	void							ResetLotteryConsumptionGems(bool isNeedSave = true);
	void							updateGemsLotteryInfo();

    void                            SetBattleArrayRecord(BattleArrayType i_type, const std::vector<int>& i_vec);
    BattleArrayComponent*           GetBattleArrayRecord(BattleArrayType i_type);
    
    void                            AddDailyAchievementRecord(int i_actId, int i_count);
    DailyAchievementRecord*         GetDailyAchievementRecord(int i_actId);
    void                            FinishDailyAchievement(int i_actId, int i_targetNum);
    void                            AddSpecificDailyAchiReward(int i_actId, int i_targetMax, const std::string& i_specSku);
    void                            ResetDailyAchievementRecord();
    void                            AddNationalDayDate(time_t iTimeStamp);
    int                             GetNationalDayGetRewardCount(time_t iTimeStamp);
    std::vector<std::string>::iterator GetTheNationalDayRecord(time_t iTimeStamp);
    void                            ResetNationalDayDate();
    std::string                     TimeToString(time_t iTimeStamp);
    void                            SetNationalGacha(bool i_gacha) { m_nationalGacha = i_gacha; }
    bool                            GetNationalGacha() { return m_nationalGacha; }
    
    void                            SetSpecialAvatarBonus(std::string i_avatar) { m_specialAvatarBonuns = i_avatar; }
    std::string                     GetSpecialAvatarBonus() { return m_specialAvatarBonuns; }
    
    void                            SetDailyAchiRecordTime(time_t i_time) { m_dailyAchiRecordTime = i_time; }
    bool                            NeedResetDailyAchiRecord();
    
    void                            SetTwoYearBirthdayRewardGet(bool i_twoYearBirthdayRewardGet);
    bool                            HaveGetTwoYearBirthdayReward() { return m_bTwoYearBirthdayRewardGet; }

    void                            ClearUnObtainedReward() { m_dangerRoomUnrewardLevels.clear(); }
    std::vector<int>                GetUnObtainedReward() { return m_dangerRoomUnrewardLevels; }
    void                            AddUnObtainedReward(int i_level) { m_dangerRoomUnrewardLevels.push_back(i_level); }
    
    bool                            GetTwoYearWeChatShared(){ return m_bTwoYearWeChatShare; }
    void                            SetTwoYearWeChatShared(bool bShared);
    void                            SetModernWeChatShared(bool bShared);
    bool                            GetModernWeChatShared(){ return m_bModernWeChatShare; }
    void                            AddBirthZRecord(time_t iStamp);
    BirthZRecord*                   GetBirthZRecord(time_t iStamp);
    int                             GetBirthZGetCount(time_t iStamp);
    int                             GetBirthZRecordCount() { return static_cast<int>(m_vBirthZRecord.size()); }
    BirthZRecord*                   GetLastBirthZRecord();
    BirthZRecord*                   GetBirthZRecord(int iIndex);
    std::vector<int>&               GetHasHouses() { return m_hasHouse; }
    void                            PushHasHouses(int houseId);
    bool                            IsUnlockPVP() { return m_unlockPVP; }
    void                            UnlockPVP();
    
    PVPTutorialState				GetPVPTutorialState() const { return m_pvpTutorialState; }
    void							SetPVPTutorialState(PVPTutorialState i_state) { m_pvpTutorialState = i_state; }
    
    bool                            IsActiveServerConfigValid();
    void                            SetSalesPoped(bool i_poped);
    bool                            IsSalesPoped();
    void                            SetActiveServerConfigValid(bool i_valid);
    
    bool                            HasBoughtLostNetActivityToday();
    bool                            CanBuyLostNetActivityToday();
    void                            OnTodayLostNetActivityBought();
    int                             GetTodayLostNetActivityBonus();
    int                             GetNextLostNetActivityBonus();
    void                            ClearLostNetActivityRecord();
    
    int                             GetTodayChristmasProtectCurrency() const { return m_todayChristmasProtectCurrency; }
    void							SetTodayChristmasProtectCurrency(int i_todayChristmasProtectCurrency);
    
    int                             GetChristmasLotteryPlantIndex() const { return m_nChristmasLotteryPlantIndex; }
    void							SetChristmasLotteryPlantIndex(int i_ChristmasLotteryPlantIndex);
    
    int                             GetChristmasLotteryIndex() const { return m_nChristmasLotteryIndex; }
    void							SetChristmasLotteryIndex(int i_ChristmasLotteryIndex);
    
    void                            SetHasPvpAccount(bool has);
    bool                            HasPvpAccount();
    
	void                            SetHasRebateReward(int iReward);
    int                             GetHasRebateReward();

    void                            SetRebateRewardState(std::vector<int>& vState);
    std::vector<int>&               GetRebateRewardState();
    void                            ResetRebateData();
    
    void                            AddRebateCharge(int iAdd);
    int                             GetRebateCharge();
    void                            ResetRebateCharge();
    
    bool                            CheckRebateRecord(std::string& strPid, pvztime_t iDate);
    bool                            CheckRebateRecord(std::string& strPid);
    void                            AddRebateRecord(std::string& strPid, pvztime_t iDate);
    
    void                            ResetPvpShop(int32 lastResetDay);
    void                            AddPvpShopRefresh(bool isrefresh);
    void                            SetPvpShopSellList(const std::vector<int32>& sellList);
    void                            BuyPvpShopObj(int32 objId);
    PvpShopInfo&                    GetPvpShopInfo() {return m_pvpShopInfo;}
    
    void                            SetNewPlaybackID(uint64 i_id) { m_newPlaybackID = i_id; }
    uint64                          GetNewPlaybackID() const { return m_newPlaybackID; }
    
    void                            SetHaveShowEvilDavidIntro(bool bShow);
    bool                            GetHaveShowEvilDavidIntro();
    
    void                            SetHasPlayedWorldCup(bool i_played);
    bool                            GetHasPlayedWorldCup();

    int                             RecordHardWorld(uint8 i_worldId, bool i_record = false);
	const std::vector<uint8>&       GetHardWorldOrder(){ return m_hardWorldOrder; }
    int                             GetChildrenDayBuyCount();
    void                            SetChildrenDayBuyCount(int count);
    void                            SetChildrenDayInfo(int dayStart, int buyLimit, const std::string& version);
    int                             GetChildrenDayStart();
    std::string                     GetChildrenDayVersion();
    bool                            CanBuyChildrenDayItem();
    
    void							SetMonthlyCardActive(uint32 fliter);
    bool                            IsMonthlyCardActivated(eMonthlyCardType type);
    bool                            CanRefreshMonthlyCard();
    void                            RefreshMonthlyCardFunc();
    int								CheckMonthlyCardRemind(); // 0 no remind, 1 first remind, 2 second remind
    const StructuredData&           GetLuaInfo();

    bool                            IsFirstPopToday(const std::string& i_index);
    void                            CalculateTheNextDay(const std::string& i_index);

    bool                            GetPlayerFlagInfo(const std::string& i_infoType);
    void                            SetPlayerFlagInfo(const std::string& i_infoType, bool i_flag);

    PlayerStorageData               GetPlayerStorageData(const std::string& i_name);
    void                            SetPlayerStorageData(const std::string& i_name, const PlayerStorageData& i_data);

    EventTimesRecord                GetEventRecordByName(const std::string& i_type);
    void                            SetEventRecordByName(const std::string& i_type, int i_record, time_t i_time);
    
    std::vector<WorldCupInfo>&      GetWorldCupInfo();
    bool                            IsStarCupUnlocked(std::string i_worldName);
    bool                            IsBossCupUnlocked(std::string i_worldName);
    bool                            IsPlantCupUnlocked(std::string i_worldName);
    void                            SetStarCupUnlocked(std::string i_worldName);
    void                            SetBossCupUnlocked(std::string i_worldName);
    void                            SetPlantCupUnlocked(std::string i_worldName);
    
    void                            SetMaterialNum(int i_id, int i_num);
    void                            SetMaterialNum(const std::string& i_name, int i_num);
    int                               GetMaterialNum(int i_id) const;
    int                               GetMaterialNum(const std::string& i_name) const;
    void                            AddBossChallengeInfo(const BossKillTimeChallengeInfo& info);
    void                            ClearBossChallengeInfo();
    std::vector<BossKillTimeChallengeInfo>& GetBossChallengeInfo();
    
    int                             GetTwDailySignDay(std::string itemVersion);
    void                            SetTwDailySignDay(int day, int newTime, std::string itemVersion);
    
    bool                            getHasPurchaseCukePkg();
    void                            setHasPurchaseCukePkg(bool hasPurchase);
    
    int								GetCurrentAdsRate() { return m_currentAdsRate; }
    void							SetCurrentAdsRate(int i_num) { m_currentAdsRate = i_num; }

    int								GetCurrentDaveShopAdsRate() { return m_currentDaveShopAdsRate; }
    void							SetCurrentDaveShopAdsRate(int i_num) { m_currentDaveShopAdsRate = i_num; }

	int								GetMonthVIPState();
	time_t							GetLastGetVIPGemTime();
	time_t							GetLastGetVIPGoldTime();
	void							SetMonthVIPState(int state);
	void							SetGetMonthVIPGemTime(time_t tt);
	void							SetGetMonthVIPGoldTime(time_t tt);

	void                            SetPlantBundleBuyTime(time_t i_time) { m_plantBundleBuyTime = i_time; }
	bool                            NeedResetPlantBundleBuyTime();
	void                            ResetPlantBundleBuyTime(int i_left);
	void							SetPlantBundleLeftBuy(int i_left) { m_plantBundleLeftBuy = i_left; }
	int								GetPlantBundleLeftBuy() { return m_plantBundleLeftBuy; }
	void                            RefreshNationalShopItemIfNeed(NationalShopItem i_item);
	void                            SetNationalShopItemBuyTimes(int objectId, int i_buyTimes);
	int                             GetNationalShopItemBuyTimes(int objectId);

	void                            RefreshFestivalShopItemIfNeed(FestivalShopItem i_item);
	void                            SetFestivalShopItemBuyTimes(int objectId, int i_buyTimes);
	int                             GetFestivalShopItemBuyTimes(int objectId);
    
    void                            Refresh5thShopItemIfNeed(FestivalShopItem i_item);
    void                            Set5thShopItemBuyTimes(int objectId, int i_buyTimes);
    int                             Get5thShopItemBuyTimes(int objectId);

	//for oppo
#ifdef HOST_ANDROID
	void							SetNewProfileCreatedTime(time_t i_time) { m_newProfileCreatedTime = i_time; }
	inline time_t                   GetNewProfileCreatedTime() const { return m_newProfileCreatedTime; }
	void							OfferTargetBundle(const std::string& i_sku);
	bool							HasOfferedTargetBundle(const std::string& i_sku);
	void							SetOppoNewerDailyLoginRewardGetTime(time_t get_time);
	bool							HasGotTodayOppoNewerDailyReward();
	int								GetDailyRewardDays();

	// anti cheat
	int								GetACLogIndex();
	void							PushACLog(const S2C_ACLog& acLog);
	void							SerializeACLog(const std::string& aclk);
	bool							UnserializeACLog(std::string& oldKey);
	void							ClearACLog();
	std::string&					GetLastACLKey() { return m_aclk; }

    void                            RecordGroupBuy(int i_index);
    void                            EraseGroupBuyRecord(int i_index);
    std::vector<SynInfo>            GetGroupBuyRecord(){ return m_groupBuyRecord; }
#endif

    bool                            IsTravelLogSaveInfoExist(int i_id);
    TravelLogTaskSaveInfo           GetTravelLogSaveInfo(int i_id);
    void                            UpdateTravelLogSaveInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearOldTaskInfo();
    const std::vector<TravelLogTaskSaveInfo>& GetAllTravelLogSaveInfo();

    bool                            IsDaveTaskSaveInfoExist(int i_id);
    TravelLogTaskSaveInfo           GetDaveTaskSaveInfo(int i_id);
    void                            UpdateDaveTaskSaveInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearOldDaveTaskInfo();
    void                            ClearAllDaveTaskInfo(int configVersion);

    bool                            IsPennyTaskSaveInfoExist(int i_id);
    TravelLogTaskSaveInfo           GetPennyTaskSaveInfo(int i_id);
    void                            UpdatePennyTaskSaveInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearOldPennyTaskInfo();
    void                            ClearAllPennyTaskInfo(int configVersion);

    bool                            IsHappyVaseBreakerTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetHappyVaseBreakerTaskInfo(int i_id);
    void                            UpdateHappyVaseBreakerTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildHappyVaseBreakerTaskInfo();
    void                            ClearHappyVaseBreakerTaskInfo(int i_serverVersion);

    bool                            ShouldRequestTrigger();
    bool                            IsNoviceSevenDaysTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetNoviceSevenDaysTaskInfo(int i_id);
    void                            UpdateNoviceSevenDaysTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildNoviceSevenDaysTaskInfo();
    void                            ClearNoviceSevenDaysTaskInfo(int i_serverVersion);

    bool                            IsCallofWishTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetCallofWishTaskInfo(int i_id);
    void                            UpdateCallofWishTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildCallofWishTaskInfo();
    void                            ClearCallofWishTaskInfo(int i_serverVersion);

    bool                            IsPvZ1AchievementExist(int i_id);
    TravelLogTaskSaveInfo           GetPvZ1AchievementInfo(int i_id);
    void                            UpdatePvZ1AchievementInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildPvZ1AchievementInfo();
    void                            ClearPvZ1AchievementInfo(int i_serverVersion);

    void                            SavePvZ1HardLevelFinishInfoForAchievement(const PvZ1LevelCompleteInfo& i_info);
    void                            SavePvZ1NormalLevelFinishInfoForAchievement(const PvZ1LevelCompleteInfo& i_info);
    const std::vector<PvZ1LevelCompleteInfo>& GetPvZ1HardLevelFinishInfoForAchievement();
    const std::vector<PvZ1LevelCompleteInfo>& GetPvZ1NormalLevelFinishInfoForAchievement();

    void PvZ1AchievementBeatEliteZombie(const std::string& i_zombieName);
    std::vector<std::string> GetPvZ1AchievementBeatEliteZombieList();

    bool                            IsGoldenEggTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetGoldenEggTaskInfo(int i_id);
    void                            UpdateGoldenEggTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildGoldenEggTaskInfo();
    void                            ClearGoldenEggTaskInfo(int i_serverVersion);

    //encapsulate
    bool                            IsTaskExist(const std::vector<TravelLogTaskSaveInfo>& i_taskInfos, int i_id);
    void                            GetTaskInfo(const std::vector<TravelLogTaskSaveInfo>& i_taskInfos, int i_id, TravelLogTaskSaveInfo& i_result);
    void                            UpdateTaskInfo(std::vector<TravelLogTaskSaveInfo>& i_taskInfos, TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildTaskInfo(std::vector<TravelLogTaskSaveInfo>& i_taskInfos);
    void                            ClearTaskInfo(std::vector<TravelLogTaskSaveInfo>& i_taskInfos);

    bool                            IsArborDayTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetArborDayTaskInfo(int i_id);
    void                            UpdateArborDayTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildArborDayTaskInfo();
    void                            ClearArborDayTaskInfo(int i_serverVersion);

    bool                            IsBattleOrderTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetBattleOrderTaskInfo(int i_id);
    void                            UpdateBattleOrderTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildBattleOrderTaskInfo();
    void                            ClearBattleOrderTaskInfo(int i_serverVersion);

    bool                            IsNewPVPTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetNewPVPTaskInfo(int i_id);
    void                            UpdateNewPVPTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildNewPVPTaskInfo();
    void                            ClearNewPVPTaskInfo(int i_serverVersion);

    bool                            IsUnchartedBirthdayTaskExist(int i_id);
	TravelLogTaskSaveInfo           GetUnchartedBirthdayTaskInfo(int i_id);
	void                            UpdateUnchartedBirthdayTaskInfo(TravelLogTaskSaveInfo i_param);
	void                            ClearInvaildUnchartedBirthdayTaskInfo();
	void                            ClearUnchartedBirthdayTaskInfo(int i_serverVersion);

    bool                            IsNewCornucopiaTaskExist(int id);
    TravelLogTaskSaveInfo           GetCornucopiaTaskInfo(int i_id);
    void                            UpdatetCornucopiaTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildCornucopiaTaskInfo();
    void                            ClearCornucopiaTaskInfo(int i_serverVersion);

    bool                            IsPlantCultivateTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetPlantCultivateTaskInfo(int i_id);
    void                            UpdatePlantCultivateTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildPlantCultivateTaskInfo();
    void                            ClearPlantCultivateTaskInfo(int i_serverVersion);

    bool                            IsGiftFoReturnTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetGiftFoReturnTaskInfo(int i_id);
    void                            UpdateGiftFoReturnTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildGiftFoReturnTaskInfo();
    void                            ClearGiftFoReturnTaskInfo(int i_serverVersion);

    bool                            IsDaveKitchenTaskExist(int i_id);
    TravelLogTaskSaveInfo           GetDaveKitchenTaskInfo(int i_id);
    void                            UpdateDaveKitchenTaskInfo(TravelLogTaskSaveInfo i_param);
    void                            ClearInvaildDaveKitchenTaskInfo();
    void                            ClearDaveKitchenTaskInfo(int i_serverVersion);

    bool                            IsToday(time_t i_time);
    bool                            IsInThisWeek(time_t i_time);


#ifdef HOST_ANDROID
    void                            SetLimitGachaDrawTimes(int type, int times);
    int                             GetLimitGachaDrawTimes(int type);
#endif

    // zhousen advertisement watching
#ifdef HOST_ANDROID
    time_t                          GetAdvertisementWatchTime(AdvertisementTimeType type);
    bool                            UpdateAdvertisementWatchTimeInfo(AdvertisementTimeType type, time_t time, bool save = true);
    int                             GetAdvertisementWatchCount(AdvertisementTimeType type);
    bool                            UpdateAdvertisementWatchCountInfo(AdvertisementTimeType type, int count, bool save = true);
#endif

    time_t 							GetWorldLevelPackageStartTime(std::string world, int level);
    void							SetWorldLevelPackageStartTime(std::string world, int level, time_t time);
    bool 							GetWorldLevelPackageFirstPlay();
    void 							SetWorldLevelPackageFirstPlay(bool status);
    void 							UpdateWorldLevelPackageStartTime();
    void 							UpdateWorldLevelPackageStartTime(std::string worldName);
    bool							IsWorldLevelPackageTimeValid(std::string world, int days);
    bool							IsWorldLevelPackageTimeValid(std::string world, int index, int days);
    time_t							GetWorldLevelPackageExpireTime(std::string world, int level, int days);

    std::string 		            CreateCheatingCheckJson(bool filter = false);// create cheating check json
    void                            SetCheatingCheckFlag(CheatingCheckFlags flag, bool status);
    bool                            IsCheatingCheckFlag(CheatingCheckFlags flag);

    void                            SetRichmanTileBattleSaveData(RichmanBattleEventSaveData data, bool save = true);
    bool                            IsPopupRichmanTileBattleEvent();
    RichmanBattleEventSaveData      GetRichmanTileBattleSaveData();
    void                            SetVerifyRewarded(bool flag);
    bool                            GetVerifyRewarded();

    void                            SetRiftStoreFirstEntered(bool i_enter);
    bool                            GetRiftStoreFirstEntered();

    void							SetNewPVPTrainingFirstEntered(bool i_enter);
    bool							GetNewPVPTrainingFirstEntered();

    void 							SetNewPVPSelectedPlants(const std::vector<int>& i_plants);
    const std::vector<int>& 		GetNewPVPSelectedPlants();

    void 							SetPVZ1ModeTutorialFinished(bool i_finished);
    bool 							GetPVZ1ModeTutorialFinished();

    void 							SetHasGotCustomLevelTutorialLevel(bool i_got);

    bool 							HasGotCustomLevelTutorialLevel();

    void                            SetTutorialFirstChecked(bool i_checked);
    bool                            GetTutorialFirstChecked();

    bool GetPVZ1ModeFirstPlay();
    void SetPVZ1ModeFirstPlay(bool status);
    bool GetCustomLevelFirstPlay();
    void SetCustomLevelFirstPlay(bool status);

    // zhousen PennyClassroom
    void SetPennyClassroomTestIndex(int index);
    int GetPennyClassroomTestIndex();

    // zhousen uncharted mode world nums
    void SetPVZ2UnchartedModeWorldCount(int count);
    int GetPVZ2UnchartedModeWorldCount();

    bool GetUnchartedAnniversaryReward();
    void SetUnchartedAnniversaryReward(bool status);
    void ClearUnchartedAnniveraryReward(int version);
    bool GetUnchartedWorldAnniversaryReward(std::string worldName);
    void SetUnchartedWorldAnniversaryReward(std::string worldName, bool status);
    void ClearUnchartedWorldAnniversaryReward(std::string worldName, int version);

    // customlevel guesslike enable
    bool GetCustomLevelGuessLikeEnable();
    void SetCustomLevelGuessLikeEnable(bool enable);

    void SetRichmanGameSaveData(RichmanGameSaveData data, bool save = true);
    RichmanGameSaveData GetRichmanGameSaveData();
    void SetRichmanGuessGameRatio(float win, float lose, bool save = true);
    void GetRichmanGuessGameRatio(float& win, float& lose);

    void SetDangerRoomSpecialOfferSaveData(DangerRoomSpecialOfferSaveData data, bool save = true);
    DangerRoomSpecialOfferSaveData GetDangerRoomSpecialOfferSaveData();

    void							SetCurrentTrainingWorldName(const std::string& i_name);
    std::string						GetCurrentTrainingWorldName() { return m_currentTrainingWorldName; }

    void 							SetDangerRoomTrainingRecord(const std::string& i_world, int i_highestLevel);
    DangerRoomTrainingRecord		GetDangerRoomTrainingRecord(const std::string& i_world);
    DangerRoomTrainingRecord 		findTrainingRecord(const std::string& i_world);
    bool							changeTrainingRecord(const std::string& i_world, int i_highestLevel);

private:

    
    void                            ResetConsumptionRewardDate();
    int 							GetNeedTotalPiece(const std::string& strPlantName, int iDesLevel);
	void							propagateUnlockStatus(const MapEventItem* i_triggerEvent, const WorldMapEventStatus& i_newStatus);
	void							propagateVisibleStatus(const MapEventItem* i_triggerEvent, const WorldMapEventStatus& i_newStatus);
	void							unlockPurchasedItem(const MagentoProductPropsPtr i_purchasedItem, const std::vector<struct PaymentBundleInfo>& i_bundleInfos);
	bool							ownsItem(const std::string& i_objectType, const std::string& i_objectItem);
	std::vector<int>::iterator		getIterForName(const std::string& i_plantTypeName);
#ifdef HOST_IPHONEOS
    bool                            tryAddFreeGem(int id, int count);
#endif
    
    //PVZ2_CHINESE_BEGIN
    //check sign for key data
    bool                            checkCoinsSign();
    void                            resetCoinsSign();
    void                            resetCoinsZeroSign();
    bool                            checkGemsSign();
    void                            resetGemsSign();
    void                            resetGemsZeroSign();
    bool                            checkStonesSign();
    void                            resetStonesSign();
    void                            resetStonesZeroSign();
    bool                            checkRedPacketsSign();
    void                            resetRedPacketsSign();
    void                            resetRedPacketsZeroSign();
    
    
    bool                            checkLeafsSign();
    void                            resetLeafsSign();
    void                            resetLeafsZeroSign();
    
    bool                            checkKeysSign();
    void                            resetKeysSign();
    void                            resetKeysZeroSign();
    bool                            checkPowerupSign();
    void                            resetPowerupSign();
    void                            resetPowerupZeroSign();
    bool                            checkPlantPieceSign();
    void                            resetPlantPieceSign();
    void                            resetPlantPieceZeroSign();
    
    bool                            checkPlantStarLevelSign();
    void                            resetPlantStarLevelSign();
    void                            resetPlantStarLevelZeroSign();
    
    bool                            checkPlantAwakenSign();
    void                            resetPlantAwakenSign();
    void                            resetPlantAwakenZeroSign();
    
    bool                            checkUnlockedPlantsSign();
    void                            resetUnlockedPlantsSign();
    void                            resetUnlockedPlantsZeroSign();
    
    bool                            checkUnlockedGameFeaturesSign();
    void                            resetUnlockedGameFeaturesSign();
    void                            resetUnlockedGameFeaturesZeroSign();
    
    bool                            checkWorldMapEeventsSign();
    void                            resetWorldMapEeventsSign();
    void                            resetWorldMapEeventsZeroSign();
    
    bool                            checkRestorePurchaseSign();
    void                            resetRestorePurchaseSign();
    void                            resetRestorePurchaseZeroSign();

    bool                            checkWorldKeysSign();
    void                            resetWorldKeysSign();
    void                            resetWorldKeysZeroSign();

    bool							CheckAvatarInfoSign();

    void							resetAvatarInfoSign();
    void							resetAvatarInfoZeroSign();

    bool							CheckAvatarPiecesInfoSign();
    void							resetAvatarPiecesInfoSign();
    void							resetAvatarPiecesInfoZeroSign();
    
    bool                            checkAccessoryPieceSign();
	void                            resetAccessoryPieceSign();
	void                            resetAccessoryPieceZeroSign();

	bool							checkAccessoryInfoSign();
	void							resetAccessoryInfoSign();
	void							resetAccessoryInfoZeroSign();

    uint32							getTotalUnlockedPlantSize();
    uint32							getTotalUnlockedAvatarSize();
    uint32							getTotalUnlockedPlantLevel();

    std::vector<WorldCupInfo>       m_worldCupInfo;
    
    //PVZ2_CHINESE_END
    
    void							createDeltaForWorldMapEventData(std::vector<WorldCompletionData>& io_lastState, const std::vector<WorldCompletionData>& i_newState);
    
    //PVZ2_CHINESE_START Copy Protection
    // Serialized
        
    bool                            m_needToResetSprintGiftIndex;
    bool                            m_lastOSVersonIsSeven;

    std::string						m_sign_uuid;
#ifdef HOST_ANDROID
    std::string						m_save_sign_uuid;
#endif
    //PVZ2_CHINESE_END

	// Not Serialized
	MapTutorialState					m_activeTutorial;
    ProfileConversionResults			m_profileConversionResults;
    std::string							m_worldBeforeEvent;		// The world the player was at when they go to an event (yeti) so we can go back to that world after the event is done
    
    //PVZ2_CHINESE_BEGIN
    //raoyj
    //std::vector<std::string>			m_unlockedMapPlants;        //just for map plant play unlock animations
    //bool                              m_firstPlayMapUnlockPlant;
    //PVZ2_CHINESE_END
    
    //PVZ2_CHINESE_BEGIN for avatar
    std::vector<PlantAvatarInfo>            m_listPlantAvatarsAvatarInfo;
    std::vector<PlantAvatarInfo>            m_listExperiencePlantAvatarsAvatarInfo;
    std::vector<PlantAvatarPiecesInfo>      m_listPlantAvatarPiecesInfo;
    std::vector<FestivalPlantRandomIndex>   m_listFestivalPlantRandomIndexInfo;

//zxq add
    std::vector<PlantNewAvatarInfo>         m_listPlantNewAvatarInfo;
    std::vector<PlantNewAvatarPiecesInfo>   m_listPlantNewAvatarPiecesInfo;
    std::vector<PlantEquipAvatarInfo>       m_listPlantAvatarEquipInfo;
//Collection
    std::vector<CollectionInfo>             m_listCollectionInfo;
    std::vector<CardInfo>                   m_listCardInfo;

    //PVZ2_CHINESE_END

	// Serialized
	PlayerProfileVersion				m_version;
    
    std::wstring						m_name;					// The player's friendly name - this can be changed without changing the id of the player. 
	
	uint32								m_randomSeed;			// Unique random seed, generated once upon player creation and remains constant

	//PVZ2_CHINESE_BEGIN
	//[WuXJ] add the encrypt for coins
    std::vector<RechargeNode>           m_unlockedRechargeNodes;
    LawnKeyField                        m_totalRechargeCurrency;
    LawnKeyField                        m_rechargeCurrency;
    std::vector<int>                    m_newTotalRechargeRewardStatus;
    LawnKeyField						m_todayRechargeCurrency;
    std::vector<DailyRechargeCurrency>  m_somedayRechargeCurrency;
    std::vector<DailyRechargeCurrency>  m_somedayGemConsumeCurrency;
    std::vector<std::string>            m_todayRechargeProductId;
    LawnKeyField						m_todayMaxRechargeCurrency;
    int									m_todayDate;
    LawnKeyField						m_monthRechargeCurrency;
    int									m_monthDate;
	LawnKeyField                        m_coins;				// Size of player's purse.
	LawnKeyField                        m_gems;
    LawnKeyField                        m_stones;
    LawnKeyField                        m_redPacket;
    GemCurrency                         m_giveGems;
    ZombossSignalCurrency				m_zombossSignal;

    uint32                              m_riftZombossWinField;  // Bitfield of zomboss wins
    uint32                              m_riftZombossAttemptCount;   // # of times Zomboss played in current attempt
	uint32                              m_riftZombossClearedCounter; // # of times Zomboss event reached - Rolling unique ID to ensure we don't merge attempt data between two different Zomboss attempts
	std::vector<int32>                  m_riftZombossAttemptDifficulty; // Difficulty selection for each Zomboss win

    LawnKeyField                        m_worldkeys;
    int									m_daysCount;
    bool                                m_bRecharge;
    bool                                m_bFirstBuyPlant;
    bool                                m_bFirstBuyPlantBag;
    bool                                m_bNewerPresent;
    bool                                m_bAdvanceNewerPresent;

    bool								m_bActivityRecharge;
    int									m_activityLeftTime;

    bool								m_bSingleRecharge;
    
    std::vector<BundleDisplay>          m_displayingBundle;
    std::vector<BundleQueueCondition>   m_queuedBundleCondition;
    std::vector<int>                    m_queuedBundles;

    bool                                m_hasGotFirstRechargeReward;
    std::vector<FirstRechargeAwardData> m_GetRechargeDoubleList;
    bool                                m_bHasRechargePieceReward;
    bool                                m_bShowRechargeDoubleDialog;
    std::string 						m_strLastProductVersion;
    std::string                         m_strLuaPersistentData;
    
    bool                                m_needSave;
	//PVZ2_CHINESE_END

	std::vector<int>					m_unlockedPlants;		// Unlocked plant types
    std::vector<int>                    m_vecExperiencePlants;

	MapEventList						m_worldMapEventList;	// Map1.0 ONLY Tracks our world map events (levels passed, gates unlocked, plants picked up, etc)
    std::vector<WorldCompletionData>	m_worldMapEventData;	// Map2.0 (NEW MAP) Tracks a list of events that have been completed at least once
    std::string							m_level;				// the level to play when loading.

    std::vector<GameFeature>			m_unlockedGameFeatures; // List of game features the player has unlocked.
    MapTutorialState					m_tutorialProgress;		// The last tutorial event the player completed.
    std::vector<MapTutorialState>       m_exTutorialProgressArray; //The new tutorial events array the player comleted.
    
    MapTutorialState					m_tutorialNewProgress;
    std::vector<MapTutorialState>       m_exTutorialNewProgressArray;

    std::vector<int>					m_completedNarrationEvents; // The narration events the player has viewed.

	std::vector<int>					m_killedZombies;		// All of the zombies that we've killed that will show up in the almanac
	ZombieAlmanac						m_zombieAlmanac;
	
	std::vector<WorldSpecificKeys>		m_worldSpecificKeys;	// List of World Name->Key Count pairs
    std::vector<PowerupRecord>			m_powerupRecords;		// How many powerups we have and which are unlocked
    //PVZ2_CHINESE_START
	LawnKeyField						m_stars;				// Calculated during runtime from world map event list data and GetNumStars.
    LawnKeyField                        m_leafs;
    //PVZ2_CHINESE_END
    TreasureYetiInfo					m_treasureYetiInfo;		// All of the info pertaining to the treasure yeti
	
	std::vector<DangerRoomInfo>			m_dangerRoomInfo;		// All of the info pertaining to the danger room, per world
    DangerRoomInfo                      m_vacationLevelInfo;
	ArenaInfo							m_arenaInfo;
	
	bool								m_onUniverseMap;		// When returning to the game via main menu, states if we go to the world map or the universe map (since we can back out of both, to the menu)
	float								m_lastWorldMapZoom;		// Last zoom level on the world map, so we return to what we left.
    
    // New-map Profile Conversion flag
    PlayerProfileMapConversionState		m_mapConversionState;

	uint8								m_highestTutorialEventReached;  // How far along the tutorial funnel are we?
	
	PlayerProfileIndex					m_index;				// Index of the profile
	int32                               m_profileId;
    int32                               m_versionNumber;
    time_t                              m_profileCreatedTime;
    
	bool								m_markedForDelete;
    
	uint32								m_lifetimeSessionCount;
	
    time_t                              m_lastTutorialFunnelEventTime;
    //PVZ2_CHINESE_BEGIN
    //[WuXJ] add the variables for plant piece feature
    std::vector<PlantPieceRecord>       m_plantPieceRecords;
    std::vector<PlantAdventureStates>   m_plantAdventureStates;
    std::vector<PlantAdventureInfo>     m_plantAdventureInfos;
    std::vector<std::string>            m_plantAdventureOpenInfo;
    std::vector<AdventurePlants>        m_plantsInAdventure;
    ChristmasAccessoryInfo              m_christmasAccessoryInfo;
    GoldenEggInfo                       m_goldenEggInfo;
#ifdef HOST_ANDROID
    GeilivableLotteryInfo               m_geilivableLotteryInfo;
	int32                               m_monthVIPState;
	time_t                              m_lastGetVIPGemTime;
	time_t                              m_lastGetVIPGoldTime;
#endif
    
    int                                 m_LastplantPieceCompletionShow;
    
    bool                                m_activeServerConfigValid;
    bool                                m_salesPoped;
    
    CurrentSalesInfo                    m_currentSalesInfo;
    ServerSalesInfo                     m_serverSalesInfo;
    
    std::vector<time_t>           m_lostNetTokenDate;
    int                                 m_lastLostNetBonus = 0;
    time_t                             m_lastLostNetTokenDate = 0;
    
	std::map<int, ServerLevelOfTheDayInfo>   m_leveloftheDayInfo;
	ServerLevelOfTheDayInfo				m_timeTravelDayInfo;
    std::vector<AccessoryPiece>       	m_accessoryPieces;
    
    std::vector<ReconstructionComponent>m_reconstructionComponents;
    std::vector<ReconstructionLevel>    m_reconstructionLevel;
    
    std::vector<PlantStarLevel>         m_plantStarLevelArray;
    int                                 m_currentArtifact;
    std::vector<ArtifactInfo>           m_artifactListArray;
    std::vector<PlantGeneInfo>          m_plantGeneList;
    std::vector<PlantGeneEssenceInfo>   m_plantGeneEssenceList;
    std::vector<PlantStarLevel>         m_plantExperienceStarLevelArray;
    std::vector<ZombieStarLevel>		m_zombieStarLevelArray;
    
    std::vector<int>                    m_plantAwakenInfo;
    
	//raoyj,add for every day event
    OnlineEventInfo                     m_curOnlineEventInfo;
    int32                               m_killZombiesNum;
    int32                               m_returnGoldValue;  //when upgrade new versison use.
    
    bool                                m_gemReturnDailyHint;
    bool                                m_gemReturnPaid;
    std::vector<int>                    m_gemsReturnList;
    
    int                                 m_returnWorldKeyValue;
    
    int                                 m_iGemReturnDays;
    int                                 m_iDayRecEventFlag;
    time_t                              m_iLoginDayTimeRec;
    time_t                              m_monthlyCardRefreshTime;
    time_t								m_monthlyCardSuperRefreshTime;
    time_t								m_monthlyCardMakeUpRefreshTime;
    
    //shizf add hardlevel world order
    std::vector<uint8>                  m_hardWorldOrder;
    
    //zhaobk add lottery data
    int                                 m_doLotteryTimes;
    int                                 m_lastLotteryDate;
    int                                 m_lastLotteryYear;
    int									m_activityLotteryTimesPerDay;
    bool                                m_needShowRewardDialog;
    bool                                m_needShowRatingDialog;
    
    std::vector<int>                    m_dangerRoomUnrewardLevels;

    //zhaobk add login days & reward vector
    int									m_totalLoginDays;
    bool                                m_bHasGotDailyReward;
    std::vector<int>					m_hasGotRewardList;
    time_t								m_lastLoginTimeStamp;
	time_t								m_lastConsumGemsTime;
    //zhaobk add daily sign time stamp & reward sheet
    time_t                              m_lastRequestSignTimeStamp;
    std::vector<SignRewardContent>      m_dailySignRewardSheet;
    bool                                m_hasDailySigned;
    
    Sexy::StructuredData                m_jsonLuaInfo;

    PurchaseInfo                        m_restorePurchaseInfo;
    std::vector<GameRankItem>           m_gameRankRecords;
    
    StoredDangerRoomEventData           m_dangerRoomEventData;
    
    std::string                         lastPurchaseReceiptmd5;
    std::string                         m_coins_sign;           // sign of coins.
    std::string                         m_stones_sign;
    std::string                         m_gems_sign;            // sign of gems.
    std::string                         m_red_packet_sign;
    std::string                         m_leafs_sign;
    std::string                         m_worldSpecificKeys_sign;
    std::string                         m_powerupRecords_sign;
    std::string                         m_plantPieceRecords_sign;
    std::string                         m_plantStarLevel_sign;
    std::string                         m_unlockedPlants_sign;
    std::string                         m_unlockedGameFeatures_sign;
    std::string                         m_worldMapEventList_sign;
    std::string                         m_worldkeys_sign;
    std::string							m_unlockedAvatar_sign;
    std::string							m_avatarPieces_sign;
    // For accessories
    std::string							m_accessoryPieces_sign;
    std::string							m_accessoryInfos_sign;
    
    std::string                         m_plantAwaken_sign;


    std::string							m_deltaInfoSummaryLevelString;
    std::string							m_deltaInfoOnlineSummaryString;
    DeltaInfoSummary					m_deltaInfoOnlineSummary;
    std::string							m_deltaInfoOfflineSummaryString;
    DeltaInfoSummary					m_deltaInfoOfflineSummary;

    std::string							m_deltaDataJsonString;
    std::string 						m_deltaDataOnline_sign;
    std::string							m_deltaDataOffline_sign;
    time_t								m_deltaDataOfflineSaveTime;
    time_t								m_deltaDataOnlineSaveTime;
    
    std::string                         m_coins_zero_sign;
    std::string                         m_gems_zero_sign;
    std::string                         m_stones_zero_sign;
    std::string                         m_leafs_zero_sign;
    std::string                         m_red_packet_zero_sign;
    std::string                         m_keys_zero_sign;
    std::string                         m_powerups_zero_sign;
    std::string                         m_plantpieces_zero_sign;
    std::string                         m_plantstarlevel_zero_sign;
    std::string                         m_unlockedPlants_zero_sign;
    std::string                         m_unlockedGameFeatures_zero_sign;
    std::string                         m_worldMapEvents_zero_sign;
    std::string                         m_restore_purchase_sign;
    std::string                         m_restore_purchase_zero_sign;
    std::string                         m_worldkeys_zero_sign;
    std::string							m_unlockedAvatar_zero_sign;
    std::string							m_avatarPieces_zero_sign;
    // For accessories
    std::string							m_accessoryPieces_zero_sign;
    std::string							m_accessoryInfos_zero_sign;
    
    std::string                         m_plantAwaken_zero_sign;
    
    int                                 m_rank;
    
    int32                               m_fakeCount;
    int32                               m_lastFakeTime;
    bool                                m_hasUseAug05LawnKeyField;
    bool								m_hasGotNewPlayerPackage;
    int32								dayPayCount_;
    std::string							lastOrderId_;
    bool								m_hasSyncDataWithServer;
    bool								m_bRechargeInActivityDays;
    
    bool                                canAdviceEnergyGrid;
    
    std::string                         m_last_world_name;

    bool								m_bShowNoticeOnce;
    
    std::vector<LevelScoreItem>         m_LevelScores;
    
    int32								m_loginCount;

    bool								m_purchasedKongfuUnlock;

    bool                                m_hasRated;
    
    int                                 m_uploadKey;
    int                                 m_configVersion;

    bool                                m_initing;

    ZombieStoredMarks				  	m_zombieStoredMarks;

    int32                               m_lastFreeGachaTime;
    bool                                m_firstDiamondGacha;
    
    // New free gacha
    int32                               m_lastFreeGachaTimeNormal;
    int32                               m_lastFreeGachaTimeRare;
    int32                               m_lastFreeGachaTimeAvatar;
    bool                                m_firstDiamondGachaNormal;
    bool                                m_firstDiamondGachaRare;
    bool                                m_firstDiamondGachaAvatar;

    bool                                m_avatarCompen;
    bool								m_gachaCompen;
    bool								m_avatarAdvanceCompen;
    bool								m_dailyRewardCompen;
    bool								m_iOSBugCompen;
    bool                                m_plantstoreOpen;
	//PVZ2_CHINESE_END
    std::vector<ZombieGift>				m_zombieGifts;
    
    std::vector<int>                    m_challengeCount;
    std::vector<int>                    m_plantStarRewardsRecord;
    std::vector<std::string>            m_vDayFirstPayFlag;
    
    std::vector<std::string>            m_vecStoneStoreRec;
    std::vector<std::string>            m_vecStoneStoreRecBuyed;
    time_t                              m_iStoneStoreRefreshTime;
    
    int                                 m_iActitiyDaysRechargeCurrency;

    int                                 m_currentSpringGiftIndex;
    bool                                m_bNeedShowSpringGift;
    std::string                         m_lastDiamondBonusname;

    bool								m_qihooLoginReward;
    
    bool                                m_hasPopupOnceDay;
    bool                                m_hasPopupPlantTrial;
    
    int                                 m_endlessCurrentRank;
    DangerRoomLevelType                 m_currentDangerRoomLevel;
    DangerRoomLifeData                  m_currentLifeData;
    time_t                              m_lastLifeResetTimeStamp;
    time_t                              m_lastLevelResetTimeStamp;
	std::vector<PlantAccessoryInfo>		m_plantAccessoryInfos;
    std::vector<PlantFamilyInfo>        m_plantFamilyInfos;
    bool                                m_gmMadeProfile;
    
    std::vector<int>                    m_riddlesHasAnswered;
    std::vector<int>                    m_riddlesGotToday;
    int                                 m_riddlesAnsweredToday;
    int                                 m_riddlesCorrectNum;
    int                                 m_riddlesAnsweredDays;
    int                                 m_riddlesPrizeGotIndex;
    int                                 m_riddlesCorrectTotal;
    time_t                              m_lastRiddleTimeStamp;
    
    int                                 m_redPackRank;
    int                                 m_redPackOpenTotal;
    bool                                m_bRedPackRewardRankGet;
    
    int                                 m_iMiniGameActivityRewardMul;
    int                                 m_iMiniGameActivityCurLv;
    bool                                m_bMiniGameBonusGet;

	uint8                               m_rechargeGiftTimes;
	uint8                               m_rechargeGiftCached;
    
    int                                 m_lastBossLevel;
    ProbabilitySet<int>                 m_bossFightLevels;
    bool                                m_bossFightToday;
    bool                                m_playingBossFightLevels;

	std::vector<LevelLostInfo>          m_vecLevelLostInfo;

	// Update reward sign for last version
	int									m_lastUpdateRewardVersion;
	bool								m_isNewUpdate;
    int									m_lastGateUnlocked;
    std::vector<std::string>			m_worldAnimPlayed;
    std::vector<PlantTrialCD>           m_vPlantTrialCD;
    std::vector<std::string>            m_vPlantTrialRecord;
    std::string                         m_strRiddlesTopicName;
    std::string                         m_strConsumptionTopicName;
    int                                 m_iConsumptionRewardCount;
    int                                 m_iConsumptionGems;
	int									m_nLotteryConsumptionGems;

	int 								m_ConsumptionActivityGems;// for ConsumeAndRecieve Activity

	int									m_nLotteryTimes;
    
    std::vector<BattleArrayComponent>   m_battleArrayRecords;
    
    std::vector<DailyAchievementRecord> m_dailyAchievementRecords;
    time_t                              m_dailyAchiRecordTime;
    
    std::vector<std::string>            m_vNationalDayDate;
    
    bool                                m_bTwoYearBirthdayRewardGet;
    
    bool                                m_bTwoYearWeChatShare;
    bool                                m_bModernWeChatShare;
    std::vector<BirthZRecord>           m_vBirthZRecord;
    std::vector<int>					m_hasHouse;
    bool                                m_unlockPVP;
    bool                                m_nationalGacha;
    std::string                         m_specialAvatarBonuns;
    
    PVPTutorialState                    m_pvpTutorialState;
    
    int                                 m_todayChristmasProtectCurrency;
    int                                 m_nChristmasLotteryPlantIndex;
    int                                 m_nChristmasLotteryIndex;
    bool                                m_hasPvpAccount;
    int                                 m_iHasRebateReward;
    std::vector<int>                    m_vRebateRewardState;
    int                                 m_iRebateCharge;
    bool                                m_bShowEvilDavidIntro;
    
    int                                 m_headshotId = 0;
    
    std::string                         m_strActivityTopic;
    
    std::vector<RebateSingleRecord>     m_vRebateSingleRecord;
    
    PvpShopInfo                         m_pvpShopInfo;
    uint64                              m_newPlaybackID;    // record for identifying if there's new battle which is not read in PlaybackDlg
    
    int                                  m_childrenDayStart;
    int                                  m_childrenDayBuyCount;
    int                                  m_childrenDayBuyLimit;
    std::string                          m_childrenDayVersion;
    int									 m_vaseBreakerActId;
    
    // Training Room
    std::string							m_currentTrainingWorldName;
    std::vector<DangerRoomTrainingRecord> m_trainingRecords;
    
    
    std::vector<int> m_unlockHeadShotIds;
    
    std::vector<int> m_unlockRankAvatarIds;
    int              m_currentRankAvatar;

    std::vector<PurchasedBundleInfo> m_bundlePurchaseInfo;
    std::vector<std::string> m_purchasedPlantTrial;
    std::vector<WorldPackInfo> m_purchasedWorldPack;

//#ifdef HOST_IPHONEOS
    std::map<std::string, int> m_plantChipList;
    std::map<std::string, int> m_avatarChipList;
    std::map<std::string, int> m_pendantList;
    std::map<std::string, int> m_pendantChipList;
//#endif
    
#ifdef HOST_ANDROID
    std::vector<MaterialInfo>   m_materialList;
#else
    std::map<int, int>          m_materialList;
#endif
    std::vector<BossKillTimeChallengeInfo>     m_bossKillTimeChallenge;
    
    int                                 m_twLoginDays           = 0;
    int                                 m_twLastRewardTime      = 0;
    std::string                         m_twDailySignVersion    = "";
    
    bool                                m_bHasPurchaseCukePkg;

    int									m_currentAdsRate;
    int									m_currentDaveShopAdsRate;

    time_t                              m_plantBundleBuyTime;
    int									m_plantBundleLeftBuy;

    std::vector<NationalShopItem>       m_shopItems;

    std::vector<FestivalShopItem>       m_festivalShopItems;
    
    std::vector<FestivalShopItem>       m_anniversaryShopItems;

	bool m_bIsAuthIDCard;

    time_t                              m_lastZmatchShopRefrashTime;

	//for oppo
#ifdef HOST_ANDROID
	time_t                              m_newProfileCreatedTime;
	std::vector<std::string>			m_offeredBundles;
	time_t								m_oppoDailyLoginGotTime;
	int									m_oppoDailyRewardDays;

	ACLogProfile						m_acLogData;
	std::string							m_aclog;
	std::string							m_aclk;
	uint32								m_aclInfo;
    std::vector<SynInfo>                m_groupBuyRecord;
#endif
	bool								m_hasPlayedWorldCup;
	uint32								m_monthlyCardType;
	time_t								m_monthlyCardRemindFirstTime;
	time_t								m_monthlyCardRemindSecondTime;
	
	// Rift
	serializable_time_t                     m_riftCurrentID;
	serializable_time_t                     m_riftCurrentSubID;
	uint64									m_riftProgressBitfieldDifficulty0;
	uint64									m_riftProgressBitfieldDifficulty1;
	uint64									m_riftProgressBitfieldDifficulty2;
	serializable_time_t						m_zombossNextAvailableTime;
	int										m_zombossFightsThisCycle;

	// PVZ1
	uint64									m_pvz1ProgressBitfieldDifficulty0;
	uint64									m_pvz1ProgressBitfieldDifficulty1;

    //Uncharted
    uint64									m_UnchartedProgressBitfieldDifficulty0;
	uint64									m_UnchartedProgressBitfieldDifficulty1;

	//Card Game
	uint64									m_CardGameProgressBitfieldDifficulty0;
	uint64									m_CardGameProgressBitfieldDifficulty1;

	std::vector<ArcadePackProgress>		    m_arcadeProgress;
	std::vector<PowerUpCollectionProgress>	m_powerUpCollections;
    std::vector<NextPopData>                m_nextdayPopGameStart;

    std::vector<TravelLogTaskSaveInfo>      m_travelLogTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_daveTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_pennyTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_happyVaseBreakerTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_noviceSevenDaysTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_callofWishTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_pvz1AchievementInfos;
    std::vector<PvZ1LevelCompleteInfo>      m_pvz1HardLevelCompleteInfos;
    std::vector<PvZ1LevelCompleteInfo>      m_pvz1NormalLevelCompleteInfos;
    std::vector<TravelLogTaskSaveInfo>      m_goldenEggTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_arborDayTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_battleOrderTaskInfos;
    std::vector<TravelLogTaskSaveInfo>		m_newPVPTaskInfos;
    std::vector<TravelLogTaskSaveInfo>		m_unchartedBirthdayTaskInfos;
    std::map<std::string, std::vector<TravelLogTaskSaveInfo> > m_unchartedTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_cornucopiaTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_plantCultivateTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_giftFoReturnTaskInfos;
    std::vector<TravelLogTaskSaveInfo>      m_daveKitchenTaskInfos;
    std::vector<EventTimesRecord>           m_eventRecord;


    std::vector<std::string>                m_pvz1BeatEliteZombieList;
    int                                     m_currentDaveTreasureVersion;
    int                                     m_currentPennyGuideVersion;
    int                                     m_currentHappyVaseBreakerVersion;
    int                                     m_consumeAndReceiveVersion;
    int                                     m_currentBattleOrderVersion;
    int										m_currentNewPVPBattlePassVersion;
    int										m_currentUnchartedBirthdayVersion;
    std::map<std::string, int>				m_currentUnchartedTaskVersions;

#ifdef HOST_ANDROID
    int                                     m_limitGachaDrawTimesOne;
    int                                     m_limitGachaDrawTimesTen;
#endif

#ifdef HOST_ANDROID
    // zhousen for advertisement watching
    AdvertisementWatchTimeInfo              m_advertisementWatchTimeInfo;
    AdvertisementWatchCountInfo             m_advertisementWatchCountInfo;
#endif
    std::map<std::string, time_t>			m_worldLevelPackageStartTimeMap;// when star get, apply current time to map. key is worldName + 1,2,3
    bool									m_worldLevelPackageFirstPlay;// first pop up ui.

    CheatingCheckFlags                      m_CheatingCheckFlags;// cheating check flag

    RichmanBattleEventSaveData              m_richmanBattleEventData;// for richman game save data
    RichmanGameSaveData                     m_richmanGameSaveData;// for richman game
    DangerRoomSpecialOfferSaveData          m_dangerRoomSpecialOfferSaveData;// for danger room special offer
    bool                                    m_authVerifyRewarded;//
    bool									m_riftStoreFirstEntered;
    bool									m_newPVPTrainingFirstEntered;
    bool									m_tutorialFirstChecked;
    std::vector<PlayerFlagInfo>             m_playerFlagInfos;
    std::vector<PlayerStorageData>          m_playerStorageInfos;
    bool									m_pvz1ModeTutorialFinished;
    bool									m_pvz1modeFirstPlay;
    bool									m_customLevelFirstPlay;
    bool									m_hasGotCustomLevelTutorialLevel;
    int										m_pennyClassroomTestIndex;// from 0 ~ 9.
    bool									m_customLevelGuessLikeEnable;// if can show guess like
    int										m_pvz2UnchartedModeWorldCount;
    std::vector<int>						m_newPVPSelectedPlants;
    bool									m_unchartedAnniversaryReward;
    int 									m_unchartedAnniversaryRewardVersion;
    std::map<std::string, UnchartedWorldAnniversaryBonusInfo> m_unchartedWorldAnniversaryBonusInfos;
};

// -----------------------------------------------------------------------------

typedef RtWeakPtr<class PlayerInfo> PlayerInfoPtr;
    
class MagentoProductProps;
namespace Message
{
    void CoinCurrencyChanged(int i_newAmount);
    void StarCurrencyChanged(int i_newAmount);
    void LeafCurrencyChanged(int i_newAmount);
    void ItemPurchasedFromStore(MagentoProductProps* i_props);
    void CoinsPurchasedFromStore(int i_amount);
    void KeygatePurchasedFromStore(MagentoProductProps* i_props);
    void StargatePurchasedFromStore(MagentoProductProps* i_props);
    void CartInstanceEvent(MagentoProductProps* i_props);
    void KeyCurrencyChanged();
	void StarCompleted(const std::string& i_eventName);
	void GemCurrencyChanged(int i_amount);
    void GemCurrencyAdd(int i_delta);
	void GemsPurchasedFromStore(int i_amount);
    void ZmatchTicketChanged(int i_amount);
    void ZmatchTicketAdd(int i_delta);
	void ZmatchTicketPurchasedFromStore(int i_amount);
    void CloseCurrentGemProductNotice(const std::string & sSku);
    void PlantUnlocked(const std::string& i_plantName);
    void BombUnlocked();
    void GetCoinsFromPlantBag();
    void RechargeCurrencyChanged();
    void RechargeRewardCurrencyChanged(int i_num);
    void RechargeBundlePurchased(int objectId);
    void RechargeBundleBeforePurchased(int objectId);
    void BuyNewerPresent();
    void RechargeBundleShowed();

    //cardPlay for chinamobilemm
    void CardPlayBuyFinish();
    
    void FestivalGameModeCountChange();
    void ServerTimeReceived();
    void PlantTrialPay(bool i_success);
    void GemReturnSuccess();
    void TodayMaxRechargeChange();
    void PlantTrialPaySuccess();
	void BuyItemPaySuccess();
    void PlantGiftPaymentSuccess();

    void LuaNotifyGeneral(const std::string& strNotify);    // use message router
    void OnLuaNotify(const std::string& strTag);            // direct call from Lua
    
    void NotifyPowerupUsesChanged(class PowerupRecord* i_record);

    void MaterialChanged();

    void RiftIDChanged(serializable_time_t i_riftID);
    void PennyTechChanged(int i_delta);
    void PennyFuelCurrencyChanged(int i_delta, const bool i_willBeBankedLater, int type);
}
    
#endif //__PLAYERINFO_H__
