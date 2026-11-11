/*
 * NewPVPGame.h
 *
 *  Created on: 2022-10-10
 *      Author: admin
 */

#ifndef NEWPVPGAME_H_
#define NEWPVPGAME_H_

#include "Singleton.h"
#include "GameSubSystem.h"
#include "ScaledBoardModule.h"
#include "StageModule.h"
#include "BoardRegion.h"
#include "PlantCursor.h"
#include "ShovelCursor.h"
#include "PlantfoodCursor.h"
#include "NetworkData.h"
#include "ZombiePropertySheet.h"
#include "OutroModule.h"
#include "UIUtil.h"
#include "NewPVPDataPackets.h"
#include "PVZGameState.h"
#include "MacroStateMachine.h"
#include "PVZGameStateTopHUDController.h"
#include "HotUIAdaptor.h"
#include "HotUIImage.h"
#include "FuelBank.h"
#include "HotUILabel.h"
#include "WarMistModule.h"
#include "ZombieLostCityGuide.h"
#include "AdaptorJoustHowToPlayScreen.h"
#include "TutorialFinger.h"

class NewPVPPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(NewPVPPropertySheet, PropertySheetBase, RtClass);
    void Copy(const NewPVPPropertySheet& src);

    NewPVPPropertySheet()
	{
    	CommonZombieCreatedCD = 2.0f;
    	StartingSun = 200;
    	SunLimit   = 10000;
    	SunAddBase = 100;
    	SunAddEachTurn = 10;
    	CommonMaxZombieCacheSize = 5;
    	CommonPlantLevelUpValue = 1;
    	MaxHealthAmount = 20.0f;
    	DealtDamage = 2.0f;
    	SunCostMultiplier = 1.0f;
	}

    float							CommonZombieCreatedCD;
    int								CommonMaxZombieCacheSize;
    int								CommonPlantLevelUpValue;
	int								StartingSun;
	int                             SunLimit;
	int                             SunAddBase;
	int                             SunAddEachTurn;
	std::vector<ZombieLevelStat>    ZombieLevelStats;
	std::vector<NewPVPZombiePacketInfo>    ZombiePacketInfos;
	std::vector<NewPVPPlantPacketInfo>    PlantPacketInfos;
	float							MaxHealthAmount;
	float							DealtDamage;
	float							SunCostMultiplier;
	std::vector<NewPVPZombieSkillInfo>    ZombieSkillInfos;
	std::vector<NewPVPZombieUpgradeInfo>    ZombieUpgradeInfos;
	std::vector<NewPVPSunUpgradeInfo> SunUpgradeInfos;
	JoustHowToPlayScreenData	AreaHowToPlayData;
	std::vector<int> 	ChooserPlantBlacklist;
	NewPVPZombieLevelUpPropertySheet NewPVPZombieLevelUpSheet;
	std::vector<int> UnsyncPlantBlacklist;
	std::vector<std::vector<NewPVPCPULevelInfo>> CPULevelInfos;
	std::vector<int> TutorialPlantList;
	NewPVPTutorialInfo TutorialInfo;
};

enum NewPVPTutorialStep
{
	NewPVPTutorialStep_None = -1,
	NewPVPTutorialStep_1,
	NewPVPTutorialStep_2,
	NewPVPTutorialStep_3,
	NewPVPTutorialStep_4,
	NewPVPTutorialStep_5,
	NewPVPTutorialStep_6,
	NewPVPTutorialStep_7,
	NewPVPTutorialStep_8,
	NewPVPTutorialStep_9,
	NewPVPTutorialStep_10,
	NewPVPTutorialStep_11,
	NewPVPTutorialStep_12,
	NewPVPTutorialStep_Count
};

enum NewPVPGameResults
{
	NewPVPGameResults_None,
	NewPVPGameResults_Win,
	NewPVPGameResults_Lose,
	NewPVPGameResults_Draw
};

class NewPVPFPSCounter : public UIWidget
{
public:
	RT_CLASS_DEFINE(NewPVPFPSCounter, UIWidget, RtClass);

	NewPVPFPSCounter();
	virtual ~NewPVPFPSCounter();

	// Public Interface (Inheritable)

	void registerForEvents() override;
	void Draw(Graphics* i_g) override;

protected:
	void onGameplayRealStarted();
	void onNotifyFPSReachLimit();
	void onUpdate() override;

	PrimeTextWidget* m_textWidget;
	bool m_hasShownWarning;
	pvztime_t m_showWarningTime;
};

class NewPVPPlantCursor : public PlantCursor
{
public:
	RT_CLASS_DEFINE(NewPVPPlantCursor, PlantCursor, RtClass) {}

	NewPVPPlantCursor();
    ~NewPVPPlantCursor();

    NewPVPPlantCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket, int i_level);
    NewPVPPlantCursor(const Sexy::Touch& i_boardSpaceTouch, PlantTypePtr i_plantType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0,0,0,0), bool i_useBoost = false, int i_level = -1);

protected:
    bool canAffordPlant(PlantTypePtr i_plantType, int i_level) const override;
	Plant* makeNewPlantAt(PlantTypePtr i_type, const int i_gridX, const int i_gridY, int iLevel = -1, bool i_useBoost = false) override;
};

class NewPVPShovelCursor : public ShovelCursor
{
public:
	RT_CLASS_DEFINE(NewPVPShovelCursor, ShovelCursor, RtClass) {}

	NewPVPShovelCursor();
	NewPVPShovelCursor(const Sexy::Touch& i_boardSpaceTouch);

protected:
	void doShovelEntity(BoardEntity* i_entity) override;
	bool CanShovelPlant(int i_x, int i_y) override;
};

class NewPVPPlantfoodCursor : public PlantfoodCursor
{
public:
	RT_CLASS_DEFINE(NewPVPPlantfoodCursor, PlantfoodCursor, RtClass) {}

	NewPVPPlantfoodCursor();
	NewPVPPlantfoodCursor(const Sexy::Touch& i_boardSpaceTouch);

	bool canApplyPlantfood(int i_x, int i_y) override;
	void applyPlantfood(class Plant* i_plant) override;
};

enum NewPVPZombieUpgradeType
{
	ZombieUpgradeType_SpeedUp,
	ZombieUpgradeType_HP,
	ZombieUpgradeType_Immune,
	ZombieUpgradeType_Attack,
	ZombieUpgradeType_Invisible
};

struct PlantCacheData
{
	PlantCacheData()
	: Level(1)
	, Type(-1)
	, PlantTime(0)
	, Seed(0)
	, ExtraValue(0.0f)
	{

	}

	PlantCacheData(int i_type, int i_level, Point i_grid, float i_plantTime, uint32 i_seed, float i_extraValue)
	: Type(i_type)
	, Level(i_level)
	, Grid(i_grid)
	, PlantTime(i_plantTime)
	, Seed(i_seed)
	, ExtraValue(i_extraValue)
	{

	}

	int Level;
	int Type;
	Point Grid;
	float PlantTime;
	uint32 Seed;
	float ExtraValue;
};

struct ZombieCacheData
{
	ZombieCacheData()
	: Type(-1)
	, Level(1)
	, Row(0)
	, Cost(0)
	, PacketLevel(1)
	, Seed(0)
	{

	}

	ZombieCacheData(int i_type, int i_level, int i_row, int i_cost, std::vector<int> i_upgrades, int i_packetLevel, uint32 i_seed)
	: Type(i_type)
	, Level(i_level)
	, Row(i_row)
	, Cost(i_cost)
	, Upgrades(i_upgrades)
	, PacketLevel(i_packetLevel)
	, Seed(i_seed)
	{

	}

	int Type;
	int Level;
	int Row;
	int Cost;
	std::vector<int> Upgrades;
	int PacketLevel;
	uint32 Seed;
};

struct ZombieCreatedCacheData
{
	ZombieCreatedCacheData()
	: Cost(0)
	{

	}

	ZombieCreatedCacheData(ZombiePtr i_zombiePtr, int i_cost)
	: Zombie(i_zombiePtr)
	, Cost(i_cost)
	{

	}

	ZombiePtr Zombie;
	int Cost;
};

struct CurrentHealthData
{
	CurrentHealthData()
	: m_hitpoints(0)
	, m_hitpointsMax(0)
	, m_damage(0)
	{

	}

	CurrentHealthData(float i_hp, float i_maxHp, float i_damage)
	: m_hitpoints(i_hp)
	, m_hitpointsMax(i_maxHp)
	, m_damage(i_damage)
	{

	}

	float m_hitpoints;
	float m_hitpointsMax;
	float m_damage;
};

enum NewPVPZombieSkillType
{
	ZombieSkillType_SpeedUp,
	ZombieSkillType_BuffPotionAttack
};

struct NewPVPZombieSkillData
{
	NewPVPZombieSkillData()
	: Type(ZombieSkillType_SpeedUp)
	, EndTime(0)
	, Value(0)
	{

	}

	NewPVPZombieSkillData(NewPVPZombieSkillType i_type, pvztime_t i_endTime, float i_value)
	: Type(i_type)
	, EndTime(i_endTime)
	, Value(i_value)
	{

	}

	NewPVPZombieSkillType Type;
	pvztime_t EndTime;
	float Value;
};

struct NewPVPZombieUpgradeData
{
	NewPVPZombieUpgradeData()
	: Type(ZombieUpgradeType_HP)
	, Cost(0)
	, Value(0)
	, Trigger(false)
	{

	}

	NewPVPZombieUpgradeData(NewPVPZombieUpgradeType i_type, int i_cost, float i_value, bool i_trigger)
	: Type(i_type)
	, Cost(i_cost)
	, Value(i_value)
	, Trigger(i_trigger)
	{

	}

	NewPVPZombieUpgradeType Type;
	int Cost;
	float Value;
	bool Trigger;
};

