//
//  BeghouledModule.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 6/22/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BeghouledModule__
#define __PlantsVersusZombies2__BeghouledModule__

#define HINT_FLASH_DELAY 5.0
#define HINT_FLASH_REPEAT_DELAY 0.25
#define HINT_FLASH_COUNT 5
#define MATCH_MINIMUM_SIZE 3

#include "BoardConstants.h"
#include "LevelModule.h"
#include "Plant.h"
#include "PVZTypes.h"
#include "StandardLevelIntro.h"
#include "ObjectTypeDescriptor.h"
#include "Curve.h"

class BeghouledModule;

enum BeghouledPlantType
{
	PVZ_BEGIN_ENUM(BEGHOULED_),
	BEGHOULED_Crater = -1,
	BEGHOULED_Empty_Spot = 0,
	BEGHOULED_First_Plant = 1,
	
	BEGHOULED_Peashooter = 1,
	BEGHOULED_Wallnut,
	BEGHOULED_Cabbagepult,
	BEGHOULED_Puffshroom,
	BEGHOULED_LightningReed,
	BEGHOULED_FirePeashooter,
	BEGHOULED_Repeater,
	BEGHOULED_Threepeater,
	BEGHOULED_Tallnut,
	BEGHOULED_Endurian,
	BEGHOULED_Pepperpult,
	BEGHOULED_Melonpult,
	BEGHOULED_Wintermelon,
	BEGHOULED_Fumeshroom,
	BEGHOULED_LaserBean,
	BEGHOULED_ElectricBlueberry,
	BEGHOULED_Iceburg,
	BEGHOULED_Stallia,
	BEGHOULED_PrimalPeashooter,
	BEGHOULED_Kernelpult,
	BEGHOULED_Akee,
	BEGHOULED_XShot,
	BEGHOULED_Starfruit,
	BEGHOULED_Snapdragon,
	BEGHOULED_ColdSnapdragon,
    BEGHOULED_SunBean,
    BEGHOULED_Hypnoshroom,
    BEGHOULED_Stunion,
    BEGHOULED_LavaGuava,
    BEGHOULED_Violet,
    BEGHOULED_Shadowshroom,
    BEGHOULED_Bloomerang,
    BEGHOULED_BonkChoy,
    BEGHOULED_Spikeweed,
	BEGHOULED_Spikerock,
    BEGHOULED_SpringBean,
    BEGHOULED_SplitPea,
    BEGHOULED_Torchwood,
    BEGHOULED_Citron,
    BEGHOULED_Infinut,
    BEGHOULED_Peanut,
    BEGHOULED_Magnetshroom,
    BEGHOULED_Chomper,
    BEGHOULED_BowlingBulb,
    BEGHOULED_HomingThistle,
    BEGHOULED_ChardGuard,
    BEGHOULED_RedStinger,
    BEGHOULED_Toadstool,
    BEGHOULED_Cactus,
    BEGHOULED_PhatBeet,
    BEGHOULED_Garlic,
    BEGHOULED_PrimalWallnut,
    BEGHOULED_Nightshade,
    BEGHOULED_Dusklobber,
    BEGHOULED_Guacodile,
    BEGHOULED_CoconutCannon,
    BEGHOULED_MagnifyingGrass,
    BEGHOULED_GhostPepper,
    BEGHOULED_JackOLantern,
    BEGHOULED_Dandelion,
    BEGHOULED_BloomingHeart,
    BEGHOULED_SweetPotato,
    BEGHOULED_Moonflower,
    BEGHOULED_Sunshroom,
    BEGHOULED_Sunflower,
    BEGHOULED_PrimalSunflower,
    BEGHOULED_TwinSunflower,
    BEGHOULED_WasabiWhip,
    BEGHOULED_ExplodeONut,
    BEGHOULED_Aloe,
    BEGHOULED_Kiwibeast,
    BEGHOULED_AppleMortar,
    BEGHOULED_WitchHazel,
    BEGHOULED_Pokra,
    BEGHOULED_Shadowpeashooter,
    BEGHOULED_ShadowVanilla,
    BEGHOULED_Electricpeashooter,
    BEGHOULED_SnowPea,
    
	BEGHOULED_Last_Plant = BEGHOULED_SnowPea,
	PVZ_END_ENUM(BEGHOULED_)
};
PVZ_MAKE_ENUM_MATH_OPERATORS(BeghouledPlantType);

enum BeghouledGameplayState
{
	BeghouledInitializing,
	BeghouledPlaying,
	BeghouledMovingPlants,
	BeghouledFillingHoles,
	BeghouledNoMatches,
};

class BeghouledBoardState
{
public:
	BeghouledPlantType m_plantType[BoardConstants::NUMBER_OF_COLUMNS_RAW - 1][BoardConstants::NUMBER_OF_ROWS_RAW];
};

class BeghouledProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(BeghouledProperties, LevelModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
	virtual void ConfigureModule(BeghouledModule* i_module) const
	{
		// Must be implemented by a derived class
		DBG_HALT();
	}
	
	virtual bool UseEndlessFlow() const
	{
		return false;
	}
	
	BeghouledProperties()
	{}
};

struct BeghouledUpgradeMap
{
	std::string BasePlant;
	std::string UpgradedPlant;
};

class BeghouledPresetProperties : public BeghouledProperties
{
public:
	RT_CLASS_DEFINE(BeghouledPresetProperties, BeghouledProperties, RtClass);
	
