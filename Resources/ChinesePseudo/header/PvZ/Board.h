#ifndef __BOARD_H__
#define __BOARD_H__

#include "MessageWidgetEnums.h"
#include "PvZ2IDs.h"
#include "BoardEnums.h"
#include "BoardConstants.h"
#include "AnimationMgr.h"
#include "GameInputHandler.h"
#include "PlantPot.h"
#include "PVZTypes.h"
#include "LevelModuleManager.h"
#include "OutroModule.h"
#include "Outros.h"
//#include "PlayerInfo.h"
//#include "GameOverDialog.h"
//#include "MetricsCollector.h"
#include "Renderable.h"
#include "SeedPacket.h"
//#include "PrimeTextWidget.h"
#include "EntityFinder.h"
#include "Wave.h"
#include "LawnKeyField.h"
#include "Wave.h"
//#include "Plant_CarrotLauncher.h"
#include "BoardRegion.h"
#include "DangerRoomDropInfo.h"
//#include "ArenaZombieCursor.h"
//#include "PVZ2UIAwardScreen.h"
#include "LawnApp.h"
//#include "ArtifactMgr.h"

#ifdef HOST_ANDROID
#include "EASquared.h"
#endif

class EffectObject;
class CollectableSun;
class CollectablePlantfood;
class CollectablePlantUpgrade;
class CollectableCoin;
class CollectableCoinFake;
class CollectableGemFake;
class SeedPacket;
class Plant;
class PlantGroupSubsystem;
class Zombie;
class Creature;
class BoardSaveState;

namespace ProfileUtils
{
	struct ChallengeStatusHolder;
}

typedef RtWeakPtr<class Zombie> ZombiePtr;

enum DebugTextMode
{
	DEBUG_TEXT_NONE,
	DEBUG_TEXT_ZOMBIE_SPAWN,
	DEBUG_TEXT_MUSIC,
	DEBUG_TEXT_MEMORY,
	DEBUG_TEXT_COLLISION,
	DEBUG_TEXT_LIFEBARS,
	DEBUG_TEXT_STREET,
	DEBUG_TEXT_END,
};

const int MAX_GRIDSIZEX = 18;
const int MAX_GRIDSIZEY = 10;

const int STREET_GRID_SIZE_X = 9;
const int STREET_GRID_SIZE_Y = 10;

STATE_ENUM_BASE_BEGIN(IntroState)
	IntroState_INIT,
	IntroState_LAUNCHING,
	IntroState_END,
	IntroState_ZOMBOSS,
STATE_ENUM_END(IntroState);

// BoardState
//	- Internal state of the board. Should be ordered in *roughly* the order they are entered during a normal game.
enum BoardState 
{
	PVZ_BEGIN_ENUM(BOARDSTATE_),
	// Initialization
	BOARDSTATE_INITIAL,							// Initial state
	BOARDSTATE_LOADING_LEVEL,					// Set from board::InitLevel, after level logic initialized. Stays until loading is complete
	
	BOARDSTATE_LOADING_SAVE,					// Set from board::InitLevelForLoadgame, when we are resuming from a saved session
	
	// Level intro
	BOARDSTATE_LEVEL_INTRO,						// Plays out the level intro
	BOARDSTATE_TUTORIAL,						// Entered manually from tutorial IntroModules, not always used

	// Gameplay
	BOARDSTATE_PLAYING_LEVEL,					// Set during all game play, NOT during tutorials?
	
	// Cinema
	BOARDSTATE_CINEMA,							// Set during the opening cinema scene. Could use for other stuff if we want.

	// Player victory state
	BOARDSTATE_PLAYER_WON_OUTRO,
	
	BOARDSTATE_PLAYER_LOSS_AVERSION_PLAYING,

	// Player loss state
	BOARDSTATE_PLAYER_LOST_OUTRO,				// Set from TriggerPlayerLoss
	
	// Post-level cleanup
	BOARDSTATE_ENDLEVEL,						// We sit in this state until we've loaded the world map, then we transition back to it

	PVZ_END_ENUM(BOARDSTATE_),
};

typedef Delegate1wRet<bool, BoardEntity*> EntitySearchAcceptDelegateType;
typedef Event1wRet<EventReturnBehavior::LogicalAnd_ShortCircuit_DefaultTrue, bool, BoardEntity*> EntitySearchAcceptEventType;

