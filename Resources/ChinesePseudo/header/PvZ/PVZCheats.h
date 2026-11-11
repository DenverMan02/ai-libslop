//
//  PVZCheats.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZCheats_h
#define PlantsVersusZombies2_PVZCheats_h

#include "Cheats.h"
#include "PVZTypes.h"
#include "GameFeatureType.h"

extern float gCheat_X;
extern float gCheat_Y;

namespace PVZCheats
{
	/// Create cheat list and cheat UI
	void SetupCheats();
	
	/// Cheat commands
    void CheatProfileReset();
    void CheatProfileSuper();
    void CheatProfileLittleSuper();
    void CheatProfileMapConversion();
    void CheatCreateSimpleDeviceIDConfig();
	void CheatShowKeyboard();
	void CheatSlowMotion(bool i_enabled);
	void CheatFastMotion(bool i_enabled);
	void CheatFreeze(bool i_enabled);
    void CheatMonthlyCard(bool i_enabled);
	void CheatDrawRSB(bool i_enabled);
	void CheatDrawGraphicsInfo(bool i_enabled);
    void CheatDrawGlyphCache(bool i_enabled);
    void CheatDrawTextRects(bool i_enabled);
    void ResetBossFight();
    void ShowAdventureUI();
    void EasyAdventure(bool i_enabled);
    void PlaySurpriseAnim();
    void SkipAdventureTutorial();
    void ResetAdventureTutorial();
    void ResetDailyAccessory();
    void ResetGoldenEgg();
    void ResetWorldCupInfo();
    void ShowCBTutorial();
    void ResetCBTutorial();
    void ShowLostNetActivityUI();
    void ResetLostNetActivity();
    void ShowLottery();
    void ShowGeilivableLottery();
    void EnableLottery(bool i_enabled);
    void TestBonusUI();
    void TestNoNetwork();
    void ShowTransGenosis();
    void CloseGameMask();
    void ClosePVZDialog();
#ifdef HOST_ANDROID
    void ClearLotteryInfo();
    void Add10Hammers();
    void CheatAdd10000Gems();
    void CheatSubtract10000Gems();
    void CheatAdd100Leafs();
    void CheatSubtract100Leafs();
    void CheatDoSyncProfile();
    void CheatAddPlantPiece();
    void CheatAddAvatarPiece();
    void CheatAddNewAvatarPiece();
    
    void CheatAdd100WhiteSpecial();
    void CheatAdd100GreenSpecial();
    void CheatAdd100BlueSpecial();
    void CheatAdd100PurpleSpecial();
    void CheatAdd100OrangeSpecial();

#ifndef RELEASEFINAL
    void CheatAdd100GemsForACLog();
    void CheatAddPlantForACLog();
    void CheatSetPlantLevelForACLog();
    void CheatAdd100PlantPiecesForACLog();
    void CheatAddAvatarForACLog();
    void CheatAddAvatarPiecesForACLog();
    void CheatAddAccessoryPiecesForACLog();
    void CheatAddNatureMaterialForACLog();
    void CheatClearACLog();
#endif

#else
    void CheatAddAvatars();
    void TestObjectsCache();
#endif
    void CheatAddPlants();
    void CheatRollPiece();
    void UnlockAllPlants();
    void LockAllPlants();
    void ShowSales();
    void CloseSales();
    void FakePurchaseSales();
    void TryNextSales();
    void TryNextSalesOUT();
    void CheatChildrenDayNextItem();
    void CheatShowPlantPieceCompletion();
	void CheatFrameStep();
    void GetServerTime();
	void CheatBoardDebugMode();
	void CheatPauseButton();
	void CheatStartMowers();
	void ResetAchievements();
	void CheatWallOfPlants();
	void CheatRandomPlants();
	void CheatCherryBombardment();
	void CheatDoStopAllRoller();
	void CheatSpawnNextWave();
	void CheatGive100Sun();
	void CheatLose100Sun();
	void CheatGiveLotsOfSun();
	void CheatLoseAllSun();
    void CheatUnlockGenes();
    void CheatClearUUID();
    void CheatGenerateLocalUUID();
    void CheatSkipAllTutorials();
	void CheatAdd10Components();
	void CheatSubtract10Components();
	void CheatAdd50NationalMat();
    void CheatResetActivityTimes();
    void CheatLevelEditorStatueMaze();
	void CheatResetRechargeGift();
    void CheatAdd1000Stones();
    void CheatSubtract1000Stones();
	void CheatAdd10000000Coins();
	void Subtract10000000Coins();
	void CheatKillAllPlants();
	void CheatShamefulFailure();
    void CheatZombieFailure();
    void CheatCannonFailure();
	void CheatUnlockLevels();
    void CheatReloadLevel();