struct CurrentSelectedPlantPacketInfo
{
	CurrentSelectedPlantPacketInfo()
	: Type(-1)
	{

	}

	CurrentSelectedPlantPacketInfo(int i_type, const NewPVPPlantPacketInfo& i_info)
	: Type(i_type)
	, PacketInfo(i_info)
	{

	}

	int Type;
	NewPVPPlantPacketInfo PacketInfo;
};

enum AddPacketReason
{
	AddPacketReason_Ok,
	AddPacketReason_NotEnoughSun,
	AddPacketReason_OnCooldown,
	AddPacketReason_Locked,
	AddPacketReason_MaxSize
};

struct NewPVPCurrentCPUPlant
{
	NewPVPCurrentCPUPlant()
	: PlantId(0)
	, Column(0)
	, NextPlantTime(0)
	, Level(1)
	, Replace(false)
	{

	}

	NewPVPCurrentCPUPlant(int i_id, int i_col, float i_nextPlantTime, int i_level, bool i_replace)
	: PlantId(i_id)
	, Column(i_col)
	, NextPlantTime(i_nextPlantTime)
	, Level(i_level)
	, Replace(i_replace)
	{

	}

	int PlantId;
	int Column;
	float NextPlantTime;
	int Level;
	bool Replace;
};

struct NewPVPCurrentLevelCPU
{
	NewPVPCurrentLevelCPU()
	: Level(-1)
	, CurrentPlantRow(0)
	{

	}

	std::vector<NewPVPCurrentCPUPlant> PlantInfos;
	int Level;
	int CurrentPlantRow;
};

struct NewPVPCPUCountObject
{
	NewPVPCPUCountObject()
	: ZombieCount(0)
	, PlantCount(0)
	{

	}

	int ZombieCount;
	int PlantCount;
};

class NewPVPGameSubsystem : public GameSubSystem
{
public:

	RT_CLASS_DEFINE(NewPVPGameSubsystem, GameSubSystem, RtClass);

	NewPVPGameSubsystem();

	virtual ~NewPVPGameSubsystem();

	class BoardEntity* TriggerEvent(TriggerEventType i_triggerType, bool i_self, int i_event = -1, int i_type = -1, int i_x = -1, int i_y = -1, float i_value = 0, uint32 i_seed = 0, const std::vector<float>& i_extraValues = {});

	void TryUpgradePlant(int i_x, int i_y);
	void TryUpgradePlantEffect(int i_x, int i_y);
	void TryAddZombie(int i_type, int i_level);
	void SetZombieCreatedCD(float i_cd) { m_zombieCreatedCD = i_cd; }
	float GetZombieCreatedCD() { return m_zombieCreatedCD; }
	AddPacketReason CanAddZombie(int i_type, int i_level);
	bool IsSpawnedZombie(Zombie* i_zombie);
	int GetCurrentZombieCacheSize();
	const std::vector<ZombieCacheData>& GetZombieCacheDatas() { return m_zombieCacheDatas; }
	const ZombieCacheData& GetTargetZombieCacheData(int i_index);
	const std::vector<ZombieCacheData>& GetOppoentZombieCacheDatas() { return m_zombieOppoentCacheDatas; }
	int GetCurrentSunAdd();
	int GetCurrentSun();
	void AddCurrentSunAdd(int i_count) { m_currentSunAdd += i_count; }
	void SetCurrentSunAdd(int i_count) { m_currentSunAdd = i_count; }
	void SetCurrentSunAddNum(int i_count) { m_currentSunAddNum = i_count; }
	int GetCurrentSunAddNum() { return m_currentSunAddNum; }
	void TryUpgradeSun(int i_toLevel);
	bool CanAfford(int i_cost);
	int GetMaxTurn();
	int GetCurrentTurn();

	void TryTriggerZombieSkill(int i_type);

	void TryTriggerZombieUpgrade(int i_type);

	static const NewPVPPropertySheet* GetNewPVPPropertySheet();

	void SetSelfPlantDelay(float i_delay) { m_selfPlantDelay = i_delay; }
	void SetOppoentPlantDelay(float i_delay) { m_oppoentPlantDelay = i_delay; }

	bool HasFullHitpoints() { return m_selfHp.m_hitpoints > 0 && m_selfHp.m_hitpoints == m_selfHp.m_hitpointsMax; }
	float GetSelfHealth() { return m_selfHp.m_hitpoints; }
	float GetOppoentHealth() { return m_oppoentHp.m_hitpoints; }

	int GetZombieCost(Zombie* i_zombie);
	float CalcSunCostMultiplier();

	std::vector<int> GetZombieUpgradeInfoForLog();

protected:
	void Update() override;
	void AddToRenderQueue(class RenderQueue* i_queue) override;

private:
	void onGameplayStarted();
	void onNotifyTutorialStep(int i_step);
	void onPlantPlanted(class Plant* i_plant);
	void addTutorialPlant(int i_wave);
	void OnNarrativeTutorialStartCompleted();
	void addTutorialZombie();
	void draw(Sexy::Graphics *i_g);
	void initCPU();
	void fillCPU(int i_level, int i_wave);
	bool hasCPUPlant(int i_id);
	void initSun();
	void initHp();
	void onWaveStarted(int i_waveIndex);
	void onPlantDied(class Plant* i_plant);
	void addPlant(bool i_self, int i_type, int i_level, Point i_grid, float i_plantTime, uint32 i_seed, float i_extraValue = 0.0f);
	void playAddPlantEffect(Point i_grid);
	void addZombie(bool i_self, int i_type, int i_level, int i_row, int i_packetLevel, uint32 i_seed);
	class Zombie* spawnZombie(const ZombieCacheData& i_data);
	class Zombie* spawnZombieCheckResource(ZombieTypePtr i_zombieType, int i_spawnInRow, int i_level, int i_packetLevel, uint32 i_seed);
	void checkZombieSkill(class Zombie* i_zombie);
	void addToZombieCreatedCache(Zombie* i_zombie, const ZombieCacheData& i_data);
	void checkZombieUpgrade(Zombie* i_zombie);
	std::vector<int> checkZombieUpgrade(int i_row);
	void updateZombies();
	void onZombieDestroyed(Zombie* i_zombie);
	void updatePlants();
	class Zombie* updateZombieSpawn(std::vector<ZombieCacheData>& i_data);
	void updatePlantSpawn(std::vector<PlantCacheData>& i_data, bool i_self);
	void playRemoveEffect(class BoardEntity* i_entity);
	void updateTurns();
	void updateZombieSkills();
	void checkZombieUpgrade();
	void updateSun();
	void updateCPU();
	void updateTutorial();
	void updateCPUPlant(NewPVPCurrentCPUPlant& i_info);
	int findEmptyRow(int i_col, int i_rowCount, int i_targetRow, bool i_replace, PlantTypePtr i_type);
	void addCurrentRow();
	int getCPUTargetRowSpawnPlant(int i_col, bool i_replace, PlantTypePtr i_type);
	bool hasUpgradeUnlocked(bool i_self, int i_type);
	bool hasUpgradeTriggered(bool i_self, int i_type);
	bool triggerUpgrade(bool i_self, int i_type);
	bool updateUpgrade(int i_type, std::vector<NewPVPZombieUpgradeData>& i_infos);
	void triggerUpgradeEffect(int i_type, class Zombie* i_zombie);
	void triggerSurrender(bool i_self);
	void updateSurrender();
	void updateFPSCheck();
	void triggerFPSCheck();
	void arrangeTopUIs();

	void showTutorialArrow(int i_arrowType, int i_x, int i_y);
	void setTutorialArrowVisible(bool i_visible);
	void addTutorialArrow();
	void setTutorialArrowPos(int iPosX, int iPosY);
	void setTutorialArrowOffset(int iOffsetX, int iOffsetY, float iRot);
	void updateTutorialArrow();
	void drawTutorialArrow(Sexy::Graphics *i_g);

	bool upgradePlant(bool i_self, int i_x, int i_y);
	bool removePlant(int i_x, int i_y);
	bool applyPlantfood(int i_x, int i_y);
	void killPlant(bool i_self, int i_x, int i_y, int i_type, int i_level);

	bool takeDamage(bool i_self);
	void onBarTakeDamage(int i_type, float i_amount);

	void triggerZombieSkill(bool i_self, int i_type);
	int getPlantCount();

	void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingErrors);

	std::vector<ZombieCacheData> m_zombieCacheDatas;
	std::vector<ZombieCacheData> m_zombieOppoentCacheDatas;
	std::vector<ZombieCreatedCacheData> m_zombieCreatedCacheDatas;
	std::vector<ZombiePtr> m_spawnedZombies;
	float m_zombieCreatedCD;
	pvztime_t m_nextCreatedZombieTime;
	pvztime_t m_nextCreatedOppoentZombieTime;
	int m_currentZombieRow;
	NewPVPZombieSkillData m_selfZombieSkill;
	NewPVPZombieSkillData m_oppoentZombieSkill;

	int m_currentSunAdd;
	int m_currentSunAddNum;
	int m_currentTurn;
	int m_previousTurn;
	pvztime_t m_nextSunAddTime;
	float m_sunCostMultiplier;

	CurrentHealthData m_selfHp;
	CurrentHealthData m_oppoentHp;

	std::vector<NewPVPZombieUpgradeData> m_selfZombieUpgrade;
	std::vector<NewPVPZombieUpgradeData> m_oppoentZombieUpgrade;

	std::vector<PlantCacheData> m_plantCacheDatas;
	std::vector<PlantCacheData> m_plantOppoentCacheDatas;
	float m_selfPlantDelay;
	float m_oppoentPlantDelay;
	float m_selfZombieDelay;
	float m_oppoentZombieDelay;
	bool m_requestTriggerSurrender;

	pvztime_t m_nextFPSCheckTime;

	NewPVPCurrentLevelCPU m_currentCPU;

	TutorialFinger m_finger;
	bool m_triggerTutorial;
	bool m_tutorialAddedZombie;
	Sexy::SexyVector2 m_vArrowOffset;
	Sexy::SexyVector2 m_vArrowPosition;
	float             m_iArrowRot;
	class PopAnimRig* m_pArrowRig;
	bool			  m_arrowVisible;
	float			  m_nextTutorialZombieSpawnTime;
};