	BeghouledPresetProperties()
	: MatchesToWin(10)
	{}
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void ConfigureModule(BeghouledModule* i_module) const override;
	int MatchesToWin;
	std::vector<std::string> InitialPlants;
	std::vector<BeghouledUpgradeMap> UpgradeMap;
};

class BeghouledIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(BeghouledIntro, StandardLevelIntro, RtClass);
	
protected:
	void onStandardIntroComplete() override;
	void onShowPlant() override;
	
private:
	void enableBeghouledGameplay();
};

class BeghouledIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(BeghouledIntroProperties, StandardLevelIntroProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return BeghouledIntro::StaticGetClass();
	}
};

class BeghouledModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(BeghouledModule, LevelModule, RtClass);
	
	BeghouledModule();
	
	void GatherDependentModulePropertySheets(std::vector<LevelModulePropertiesPtr>& io_dependent) override;
	void EnableSwapping(bool i_allowSwaps);
	static std::string BeghouledTypeToString(BeghouledPlantType i_beghouledType);
	
protected:
	void registerForEvents() override;
	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onPlantDied(Plant* i_plant);
	void onLocationCleared(int i_gridX, int i_gridY);
	void postInitialize() override;
	
private:
	void InitPlantMap();
	void InitPlantUpgradeMap();
	void onUpdate();
	void onClearBoard();
	bool checkWinCondition();
	void onPlantUpgraded(std::string& i_plantName);
	
	void CheckStuckState();
	
	void setToolVisibility();
	BeghouledPlantType CalcBeghouledTypeFromPlantType(std::string i_plantName);
	void LoadBeghouledBoardState(BeghouledBoardState *theBoardState);
	bool BoardHasMatch(BeghouledBoardState *theBoardState);
	
	BeghouledPlantType GetPlantAt(int x, int y, BeghouledBoardState *theBoardState);
	int VerticalMatchLength(int x, int y, BeghouledBoardState *theBoardState);
	int HorizontalMatchLength(int x, int y, BeghouledBoardState *theBoardState);
	
	void RemoveMatches(BeghouledBoardState *theBoardState);
	void CacheMatch(int i_x, int i_y, BeghouledBoardState *theBoardState, int i_length, bool i_isHorizontal, bool& o_isPlantfoodedMatch);

	void FallIntoSquare(int x, int y, BeghouledBoardState *theBoardState);
	void MakePlantsFall(BeghouledBoardState *theBoardState);

	void Score(int x, int y, int theNumPlants, bool theIsHorizontal, bool i_matchIsPlantfooded);

	void FillHoles(BeghouledBoardState *theBoardState, bool theAllowMatches);
	void Shuffle();
	void PopulateBoard();
	bool CheckForPossibleMoves(BeghouledBoardState *theBoardState);
	bool IsValidMove(int x1, int y1, int x2, int y2, BeghouledBoardState *theBoardState);
	void CreatePlants(BeghouledBoardState *theOldBoardState, BeghouledBoardState *theNewBoardState);
	BeghouledPlantType PickPlant(int theGridX, int theGridY, BeghouledBoardState *theBoardState, bool theAllowMatches);
	
	void StartFalling(BeghouledGameplayState theState);
	void DragStart(Point i_boardLoc);
	void DragUpdate(Point i_boardLoc);
	
	void FlashAMatch();
	bool FlashFromBoardState(BeghouledBoardState *theBoardState, int theSwap1X, int theSwap1Y, int theSwap2X, int theSwap2Y);
	void FlashPlant(int x, int y, int theSwap1X, int theSwap1Y, int theSwap2X, int theSwap2Y);
	
	bool m_hasEnteredInitialize;
	bool m_mouseCapture;
	bool m_allowSwaps;
	bool m_isCascading;
	
	RtWeakPtr<class BeghouledArcadeModule> m_arcadeModule;
	BeghouledGameplayState m_state;
	std::map<std::string, BeghouledPlantType> m_plantMap;
	std::map<std::string, BeghouledPlantType> m_upgradeMap;
	
	pvztime_t m_hintFlashTime;
	int m_hintFlashCount;
	int m_matchCounter;
	int m_matchesThisMove;
	Sexy::Point m_mouseCaptureLoc;
	std::vector<BeghouledPlantType> m_currentPlantUpgrades;
	int m_purchasedUpgradeCount;
	
	RtWeakPtr<Plant> m_swappingPlant1;
	RtWeakPtr<Plant> m_swappingPlant2;
	std::vector<RtWeakPtr<Plant>> m_plantsToPlantfood;
	std::vector<RtWeakPtr<Plant>> m_plantsToDestroy;
	std::vector<RtWeakPtr<Plant>> m_plantfoodedPlantsToDestroy;
	std::vector<RtWeakPtr<Plant>> m_plantsInHorizontalMatches;
	std::vector<RtWeakPtr<Plant>> m_plantsInVerticalMatches;
	
	// helper functions
	bool isPlantPlantfooded(RtWeakPtr<Plant> i_plant);
	void calcCrossingPlants();
	void removeAllMatches();
	void updateBoardForUpgradedPlant(BeghouledPlantType i_upgradedPlant);
	void updateZombieSpawner();
	void updateSeedBank(BeghouledPlantType i_upgradedPlant);
	void resetFlashTimer();
};

#endif /* defined(__PlantsVersusZombies2__BeghouledModule__) */