    void ClearLevelPackageTime();
    void SetLevelPackageTime1();
    void SetLevelPackageTime2();
    void SetLevelPackageTime3();

    void CheatLoadPackageNetwork();
    void CleanPackageNetwork();
	void CheatSandboxEgypt();
	void CheatSandboxPirate();
	void CheatSandboxCowboy();
	void CheatSandboxFuture();
	void CheatAddStar();
	void CheatRemoveStar();
	void CheatReloadProfile();
	void CheatSaveProfile();
    void CheatSaveProfileInfo();
	void CheatSaveiCloud();
	void CheatLoadiCloud();
	void CheatSpawnMapYeti();
	void CheatAddKeys();
	void CheatRemoveKeys();
    void CheatAddAccessoryPiece();
    //PVZ2_CHINESE_START
	void CheatSpawnBasicZombie();
	void CheatSpawnArmor1Zombie();
	void CheatSpawnArmor2Zombie();
	void CheatSpawnFlagZombie();
	void CheatSaveLoad();

	void CheatSkipLevel();
    void PopUpDisabled(bool i_disabled);

	void CheatBoardPause();

	void CheatCrash();
	void CheatLogGroups();
    
    void CheatForceOpenBossChallenge(bool i_value);
	void CheatToggleWorldMapEditor(bool i_enabled);
	void CheatEasyPlanting(bool i_enabled);
	void CheatIgnoreTutorialInput();
	void CheatFinishLevel();
	void CheatAdBox();
	void SpawnResistenceZombie();
	void CheatArtifact();
	void CheatSetSpawnZombieLevel(float i_float);
	void CheatSetSpawnZombieRow(float i_float);
	void CheatSetSpawnZombieResistence(int i_type, float i_value);
	void CheatKillAllZombies();
    void CheatKillZomboss();
	void CheatKillAllZombiesWithDrops();
	void CheatShowPlantID(bool i_enabled);
	void CheatBreakAllVases();
    
    void PusherRegister();
    void PusherShowInfo();

    void CheatForceLoadData();
    
    void updatePropertySheet();
    void updateDropSheet();
    void updatePlantAndZombie();
    void setStaminaTo1();

    void CheatDangerRoom();
    void CheatLuaExecute();
    
    void CheatTest20013();

    void CheatAccessoryPreview();
    
    void CheatLotteryResultUI();
    
    void CheatArenaEndingUI();
    
    void CheatArenaAwakenWidget();

    void CheatTestNewNetworkFunc();
    void CheatTestWechatShare();

	void CheatTreasureChoose(bool i_enabled);
	void CheatDropList();
	void CheatDropListChallenge();
    void CheatPlantLevel1(bool i_enabled);
    void CheatPlantLevel2(bool i_enabled);
    void CheatPlantLevel3(bool i_enabled);
    void CheatPlantLevel4(bool i_enabled);
    void CheatPlantLevel5(bool i_enabled);
    
    void CheatCannonLevel1(bool i_enabled);
    void CheatCannonLevel2(bool i_enabled);
    void CheatCannonLevel3(bool i_enabled);
    
	void CheatDebugCheck();
	void CheatUIEditor();

    void CheatUIDebug(bool i_enabled);
	void CheatFishingEditor(bool i_enabled);
	void CheatPVPPing(bool i_enabled);
    
    void CheatAddX();
	void CheatSubtractX();
    void CheatAddY();
	void CheatSubtractY();

	void CheatArenaPlant1();
    void CheatArenaPlant2();
    void CheatArenaPlant3();
	void CheatArenaBattle1();
    void CheatArenaBattle2();
    void CheatArenaBattle3();
    
    void CheatArenaEditPlant();
    void CheatArenaBattle();
    
    void CheatArenaEditOccupyPlant1();
    void CheatArenaOccupy1();
    void CheatPVPTutorial(bool i_enabled);
    
    void CheatAutoTest(bool i_enable);
    void CheatPVZTest(bool i_enable);// plants vs zombies test
    void CheatAutoTestUnlockLevel(bool i_enable);
    void CheatAutoTestPlantLevelUp(bool i_enable);
    
    void CheatShowDailysignWith4399();
    void CheatTestDailysignWith4399(bool i_enabled);

    // richman test
    void TestRichmanEvent0();
    void TestRichmanEvent1();
    void TestRichmanEvent2();
    void TestRichmanEvent3();
    void TestRichmanEvent4();
    void TestRichmanEvent5();
    void TestRichmanEvent6();
    void TestRichmanEvent7();
    void TestRichmanEvent8();
    void TestRichmanEvent9();
    void TestRichmanEvent10();
    void TestRichmanEvent11();
    void TestRichmanEvent12();
    void TestRichmanEvent13();
    void TestRichmanEvent14();
    void TestRichmanEvent15();
    void TestRichmanEvent16();
    void TestRichmanEvent17();
    void TestRichmanEvent18();
    void TestRichmanEvent19();
    void TestRichmanEvent20();
    void TestRichmanEvent21();
    void TestRichmanEvent22();
    void TestRichmanEvent23();