enum RandomSeedSource
{
	PVZ_BEGIN_FLAG_ENUM(SEED_),
	PVZ_FLAG(SEED_CurrentTime),
	PVZ_FLAG(SEED_AppLaunchTime),
	PVZ_FLAG(SEED_PlayerSpecific),
	PVZ_FLAG(SEED_LevelSpecific),
	PVZ_FLAG(SEED_LevelPlayCount),
	PVZ_END_FLAG_ENUM(SEED_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(RandomSeedSource);
uint32 CalcRandomSeed(RandomSeedSource i_sources);

struct WarningData
{
	int x;
	int y;
	int width;
	int height;
	WarningData()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
};

struct FinalWarningPointData
{
	int col;
	int row;
	FinalWarningPointData()
	{
		col = 0;
		row = 0;
	}
};

struct LootStats
{
	LootStats()
	{
		NothingCount = 0;
		SilverCount = 0;
		GoldCount = 0;
		DiamondCount = 0;
		PowerupCount = 0;
        ComponentCount = 0;

		NoKeyCount = 0;
		KeyCount = 0;
	}

	int NothingCount;
	int SilverCount;
	int GoldCount;
	int DiamondCount;
	int PowerupCount;
    int ComponentCount;

	int NoKeyCount;
	int KeyCount;
};

struct BoardPanLocations
{
	BoardPanLocations()
	{
		HouseX = 0;
		GameX = 0;
		ZombieX = 0;
		BoardEdgeX = 0;
	};
	
	int HouseX;
	int GameX;
	int ZombieX;
	int BoardEdgeX;
};


enum PieceType
{
    PT_PLANT_PIECE = 0,
    PT_AVATAR_PIECE,
    PT_ACESSORY,
};

struct CollectedPiece
{
    std::string     pieceName;
    PieceType       pieceType;
    PlantAvatarType avatarPieceType;
    int32           pieceCount;
    bool 			ad;
    
    CollectedPiece()
    {
        pieceType       = PT_PLANT_PIECE;
        avatarPieceType = E_AVATAR_NONE;
        pieceCount      = 0;
        ad				= false;
    }
};

struct ZombieJuggledData
{
	ZombieJuggledData()
	{
		MaxProjectilesToJuggle = 0;
		JuggleLaunchDelay = 0.0f;
		MoveSpeedMultiplierWhileJuggling = 0.0f;
		CatchArcDegrees = 0.0f;
		IsActivated = false;
		IsSpecialMode = false;
	}

	SexyVector3 LaunchVelocity;
	SexyVector3 LaunchAcceleration;
	ValueRange LaunchHeight;

	int MaxProjectilesToJuggle;
	float JuggleLaunchDelay;
	float MoveSpeedMultiplierWhileJuggling;
	float CatchArcDegrees;

	std::vector<std::string> JuggleableProjectiles;
	std::vector<std::string> UnthrowableProjectiles;
	std::vector<std::string> AngleAgnosticProjectiles;
	bool IsActivated;
	bool IsSpecialMode;
};

struct ZombieReachLineData
{
	ZombieReachLineData()
	{
		Position = 0.0f;
		IsActivated = false;
	}

	float Position;
	bool IsActivated;
};

struct PlantReducedRangeData
{
	PlantReducedRangeData()
	{
		ReducedGrids = 0;
		IsActivated = false;
	}

	int ReducedGrids;
	bool IsActivated;
	PlantRestrictionSet TargetablePlantTypes;
};

///
/// Board - main level state and data.
///
class Board : public Widget, public ButtonListener
{
public:
	RT_CLASS_DEFINE(Board, RtObject, RtClass);

	Board();
	virtual ~Board();

	virtual bool CanSaveGameState();
	void SaveGameState(bool i_special);
	void LoadGameState(bool i_special);
	void PreSave(BoardSaveState* i_saveState);
	void PostLoad(BoardSaveState* i_saveState);
	void GetGameplayResourceGroups(std::vector<std::string>& o_resourceGroups);

	// Gameplay Input Handling
	void RegisterTouchGameplayObject(GameInputDelegate i_touchDelegate, const int i_priority, BoardEntityPtr i_boardEntity=BoardEntityPtr(), CancelInputDelegate i_cancelDelegate=CancelInputDelegate());
	void UnregisterTouchGameplayObject(void* i_touchOwner);
	void CancelTouch(const Sexy::Touch& i_touch, void* i_ignoredDelegateOwner=NULL);
	void RegisterGesture(GestureDelegate i_pinchDelegate);
	void UnregisterGesture(void* i_gestureOwner);
	
	void RegisterLongPress(LongPressDelegate i_longPressDelegate);
	void UnregisterLongPress(void* i_longPressOwner);

    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
	virtual void TouchMoved( const Sexy::Touch& i_touch ) override;
	virtual	void TouchEnded( const Sexy::Touch& i_touch ) override;
	virtual void TouchesCanceled() override;
	virtual void OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta) override;
	virtual void OnGestureLongPress(Sexy::Point i_startingLocation) override;

	virtual void Resize(int theX, int theY, int theWidth, int theHeight) override;
	virtual void Move(int i_newX, int i_newY) override;

	virtual void KeyChar(SexyChar i_char) override;
	virtual void KeyDown(KeyCode i_key) override;
	
	virtual bool Contains(int i_mouseX, int i_mouseY) override;
	
	class WaveGenerator* GetWaveGenerator();
	
	class WaveManager* GetWaveManager();

	BoardResult GetBoardResult();
	
    EndOfPlayReason		GetReasonPlayEnded() const;
    bool				PlayEndedInVictory() const;
    
    bool GetHasPlayerPreviouslyCompletedLevel();
    void SetHasPlayerPreviouslyCompletedLevel(bool i_override);
	
	// Test functions
	void TestSpawnAllPlants();
	Plant* TestSpawnPlant(const std::string& i_plantTypeName, int i_x, int i_y);
	void TestSpawnRandomPlants();
	void TestPlantFoodAllPlants();
	
	int CountSunBeingCollected();

	bool CanPlantsAttack() const { return m_plantsCanAttack; }
	void SetPlantsCanAttack(const bool i_plantsCanAttack) { m_plantsCanAttack = i_plantsCanAttack; }
	bool ManualPlantsActive() const { return m_manualPlantsActive; }
	void ActivateManualPlants(const bool i_manualPlantsActive) { m_manualPlantsActive = i_manualPlantsActive; }
	
	int	GetInitialLawnItemsCount() const;
	int GetUntriggeredLawnMowerCount();

	template<typename T>
	T* FindLawnItemInRow(int i_row) const;

	void InitLevel(const std::string& i_levelName, bool i_hardModule = false);
	void InitLevelForLoadGame(const std::string& i_levelName, bool i_hardModule = false);
	
	void LoadResourceGroupsForGameplay(const std::vector<std::string>& i_groupNames);
	void LoadResourceGroupForGameplay(const std::string& i_groupName);

    void DeleteResourceGroupsForGameplay(const std::vector<std::string>& i_ResourceGroupName);
    void DeleteResourceGroupForGameplay(const std::string& i_ResourceGroupName);

    void ParseBackground();
    void StartLevel();           	// starts the level (perhaps with a level intro)
    void EndLevel();  				// Asynchronously loads world map, returns to it as soon as loaded
    void PutIntoTutorialMode();
	void PutIntoCinemaMode();
    void EndCannonLevel();

    void ResumeGameplay();

	bool IsLevelEnded();
	bool IsCurrentLevelBeghouled();

	void SetGameplayObjectPause(bool i_paused);
	void SetSoftPause(bool i_paused);

	bool TryToAddCursor(class BaseCursor* i_cursor,bool isCallBack = true); // returns false if it won't add the cursor
	void SetCachedCursor(class BaseCursor* i_cursor);
	void MakeCachedCursorRealCursor();
	bool IsThereCachedCursor() const;
	void ClearCursors();
	void ClearCachedCursor();
    bool IsCachedCursor(const BaseCursor* i_cursor) const;
	void DrawCursorsOnBackground(Sexy::Graphics* i_g);
	const std::vector<class BaseCursor*> &GetCursors() { return m_cursors; }
	
	void AddPowerup(const std::string &i_powerupName);
	void AddConveyorPowerup(const std::string &i_powerupName);
	void RemovePowerup(const std::string &i_powerupName);
	void SelectPowerup(const PowerupType* i_powerupType, const bool i_ignoreCost=false);
	void ActivatePowerup();
	void DeactivatePowerup();
	void CancelActivePowerup();
	class BasePowerup* GetSelectedPowerup();
	class BasePowerup* GetActivePowerup();
    
    const std::string&  GetLevel() { return m_level; }
	const LevelDefinition* GetLevelDefinition() { return m_levelDefinition; }
	RtWeakPtr<LevelDefinition> GetLevelDefinitionPtr() { return m_levelDefinition; }
    
    bool GetLevelIsHard(){ return m_hardModule; }

    int GetCurrentZombieMaxLevel();
//PVZ2_CHINESE_BEGIN
	/*
	DropOutItemData* TryGetActivityDropItem();	//if this game has activity drop item ,get it. otherwise return null
	DropOutItemData* TryGetYetiDropItem();
	*/
	std::string TryGetYetiDropItemName();
    std::string TryGetYetiDirectDropItemName(std::string &strWorldName, std::string &strDifficult);
    std::string TryGargantuarDirectDropItemName(std::string &strWorldName, std::string &strDifficult);
    std::string TryDevilDirectDropItemName(std::string &strWorldName, std::string &strDifficult);
//PVZ2_CHINESE_END

	inline int GetLevelNumber() { return m_levelNumber; }
	bool IsStarChallengeActive();
	void SetActiveStarIndex(int i_newIndex) { m_activeStarIndex = i_newIndex; }
	int GetActiveStarIndex() { return m_activeStarIndex; }
	bool GetActiveChallengeAwardedThisPlaythrough();
	
	SexyString GetLevelNameForDisplay();
    
    void PlaceLawnItems();
	void ShowLawnItems();

	void StartBoardFade(const Color& i_endColor, pvztime_t i_duration, Delegate0 i_onCompletion = Delegate0());
	void StartBoardFade(const Color& i_startColor, const Color& i_endColor, pvztime_t duration, Delegate0 i_onCompletion = Delegate0());
	void KillBoardFadeOverlay();

    void PrepSeedBankForPlay();
    void PrepSeedBankForPicking();

	void DestroyAllMowers();
    
    void DestroyAllZombieProjectiles();
	void DestroyAllZombies();
    void DestroyZomboss();
	void DestroyCutsceneZombies();
    void DestroyCutsceneCreatures();
	void DeferCutsceneZombieDestruction() { m_DeferCutsceneZombieDestruction = true; }

    void RandFillToCol( int i_col );
	void MovePlant(Plant *i_plant, int i_gridX, int i_gridY, bool i_canMoveIntoOccupiedLocation = false);

    std::vector<Point> FindAllPlantableCells(PlantTypePtr i_plantType);
    bool                CanSpawnZombieAt(int i_gridX, int i_gridY);
    bool				CanSpawnDuskSeedAt(int i_gridX, int i_gridY);
    bool				CanSpawnIcePitAt(int i_gridX, int i_gridY);
    bool                CanPlantAt(const Sexy::Point& i_gridPosition, PlantTypePtr i_plantType);
	PlantingReason      GetCanPlantAtReason(const Sexy::Point& i_gridPosition, PlantTypePtr i_plantType, bool i_ignoreExistingPlant = false, int i_plantLevel = -1);
    
	const SexyString	GetSeedChooserWarnings(const std::vector<PlantTypePtr>& i_seedList);
	
	//launch state
	bool       			 	isInState(IntroState i_state) const;
	void        			setState(IntroState i_newState);
    
    void SetNeedShineKernelpult(bool i_shine = true);
    void UpdateKernelPultsShine();
    
	virtual void Update() override;
	
	void UpdateGame();
	void UpdateGameObjects();
	void UpdateLayers();
	void UpdateProgressMeter();
	void UpdateTutorial();

	virtual void Draw(Graphics* g) override;
	void DrawDebugLifeBars(Graphics* g);
	void DrawDebugObjectRects(Graphics* g);
	void DrawDebugText(Graphics* g);
	void DrawBoardFade(Graphics* g);
	void DrawGameObjects(Graphics* g);
	void DrawLevelName(Graphics* g);
	void DrawUITop(Graphics* g);
    void DrawRightHighlight(Graphics* g);
	void DrawCelHighlight(Graphics* g, const int i_col, const int i_row);
    void DrawCelPlantAnimation(Graphics* g, const int i_col, class OverwhelmCursor* i_cursor);
    void DrawScopeHighlight(Graphics* g, const int i_col, const int i_row, const int scope);
    void DrawArenaZombieHighlight(Graphics* g, const int i_row);
	void DrawGrid(Graphics* g);
	void DrawStreetGrid(Graphics* i_g);
	void DrawNonMaskedArea(Graphics* g, int x, int y, int w, int h);
    void DrawArenaZombieAnim(Graphics* g, class ArenaZombieCursor* i_cursor, int i_gridX, int i_gridY);
    
    void drawAdviceText(Graphics* i_g);

	bool MoveToDestination(const float i_destX, const float i_destY);
    
    static void DrawRenderQueuesInterleaved(const std::vector<RenderItem>& i_sortedQueueBoard, const std::vector<RenderItem>& i_sortedQueueUI, SexyMatrix3& i_boardScaleTransform, Graphics* i_g);

	void AddSunMoney(const int i_amount);
	bool TakeSunMoney(int i_amount, bool i_force = false, bool i_theme = false);
    void SetSunMoney(int i_amount);
	bool CanTakeSunMoney(const int i_amount);

	bool RowCanHaveZombieType(int i_row, ZombieTypePtr i_zombieType);
	bool RowCanHaveZombies(int i_row);
	
	int GetPlantedPacketCount(const std::string& i_packetType);
    
    int GetPlantedPacketCountForConveyorBelt(const struct ConveyorPlantEntry& i_plantListItem);

	void GetOpenedPresentTablesAndContents(std::vector<RtWeakPtr<const class PresentTable> >& o_openedTables, std::vector<RtWeakPtr<const class PresentType> >& o_openedPresents);
//PVZ2_CHINESE_BEGIN
	void GetOpenedActivityPresentContents(std::vector<RtWeakPtr<const class PresentType> > &o_openedActivityPresents);
//PVZ2_CHINESE_END
    
	// Collectable spawning
    class Collectable* AddCollectableWithDefaultMotion(const std::string& i_collectableTypeName, const SexyVector3& i_pos);
	class Collectable* AddCollectable(const std::string& i_collectableTypeName);
	
	// Collectable tossing
	void FanOutCollectables(const std::vector<class Collectable*>& i_collectables, const SexyVector3& i_pos) const;
	void SpewOutCollectables(const std::vector<class Collectable*>& i_collectables, const SexyVector3& i_pos) const;

	// Specialized Collectable spawning
	class CollectablePowerup*       AddPowerupCollectable(const SexyVector3& i_position, const std::string& i_powerupType);
	class CollectablePlantfood* 	AddPlantfood(const SexyVector3& i_position, int pfCategory = 0);
    class CollectableSpacetimeEnergy*   AddSpacetimeEnergy(const SexyVector3& i_position, int i_energyValue);
    class CollectableHeroPlantFakeSun*  AddHeroPlantFakeSun(const SexyVector3& i_position, int i_sunValue);
    class CollectablePlantUpgrade* 	AddPlantUpgrade(const SexyVector3& i_position);
	class CollectableCoin* 			AddCoin(const SexyVector3& i_position, const std::string& i_coinType);
	class CollectableCoinFake* 		AddCoinFake(const SexyVector3& i_position, const std::string& i_coinType);
    class CollectableCoinDangerDrop*AddCoinDangerDrop(const SexyVector3& i_position, const std::string& i_coinType);
	class CollectableGemFake* 		AddGemFake(const SexyVector3& i_position, const std::string& i_coinType);
	class CollectablePresent* 		AddPresent(const SexyVector3& i_position, bool i_isShiny);
    class Collectable *             AddDirectCollectable(const SexyVector3& i_position, const std::string& i_TypeName);
    class CollectableDRMadal *      AddDRMadal(const SexyVector3& i_position, const std::string& i_TypeName);
    
    std::vector<class Collectable*>   ShowGemFake(const SexyVector3& i_position, const std::string& i_coinType, int i_num);
    
    void  AddNewerPresent(const Sexy::SexyVector3 &i_position, bool bAdvance);
    
    bool                            IsWorldNeedDropKey(std::string& i_worldName);
	class Collectable*				AddStageSpecificKey(const SexyVector3& i_position);
    class Collectable*				AddUpgradeComponent(const SexyVector3& i_position);
    
    void TossCollectableOntoBoard(Collectable* i_collectable) const;
    
    // Specialized Collectable spawning
    void SplitSun(int i_sunCurrency, bool i_roundUp, int& o_smallSun, int& o_largeSun, int& o_remainder);
    void FanOutSun(const SexyVector3& i_pos, int i_sunCurrency, bool i_roundUp, bool i_useGravity, bool i_autoCollect, bool i_dropByZombie = false);
	
	// Plant spawning
    std::vector<Plant*> AddPlants(const std::string& i_plantTypeName, int i_minColumn, int i_maxColumn, int i_count, int i_level = 1);
    std::vector<Plant*> AddPlants(PlantTypePtr i_plantType, int i_minColumn, int i_maxColumn, int i_count, int i_level = 1);

	Plant* AddPlant(int i_gridX, int i_gridY, const std::string& i_plantTypeName, int i_level=-1, bool i_useBoost = false, bool duplicate = false, bool ignore_plantfood = false);
	Plant* AddPlant(int i_gridX, int i_gridY, PlantTypePtr i_plantType, bool bAvatarEnable = true, bool bLevelEnable = true, int i_level=-1, bool i_useBoost = false, bool playlevelEffect = true, bool playPlantingEffect = true, bool duplicate = false, bool ignore_plantfood = false, uint32 i_seed = 0, float i_extraValue = 0.0f);
    
	// Projectile spawning
	class Projectile* AddProjectile(float i_x, float i_y, float i_height, RtWeakPtr<class ProjectilePropertySheet> i_projectileProps, class BoardEntity* i_instigator = NULL, int i_pierceCount = 0);
    
    // Creature spawning
    Creature* CheatAddCreature(CreatureTypePtr i_creatureType, int i_spawnInRow = -1);
    Creature* AddCreature(CreatureTypePtr i_zombieType);
    Creature* AddCreatureInRow(CreatureTypePtr i_zombieType, int i_spawnInRow, int i_duration = 0);
    void PlaceCreatureInRow(Creature* i_creature, int i_spawnInRow, int i_duration = 0);
    Creature* SpawnCreature(CreatureTypePtr i_zombieType);
    void DestroyAllCreatures();

	// Armor spawning
	class Armor* AddArmor(RtWeakPtr<class ArmorPropertySheet> i_projectileProps, class BoardEntity* i_owner);

    struct SpawnZombieParams
    {
    public:
        int  m_level = 1;
        bool m_bIntro = false;
        bool m_bSkipDifficultLevel = false;
        bool m_bAccessory = false;  // mark if the zombie is spawned by another zombie
        bool m_levellock = false;
        int m_packetLevel = 0;
        uint32 m_seed = 0;
    };
    
	// Zombie spawning
	Zombie*	AddZombie(ZombieTypePtr i_zombieType, int i_fromWaveNumber, int i_level = 1, bool i_isIntro = false, bool i_skipDifficultLevel = false);
	Zombie*	AddZombieInRow(ZombieTypePtr i_zombieType, int i_spawnInRow, int i_fromWaveNumber, SpawnZombieParams* pParams = nullptr, bool i_random = true, bool i_placeOnBoard = true);
    Zombie* CheatAddZombie(ZombieTypePtr i_zombieType, int i_spawnInRow = -1, bool i_random = true);
    ZombieTypePtr   GetZombieType(const std::string& i_zombieName);
    
	virtual Zombie* SpawnZombie(ZombieTypePtr i_zombieType, int i_spawnedFromWave, SpawnZombieParams* pParams = nullptr);
    Zombie* SpawnZombieHelper(ZombieTypePtr i_zombieType, int i_spawnedFromWave, bool i_checkAlmanac, SpawnZombieParams* pParams = nullptr);
	void PlaceZombieInRow(Zombie* i_zombie);
	void PlaceZombieInRow(Zombie* i_zombie, int i_spawnInRow, bool i_random = true, bool i_placeOnBoard = true);
    
    Zombie* PlaceAStreetZombie(ZombieTypePtr i_zombieType, int i_gridX, int i_gridY, int i_level = 1);
    void PlaceAStreetCreature(CreatureTypePtr i_creatureType, int i_row, int i_placementX, bool i_walkIn);

	// Puts the zombie in a list so we don't have to iterate over the RtDB table
	// in performance critical sections of our code.
	void AddCachedZombie(Zombie* i_zombie);
	void RemoveCachedZombie(Zombie* i_zombie);
	void RemoveDeferredDeleteCachedZombies();
    void ClearZombie();
	const std::vector<Zombie*>& GetZombies();

	// StandaloneEffect spawning
	class StandaloneEffect* AddEffect(RtClass* i_effectClass);
	template<typename T>
	T* AddEffect();
	
	GridItem* GetGridItemAt(const std::string& i_type, int i_gridX, int i_gridY);
    void GetGridItemsAt(int i_gridX, int i_gridY, std::vector<GridItem*>& o_gridItems);
    class GridItemGravestone* GetGridItemGravestone(int i_gridX, int i_gridY);
    
    template <typename T>
	T* GetGridItemAt(int i_gridX, int i_gridY)
	{
		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesAtGridSquare(entities, ENTITYTYPE_GRIDITEM, i_gridX, i_gridY);
        
		for (auto entity : entities)
		{
			T* gridItem = entity->Cast<T>();
			if (gridItem)
			{
				return gridItem;
			}
		}
		return NULL;
	}

    PlantPot* 		AddPlantPot(int i_gridX, int i_gridY, ImagePtr potImage, float offsetY = 0);

    void            SetGridSquareType(int i_gridX, int i_gridY, GridSquareType i_type);
    GridSquareType  GetGridSquareType(int i_gridX, int i_gridY);
	
	bool			IsPitOfDoom(const Point& i_gridLoc);
	bool			IsPitOfDoom(const SexyVector3& i_position);
	void			DoPitOfDoomEffects(const SexyVector3& i_entityLocation, BoardEntity* i_doomedEntity);
	void			DoEntityLandedEffects(const SexyVector3& i_entityLocation, BoardEntity* i_landingEntity);
    
    bool                        IsShallowWater(const Point& i_gridLoc);
	bool                        IsShallowWater(const SexyVector3& i_position);
    bool                        IsSky(const Point &i_gridLoc);
    bool                        IsSky(const Sexy::SexyVector3 &i_position);
    bool                        IsRoof(const Point &i_gridLoc);
    bool                        IsRoof(const Sexy::SexyVector3 &i_position);
    
    class BoardRegion*          AddRegion(RtClass* i_regionClass);
    template<typename T>
	T* AddRegion()
    {
        return AddRegion(T::StaticGetClass())->template CastChecked<T>();
    }
    
    class BoardRegion*          FindRegionWithFlags(BoardRegionFlags i_flags);
	class BoardRegion*          FindRegionWithFlags(const Point& i_gridLoc, BoardRegionFlags i_flags);
	class BoardRegion*          FindRegionWithFlags(const SexyVector3& i_position, BoardRegionFlags i_flags);
    
	inline void			SetOutroType(OutroType i_outroType);
	inline OutroType	GetOutroType();

	inline void			SetLevelNumber(const int i_levelNumber);
	
	void InitPlantGroupSystem();

	void SetLevelNameOverride(const SexyString& i_name);
	
	StageModule* GetStage();
	template<typename T>
	T* GetLevelModuleByClass();
	
	const class BoardPropertySheet* GetBoardProperties() const;

	Zombie* GetWinningZombie();

	GridItem* AddGridItem(const std::string& i_gridItemTypeName, int i_gridX, int i_gridY, int i_level = 1);
	GridItem* AddGridItem(GridItemTypePtr i_gridItemType, int i_gridX, int i_gridY, int i_level=1);
    GridItem* AddGridItemUnbounded(const std::string& i_gridItemTypeName, int i_gridX, int i_gridY, int i_level = 1);
    GridItem* AddGridItemUnbounded(GridItemTypePtr i_gridItemType, int i_gridX, int i_gridY, int i_level = 1);
    
    EffectObject* AddEffectObject(const std::string &i_effectObjectTypeName, int i_gridX, int i_gridY);
	EffectObject* AddEffectObject(EffectObjectTypePtr i_type, int i_gridX, int i_gridY);

    bool CanAddGraveStoneAt(int i_gridX, int i_gridY, bool i_ignorePlants);
    
    bool CanAddArmrackAt(int i_gridX, int i_gridY);

	bool ChooseSeedsOnCurrentLevel();
    
    bool IsPaused() { return m_paused; }
    bool IsPlaying() { return GetState() == BOARDSTATE_PLAYING_LEVEL; }
	bool IsGameplayEnded();
    
    void EnableGridItems();

	int CountZombiesOnScreen(bool i_squidified = false);
	int CountDamagableGridItemsOnScreen();
    
	static int MakeRenderOrder(RenderLayer i_renderLayer, int i_row, int i_layerOffset);
    static int MakeGroundRenderOrder(int i_row, int i_layerOffset);

    void ClearAdvice();
	void ClearAdvice(const SexyString& i_advice);
    void ClearLowPriorityAdvice();
	void ClearAdviceImmediately();
	void DisplayAdvice(const SexyString& i_advice, MessageStyle i_messageStyle, AdvicePriority i_advicePriority = ADVICE_PRIORITY_HIGH);
	void DisplayAdviceAgain(const SexyString& i_advice, MessageStyle i_messageStyle, AdvicePriority i_advicePriority = ADVICE_PRIORITY_HIGH);
    void GiveAdvice(const int i_gridX, const int i_gridY, PlantTypePtr i_plantPtr, PlantingReason i_reason);

	void DoPlantingEffects(int i_gridX, int i_gridY, Plant *i_plant);

    // plant group functions begin
    bool HasPlantAt(Plant* i_plant, const Sexy::Point& i_gridPosition);
    bool HasPlantAt(const Sexy::Point& i_gridPosition);
    PlantGroupSubsystem* GetPlantGroupSubsystem()        { return m_plantGroupSubsystemCache; }
    class PlantGroup* GetPlantGroupAt(int i_column, int i_row) { Point point = Point(i_column, i_row); return GetPlantGroupAt(point); }
    class PlantGroup* GetPlantGroupAt(const Sexy::Point& i_gridPosition);
    class PlantGroup* FindPlantGroup(Plant* i_plant);
    int GetPlantsCountInARow(int i_row, bool i_considerMoreThanOnePlantInACellAsOne);
    Plant* GetPlantAt(const Sexy::Point& i_gridPosition, MultiPlantGridLayer i_layer);
    const std::vector<PlantPtr>& GetPlantsAt(const Sexy::Point& i_gridPosition);
    const std::vector<PlantGroupPtr>& GetAllActivePlantGroups();
    bool TryGetValidRelocationPosition(const Rect& i_excludedArea, Point i_originalPlantGridPosition, std::vector<PlantPtr> i_originalPlants, Point& o_validPosition);
    // plant group functions end
    
    Plant *     GetPlantAt(int i_gridX, int i_gridY, const std::string& ignoreType = "");
    Zombie *    GetZombieAt(int i_gridX, int i_gridY);
    
	int 	GetPlantsCostInRow(int i_row);
    
	void InitLawnMowers();
    
	void DestroyAllPlants();
	void KillPlantAt(int i_x, int i_y);
 	void KillPlantNotInvincibleAt(int i_x, int i_y, bool i_check = true);
	void KillPlantIn(const Sexy::Rect& i_searchRectGridSquares);

    // FIX: below should be in the wave generator? Perhaps the Level def. 
    void PlaceStreetZombies();
    
    // Place will 'pop' them in the right location - used for conveyor levels, far far right of screen.
    // Spawn will spawn them offscreen and have them walk in - used for chooser levels, right of zombies.
    // Create is the helper function called by both of the above.
    void PlaceStreetDinos();
    void SpawnStreetDinos();
    void CreateStreetDinos(int i_placementX, bool i_walkIn);

	void OffsetYForPlanting(int &i_y, PlantTypePtr i_seedType);

    void ArrangeChallengeUI();
    void ArrangeStarChallengeUI();
	virtual void Pause(bool i_pause);
    bool CanPause() { return IsPlaying(); }
    
	void ProcessDeleteQueue();

	void ShakeBoard(int i_shakeAmountX, int i_shakeAmountY, pvztime_t duration = 0.f);
	void ExplosionShakeBoard(int i_xQuakeness, int i_yQuakeness, pvztime_t i_duration = 0.f);

	void PlayerWon();

	void AddPendingPresentReward(const std::string& i_presentTableName);
	void AwardPendingPresents();
//PVZ2_CHINESE_BEGIN	
	void AddPendingActivityPresentReward(const std::string& i_presentName);
	void AwardPendingActivityPresents();
//PVZ2_CHINESE_END
    void OnSeedChooserDone();
    void OnPowerupChooserDone();
    
	// Will create the subsystem if it does not exist
	class GameSubSystem* GetGameSubSystem(RtClass* i_class);
	template<typename T> T* GetGameSubSystem();
    class GameSubSystem* CreateGameSubSystem(RtClass* i_class);
    template<typename T> void CreateGameSubSystem();
    // Will NOT create the subsystem if it does not exist
	class GameSubSystem* FindGameSubSystem(RtClass* i_class);
	template<typename T> T* FindGameSubSystem();
    
	void SunIsInsufficient();
	void SpawnSunFromSky();
	void SetCollectableID_SunFromSky(const std::string& collectableID);
	
	void SuppressSunSpawners(bool i_suppress);
	bool IsSunSpawningSuppressed() const;
    
    void PausePlantGrowthAndDecay(bool i_paused);
	bool IsPlantGrowthAndDecayPaused() const;

    // State change request
    void RestartLevel();
    void Quit(); // quit this level.
    
    bool GridItemsEnabled() const { return m_gridItemsEnabled; }
	
    int GetNumWaves();
    int GetCurrentWave();
  
//PVZ2_CHINESE_START  
    void SetShouldChallengeDrop(bool flag) { m_shouldChallengeDrop = flag;};
//PVZ2_CHINESE_END

    void BeginPlayingLossAversionUpsellEffect();
	bool TryTriggerPlayerLoss(OutroType i_outroType);
	
	template<typename T>
	T* GetOutroModule();

	void NotifyOutroComplete();

	const std::string GetLevelPowerupSet();

    // Debugging 
    void ToggleShowPig();

	inline const SunCurrency	GetSunCurrency();
    SunCurrency             GetSunCurrencyMax();
	void						SetPlantfoodCount(const int i_count);
	inline uint8				GetPlantfoodCount();
	inline uint8				GetPlantfoodMax();
	inline void					SetBoardBaseOffset(const Sexy::Point i_offset);
	inline const Sexy::Point	GetBoardBaseOffset();
	inline Sexy::Rect			GetGridBoundingRect();
	inline const int			GetGridSquareWidth();
	inline const int			GetGridSquareHeight();
	inline bool					IsGridSquareOnBoard(const Sexy::Point& i_gridPosition) const;
	inline bool					IsGridSquareLocked(const int i_gridX, const int i_gridY);
	inline void					SetGridSquareLocked(const int i_gridX, const int i_gridY, bool i_isLocked);
	
	inline SexyVector3			GetFinalDestroyedZombiePosition();
	
	inline float				GetAudioListenerX() const;
	inline BoardPanLocations*	GetBoardPanLocations();

	LevelModuleManager*			GetLevelModuleManager() const { return m_levelModuleManager; }

	class PowerupManager*		GetPowerupManager();
	class BoardArtifactManager* GetArtifactManager();
	class SeedBankNew*			GetSeedBank();
	class SeedChooser*			GetSeedChooser();
	class SeedBankModule*		GetSeedBankModule();
	void						RemoveSeedChooser();

	int							PickRowForNewZombie(ZombieTypePtr i_zombieType, class MTRand* i_optionalRand = NULL);
    
    class Zombie*		DoZombieAtGridSingle(SeedPacketPtr i_seedType, int i_gridX, int i_gridY, bool i_plantfood = false, int level = 1);
    void						DoRainZombieAtGridSingle(ZombieTypePtr i_zombieType, int i_gridX, int i_gridY);
    
	void						PushAnimationMgr();
	void						PopAnimationMgr();
	
    BoardState					GetState() { return m_boardState;}
    
    void						SetBoardScale(float i_scale) { m_boardScale = i_scale; }
    float						GetBoardScale() { return m_boardScale; }
    float 						GetBoardScaleOffsetX() { return m_boardScaleOffsetX; }
    float 						GetBoardScaleOffsetY() { return m_boardScaleOffsetY; }
    void						TranslateScreenPositionToBoardPosition(Sexy::Point& io_position);
    void						TranslateBoardPositionToScreenPosition(Sexy::Point& io_position);
    void						TranslateUIWidgetPositionToBoardPosition(Sexy::Point& io_position);
    void						TranslateUIWidgetRectToBoardRect(Rect& io_rect);
    void						TranslateBoardPositionToUIWidgetPosition(Sexy::Point& io_position);
    // These two functions are not inverses of one another which is super sad.
    void						TranslateScreenRectToBoardRect(Rect& io_rect);
    void						TranslateBoardRectToScreenRect(Rect& io_rect);
    
	inline void					SetBoardResult(const BoardResult i_newBoardResult);
    
    bool  GetIsYetiBattle() const { return m_IsYetiBattle; }   //PVZ2_CHINESE TLog
    
    //new functions of save and get the collectable piece counts
    void  SaveDropedPieceCount() { m_iCollectablePiece++; }
    int   GetDropedPieceCount() const { return m_iCollectablePiece; }    

    void RemoveBoardResource();
    
    void 						ClearAllEntitiesAndCollectCollectables();
    void						DestroyPlantfoodCollectables();
    
	bool							CheckCanBuyPresent();
    
    std::vector<Sexy::Point>& GetWalrusFoot() { return m_vWalrusFoot; }
    
    void SetIceHoleExist(bool bExist) { m_bIceHoleExist = bExist; }
    
    bool GetIceHoleExist() { return m_bIceHoleExist; }
    
    Zombie* AddZombie(std::string i_zombieName, int i_level, int posX, int posY);
    
    bool HasBossFightBonus() { return m_bossFightBonus; }
    bool ShouldDropPlantPieceTwice() { return m_dropPlantPieceTwice; }
    bool ShouldDropAvatarPieceTwice() { return m_dropAvatarPieceTwice; }
    
    bool GetShouldShowPlantTrial() { return m_bShowPlanttrial; }
    void OnGameOverExitLevel();
    
    bool isNormalAwardLevel();
    
    Sexy::Point GetTargetGridPosition(Sexy::Point i_location);
    void SetCoinSpecialCollected(int amount);
    int GetCoinSpecialCollected();
    int GetExtraMaxCoinSpecialCollected();

    void SetkillZombieProductSunmoneyNum(int amount);
    int GetkillZombieProductSunmoneyNum();
    
    bool getHasShowCukePackage() { return m_bHasShowCukePackage; }
    void setHasShowCukePackage(bool hasShow) { m_bHasShowCukePackage = hasShow; }
    
    void SetDinoSpawned() {	m_dinoSpawnedInLevel = true; }
    void SetDinoAffectedAZombie() {	m_dinoAffectedAZombie = true; }
    void IncrementTRexKillCount() { }
    int  GetTRexKillCount() {	return 0; }
    bool IsDangerRoom();
    bool IsBattleZ();
    bool PopDangerRoomBoostIfNeed();
    void InitBoardArtifactManager();
    float calculateRoofOffsetZ(float i_positionX);
    std::vector<std::string> GetBoardPlants();
    void FillBoardPlants();

    void onPlantCreate(Plant* i_plant);   // for peavine

    virtual bool IsMiniBoard();
    bool IsDisablePeavine();

//hero plant
    void InitBoardHeroPlantManager();
	class BoardHeroPlantManager* GetBoardHeroPlantManager();


private:
    
    typedef bool (*AcceptanceFunc)(BoardRegion*, BoardRegionFlags);
    
    BoardRegion*				findContainingRegion(const SexyVector3& i_location, BoardRegionFlags regionFlags, AcceptanceFunc i_acceptanceFunc = NULL);
    std::vector<BoardRegion*>	findAllContainingRegions(const SexyVector3& i_location, AcceptanceFunc i_acceptanceFunc = NULL);
    
    static bool AcceptanceCallFunc(BoardRegion* pBoardRegion, BoardRegionFlags regionFlags);

protected:
    DECLARE_STATE_FUNCTIONS(IntroState, INIT);
	DECLARE_STATE_FUNCTIONS(IntroState, LAUNCHING);
	DECLARE_STATE_FUNCTIONS(IntroState, END);
	DECLARE_STATE_FUNCTIONS(IntroState, ZOMBOSS);
	
private:
    
    std::vector<RtWeakPtr<class BoardRegion> > m_boardRegions;

	int32						getIntroStateSerialization();
	void						setIntroStateSerialization(int32 i_state);

	void						loadDefinitions();
    
	void						setBoardSizeAndPanData();
    
    void						CreateUI();
    void						CalculateBoardScaleAndOffset();
	
    void						collectAllCoins();
    
    bool                        IsPlayerAtWorldMap();

    // event responses
	void						OnZombieAddedToBoard(Zombie *i_zombie);
    void						OnZombieWantsToDropLoot(Zombie *i_zombie);
    void						OnZombieDestroyed(Zombie *i_zombie);
	void						OnZombieDied(Zombie *i_zombie, const DamageInfo* i_deathBlow);
	bool						OnPauseButtonPressed();
#ifdef HOST_ANDROID
	void						OnPauseAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
#endif
    bool                        OnPauseYetiFleeLevelFive();
    void                        OnSpeedChangeButtonPressed(float mSpeed);
    bool						OnNextWaveButtonPressed();
    void                        OnSetNextWaveVisible(bool i_visible);
    bool                        PauseOnInterrupt();
	void						onAppEnteredBackground();
	void                        OnAppLostFocus();
    void                        OnAppResumeFocus();
    void                        OnTreasureYetiTutorialFailed();
    void                        OnChangeSpeedButtonPressed(float i_speed);
    void                        OnArenaChangeSpeedButtonPressed(float i_speed);
	void						OnStarChallengeFailed(class Challenge* i_challenge);
    void						handleTouch(const Sexy::Touch& i_touch);
    bool						handleUITouchEvent(const Sexy::Touch& i_touch);
    
	void 						OnRechargeCurrencyChanged();
	void  						OnZombieWarned(int i_row, int i_col, const std::string& i_narrativeID);
    void                        OnStealChristmasProtect();
    
	void						updateZombiePlantFoodAudio();

	void						OnLossIsImminent();
    void						OnCollectableTryToCollect(class Collectable* i_collectable);
    void						OnCollectableBanked(class Collectable* i_collectable);
	void                        OnGameOverRetryLevel();
    void 						onHugeWaveComing(bool i_isFinal, int i_wave);
    void 						onWaveStarted(int i_wave, WaveType::WaveType i_type, bool i_isFinal);

    void						gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
    
	// level intro zombie placing. 
    typedef int                ZombieGridArray[STREET_GRID_SIZE_X][STREET_GRID_SIZE_Y]; // entry is severity of blockage (5 for most)

    Sexy::Point					GetStreetDimensions(ZombieTypePtr i_zombieType);
    Sexy::Point					GetStreetCriticalDimensions(ZombieTypePtr i_zombieType);
    Sexy::Point					GetStreetOffset(ZombieTypePtr i_zombieType);
    void						FindAndPlaceStreetZombie(ZombieTypePtr i_zombieType, ZombieGridArray i_zombieGrid, int i_level = 1);
    
    int                         makeStreetPicks(TodWeightedGridArray* io_picks, ZombieTypePtr i_zombieType,
                                                 ZombieGridArray io_zombieGrid, int blockingThreshold, bool restrictToCriticalSize);
	
	bool						checkForPlayerWinCondition();

    void						SetState(BoardState i_boardState);

    void						setReasonPlayEnded(const EndOfPlayReason i_newReason);

	void						calculateGridBoundingRect();
    
    std::string					getStringForBoardState(BoardState i_boardState) const;
	
	void                        checkAutoSunCollect();
    
    void                        checkNewerPresent();
    
    void                        checkZombieAlmanacCondition(ZombiePtr i_zombie);

    void						onZombossIntroCompleted();

    void						onZombieWarningEffectStarted();
    
    void 						onSpawnPetZombie(int column, int row);

    void                        fragmentLoad();

    void                        fragmentUnload();
    
    void                        DangerRoomDropReward(Zombie* pZombie);
    
    void                        DoDangerRoomDrop(Zombie* pZombie, std::string strName);
    
    void                        OnWaveStartCreatZombieEnd();
    
    void                        OnDangerRoomReady();
public:
	void				SetAllStarSpawned() { m_allStarSpawned = true; }
	void				SetAllStarDestroyedPlant() { m_allStarDestroyedPlant = true; }


public:

	/// Serializable properties
	int m_gridSizeX;
    int m_gridSizeY;
    
    int m_zombieDistance;
	
    BoardState m_boardState;

    std::string 		m_level; // Name of our current level
	int					m_levelNumber;
	pvztime_t 			m_levelStartTime;
    bool                m_hardModule;
    bool                m_roofStage;

	std::vector<std::string> m_gameplayResources;
	
	std::vector<PresentRecord>  m_pendingPresentRewards;
    std::vector<std::string>    m_pendingActivityRewards;
    std::vector<CollectedPiece> m_pendingCollectedPiece;
    
    int                         m_redpacksCollected;
    
    int                         m_coinsCollected;
    int                         m_specialCoinCollected;
    int                         m_killZombieProductSunmoneyNum;
    int                         m_countYetiDefeated;
    int                         m_countPlantLost;

    int				 			m_levelDefinitionRandomSetIndex;
	
	SexyVector3			m_finalDestroyedZombiePosition;

    //PVZ2_CHINESE_BEGIN
    LawnKeyField		m_plantfoodCount;
    LawnKeyField		m_plantfoodCountMax;
	LawnKeyField		m_sunCurrency;
    //PVZ2_CHINESE_END

	PlantRowType		m_plantRow[MAX_GRIDSIZEY];
	pvztime_t			m_timeRowGotLawnMowered[MAX_GRIDSIZEY];
	TodSmoothArray		m_rowPickingArray[MAX_GRIDSIZEY];
    GridSquareType		m_gridSquareType[MAX_GRIDSIZEX][MAX_GRIDSIZEY];
	int					m_gridSquareLocked[MAX_GRIDSIZEX][MAX_GRIDSIZEY];
	bool				m_mowerAllowedInRow[MAX_GRIDSIZEY];
	
	LootStats m_lootRollStats;

	int m_activeStarIndex;

	BoardResult m_boardResult;
	bool                m_levelPreviouslyCompleted;
	bool				m_sunSpawningSuppressed;
    bool				m_plantGrowthAndDecayPaused;
	bool				m_plantsCanAttack;
	bool				m_manualPlantsActive;

	bool m_pauseGameplayObjects;

	/// Transient properties
	class MessageWidget*				m_advice;
    AnimationMgrWkPtr					m_animationMgr;
	std::vector<AnimationMgrWkPtr>		m_pushedAnimationMgr;
	
	PrimeTypeface* m_debugFont;
	
	std::map<const SexyString, bool>	m_adviceDisplayed;
	SexyString							m_currentAdvice;
	AdvicePriority						m_currentAdvicePriority;

	DebugTextMode m_debugTextMode;
	
	Color m_boardFadeStartColor;
	Color m_boardFadeEndColor;
	pvztime_t m_boardFadeStartTime;
	pvztime_t m_boardFadeEndTime;
	Delegate0 m_onBoardFadeEnd;
	
	BoardState m_postLoadQueuedBoardState;
	
	int m_endLevelDelay;
	bool m_disableShakeBoard;

    #ifndef WANTS_CHEATS_DISABLED
    // Workaround to get a cheat into the cannon minigame
    bool m_forceCannonLevelDone;
    #endif
    
    bool m_bYetiDie;
    bool m_bYetiFlee;
	
    std::string m_FriendPlantName;
    bool        m_bEventUnLockState;
    
    bool m_bImmediatePlantFood;
    bool m_bAutoSunCollect;
    bool m_bCannonEnabled;
    bool m_bStarAwardedSuccess;
    bool m_bDropNewerPresent;
    int  m_nDropWave;
    bool m_bHasStarChallenge;
    bool m_bCanBuyPresent;
    
    //zombie warning related
    bool m_bNeedWarning;
    WarningData m_warningData;
    FinalWarningPointData m_finalWarningPointData;
    int m_destCol;
    int m_destRow;
    int m_totalWarningNumber;
    std::string m_warningText;
    
    std::vector<std::string> m_boardAlmanacZombies;
    
    int m_mowerLaunchesLeft;
    
    int m_nStealChristmasProtectNum;
    
    bool m_IgnoreTaskFailed;
    
    int m_currentLevelBoxSpawned;
    pvztime_t m_spawnTime;

    class PVZ2UIAwardScreen*		GetBoardAwardScreen() { return m_awardScreen; }
    
    float GetSunShovelRefundAmount();	// public
    void  OverrideSunShovelRefundAmount(const float i_overridePercent) { m_shovelOverridePercent = i_overridePercent; }
    void  SetDisableSunShovelRefund(bool i_disabled) { m_shovelRefundDisabled = i_disabled; }
    
    void SetArenaZombieAnim(PopAnimRig* i_animRig);
    template <typename T>
    T* GetCursorByClass();
protected:
    bool 				m_paused;    
    void                Unload();

private:
    // zhousen for advertisement
    void SetupAdvertisement();
    bool IsAdvertisementEnable();
    void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    void CreateSunshine();

    PVZ2UIButton* m_advertisementButton;

    std::vector<std::string> m_boardPlants;// all on board plants' name

public:
    virtual void ButtonDepress(int i_id) override;


private:
    
    bool                m_bossFightBonus;
    bool                m_dropPlantPieceTwice;
    bool                m_dropAvatarPieceTwice;
    bool				m_gridItemsEnabled;
    bool                m_bStartGameFromSave;
	bool				m_allStarDestroyedPlant;
	bool				m_allStarSpawned;
    std::vector<std::string> m_resourceGroupNeedRelease;

    StateMachine<IntroState> 		m_IntroState;
    
    EndOfPlayReason		m_reasonPlayEnded;
    
    class PVZ2UIAwardScreen*	m_awardScreen;

    std::string         m_collectableID_SunFromSky;

    LevelModuleManager* m_levelModuleManager;
    
	class GameInputHandler* m_gameInputHandler;
    std::vector<class BaseCursor*> m_cursors;
    class BaseCursor* m_cachedCursor;
	
	class BoardPropertySheet* m_boardProps;
    
	LevelDefinitionPtr 	m_levelDefinition;

	pvztime_t			m_saveLoadStressTestTimer;
	pvztime_t			m_lastFailedPlantFoodGrab;
	
	SexyString			m_levelNameOverride; // Will still be passed through the translation code
    
	Sexy::Point			m_boardBaseOffset; // No need to serialize, set up when board is created
	Sexy::Rect			m_gridBoundingRect;
	
	OutroType			m_useOutroType;
	
	bool				m_DeferCutsceneZombieDestruction;
    bool                m_shouldChallengeDrop;
    
	class Sexy::PrimeTextWidget*    m_levelTextWidget;
	class Sexy::PrimeTextWidget*    m_authorTextWidget;
    
    float				m_boardScale;
    float				m_boardScaleOffsetX;
    float				m_boardScaleOffsetY;
    
	float				m_audioListenerX;
	BoardPanLocations	m_boardPanLocations;

	std::vector<RtWeakPtr<const class PresentTable> > m_openedPresentTables;
	std::vector<RtWeakPtr<const class PresentType> > m_openedPresentContents;
    
    //PVZ2_CHINESE_BEGIN
    std::vector<RtWeakPtr<const class PresentType> > m_opendActivityPresentContents;//for activity drop item
    //PVZ@_CHINESE_END

	std::map<RtClass*, class GameSubSystem*> 	m_gameSubsystemMap;
    
    std::vector<Zombie*> m_cachedZombiesToRemove;
    std::vector<Zombie*> m_cachedZombies;
    
    float				 m_shovelOverridePercent;
	bool				 m_shovelRefundDisabled;
    
    bool    m_IsYetiBattle;   //PVZ2_CHINESE TLog
    uint8   lastPercentage;
    int     lastWave;
    
    //new value of saveing collectable piece count on stack
    int     m_iCollectablePiece;    
    
    std::vector<std::string> m_loadedGroupName;
    
    DangerRoomDropInfo                      m_stDangerRoomDropInfo;
    
    std::vector<Sexy::Point>                m_vWalrusFoot;
    
    bool                                    m_bIceHoleExist;
    
    bool                                    m_bShowPlanttrial;
    
    PopAnimRig*                             m_arenaCursorAnimRig;
    
    bool m_needShineKernelpults = false;
    bool                                    m_bHasShowCukePackage;
    
    bool m_dinoSpawnedInLevel;
    bool m_dinoAffectedAZombie;

protected:
    // plant group data members
    PlantGroupSubsystem* m_plantGroupSubsystemCache;

public: // variables for collect info
    int		m_iNewerPresentCount;
    int		m_iNewerPresentPayCount;
    void	ClearNewerPresentCollectCount()
    {
    	m_iNewerPresentCount = 0;
    	m_iNewerPresentPayCount = 0;
    }

    struct MissionEndItem
    {
    	std::string itemName;
    	bool buy;
    };
    std::vector<MissionEndItem> m_listMissionEndItem;

    std::vector<SunGet> m_vecSunGetInfo;
    std::vector<int> m_vecSunConsumeInfo;
    std::vector<PlantfoodGet> m_vecPlantfoodGetInfo;
    std::vector<int> m_vecPlantfoodConsumeInfo;
    std::vector<int> m_vecPowerupConsumeInfo;

    ZombieJuggledData m_juggledData;
    ZombieReachLineData m_reachLineData;
    PlantReducedRangeData m_reducedRangeData;
};

//
// MESSAGES
//

namespace Message
{
	void GameWon();
    void GameLost();
	void LevelLoadComplete();
	void LevelStarting();
    void ReadyForLawnItems();
    void MissionFinish();
	void GameplayEnded();
    void LevelEnded();
	void SunClicked(CollectableSun* i_sun, SunCurrency i_upcomingAmount);
	void PlantfoodGrabbed(CollectablePlantfood* i_plantfood);
	void PlantfoodGrabbedWhenFull(CollectablePlantfood* i_plantfood);
	void CoinCurrencyFakeBanked(CoinCurrency i_amount);
	void CoinCurrencySpawned(CollectableCoin* i_coin);
	void PlantfoodSpawned(CollectablePlantfood* i_plantfood);
    void PlantUpgradeSpawned(CollectablePlantUpgrade* i_plant_upgrade);
    void GemCurrencyFakeBanked(GemCurrency i_amount);
    void GemFakeSpawned(CollectableGemFake* i_gem);
	void CoinSpawned(CollectableCoin* i_coin);
	void CoinFakeSpawned(CollectableCoinFake* i_coin);
    void SeedPacketPlanted(SeedPacket* i_packet);
    void PlantPlanted(Plant* i_plant);
    void ZombiePlanted(Zombie* i_zombie);
    void GridItemPlanted(GridItem* i_gridItem);
	void GamePaused();
	void GameUnpaused();
    void PlantGrowthAndDecayPaused();
	void PlantGrowthAndDecayResumed();
    void GameChangeSpeed();
	void CursorAdded(BaseCursor* i_cursor);
	void PlantfoodCountChanged(int i_newCount);
	void SunIsInsufficient();
	void SunSpawnedFromSky(CollectableSun* i_sun);
	void ProgressMeterSetPercentage(uint8 i_percentage);
    void ProgressMeterSetCurrentDisplayPercentage(uint8 i_percentage); //PVZ2_CHINESE Next_Wave
    void SetNextWaveVisible(bool i_visible);                           //PVZ2_CHINESE Next_Wave
	void SunChanged(SunCurrency i_newCount);
	void SunBanked(SunCurrency i_upcomingAmount);
    void SunBankMax(bool i_max);
	void SunSpent(int i_amount);
	void TutorialFunnelEvent(uint64 i_funnelEvent);
	void GemCurrencyBanked(GemCurrency i_amount);
	void SunAdd(SunCurrency i_newCount);
	void AvatarPiecesAdd(const MagentoProductPropsPtr& prpduct,int costFreeGems);
	void WishItem(const std::string& itemName);
    void BossPowerWin(bool i_win);
	void ReadyForFlameExtinguished();
	void ReadyForFuseLitEnd();
    void GatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingErrors);
    void GatherPlantlessPlantingRestrictions(const Sexy::Point& i_atLocation, std::vector<PlantingReason> *io_plantingErrors);
    void BlockGravestoneSpawning(const Sexy::Point& i_atLocation, bool *o_blocked);
    void GatherPlantedPacketCount(const std::string& i_packetType, int* io_plantedPacketAccumulator);
    void ClearBoard();
    void GameplayWinConditionMet();
    void PlantBloverBlowAwayJetpackZombie();
    void TakePlantWeapon(const std::string& plant_name);
    void FireSingleHandedRockets();
    void TakeImmediatePlantFood();
    void PlantCostChanged(Plant* i_plant, int i_newCost);
    void PlantDieCostChanged(Plant* i_plant, int i_newCost);
    void EnableGridItems();
    void PlantAdded(Plant* plant);
    void NoticeTryUseArenaZombie(int x, int y);
    void LastStandLevelInitializing();
    void LastStandLevelStarting();
    void NotifyPlantfoodRelease(Plant* i_entity);