class NewPVPGameModule : public ScaledBoardModule
{
public:
	RT_CLASS_DEFINE(NewPVPGameModule, ScaledBoardModule, RtClass);

	NewPVPGameModule();
	~NewPVPGameModule();

	bool HasObtainedDailyChest() { return m_hasObtainedDailyChest; }
	bool HasObtainedWeeklyChest() { return m_hasObtainedWeeklyChest; }

protected:
	void registerForEvents() override;
	void initializeModule() override;

private:
	void onLoadComplete();
	void onNotifyHealthEmpty(bool i_self);
	void generateHealthBars();
	void generateTestUpgrade();
	void generateFPSCounter();
	void generatePlantNumCounter();

	void onZombieCloseToHouse(class Zombie* i_zombie);
	bool checkWin();
	void onInit();
	void initializeAreas();
	void onGameplayEnded();
	void onUpdate();
	void onNewPVPCompleteTask(int i_taskID);
	void onZombieAddedToBoard(Zombie* i_zombie);

	bool m_hasWon;
	bool m_hasObtainedDailyChest;
	bool m_hasObtainedWeeklyChest;
};

class NewPVPGameModuleProperties : public ScaledBoardModuleProperties
{
public:
	RT_CLASS_DEFINE(NewPVPGameModuleProperties, ScaledBoardModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return NewPVPGameModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> LevelBlacklist;
};

class NewPVPIntro : public StandardLevelIntro
{
public:
	enum NewPVPIntroState
	{
		NewPVPIntroState_Init,
		NewPVPIntroState_IntroStart,
		NewPVPIntroState_WaitingForPlayers,
		NewPVPIntroState_WaitingForCardEnter,
		NewPVPIntroState_ReadySetPlant,
		NewPVPIntroState_Finished
	};

	RT_CLASS_DEFINE(NewPVPIntro, StandardLevelIntro, RtClass);

	NewPVPIntro();

	float GetShowReadyTime() override;
	bool suppressReadySetGo() const override { return true; }

protected:
	void onStandardIntroComplete() override;
	void registerForEvents() override;

private:
	void setState(NewPVPIntroState i_state);
	NewPVPIntroState getState() { return m_state; }
	void updateState();
	void onNewPVPNetworkResponseReceived(int i_context, int i_status);
	void onRequestSyncPlayerData();
	void onRequestQueryPlayerData();
	void onUpdate();
	void startGame();
	void onTimeOut();
	void syncPlayers();
	void displayPlayerCards();
	void onEnterCallback(int i_type, class NewPVPInfoCard* i_card);
	void readyForPlayerEnter();
	void addReadyForPlayerEnterToAnimMgr(class AnimationMgr* i_animMgr, float& io_startTime);
	void onPlayerEnterReady();
	void readyForPlantSet();
	void onSetPlantComplete();

	pvztime_t m_nextQuerySyncTime;
	int m_currentQueryCount;
	NewPVPIntroState m_state;
	int m_currentEnteredCard;
	pvztime_t m_startWaitingForPlayerTime;
};

class NewPVPIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(NewPVPIntroProperties, StandardLevelIntroProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return NewPVPIntro::StaticGetClass();
	}
};

class NewPVPStage : public StageModule
{
public:
	RT_CLASS_DEFINE(NewPVPStage, StageModule, RtClass);

	bool CanZombieSpawnInRow(int i_row, ZombieTypePtr i_type) override;

protected:

    void initializeModule() override;
    void registerForEvents() override;

private:
	void onLoadComplete();
	void onUpdate();

	void generateRegions();
	void generateConcreteRegion();
	void generateOppoentRegion();

    void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
};

class NewPVPStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(NewPVPStageProperties, StageModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return NewPVPStage::StaticGetClass();
	}

	NewPVPStageProperties()
	{

	}
};

class BoardRegionConcrete : public BoardRegion
{
public:
	RT_CLASS_DEFINE(BoardRegionConcrete, BoardRegion, RtClass);

	BoardRegionConcrete();
};

class BoardRegionOppoent : public BoardRegion
{
public:
	RT_CLASS_DEFINE(BoardRegionOppoent, BoardRegion, RtClass);

	BoardRegionOppoent();
};

enum
{
	NewPVP_Result_Screen_Button = 1000,
	NewPVP_Result_Screen_BackToMap
};

///
/// Card Game Result Screen
///
class NewPVPResultScreen : public UISingletonDialog<NewPVPResultScreen>
{
public:
    typedef Delegate1<int> NewPVPResultScreenCabllBackSelect;

    NewPVPResultScreen();
	~NewPVPResultScreen();

	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;
	void Update() override;
	virtual std::string GetLayoutName() override { return "UINewPVPResultScreen"; }
	virtual void ButtonDepress(int i_id) override;

	void InitView(NewPVPGameResults type);
	void SetCallback(NewPVPResultScreenCabllBackSelect func);

private:
	void triggerNext();
	void triggerNextAnim();
	void triggerChestAnim();
	void triggerWeeklyChestAnim();
	void displayNextAnim();
	void displayChest();
	void displayWeeklyChest();
	void showNextAnim(class UIWidgetAnim* i_anim, int i_currentBigRank, int i_currentSmallRank, int i_currentStar);

	NewPVPGameResults _screenType;// win / loss
	NewPVPResultScreenCabllBackSelect _buttonCallback;
	SexyString _winDesc;// win desc str
	Rect _winDescRect;
	pvztime_t m_startResultAnimTime;
	pvztime_t m_startChestAnimTime;
	pvztime_t m_startWeeklyChestAnimTime;

	bool m_hasDailyChestReward;
	bool m_hasWeeklyChestReward;
};

class NewPVPGameOutro : public OutroModule
{
public:
	RT_CLASS_DEFINE(NewPVPGameOutro, OutroModule, RtClass);

	NewPVPGameOutro();
	virtual ~NewPVPGameOutro();

	void registerForEvents() override;

protected:
	void postInitialize() override;
	void gameStart();
	void onUpdate();

	void startBoardFade();
	void onBoardFadeDone();

	void startWinOutro();
	void startLossOutro();

    void showResultsScreen(NewPVPGameResults type);
    void onResultsScreenDismissed(int i_type);

    void sendPostEndPlay();

	void onNewPVPNetworkResponse(int i_context, int i_status);

	void onSuccessResponse();

	void onNewPVPNetworkResponseReceived(int i_context, int i_status);

protected:
	class NewPVPResultScreen* m_resultScreen;
	NewPVPGameResults m_result;
};

class NewPVPGameOutroProperties : OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(NewPVPGameOutroProperties, OutroModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return NewPVPGameOutro::StaticGetClass();
	}

	NewPVPGameOutroProperties()
    {

    }
};

// *************************************Hot UIs****************************************
struct AdaptorNewPVPEntryScreenConfig
{
	AdaptorNewPVPEntryScreenConfig()
        : PlayerHeadshot(0)
        , PlayerRankAvatar(0)
    {}

    SexyString PlayerName;
    int PlayerHeadshot;
    int PlayerRankAvatar;
};

class AdaptorNewPVPPlayerInfoScreen : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPPlayerInfoScreen, HotUIAdaptor, RtClass);

	enum ButtonID
	{
		Back = 10
	};

	AdaptorNewPVPPlayerInfoScreen();

public:
	void ButtonDepress(int i_buttonID) override;

	void Update() override;

	void Close();

	void Setup(const AdaptorNewPVPEntryScreenConfig& i_config) { m_config = i_config; }
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

private:
	void setup();
	void updateAvatarIcon();
	void updateRankAvatar();
	void showTab(int i_tabID);
	void updateTabImages(int i_activeTab);

	AdaptorNewPVPEntryScreenConfig m_config;
	std::string m_currentTab;
	std::vector<ImagePtr> m_inactiveTabImages;
	std::vector<ImagePtr> m_activeTabImages;
	std::vector<class HotUIButton*> m_tabs;
};

// Training
struct NewPVPTrainingPacketInfo
{
	NewPVPTrainingPacketInfo()
	: Type(-1)
	, Rare(0)
	, Level(1)
	, UnlockedTurn(1)
	, Unlocked(false)
	, Cost(0)
	{

	}

	NewPVPTrainingPacketInfo(int i_type, int i_rare, int i_level, int i_unlockedTurn, int i_unlocked, int i_cost)
	: Type(i_type)
	, Rare(i_rare)
	, Level(i_level)
	, UnlockedTurn(i_unlockedTurn)
	, Unlocked(i_unlocked)
	, Cost(i_cost)
	{

	}

	int Type;
	int Rare;
	int Level;
	int UnlockedTurn;
	bool Unlocked;
	int Cost;
};

enum TrainingPacketType
{
	TrainingPacketType_Upper,
	TrainingPacketType_Lower
};

struct AdaptorNewPVPTrainingEntryConfig
{
	AdaptorNewPVPTrainingEntryConfig()
	: Type(-1)
	, Rare(0)
	, Level(1)
	, UnlockedTurn(1)
	, PieceNum(-1)
	, RequiredPieceNum(-1)
	, Unlocked(false)
	, Cost(0)
	{

	}

	int Type;
	int Rare;
	int Level;
	int UnlockedTurn;
	int PieceNum;
	int RequiredPieceNum;
	bool Unlocked;
	int Cost;
};