    void TestRichmanGuessGame();

    // artifact
    void TestArtifactWind();
    void TestArtifactLightning();
    void TestArtifactVase();
    void TestArtifactCure();
};

class CheatGameSpawnZombieCommand : public CheatCommand
{
public:
	RT_CLASS_DEFINE(CheatGameSpawnZombieCommand, CheatCommand, RtClass) {}
	
	CheatGameSpawnZombieCommand()
	{}
	
	CheatGameSpawnZombieCommand(const std::string& i_name, const std::string& i_zombieTypeName)
		: CheatCommand(i_name, std::bind(&ThisClass::spawnZombie, this))
		, m_zombieTypeName(i_zombieTypeName)
	{}
	
private:
	void spawnZombie();
	
	std::string m_zombieTypeName;
};

class CheatGameSpawnCreatureCommand : public CheatCommand
{
public:
    RT_CLASS_DEFINE(CheatGameSpawnCreatureCommand, CheatCommand, RtClass) {}
    
    CheatGameSpawnCreatureCommand()
    {}
    
    CheatGameSpawnCreatureCommand(const std::string& i_name, const std::string& i_creatureTypeName)
    : CheatCommand(i_name, std::bind(&ThisClass::spawnCreature, this))
    , m_creatureTypeName(i_creatureTypeName)
    {}
    
private:
    void spawnCreature();
    
    std::string m_creatureTypeName;
};

class CheatGameSpawnCollectable : public CheatCommand
{
public:
	RT_CLASS_DEFINE(CheatGameSpawnCollectable, CheatCommand, RtClass) {}
	CheatGameSpawnCollectable() {}
	CheatGameSpawnCollectable(const std::string i_name, const std::string& i_collectableType)
		: CheatCommand(i_name, std::bind(&ThisClass::spawnCollectable, this))
		, m_collectableType(i_collectableType)
	{}

private:
	void spawnCollectable();

	std::string m_collectableType;
};

class CheatGameStartLevelCommand : public CheatCommand
{
public:
	RT_CLASS_DEFINE(CheatGameStartLevelCommand, CheatCommand, RtClass) {}

	CheatGameStartLevelCommand()
	{}

	CheatGameStartLevelCommand(const std::string& i_name, const std::string& i_levelName)
			: CheatCommand(i_name, std::bind(&ThisClass::startLevel, this))
			, m_levelName(i_levelName)
	{}

private:
	void startLevel();

	std::string m_levelName;
};

class CheatDangerRoomStartLevelCommand : public CheatCommand
{
public:
    RT_CLASS_DEFINE(CheatDangerRoomStartLevelCommand, CheatCommand, RtClass) {}
    
    CheatDangerRoomStartLevelCommand()
    {}
    
    CheatDangerRoomStartLevelCommand(const std::string& i_name, const std::string& worldName)
    : CheatCommand(i_name, std::bind(&ThisClass::startLevel, this))
    , m_worldName(worldName)
    {}
    
private:
    void startLevel();
    
    std::string m_worldName;
};

class CheatGameSpawnPlantCommand : public CheatCommand
{
public:
	RT_CLASS_DEFINE(CheatGameSpawnPlantCommand, CheatCommand, RtClass) {}
	
	CheatGameSpawnPlantCommand()
	{}
	
	CheatGameSpawnPlantCommand(const std::string& i_name, const std::string& i_plantTypeName)
	: CheatCommand(i_name, std::bind(&ThisClass::spawnPlant, this))
	, m_plantTypeName(i_plantTypeName)
	{}
	
private:
	void spawnPlant();
	
	std::string m_plantTypeName;
};

class CheatGameStartNarrative : public CheatCommand
{
public:
	RT_CLASS_DEFINE(CheatGameStartNarrative, CheatCommand, RtClass) {}

	CheatGameStartNarrative()
	{}

	CheatGameStartNarrative(const std::string& i_name, const std::string& i_narrative)
	: CheatCommand(i_name, std::bind(&ThisClass::startNarrative, this))
	, m_narrative(i_narrative)
	{}

	const std::string& GetNarrativeID()
	{
		return m_narrative;
	}

private:
	void startNarrative();

	std::string m_narrative;
};

class CheatGameFeatureToggle : public CheatToggle
{
public:
	RT_CLASS_DEFINE(CheatGameFeatureToggle, CheatToggle, RtClass) {}
	
	CheatGameFeatureToggle()
	{}
	
	CheatGameFeatureToggle(const std::string& i_name, GameFeature i_feature)
		: CheatToggle(i_name)
		, m_feature(i_feature)
	{}
	