	// when new plant create
	void PlantCreate(Plant* plant);
    // when plant destroyed
    void PlantDestroyed(Plant* plant);
	// when zombie enter the plant_aloes water mist
	void ZombieEnter(Zombie* zombie);
	// plant_aloes water mist clean poison
	void CleanPoison(int x, int y, bool i_fromPlant);
    // plant blow zombie
    void PlantBlow(Plant* plant);
    void PreSeedchooserFlowComplete();
    void GatherExtraChallenges(ProfileUtils::ChallengeStatusHolder *io_challengeStatus);
    void InitBoardArtifactManager();
    void ReadyGoFinish();
    void InitBoardHeroPlantManager();
    void PaidSunmoneyAtGridForPlant(int i_sunCost, int i_gridX, int gridY);
}


inline void	Board::SetOutroType(OutroType i_outroType)
{
	m_useOutroType = i_outroType;
}

inline OutroType Board::GetOutroType()
{
	return m_useOutroType;
}

inline void Board::SetGridSquareType(int i_gridX, int i_gridY, GridSquareType i_type)
{
    DBG_ASSERT(i_gridX >= 0 && i_gridY >= 0);
    DBG_ASSERT(i_gridX < m_gridSizeX && i_gridY < m_gridSizeY);
    
    m_gridSquareType[i_gridX][i_gridY] = i_type;
}