class HotUIWidgetTrainingProgressBar: public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIWidgetTrainingProgressBar, HotUIWidget, RtClass);

	HotUIWidgetTrainingProgressBar();

	virtual ~HotUIWidgetTrainingProgressBar();

	void SetInfo(const AdaptorNewPVPTrainingEntryConfig& i_info);

protected:
	// Widget initialization
	void			onInitializeWidget() override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	void 			onUpdate() override;

private:
	void drawProgress(Graphics* i_g);
	void init();

	AdaptorNewPVPTrainingEntryConfig m_info;
	SexyString m_pieceStr;
};

class HotUIWidgetTrainingProgressBarProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetTrainingProgressBarProperties, HotUIWidgetProperties, RtClass);

	HotUIWidgetTrainingProgressBarProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetTrainingProgressBar::StaticGetClass();
	}
};

enum TrainingPacketMotion
{
    PVZ_BEGIN_ENUM(TrainingPacketMotion_),
    TrainingPacketMotion_Idle,
    TrainingPacketMotion_Interpolate,
    PVZ_END_ENUM(TrainingPacketMotion_),
};

class HotUIWidgetTrainingPacket: public HotUIWidget
{
public:
	enum PacketType
	{
		PacketType_Plant,
		PacketType_Zombie
	};

	RT_CLASS_DEFINE(HotUIWidgetTrainingPacket, HotUIWidget, RtClass);

	HotUIWidgetTrainingPacket();


	virtual ~HotUIWidgetTrainingPacket();

	void SetInfo(const NewPVPTrainingPacketInfo& i_info);
	void SetTrainingPacketType(TrainingPacketType i_type) { m_trainingPacketType = i_type ;}
	const NewPVPTrainingPacketInfo& GetInfo() { return m_info; }

	void SetSelected(bool i_selected);
	bool IsSelected() { return m_selected; }
	bool IsLocked() { return !m_info.Unlocked; }

	virtual bool CanSelect() { return true;}
    void SetDrawScale(float i_scale) { m_drawScale = i_scale; }

protected:

	// Widget initialization
	void			onInitializeWidget() override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	void 			onUpdate() override;

protected:
	void onNotifyTraingingPacketSelected(bool i_upper, int i_type, bool i_selected);
	void drawPacket(Graphics* i_g);
	virtual void init();

	bool m_unlocked;
	bool m_selected;
	NewPVPTrainingPacketInfo m_info;
	PacketType m_type;
	Sexy::DeviceImage* m_seedPacketImage;
	std::vector<Image*> m_unlockedTurnImgs;
	SexyString m_levelStr;
	TrainingPacketType m_trainingPacketType;
    float m_drawScale;
};

class HotUIWidgetTrainingPacketProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetTrainingPacketProperties, HotUIWidgetProperties, RtClass);

	HotUIWidgetTrainingPacketProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetTrainingPacket::StaticGetClass();
	}
};

class HotUIWidgetTrainingPacketMotion: public HotUIWidgetTrainingPacket
{
public:
	RT_CLASS_DEFINE(HotUIWidgetTrainingPacketMotion, HotUIWidgetTrainingPacket, RtClass);

	HotUIWidgetTrainingPacketMotion();

	virtual ~HotUIWidgetTrainingPacketMotion();

	void UpdateMotion();
	void SetMotionInterpolate(HotUIWidgetTrainingPacket* i_bindPacket, const SexyVector2& i_initialPosition, const SexyVector2& i_finalPosition, pvztime_t i_duration, CurveType i_interpMethod);
	void SetMotionIdle();
	bool IsFinished() { return m_finishMotion; }

	bool CanSelect() override { return false; }

	void SetOnFinishAction(std::function<void()> i_onFinish) { m_onFinishCallback = i_onFinish; }

protected:

	// Widget initialization
	void 			onInitializeWidget() override;
	void 			init() override;

	// Widget drawing
	void 			onUpdate() override;

private:
	void onFinishMotion();

	TrainingPacketMotion 	m_motion;
	pvztime_t			m_motionStartTime;
	SexyVector2		m_interp_initialPosition;
	SexyVector2		m_interp_finalPosition;
	pvztime_t		m_interp_duration;
	CurveType		m_interp_method;

	bool            m_finishMotion;
	HotUIWidgetTrainingPacket* m_bindPacket;
	std::function<void()> m_onFinishCallback;
};

class HotUIWidgetTrainingPacketMotionProperties : public HotUIWidgetTrainingPacketProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetTrainingPacketMotionProperties, HotUIWidgetTrainingPacketProperties, RtClass);

	HotUIWidgetTrainingPacketMotionProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetTrainingPacketMotion::StaticGetClass();
	}
};

class AdaptorNewPVPTrainingConfig
{
public:
	void Order();

	std::vector<AdaptorNewPVPTrainingEntryConfig> Entries;
};

class AdaptorNewPVPTrainingEntry : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPTrainingEntry, HotUIAdaptor, Sexy::RtClass);

	enum ButtonID
	{
		Selected
	};

	enum EditState
	{
		Idle,
		WaitingForEdit
	};

	AdaptorNewPVPTrainingEntry();
	virtual ~AdaptorNewPVPTrainingEntry();

	void Configure(WidgetContainer* i_parent, const AdaptorNewPVPTrainingEntryConfig& i_config);

	void ButtonDepress(int i_buttonID) override;

	virtual void UnlockBtn(bool i_unlock);

	void SetState(EditState i_state);
	EditState GetState() { return m_editState; }
	bool IsSelected();

	void SetConfig(const AdaptorNewPVPTrainingEntryConfig& i_config);
	const AdaptorNewPVPTrainingEntryConfig& GetConfig() { return m_config; }

	void SetParentScreen(class AdaptorNewPVPTrainingScreen* i_board) { m_screen = i_board; }

	void Switch(AdaptorNewPVPTrainingEntry* i_src);
	virtual bool IsUpperTrainingPacket();
	void unselect();
	virtual void select(bool i_notify = true);

	SexyVector2 GetTrainingPacketAbsLocation();
	void HidePacket(bool i_visible);
	HotUIWidgetTrainingPacket* GetTrainingPacket();

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

	void onNotifyTraingingPacketSelected(bool i_upper, int i_type, bool i_selected);

	WidgetContainer* m_parent;
	AdaptorNewPVPTrainingEntryConfig m_config;
	EditState m_editState;
	class AdaptorNewPVPTrainingScreen* m_screen;
};

class AdaptorNewPVPUpperTrainingEntry : public AdaptorNewPVPTrainingEntry
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPUpperTrainingEntry, AdaptorNewPVPTrainingEntry, Sexy::RtClass);


	AdaptorNewPVPUpperTrainingEntry();
	virtual ~AdaptorNewPVPUpperTrainingEntry();

protected:
	void onLinkToUIViewCreated() override;

	void select(bool i_notify = true) override;
	bool IsUpperTrainingPacket() override;
};

class AdaptorNewPVPTrainingBoard : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPTrainingBoard, HotUIAdaptor, Sexy::RtClass);

	AdaptorNewPVPTrainingBoard();
	virtual ~AdaptorNewPVPTrainingBoard();

	void Configure(WidgetContainer* i_parent, const AdaptorNewPVPTrainingConfig& i_config);
	virtual void UnloadEntries();
	void WaitingForEdit();
	bool IsWaitingForEdit();
	void FinishEdit();
	AdaptorNewPVPTrainingEntry* GetUpperSelectedEntry();
	const AdaptorNewPVPTrainingEntryConfig& GetEntryConfigById(int i_type);

	void GetEntriesIds(std::vector<int>& i_outIds);
	bool IsEmpty();

	// Set config and refresh
	void SetConfig(const AdaptorNewPVPTrainingConfig& i_config);
	void SetScreen(class AdaptorNewPVPTrainingScreen* i_screen) { m_screen = i_screen; }

	void UnlockBtns(bool i_unlock);
	void Unselect();

	void RepositionEntries();
	void SelectEntry(int i_index);
	void SelectEntryById(int i_id);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	virtual void fillEntries();

	WidgetContainer* m_parent;
	std::vector<AdaptorNewPVPTrainingEntry*> m_trainingEntries;

	AdaptorNewPVPTrainingConfig m_config;
	class AdaptorNewPVPTrainingScreen* m_screen;
};

class AdaptorNewPVPUpperTrainingBoard : public AdaptorNewPVPTrainingBoard
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPUpperTrainingBoard, AdaptorNewPVPTrainingBoard, Sexy::RtClass);

	AdaptorNewPVPUpperTrainingBoard();
	virtual ~AdaptorNewPVPUpperTrainingBoard();

protected:
	void onLinkToUIViewCreated() override;
	void fillEntries() override;
};

// Level Up
class AdaptorNewPVPLevelUpScreen : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPLevelUpScreen, HotUIAdaptor, RtClass);

	enum ButtonID
	{
		Unlock,
		LevelUp,
		Exit
	};

	AdaptorNewPVPLevelUpScreen();

	virtual ~AdaptorNewPVPLevelUpScreen();

	void SetConfig(const AdaptorNewPVPTrainingEntryConfig& i_config);
	const AdaptorNewPVPTrainingEntryConfig& GetConfig() { return m_config; }
	void ApplyPacketInfo();
	void SetOnBackAction(std::function<void()> i_onBack);

public:
	void ButtonDepress(int i_buttonID) override;

	void Update() override;

	void Close();

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

	void onNewPVPNetworkResponseReceived(int i_context, int i_status);

private:
	void setup();
	void initStats(HotUIStringMap& i_stringMap);
	void onLevelUp();
	void onLevelUpResult(bool i_success);

	AdaptorNewPVPTrainingEntryConfig m_config;
	std::function<void()> m_onBackCallback;
};