	virtual bool GetValue() const override;
	virtual void SetValue(bool i_newValue) override;
	
private:
	GameFeature m_feature;
};

class CheatGameProfileLockToggle : public CheatToggle
{
public:
	RT_CLASS_DEFINE(CheatGameProfileLockToggle, CheatToggle, RtClass) {}
	
	CheatGameProfileLockToggle()
	{}
	
	CheatGameProfileLockToggle(const std::string& i_name)
		: CheatToggle(i_name)
	{}
	
	virtual bool GetValue() const override;
	virtual void SetValue(bool i_newValue) override;
};

class CheatGameUnlockToEvent : public CheatCommand
{
public:
    RT_CLASS_DEFINE(CheatGameUnlockToEvent, CheatCommand, RtClass) {}
    
    CheatGameUnlockToEvent() {}
    
    CheatGameUnlockToEvent(const std::string& i_cheatName, const std::string& i_eventName, const std::string& i_dataString, bool i_newMap)
    : CheatCommand(i_cheatName, std::bind(&ThisClass::unlockToEvent, this))
    , m_eventName(i_eventName)
    , m_dataString(i_dataString)
    , m_newMap(i_newMap)
    {}
    
private:
    void			unlockToEvent();
    
    std::string		m_eventName;
    std::string		m_dataString;
    bool			m_newMap = true;
};

class CheatAutoTestStartLevelCommand : public CheatCommand
{
public:
    RT_CLASS_DEFINE(CheatAutoTestStartLevelCommand, CheatCommand, RtClass) {}
    
    CheatAutoTestStartLevelCommand() {}
    
    CheatAutoTestStartLevelCommand(const std::string& i_cheatName, const std::string& i_eventName)
        : CheatCommand(i_cheatName, std::bind(&ThisClass::changeLevel, this))
        , m_eventName(i_eventName)
    {}
    
private:
    void changeLevel();
    
    std::string m_eventName;
};

class CheatPlantsVsZombiesStartWorldCommand : public CheatCommand
{
public:
    RT_CLASS_DEFINE(CheatPlantsVsZombiesStartWorldCommand, CheatCommand, RtClass) {}
    
    CheatPlantsVsZombiesStartWorldCommand() {}
    
    CheatPlantsVsZombiesStartWorldCommand(const std::string& i_cheatName, const std::string& i_worldName)
    : CheatCommand(i_cheatName, std::bind(&ThisClass::changeWorld, this))
    , m_worldName(i_worldName)
    {}
    
private:
    void changeWorld();
    
    std::string m_worldName;
};

class CheatAutoTestStartUnlockLevelCommand : public CheatCommand
{
public:
    RT_CLASS_DEFINE(CheatAutoTestStartUnlockLevelCommand, CheatCommand, RtClass) {}
    
    CheatAutoTestStartUnlockLevelCommand() {}
    
    CheatAutoTestStartUnlockLevelCommand(const std::string& i_cheatName, const std::string& i_eventName)
    : CheatCommand(i_cheatName, std::bind(&ThisClass::changeLevel, this))
    , m_eventName(i_eventName)
    {}
    
private:
    void changeLevel();
    
    std::string m_eventName;
};


//// Cheat Set Value

class CheatVariable : public Cheat
{
public:
    RT_CLASS_DEFINE(CheatVariable, Cheat, RtClass) {}

    CheatVariable()
    {}

    CheatVariable(const std::string& i_name, std::function<void(float)>&& i_action, float i_value)
    : Cheat(i_name)
    , m_action(std::move(i_action))
    , m_value(i_value)
    , m_type(0)
    {}

    CheatVariable(const std::string& i_name, std::function<void(int, float)>&& i_action, float i_value, int i_type = 0)
	: Cheat(i_name)
	, m_action2(std::move(i_action))
	, m_value(i_value)
    , m_type(i_type)
	{}

    int GetType() { return m_type; }
    const std::function<void(float)>& GetAction() const { return m_action; }
    const float GetValue() const { return m_value; }
    const std::function<void(int, float)>& GetAction2() const { return m_action2; }

    void SetValue(float i_value)
    {
    	m_value = i_value;
    	if (m_action)
    	{
    		m_action(m_value);
    	}
    }

    void SetValue2(float i_value)
	{
		m_value = i_value;
		if (m_action2)
		{
			m_action2(m_type, m_value);
		}
	}

private:
    std::function<void(float)> m_action;
    std::function<void(int, float)> m_action2;
    float m_value;
    int m_type;
};







namespace Message
{
	void SunChanged(SunCurrency i_newAmount);
	void SunSpent(int i_delta);
	void FreeplantingCheatEnabled();
	void FreeplantingCheatDisabled();
    void SeedChooserReady();
	void CheatPauseEnd();
    void RefreshAdventureEditor();
}

#endif