inline GridSquareType Board::GetGridSquareType(int i_gridX, int i_gridY)
{
    DBG_ASSERT(i_gridX >= 0 && i_gridY >= 0);
    DBG_ASSERT(i_gridX < m_gridSizeX && i_gridY < m_gridSizeY);
    
    return m_gridSquareType[i_gridX][i_gridY];
}

inline const SunCurrency Board::GetSunCurrency()
{
	return m_sunCurrency;
}

inline uint8 Board::GetPlantfoodCount()
{
	return m_plantfoodCount;
}

inline uint8 Board::GetPlantfoodMax()
{
	return m_plantfoodCountMax;
}

inline void Board::SetBoardBaseOffset(const Sexy::Point i_offset)
{
	m_boardBaseOffset = i_offset;
	mMouseInsets.mLeft = -i_offset.mX;
	mMouseInsets.mTop = -i_offset.mY;
}

inline const Sexy::Point Board::GetBoardBaseOffset()
{
	return m_boardBaseOffset;
}

inline Sexy::Rect Board::GetGridBoundingRect()
{
	return m_gridBoundingRect;
}

inline const int Board::GetGridSquareWidth()
{
	return BoardConstants::GRIDSQUARE_WIDTH();
}

inline const int Board::GetGridSquareHeight()
{
	return BoardConstants::GRIDSQUARE_HEIGHT();
}