class AdaptorNewPVPLevelUpResultScreen : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPLevelUpResultScreen, HotUIAdaptor, RtClass);

	enum ButtonID
	{
		Exit
	};

	AdaptorNewPVPLevelUpResultScreen();

	virtual ~AdaptorNewPVPLevelUpResultScreen();

	void SetConfig(const AdaptorNewPVPTrainingEntryConfig& i_config);
	const AdaptorNewPVPTrainingEntryConfig& GetConfig() { return m_config; }
	void ApplyPacketInfo();

public:
	void ButtonDepress(int i_buttonID) override;

	void Update() override;

	void Close();

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

private:
	void setup();

	AdaptorNewPVPTrainingEntryConfig m_config;
};

class AdaptorNewPVPTrainingScreen : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPTrainingScreen, HotUIAdaptor, RtClass);

	enum ButtonID
	{
		Back,
		Edit,
		Save,
		Info
	};

	AdaptorNewPVPTrainingScreen();

	virtual ~AdaptorNewPVPTrainingScreen();

public:
	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;

	void Update() override;

	void Close();
	void SetOnBackAction(std::function<void()> i_onBack);

	AdaptorNewPVPTrainingEntry* GetUpperSelectedEntry();
	bool IsWaitingForEdit();
	void Reload();
	const AdaptorNewPVPTrainingEntryConfig& GetEntryConfigById(int i_type);
	const AdaptorNewPVPTrainingEntryConfig& GetUpperEntryConfigById(int i_type);

	void ApplyTrainingPacketMotion(HotUIWidgetTrainingPacket* i_upper, HotUIWidgetTrainingPacket* i_lower);
	void BuildUnlockedTrainingInfo(int i_unlockedTurn);
	void RepositionBoard();

	void SetCacheBattleInfos(const std::vector<int>& i_infos) { m_cacheBattleInfos = i_infos; }
	void UpdateCacheBattleInfos(int i_srcId, int i_swapId);
	bool IsInCacheBattleInfos(int i_id);
	void UnlockBtns(bool i_unlock);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

	void onNewPVPNetworkResponseReceived(int i_context, int i_status);
	void onNotifyTraingingPacketSelected(bool i_upper, int i_type, bool i_selected);

private:
	void setup();
	void enableFuncBtns(bool i_enable);
	void onEdit();
	void onEditBack();
	void onSave();
	void onShowInfo();
	void onPacketMotionFinished(int i_id);
	AdaptorNewPVPTrainingConfig buildTrainingInfo();
	void addTrainingEntry(AdaptorNewPVPTrainingConfig& io_config);

	AdaptorNewPVPTrainingConfig buildUpperTrainingInfo();
	void addUpperTrainingEntry(AdaptorNewPVPTrainingConfig& io_config);

	AdaptorNewPVPTrainingConfig buildUnlockedTrainingInfo();
	AdaptorNewPVPTrainingConfig buildUnlockedTrainingInfo(int i_unlockedTurn);
	void addUnlockedTrainingEntry(AdaptorNewPVPTrainingConfig& io_config);
	void addUnlockedTrainingEntry(AdaptorNewPVPTrainingConfig& io_config, int i_unlockedTurn);

	void onSavedResult(bool i_success);
	void onLevelUpResult(bool i_success);
	void onConfirmSavedResult();

	void createLevelUpScreen(int i_type);
	void createLevelUpResultScreen(int i_type);
	void onLevelUpBack();

	std::function<void()> m_onBackCallback;
	AdaptorNewPVPTrainingBoard* m_trainingBoard;
	AdaptorNewPVPUpperTrainingBoard* m_upperTrainingBoard;
	int m_currentLevelUpId;
	std::vector<int> m_cacheBattleInfos;
};

class AdaptorNewPVPPreMatchingScreen : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPVPPreMatchingScreen, HotUIAdaptor, RtClass);

	enum ButtonID
	{
		Match,
		Back
	};

	AdaptorNewPVPPreMatchingScreen();
	virtual ~AdaptorNewPVPPreMatchingScreen();

public:
	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;

	void Update() override;

	void Close();
	void SetOnPlayAction(std::function<void()> i_onPlay);
	void SetOnBackAction(std::function<void()> i_onBack);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

private:
	void setup();
	void onNotifyTutorialStep(int i_step);

	std::function<void()> m_onPlayCallback;
	std::function<void()> m_onBackCallback;
};

STATE_ENUM_BASE_BEGIN(NewPVPMatchingScreenState)
	MS_QUEUEING,
    MS_FINDING,
    MS_FOUND,
    MS_OUTRO,
    MS_FINISHED,
STATE_ENUM_END(NewPVPMatchingScreenState);

struct AdaptorNewPVPMatchingScreenConfig
{
	AdaptorNewPVPMatchingScreenConfig()
        : PlayerHeadshot(0)
        , PlayerRankAvatar(0)
		, Mode(0)
    {}

    SexyString PlayerName;
    SexyString OpponentName;
    int PlayerHeadshot;
    int PlayerRankAvatar;
    std::vector<int> SelectedPlants;
    std::vector<int> SelectedMaps;
    int Mode;
};

class HotUIImageNetConnecting: public HotUIImage
{
public:

	RT_CLASS_DEFINE(HotUIImageNetConnecting, HotUIImage, RtClass);

	HotUIImageNetConnecting()
	: m_Rot(0)
	{}

	virtual ~HotUIImageNetConnecting()
	{}

	void SetWaitingImage(ImagePtr i_image);

protected:

	// Widget initialization
	void			onInitializeWidget() override;
	void			onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	void 			onUpdate() override;

private:

	std::string				m_processedImageName;
	std::string				m_processedTips;
	ImagePtr				m_waitingImage;
	double 					m_Rot;
};

class HotUIImageNetConnectingProperties : public HotUIImageProperties
{
public:
	RT_CLASS_DEFINE(HotUIImageNetConnectingProperties, HotUIImageProperties, RtClass);

	HotUIImageNetConnectingProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIImageNetConnecting::StaticGetClass();
	}

	std::string			WaitingImage;
	std::string			Tips;
};

class HotUIWidgetPacketContainer: public HotUIWidget
{
public:

	enum PacketType
	{
		PacketType_Plant,
		PacketType_Zombie
	};

	RT_CLASS_DEFINE(HotUIWidgetPacketContainer, HotUIWidget, RtClass);

	HotUIWidgetPacketContainer()
	{}

	virtual ~HotUIWidgetPacketContainer();


	void SetType(PacketType i_type) { m_type = i_type; }
	void AddPacket(int i_id);

protected:

	// Widget initialization
	void			onInitializeWidget() override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	void 			onUpdate() override;

private:
	void drawPacket(Graphics* i_g, const std::string& i_typeName, Rect i_drawRect, int i_index);

	std::vector<std::string> m_ids;
	PacketType m_type;
	std::vector<Sexy::DeviceImage*> m_seedPacketImages;
};

class HotUIWidgetPacketContainerProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetPacketContainerProperties, HotUIWidgetProperties, RtClass);

	HotUIWidgetPacketContainerProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetPacketContainer::StaticGetClass();
	}
};

class NewPVPMatchingTips: public HotUILabel
{
public:

	RT_CLASS_DEFINE(NewPVPMatchingTips, HotUILabel, RtClass);

	NewPVPMatchingTips()
	{

	};

	virtual ~NewPVPMatchingTips()
	{

	};

	const std::vector<std::string>& GetTips();
};

class NewPVPMatchingTipsProperties : public HotUILabelProperties
{
public:
	RT_CLASS_DEFINE(NewPVPMatchingTipsProperties, HotUILabelProperties, RtClass);

	NewPVPMatchingTipsProperties()
	{

	};

	RtClass* GetWidgetClass() const override
	{
		return NewPVPMatchingTips::StaticGetClass();
	}

	std::vector<std::string> Tips;
};

class AdaptorNewPVPMatchingScreen : public HotUIAdaptor
{
public:
    RT_CLASS_DEFINE(AdaptorNewPVPMatchingScreen, HotUIAdaptor, RtClass);

    enum ButtonID
	{
		Re_Matching,
		Cancel_Matching
	};

    enum MatchingResult
    {
    	Enter_Matching,
    	Already_Matched,
    	Matching_Failed,
    	Need_Queueing
    };

    AdaptorNewPVPMatchingScreen();
    virtual ~AdaptorNewPVPMatchingScreen();

    void Setup(const AdaptorNewPVPMatchingScreenConfig& i_config);
    void Update() override;

    void ButtonDepress(int i_buttonID) override;

    void SetOnCancelAction(std::function<void()> i_onCancel) { m_onCancelCallback = i_onCancel; }
    void SetOnCloseAction(std::function<void()> i_onClose) { m_onCloseCallback = i_onClose; }

protected:
    void onLoadUIView() override;
    void onLinkToUIViewCreated() override;
    void onLayoutFinished() override;

    void onNewPVPNetworkResponseReceived(int i_context, int i_status);

    void checkQueue();
    void startQueue();
    void updateQueueing();
    void startFindingOppoent();
    void finishFindingOppoent();
    void findOppoent();
    void onRequestMatchingPlayerData();
    void onRequestCancelMatchingPlayerData();
    void onRequestQueryMatchingPlayerData();
    void updateFindingOppoent();
    //void onTimeOut();
    void enterGame();
    void setup();
    void showNetConnecting(bool i_show);
    void onNotifyLoadingLevelFinished();
    void startShowMatchingText(bool i_show);
    int getEstimitedMatchingTime();
    void updateAvatarIcon();
    void updateRankAvatar();
    void onMatchingError(class UIMessageBox* box, int buttonID);
    void timeout();
    void onTimeOut(UIMessageBox* box, int buttonID);

    DECLARE_FSM_HANDLER_BASE(NewPVPMatchingScreenState);