inline SexyVector3 Board::GetFinalDestroyedZombiePosition()
{
	return m_finalDestroyedZombiePosition;
}

inline float Board::GetAudioListenerX() const
{
	return m_audioListenerX;
}

inline BoardPanLocations* Board::GetBoardPanLocations()
{
	return &m_boardPanLocations;
}

inline bool Board::IsGridSquareOnBoard(const Sexy::Point &i_gridPosition) const
{
	if (i_gridPosition.mX < 0 || i_gridPosition.mX >= m_gridSizeX)
	{
		return false;
	}
	if (i_gridPosition.mY < 0 || i_gridPosition.mY >= m_gridSizeY)
	{
		return false;
	}
	return true;
}


inline bool Board::IsGridSquareLocked(const int i_gridX, const int i_gridY)
{
    DBG_ASSERT(i_gridX >= 0 && i_gridY >= 0);
    DBG_ASSERT(i_gridX < m_gridSizeX && i_gridY < m_gridSizeY);
	return m_gridSquareLocked[i_gridX][i_gridY] > 0;
}

inline void Board::SetGridSquareLocked(const int i_gridX, const int i_gridY, bool i_isLocked)
{
    DBG_ASSERT(i_gridX >= 0 && i_gridY >= 0);
    DBG_ASSERT(i_gridX < m_gridSizeX && i_gridY < m_gridSizeY);

    if(i_isLocked)
    {
    	m_gridSquareLocked[i_gridX][i_gridY]++;
    }
    else
    {
    	m_gridSquareLocked[i_gridX][i_gridY]--;
    }
}

inline void Board::SetLevelNumber(const int i_levelNumber)
{
	m_levelNumber = i_levelNumber;
	if(GetLevelDefinition() && GetLevelDefinition()->IsVasebreaker)
	{
		SAFE_DELETE(m_levelTextWidget);
	}
}

inline void Board::SetBoardResult(const BoardResult i_newBoardResult)
{
	m_boardResult = i_newBoardResult;
}

template<typename T>
T* Board::GetLevelModuleByClass()
{
    if(m_levelModuleManager)
    {
        return m_levelModuleManager->GetModuleByClass<T>();
    }
    return NULL;
}

template<typename T>
T* Board::GetOutroModule()
{
    if(m_levelModuleManager)
    {
        OutroModule* outro = m_levelModuleManager->GetModuleByClass<OutroModule>();
        if (outro)
        {
            return outro->Cast<T>();
        }
    }
	return NULL;
}

template<typename T>
T* Board::GetGameSubSystem()
{
	return ((RtObject*)(GetGameSubSystem(T::StaticGetClass())))->template CastChecked<T>();
}

template<typename T>
void Board::CreateGameSubSystem()
{
    GetGameSubSystem<T>();
}

template<typename T>
T* Board::FindGameSubSystem()
{
	GameSubSystem* subSystem = FindGameSubSystem(T::StaticGetClass());
	return (subSystem != nullptr) ? ((RtObject*)subSystem)->CastChecked<T>() : nullptr;
}