    DECLARE_FSM_STATE_VALUE(NewPVPMatchingScreenState);

private:
    void close();
    void adjustCancelButton(bool i_isQueueing);

    AdaptorNewPVPMatchingScreenConfig m_config;
    pvztime_t m_nextQuerySyncTime;
    pvztime_t m_nextQueryQueueTime;
    int m_currentQueryCount;
    HotUIWidget* m_netConnecting;
    pvztime_t m_startMatchingTime;
    pvztime_t m_startQueueingTime;

    std::function<void()> m_onCancelCallback;
    std::function<void()> m_onCloseCallback;

    int m_totalDisconnectCount;
};

class NewPVPCoinBank : public FuelBank
{
public:
	RT_CLASS_DEFINE(NewPVPCoinBank, FuelBank, RtClass);

    void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    void OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	void OnMouseDown(const int i_mouseX, const int i_mouseY) override;

private:
    void updateButtonStates(const int i_screenX, const int i_screenY, const bool i_isPressed) override;
};

class AdaptorNewPVPEntryScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorNewPVPEntryScreen, HotUIAdaptor, Sexy::RtClass);

public:
	enum ButtonID
	{
		Play = 10,
		BackToMap,
		FreeToPlay,
		MatchToPlay,
		ShowPlayerInfo,
		ShowRank,
		ShowAreaInfo,
		ShowOverview,
		OpenShop
	};

public:
	AdaptorNewPVPEntryScreen();
	virtual ~AdaptorNewPVPEntryScreen();

	void ButtonDepress(int i_buttonID) override;

	void Update() override;
	// void Draw(Graphics* g) override;
//	void DrawAll(ModalFlags* theFlags, Graphics* g) override;

	void RemovedFromManager(WidgetManager* i_widgetMgr) override;
	void Setup(const AdaptorNewPVPEntryScreenConfig& i_config) { m_config = i_config; }

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

private:
	void setup();
	void close();

	void onNotifyTutorialStep(int i_step);
	bool canHandleInput();
	void onPlay(int i_mode);
	void onMatching(int i_mode);
	void onPlayerInfo();
	void onShowRank();
	void onShowAreaInfo();
	void createPlayerInfoScreen();
	void getSelectInfo();
	void createPrematchingScreen(int i_mode);
	void onPrematchingBack();
	void updateAvatarIcon();
	void updateRankAvatar();
	void showTab(int i_tabID);
	void updateTabImages(int i_activeTab);
	void showOverview();
	void onShowOverview();
	void openShop();
	bool hasAnyPlantsSelect();
	void onEnterTraining();
	void createTrainingScreen();
	void onTrainingBack();
	void onCheckTasks();
	void onCheckTaskRanks();	// just for pass ranks
	void onCheckRanks();
	void showThirdSeasonTips();
	bool checkPass();

	AdaptorNewPVPPreMatchingScreen* m_preMatchingScreen;
	AdaptorNewPVPEntryScreenConfig m_config;

	AdaptorNewPVPTrainingScreen* m_trainingScreen;

	std::string m_currentTab;

	std::vector<ImagePtr> m_inactiveTabImages;
	std::vector<ImagePtr> m_activeTabImages;

	std::vector<class HotUIButton*> m_tabs;
	pvztime_t m_accumulatedTime;
};

class NewPVPMainEntryScreenTopHUD : public PVZGameStateTopHUDController
{
public:
	RT_CLASS_DEFINE(NewPVPMainEntryScreenTopHUD, PVZGameStateTopHUDController, Sexy::RtClass);

	void Open() override;
};

class NewPVPMainEntryScreenState : public PVZHotUIGameState
{
public:
	RT_CLASS_DEFINE(NewPVPMainEntryScreenState, PVZHotUIGameState, RtClass);

protected:
	RtClass* getTopHudControllerClass() override;
	RtClass* getHotUIAdaptorClass() override;

	void Enter() override;

	std::string GetMusicStartEvent() override { return "Play_Joust_Dashboard_Music"; }
	std::string GetMusicStopEvent() override { return "Stop_Joust_Dashboard_Music"; }

};

class AdaptorNewPVPAreaHowToPlayScreen : public AdaptorJoustHowToPlayScreen
{
    RT_CLASS_DEFINE(AdaptorNewPVPAreaHowToPlayScreen, AdaptorJoustHowToPlayScreen, RtClass);

protected:
    void onLoadUIView() override;
};

// *************************************Areas***********************************
typedef RtWeakPtr<class NewPVPAreaProperties> NewPVPAreaPropertiesPtr;
typedef RtWeakPtr<class NewPVPAreaMainProperties> NewPVPAreaMainPropertiesPtr;

enum AreaType
{
	Area_None = -1,
	Area_Slider,
	Area_Mist,
	Area_GuideDoor,
	Area_Merge
};

class NewPVPAreaMainProperties : public PropertySheetBase
{
	RT_CLASS_DEFINE(NewPVPAreaMainProperties, PropertySheetBase, RtClass);

	std::string Description;
	std::string Name;
	AreaType Type;
	std::vector<std::string> AreaNames;

	virtual SexyString GetDescription();
	virtual SexyString GetName();
};

class NewPVPAreaProperties : public PropertySheetBase
{
	RT_CLASS_DEFINE(NewPVPAreaProperties, PropertySheetBase, RtClass);

	std::string TypeName;
	std::string ClassName;
};

class NewPVPArea : public GameObject
{
public:
	RT_CLASS_DEFINE(NewPVPArea, GameObject, RtClass);
	NewPVPArea();
	virtual ~NewPVPArea();
	virtual void Initialize(NewPVPAreaPropertiesPtr i_propsPtr);
	NewPVPAreaPropertiesPtr GetProps() { return m_props; }
	virtual void Activate();
	virtual void Update() {}
	virtual void Draw(Graphics* i_g) {}

	void AddToRenderQueue(class RenderQueue* i_queue);

	virtual int GetRenderOrder();

	bool IsActivated() { return m_activated; }

protected:
	NewPVPAreaPropertiesPtr m_props;
	bool m_activated;
};

struct AreaData
{
	AreaData()
	{
		PropsPtr = NewPVPAreaPropertiesPtr();
	}
	NewPVPAreaPropertiesPtr PropsPtr;
};

struct NewPVPGridItemPlacement
{
	NewPVPGridItemPlacement()
	{
		GridX = -1;
		GridY = -1;
	}

	std::string		TypeName;
	int				GridX;
	int				GridY;
};

class NewPVPAreaSliderProperties : NewPVPAreaProperties
{
public:
	RT_CLASS_DEFINE(NewPVPAreaSliderProperties, NewPVPAreaProperties, RtClass);

	NewPVPAreaSliderProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<NewPVPGridItemPlacement> InitialGridItemPlacements;
};

class NewPVPAreaSlider : public NewPVPArea
{
public:
	RT_CLASS_DEFINE(NewPVPAreaSlider, NewPVPArea, RtClass);
	~NewPVPAreaSlider();

	void Activate() override;

private:
	void onGameplayStarted();
};

class NewPVPAreaMistProperties : NewPVPAreaProperties
{
public:
	RT_CLASS_DEFINE(NewPVPAreaMistProperties, NewPVPAreaProperties, RtClass);

	NewPVPAreaMistProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float       m_iNormValX;
	pvztime_t   m_iBloverEffectInterval;
	int         m_iInitMistPosX;
};

class NewPVPAreaMist : public NewPVPArea
{
public:
	RT_CLASS_DEFINE(NewPVPAreaMist, NewPVPArea, RtClass);
	NewPVPAreaMist();

	~NewPVPAreaMist();

	void Activate() override;
	void Draw(Graphics* i_g) override;
	void Update() override;
	int GetRenderOrder() override;

private:
	void onGameplayStarted();

	void            InitMistImage();
	void            SetMistImagePos(float iX, float iY);
	MistImageInfo*  GetWarMistModule(int i, int j);
	void            DrawMistImage(Graphics* pGraphics);
	void            AddEmptyRect(Point& p);
	void            UpdateEmptyRect();
	void            RealRefreshRect();

	void            OnPlantRefresh(Plant* pPlant);

	void            CheckStreetEffect(BoardEntity* pEntity);
	void            CheckTorchWoodEffect(BoardEntity* pEntity);
	void            CheckBloverEffect();

	void            StreetLampUseSkill();
	void            StreetLampUseSkillEnd();

	void            MistyIntervalUpdata();

private:

	bool                        m_bGameStart;
	bool                        m_bStatic;
	bool                        m_bRefresh;
	bool                        m_bStreetLampFoodEffectRunning;
	float                       m_iTargetPosX;
	pvztime_t                   m_iIntervalEndTime;

	std::vector<MistImageInfo>  m_vMistImageVec;
	std::vector<Point>          m_EmptyPointVec;
	std::vector<SupplymentInfo> m_SupplymentVec;
	std::vector<MistImageInfo>  m_vFragmentMistImageVec;
};

struct NewPVPGuideDoorLocation
{
	NewPVPGuideDoorLocation()
	{

	}

	Point StartLocation;
	Point EndLocation;
};

class NewPVPGuideStartDoor : public GuideStartDoor
{

public:

    RT_CLASS_DEFINE(NewPVPGuideStartDoor, GuideStartDoor, RtClass);

    NewPVPGuideStartDoor() {}

    virtual ~NewPVPGuideStartDoor() {}

protected:
    bool manualDestroy() override;
};

class NewPVPAreaGuideDoorProperties : NewPVPAreaProperties
{
public:
	RT_CLASS_DEFINE(NewPVPAreaGuideDoorProperties, NewPVPAreaProperties, RtClass);

	NewPVPAreaGuideDoorProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<NewPVPGuideDoorLocation> GuideDoors;
};

class NewPVPAreaGuideDoor : public NewPVPArea
{
public:
	RT_CLASS_DEFINE(NewPVPAreaGuideDoor, NewPVPArea, RtClass);
	~NewPVPAreaGuideDoor();

	void Activate() override;

private:
	void onGameplayStarted();
	void generateDoor(Sexy::Point startGrid, Sexy::Point endGrid);
	class Effect_PopAnim* locateEffect(Sexy::Point effectGrid, bool bStart);
};

struct MergeGroup
{
	MergeGroup()
	: MergeEndTime(PVZ_EOT())
	, MinRequireNum(0)
	, Duration(0)
	, GroupSize(0)
	, Merging(false)
	{

	}

	MergeGroup(int i_minRequireNum, float i_duration)
	: MergeEndTime(PVZ_EOT())
	, MinRequireNum(i_minRequireNum)
	, Duration(i_duration)
	, GroupSize(0)
	, Merging(false)
	{

	}

	bool CanAddToGroup(ZombiePtr i_zombiePtr);
	bool AddToGroup(ZombiePtr i_zombiePtr);
	bool AddToEmptyGroup(ZombiePtr i_zombiePtr);
	void AddDirectly(ZombiePtr i_zombiePtr);
	bool Find(ZombiePtr i_zombiePtr);
	bool FindType(ZombiePtr i_zombiePtr);
	void Update();
	void Merge(pvztime_t i_duration);
	class Zombie* SpawnMergedZombie(ZombiePtr i_srcZombiePtr, float i_totalMaxHP, float i_totalMaxHelmHP, float i_totalDPS);
	void Clear();
	bool Remove(ZombiePtr i_zombiePtr);
	void Reset();
	bool IsMergingComplete();
	bool IsMerging() { return Merging; }
	void SetIsMerging(bool i_merging) { Merging = i_merging; }

	pvztime_t MergeEndTime;
	std::vector<ZombiePtr> ZombiesToMerge;
	int MinRequireNum;
	float Duration;
	int GroupSize;
	bool Merging;
};

class NewPVPAreaMergeProperties : NewPVPAreaProperties
{
public:
	RT_CLASS_DEFINE(NewPVPAreaMergeProperties, NewPVPAreaProperties, RtClass);

	NewPVPAreaMergeProperties()
	: MinMergeNum(3)
	, MergeDuration(3.0f)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	ZombieRestrictionSet TargetableZombieTypes;
	int MinMergeNum;
	float MergeDuration;
};

class NewPVPAreaMerge : public NewPVPArea
{
public:
	RT_CLASS_DEFINE(NewPVPAreaMerge, NewPVPArea, RtClass);
	~NewPVPAreaMerge();

	void Activate() override;
	void Update() override;

private:
	MergeGroup* FindSameGroup(ZombiePtr i_zombiePtr);

	void onZombieDestroyed(class Zombie* i_zombie);
	void updateMerges();
	void updateMergeGroups();
	void addToGroup(class Zombie* i_zombie);

	std::vector<MergeGroup> m_mergeGroups;
};

// *************************************Hot UIs****************************************

struct LogSunUpgradeInfo
{
	LogSunUpgradeInfo()
	: Level(0)
	, Turn(0)
	{

	}

	LogSunUpgradeInfo(int i_level, int i_turn)
	: Level(i_level)
	, Turn(i_turn)
	{

	}

	int Level;
	int Turn;
};

struct LogActionCountInfo
{
	LogActionCountInfo()
	: AddPlantsCount(0)
	, AddZombiesCount(0)
	, SpeedUpgradeCount(0)
	, HPUpgradeCount(0)
	, BerserkUpgradeCount(0)
	, OppoentMergeCount(0)
	, OppoentMergeHighestLevel(0)
	, TriggerUpgradeCount(0)
	{

	}

	int AddPlantsCount;
	int AddZombiesCount;
	int SpeedUpgradeCount;
	int HPUpgradeCount;
	int BerserkUpgradeCount;
	int OppoentMergeCount;
	int OppoentMergeHighestLevel;
	int TriggerUpgradeCount;
};

class NewPVPMgr : public LazySingleton <NewPVPMgr>
{
public:
	NewPVPMgr();
    ~NewPVPMgr();

    const class NewPVPPropertySheet* GetProps();
    void InitProps(const class Network_NewPVPPropertySheet* props, int i_networkVersion);

    void Update();

    class BaseCursor* TryAddPlantCursor(const Sexy::Touch& i_boardSpaceTouch, RtWeakPtr<class SeedPacket> i_seedPacket);
    class BaseCursor* TryAddShovelCursor(const Sexy::Touch& i_boardSpaceTouch);
    BaseCursor* TryAddPlantfoodCursor(const Sexy::Touch& i_boardSpaceTouch);
    void TryAddZombie(int i_type, int i_level);
    void TryUpgradePlant(int i_x, int i_y);
    void TryUpgradePlantEffect(int i_x, int i_y);
    void TryTriggerZombieSkill(int i_type);
    void TryTriggerZombieUpgrade(int i_type);
    void TryTriggerSurrender();
    void TryTriggerReport();
    AddPacketReason CanAddZombie(int i_type, int i_level);
    int GetCurrentTurn();
    int GetMaxTurn();

    bool IsValidZombie(int i_type, int i_level);
    bool IsValidPlant(int i_type, int i_level);

    bool HasFullHitpoints();

    float GetGlobalZombieCreatedCD();
    int GetPlantLevelUpValue();
    int GetMaxZombieCacheSize();
    int GetStartingSun();
    int GetSunAddBase();
    int GetSunAdd();
    int GetTutorialSunAdd();
    int GetCurrentMaxPlantNum();
    int GetMaxPlantNum(int i_level);
    void SetCurrentSunLevel(int i_level);
    int GetCurrentSunLevel() { return m_currentSunLevel; }
    bool IsSunUpgradeFull();
    int GetSunUpgradeCost(int i_toLevel);
    int GetSunUpgradeValue(int i_level);
    bool CanUpgradeSun(int i_toLevel);
    float GetMaxHealthAmount(bool i_self);
    float GetDamageDealt(bool i_self);
    float GetSunCostMultiplier();
    int GetSafeCost(int i_src);
    float CalcCurrentSunCostMultiplier();

    const std::vector<NewPVPZombiePacketInfo>& GetZombiePacketInfos();
    const std::vector<NewPVPPlantPacketInfo>& GetPlantPacketInfos();
    const std::vector<NewPVPZombieSkillInfo>& GetZombieSkillInfos();
    const std::vector<NewPVPZombieUpgradeInfo>& GetZombieUpgradeInfos();
    const std::vector<int>& GetChooserPlantBlacklist();

    const std::vector<CurrentSelectedPlantPacketInfo>& GetSelectedPlantPacketInfos() { return m_currentSelectedPlantInfos; }
    void SetSelectedPlantPacketInfos(const std::vector<CurrentSelectedPlantPacketInfo>& i_infos) { m_currentSelectedPlantInfos = i_infos; }

    const Network_NewPVPZombieLevelUpData& GetNetworkZombieLevelUpData(int i_type, const Network_NewPVPPropertySheet* props);
    int GetZombieCost(int i_type, int i_level);
    int GetZombieCostAdd(int i_type, int i_level);
    const NewPVPZombieSkillInfo& GetZombieSkillInfo(int i_type);
    const NewPVPZombieUpgradeInfo& GetZombieUpgradeInfo(int i_type);
    float GetSunAddCD(int i_sunAddTotal);
    int GetPlantCost(int i_type, int i_level);
    //bool HasPlantInfo(int i_type);
    const NewPVPPlantPacketInfo& GetPlantPacketInfo(int i_index);

    const std::vector<NewPVPTutorialPlantInfo>& GetTutorialPlantInfo();
    const std::vector<NewPVPCPULevelInfo>& GetCPUInfo(int i_index);
    int GetCPUInfoSize();

    const std::vector<ZombieCacheData>& GetOppoentZombieCacheDatas();

    const JoustHowToPlayScreenData& GetAreaHowToPlayData();

    const NewPVPZombieLevelUpData& GetZombieLevelUpData(int i_type);
    const NewPVPZombieLevelUpValueData& GetZombieLevelUpValueInfo(int i_type, int i_level);

    // Networks
    void ShowNetConnectingUI(const std::string& i_tip);
    void KillNetConnectingUI();

    void SetCurrentGameResult(NewPVPGameResults i_result);
    NewPVPGameResults GetCurrentGameResult() { return m_currentGameResult; }