template<typename T>
T* Board::AddEffect()
{
	return AddEffect(T::StaticGetClass())->template CastChecked<T>();
}

template<typename T>
T* Board::FindLawnItemInRow(int i_row) const
{
	for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BOARDENTITIES); (iter); ++(iter))
	{
		T* lawnItem = RtWeakPtr<RtObject>(*iter)->Cast<T>();
		if (lawnItem && lawnItem->GetRow() == i_row)
		{
			return lawnItem;
		}
	}

	return NULL;
}

template<typename T>
T* Board::GetCursorByClass()
{
    T* cursor = nullptr;
    for (auto& cs : m_cursors)
    {
        if (cs->IsA<T>())
        {
            cursor = cs->CastChecked<T>();
            break;
        }
    }
    return cursor;
}

//
// Move board - using the animation manager
//
class MoveBoard : public AnimationController
{    
public:
    RT_CLASS_DEFINE(MoveBoard, AnimationController, RtClass);
    
    static MoveBoard* Create()
    {
        return GameObject::Create<MoveBoard>(PVZDB::TABLE_GAMEOBJECTS);
    }
    
    static MoveBoard* Create(pvztime_t i_duration, int i_startX, int i_endX, int i_startY, int i_endY, CurveType i_curveType)
    {
        MoveBoard* moveBoard = Create();
        return moveBoard->Init(i_duration, i_startX, i_endX, i_startY, i_endY, i_curveType);
    }
    
    MoveBoard* Init(pvztime_t i_duration, int i_startX,  int i_endX, int i_startY, int i_endY, CurveType i_curveType)
    {
        SuperClass::Init(i_duration);
        m_curveType = i_curveType;
        m_startXPos = i_startX;
        m_startYPos = i_startY;
        m_endXPos   = i_endX;
        m_endYPos   = i_endY;
        
        return this;
    }
    
    
    void Update(pvztime_t i_time) override
    {
        const pvztime_t startTime = GetStartTime();
        const pvztime_t endTime = GetEndTime();
        
        const int moveX =  CurveLerp(startTime, endTime, i_time, S(m_startXPos), S(m_endXPos), m_curveType);
        const int moveY =  CurveLerp(startTime, endTime, i_time, S(m_startYPos), S(m_endYPos), m_curveType);
        
        gLawnApp->m_board->Move(moveX, moveY);
    }
    
private:
    int m_startXPos, m_endXPos, m_startYPos, m_endYPos;
    
    CurveType m_curveType;
};

//
// Shake board using animation manager.
//
class ShakeBoard: public AnimationController
{
public:
    RT_CLASS_DEFINE(ShakeBoard, AnimationController, RtClass);
    
    static ShakeBoard* Create()
    {
        return GameObject::Create<ShakeBoard>(PVZDB::TABLE_GAMEOBJECTS);
    }
    
    ShakeBoard* Init(pvztime_t i_dur, int i_xAmount, int i_yAmount)
    {
        SuperClass::Init(i_dur, false);
        m_xAmount = i_xAmount;
        m_yAmount = i_yAmount;
        
        return this;
    }

    void Update(pvztime_t i_time) override
    {
        const pvztime_t startTime = GetStartTime();
        const pvztime_t endTime   = GetEndTime();
        
        if (Rand(2) == 0)
        {
            m_xAmount = -m_xAmount;
        }
        
        int offset = 0;
        
        if(gLawnApp->m_board && gLawnApp->m_board->GetLevelDefinition() && (gLawnApp->m_board->GetLevelDefinition()->IsArenaBattle || gLawnApp->m_board->GetLevelDefinition()->IsArenaEdit))
        {
            offset = S(80);
        }
        
        int boardOffset = 0;
        if(gLawnApp->IsFullScreen())
        {
        	boardOffset = gLawnApp->CalcFullScreenOffset();
        }

        gLawnApp->m_board->Move( CurveLerp(startTime, endTime, i_time, 0 - offset, m_xAmount, CURVE_BOUNCE) + gLawnApp->m_board->GetBoardBaseOffset().mX - boardOffset,
                      CurveLerp(startTime, endTime, i_time, 0, m_yAmount, CURVE_BOUNCE));
    }

private:
    int m_xAmount = 0;
    int m_yAmount = 0;

};

//
// Shake board using animation manager.
//
class ExplosionShakeBoard: public AnimationController
{
public:
    RT_CLASS_DEFINE(ExplosionShakeBoard, AnimationController, RtClass);

    static ExplosionShakeBoard* Create()
    {
        return GameObject::Create<ExplosionShakeBoard>(PVZDB::TABLE_GAMEOBJECTS);
    }

    ExplosionShakeBoard* Init(pvztime_t i_dur, int i_xQuakeness, int i_yQuakeness)
    {
        SuperClass::Init(i_dur);
        m_xQuakeness = i_xQuakeness;
        m_yQuakeness = i_yQuakeness;

        return this;
    }

    void Update(pvztime_t i_time) override;
private:
    int m_xQuakeness = 0;
    int m_yQuakeness = 0;
};

//
// Dispatch to the board commands trigged by animation manager timed event. 
//
class IntroBoardDispatch : public AnimationController
{
public:
    typedef void (Board::*BoardMethod) (void);
    
    RT_CLASS_DEFINE(IntroBoardDispatch, AnimationController, RtClass);
    
    static IntroBoardDispatch* Create(const std::string& i_dispatchCommand)
    {
        IntroBoardDispatch* ibd = GameObject::Create<IntroBoardDispatch>(PVZDB::TABLE_GAMEOBJECTS);
        ibd->SetDuration(0.0f);
        ibd->Init(i_dispatchCommand);
        return ibd;
    }
    
    IntroBoardDispatch* Init(const std::string& i_dispatchCommand)
    {
        if (s_dispatchMap.size() == 0)
        {
            s_dispatchMap["EnableGridItems"] = &Board::EnableGridItems;
            s_dispatchMap["PlaceLawnItems"]  = &Board::PlaceLawnItems;
            s_dispatchMap["PlaceStreetZombies"] = &Board::PlaceStreetZombies;
            s_dispatchMap["SpawnStreetDinos"] = &Board::SpawnStreetDinos;
            s_dispatchMap["PlaceStreetDinos"] = &Board::PlaceStreetDinos;
            s_dispatchMap["ShowLawnItems"] = &Board::ShowLawnItems;
        }
        
        m_dispatchCommand = i_dispatchCommand;
        
        SetDescription(std::string("IntroBoardDispatch ") + m_dispatchCommand);
        
        return this;
    }
    
    void Update(pvztime_t i_time) override
    {
        std::map<std::string, BoardMethod>::iterator itr = s_dispatchMap.find(m_dispatchCommand);
        
        if (itr != s_dispatchMap.end() && gLawnApp && gLawnApp->m_board)
        {
            BoardMethod boardMethod = itr->second;
            (gLawnApp->m_board->*boardMethod)();
        }
        else
        {
            DBG_ASSERT_MSG(false, "IntroBoardDispatch - warning didn't get expected dispatch command");
        }
    }
private:
    
    void onPostLoad() override
    {
        Init(m_dispatchCommand);
    }

    static std::map<std::string, BoardMethod> s_dispatchMap;
    
    std::string m_dispatchCommand;
};

bool RenderItemSortFunc(const RenderItem &i_item1, const RenderItem &i_item2);

#endif //__BOARD_H__