    void CheatEnter();
    void RequestMainEntryData(std::function<void()> i_afterAction);
    void RequestSyncPlayerData(int i_progress = 100, bool i_fake = false);
    void RequestQueryPlayerData(const std::string& i_matchId, bool i_matching, bool i_fake = false);
    void RequestMatching(int i_type, std::vector<int> i_plants, std::vector<int> i_maps, bool i_fake = false);
    void RequestEndPlay(NewPVPGameResults i_result, bool i_fake = false);
    void RequestCancelMatching(bool i_fake = false);
    void RequestReport(const std::string& i_matchId, const std::string& i_oppoentId);
    void RequestSaveZombieBattleInfo(std::vector<int> i_infos, int i_battleIndex);
    void RequestZombieLevelUp(int i_type);
    const NewPVPQueryPlayerData& GetQueryPlayerData() { return m_currentQueryPlayerData; }
    const std::string& GetCurrentMatchId() { return m_currentMatchData.m_matchId; }
    int GetCurrentMatchingResult() { return m_currentMatchData.m_result; }
    void SetCurrentMatchId(const std::string& i_matchId) { m_currentMatchData.m_matchId = i_matchId; }
    const NewPVPMainEntry& GetMainEntryData() { return m_currentMainEntryData; }
    int GetMaxSyncPlayerTryTime() { return m_currentMainEntryData.m_maxSyncPlayerTryTime; }
    float GetSyncQueueInterval();
    float GetSyncPlayerInterval();
    float GetSyncGameInterval();
    int GetSyncGameDisconnectLimit();
    int GetMatchingDisconnectLimit();
    void syncMainEntryInfo();
    void syncMainEntryInfoTest();
    const Network_PlayerSyncData& GetOppoentPlayerData();
    const Network_PlayerSyncData& GetSelfPlayerData();
    const Network_PlayerSyncData& GetPlayerData(bool i_self);
    bool IsPreviousMatchingTimeout();
    bool IsCurrentMatchingTimeout(bool i_fake = false);
    void ClearCurrentQueryPlayerData();
    const std::vector<int>& GetCurrentMatchSelectedPlants();
    const std::vector<int>& GetCurrentMatchSelectedMaps();
    void SetCurrentSelectedPlants(const std::vector<int>& i_plants);
    void SetCurrentSelectedMaps(const std::vector<int>& i_maps) { m_currentSelectedMaps = i_maps; }
    const std::vector<int>& GetCurrentSelectedPlants();
    const std::vector<int>& GetCurrentSelectedMaps() { return m_currentSelectedMaps; }
    const NewPVPEndPlay& GetCurrentEndPlayData() { return m_currentEndPlayData; }
    const NewPVPSyncPlayerData& GetCurrentCancelMatchingData() { return m_currentCancelMatchingData; }
    bool IsCurrentCancelMatchingSuccess() { return m_currentCancelMatchingData.m_result == 0; }
    int GetCurrentPropVer() { return m_currentPropVer; }
    void SetCurrentPropVer(int i_version) { m_currentPropVer = i_version; }
    int GetMinEstimitedMatchingTime();
    int GetMaxEstimitedMatchingTime();
    int GetEstimatedQueueingTime();
    int GetSelfMatchingScore() { return m_currentMainEntryData.m_playerInfo.m_matchingScore; }
    void PlayPositionalSound(const std::string& i_eventName, float i_throttleTime = 0.f);

    const Network_NewPVPDuanState& GetCurrentRank() { return m_currentMainEntryData.m_playerInfo.m_currentRank; }
    void onObtainedDuanReward(int i_index) { m_currentMainEntryData.m_duanRewardStatus[i_index] = 1; }
//    void onBoughtShopItem(int i_index);
//    void onResetShopItemBuyTimes();
    const Network_NewPVPDuanState& GetTopRank() { return m_currentMainEntryData.m_topDuanStatus; }
    const Network_NewPVPSmallDuan& GetTargetRankInfo(int i_big, int i_small);
    const std::vector<int>& GetTutorialPlantList();
    const std::vector<int>& GetUnsyncPlantBlacklist();
    bool IsUnsyncDyingPlant(int i_type);

    // Zombie level infos
    int GetCurrentBattleIndex();
    const std::vector<int>& GetInBattleZombies();
    const std::vector<NewPVPZombieRareInfo>& GetZombieRareInfos() { return m_currentMainEntryData.m_zombieConfig.m_rareInfos; }
    int GetZombieRarityById(int i_type);
    int GetCurrentZombiePacketLevel(int i_type);
    int GetCurrentLevelUpPiece(int i_type);
    int GetLevelUpPieceRequired(int i_rare, int i_level);
    const NewPVPZombiePacketInfo& GetZombiePacketInfoById(int i_type);
    bool IsInCurrentBattleInfo(int i_type);
    int GetZombieLevelUpPieceRequired(int i_type, int i_level);
    void SetZombiePlayerInfo(const NewPVPZombiePlayerInfo& i_info) { m_currentMainEntryData.m_zombiePlayerInfo = i_info; }
    void onObtainedZombieCardPiece(int i_pieceId, int i_num);

    // Areas
    bool IsAreaDisabled(const std::string& i_levelName);
	bool IsCurrentLevelAreaDisabled();

	std::vector<AreaData> GetAreaList();

	AreaData CreateAreaData(std::string i_areaName);

	void SyncArea(int i_areaType);
	void SyncArea(const std::vector<int>& i_areaTypes);

	NewPVPAreaMainPropertiesPtr GetAreaMainById(AreaType i_type);

	std::string GetAreaName(int i_type);
	std::string GetAreaDescription(int i_type);

	bool TryShowFPSWarning();
	bool ReachFPSLimit(bool i_outSide);
	int GetFPSLimit(bool i_outSide);
	int GetLowFPSCount();
	int GetFPSBlockStart();
	bool IsLastGameReachFPSLimit();
	int GetSeasonEndTime();
	bool IsSeasonEnd();
	bool IsThirdSeason();
	void TryShowSeasonEndTips();
	void StartFrameCalc();
	void ResetFrameInfo();
	float GetCurrentFPS() { return m_currentFrames; }
	float GetAverageFPS();
	bool IsCurrentGameReachFPSLimit();
	bool IsCurrentGameInvalid();

	void SetTutorialStep(NewPVPTutorialStep i_step);
	NewPVPTutorialStep GetTutorialStep() { return m_tutorialStep; }

	// Logs
	void ResetLogs();
	void SetStartMatchingTime() { m_startMatchingTime = PVZ_T(); }
	float GetMatchingTime() { return PVZ_T() - m_startMatchingTime; }
	void SetStartPlayTime() { m_startPlayTime = PVZ_T(); }
	float GetPlayingTime() { return PVZ_T() - m_startPlayTime; }
	void SetCurrentPlayingTurn(int i_turn) { m_currentTurn = i_turn; }
	int GetCurrentPlayingTurn() { return m_currentTurn; }
	const std::vector<LogSunUpgradeInfo>& GetSunUpgradeInfos() { return m_sunUpgradeInfos; }
	void AddPlantCount() { m_actionCountInfo.AddPlantsCount++; }
	void AddZombieCount() { m_actionCountInfo.AddZombiesCount++; }
	const LogActionCountInfo& GetLogActionCountInfo() { return m_actionCountInfo; }
	void SetCurrentZombiePacketInfos(const std::vector<int>& i_infos) { m_currentZombiePacketInfos = i_infos; }
	const std::vector<int>& GetCurrentZombiePacketInfos() { return m_currentZombiePacketInfos; }
	void AddZombieUpgradeSpeedCount() { m_actionCountInfo.SpeedUpgradeCount++; }
	void AddZombieUpgradeHPCount() { m_actionCountInfo.HPUpgradeCount++; }
	void AddZombieUpgradeBerserkCount() { m_actionCountInfo.BerserkUpgradeCount++; }
	void AddZombieMergeCount(int i_mergedLevel);
	void AddZombieUpgradeTriggerCount();
	void SendTimoutLog();
	std::vector<int> GetZombieUpgradeInfoForLog();

private:
    void sortSunCDs(std::vector<NewPVPSunUpgradeInfo>& i_infos);
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void testResponse();
    void tryUpdateNetworkConfig();

    // Areas
    bool areaDisabled(const std::string& i_levelName);
	void syncArea(int i_areaType);
	void addArea(std::string i_areaName);
	void handleRandomArea(const std::vector<std::string>& i_list);
	void updateFrameCalc();
	bool canStartFrameCalc();

	std::vector<AreaData> m_currentAreaList;

    class NewPVPPropertySheet* m_props = nullptr;
    int m_currentPropVer;

    bool m_requested;
    std::function<void()> m_afterRequest;
    NewPVPQueryPlayerData m_currentQueryPlayerData;
    NewPVPMatchPlayer m_currentMatchData;
    NewPVPMainEntry m_currentMainEntryData;
    NewPVPEndPlay m_currentEndPlayData;
    NewPVPSyncPlayerData m_currentCancelMatchingData;
    NewPVPSaveBattleInfoData m_currentSavedBattleInfo;

    class NetConnectingUI* m_netConnectingUI;
    std::vector<int> m_currentSelectedPlants;
    std::vector<int> m_currentSelectedMaps;
    std::vector<CurrentSelectedPlantPacketInfo> m_currentSelectedPlantInfos;

    NewPVPGameResults m_currentGameResult;
    int m_currentSunLevel;

    float m_frames;
    float m_totalFramesFragment;
    int m_totalFrameFragmentCount;
    float m_nextFramesCalcTime;
    int m_framesCalcCount;
    float m_currentFrames;

    static const int MAX_FRAME_ARRAY_SIZE = 10;

    float m_framesArray[MAX_FRAME_ARRAY_SIZE];

    NewPVPTutorialStep m_tutorialStep;

    // Logs
    pvztime_t m_startMatchingTime;
    pvztime_t m_startPlayTime;
    int m_currentTurn;
    std::vector<LogSunUpgradeInfo> m_sunUpgradeInfos;
    LogActionCountInfo m_actionCountInfo;
    std::vector<int> m_currentZombiePacketInfos;

};

#define gNewPVPMgr NewPVPMgr::GetInstancePtr()

namespace Message
{
	void NotifyZombieCacheDatasChanged(const std::vector<ZombieCacheData>& i_current);
	void NotifyTurnChanged(int i_current);
	void NotifyHealthEmpty(bool i_self);
	void NotifyZombieUpgradeUnlocked(int i_type);
	void NotifyUpgradePlant(class Plant* i_plant);
	void NotifySunAddIncrease();
	void NotifyLoadingLevelFinished();
	void NotifyGameplayStarted();
	void NotifyTriggerUpgradeSkill(float i_sunMultiplier);
	void NotifyFPSReachLimit();
	void NotifyTraingingPacketSelected(bool i_upper, int i_type, bool i_selected);
	void RefreshTaskTips();
	void RefreshRankNotice();
	void NotifyTutorialStep(int i_step);
}

#endif /* NEWPVPGAME_H_ */
