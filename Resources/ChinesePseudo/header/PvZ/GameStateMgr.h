//
//  GameStateMgr.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/10/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GameStateMgr_h
#define PlantsVersusZombies2_GameStateMgr_h

#include <string>
#include <vector>

#include "PVZTypes.h"
#include "Color.h"
#include "LevelUtils.h"
#include "ObjectTypeDescriptor.h"
#include "RtObject.h"
#include "StateMachine.h"

class GameStateTransitionController;
class MapEventItem;

STATE_ENUM_BASE_BEGIN(GameState)
	GAME_Unloaded,
	GAME_Initializing,
	GAME_LogoScreen,
    GAME_DirtyAccount,
	GAME_MainMenu,
	GAME_Game,
	GAME_WorldMap,
    GAME_DangerRoom,
    GAME_Almanac,
    GAME_Store,
    GAME_Lottery,
    GAME_LevelUp,
    GAME_PlantAvatar,
    GAME_Lantern,
    GAME_RedPack,
    GAME_PlantTrial,
    GAME_Consumption,
    GAME_DailyAchievement,
    GAME_ActiveCenter,
    GAME_PVPMap,
    GAME_PlantAdventure,
    GAME_AutoTranslateBegin,
    GAME_PVPEntry,
    GAME_PVPLab,
    GAME_AutoTranslateEnd,
	GAME_WaitForNetworkLoad,
    GAME_DangerRoomSkipLevel,
    GAME_PlantFamily,
    GAME_FestivalCenter,
    GAME_RechargeWelfare,// new icon
    GAME_JoustLoadDashboard,
    GAME_JoustDashboardScreen,
	GAME_JoustOrAdventureSelector,
	GAME_JoustTournamentEndScreen,
	GAME_RiftTournamentEndScreen,
	GAME_5thCenter,
	GAME_RichManScreen,
	GAME_RiftLoadDashboard,
    GAME_ArtifactCultivation,
    GAME_PVZ1LoadDashboard,
    GAME_NostalgiaPVZ,
    GAME_CustomLevel,
    GAME_PlantGeneEnhancement,
    GAME_NewPVPMainEntryScreen,
    GAME_NewPVPPreMatchingScreen,
    GAME_NewPVPMatchingScreen,
    GAME_NewPlantUIEntryScreen,
STATE_ENUM_END(GameState)

enum LevelSource
{
    PVZ_BEGIN_ENUM(LEVELSOURCE_),
    LEVELSOURCE_Arcade,
    LEVELSOURCE_Cheat,
    LEVELSOURCE_LevelOfTheDay,
    LEVELSOURCE_Sandbox,
    LEVELSOURCE_Store,
    LEVELSOURCE_WorldMap,
    LEVELSOURCE_Yeti,
    LEVELSOURCE_ZenGarden,
    LEVELSOURCE_MainMenu,
    LEVELSOURCE_Joust,
    LEVELSOURCE_CustomLevelDownload,
    LEVELSOURCE_CardGame,
    LEVELSOURCE_NewPVP,
    PVZ_END_ENUM(LEVELSOURCE_),
};

enum WorldMapFocus
{
    WM_FOCUS_None,
    WM_FOCUS_Quests,
};

enum GameTransitionType
{
	GAMETRANSITION_None,
	GAMETRANSITION_QuickWhite,
	GAMETRANSITION_QuickBlack,
	GAMETRANSITION_SlowWhite,
	GAMETRANSITION_SlowBlack,
	GAMETRANSITION_QuickSpiral,
	GAMETRANSITION_QuickGrass,
	GAMETRANSITION_Matchmaking
};

enum FullScreenTransitionType
{
	FS_TRANSITION_None,
	FS_TRANSITION_Timewarp,
	FS_TRANSITION_TimewarpPVZ1
};

enum ReturnFromBoardType
{
    ReturnFromBoard_Default,
    ReturnFromBoard_ShowPlantUp,
    ReturnFromBoard_ShowTreasure,
    ReturnFromBoard_ShowPlantAdventure,
};

enum FestivalEventType
{
	Event_RedPack,
	Event_DragonBoat,
};

const std::string g_strTutorialwldName = "tutorial";
const std::string g_strActivitywldName = "activity";
const std::string g_strCheatwldName = "cheat";

class GameStateMgr : public RtObject
{
public:
	RT_CLASS_DEFINE(GameStateMgr, RtObject, RtClass) {}
	
	void Initialize(GameState i_initialState);
	void Update();
	
	bool IsTransitioning() const;
    GameState GetState();
    void DoStateChange(GameState i_newState);
    
    // zhousen test code
    StateMachine<GameState> GetStateMachine() { return m_stateMachine; }
    GameStateTransitionController* GetTransitionController() { return m_transitionController; }
    
	/// Public interface. Use these to change game state!
	void ShowMainMenu(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
	void StartLevel(const std::string& i_wldName,const std::string& i_newLevel, int i_activeStarIndex=-1, GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None,
			const LevelSource i_levelSource = LEVELSOURCE_Arcade);
	void StartLevelFromSave(const std::string& i_newLevel, GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
	void WaitForNetworkLoad();
    void ShowDangerRoom(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
	void ShowWorldMap(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowPlantAdventure(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    
	void ShowWorldMapWithDestination(const class MapEventItem* i_destination, GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
	void ShowAlmanac(ObjectTypeDescriptorPtr i_objectType, GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
	void ShowStore(const std::string& i_focusPanel, GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowLevelUp(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowPlantAvatar(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowPlantFamily(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowLanternRiddles(const bool& i_canRiddle, GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowRedPack(FestivalEventType i_type, GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowPlantTrial(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowConsumption(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowDailyAchievement(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowActiveCenter(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowLottery(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowPVPMap(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void TranslateTo(GameState i_targetState, GameTransitionType i_out = GAMETRANSITION_QuickSpiral, GameTransitionType i_in = GAMETRANSITION_QuickSpiral);
    void ShowLogoScreen();
    void SetLevelSource(LevelSource i_levelSource) { m_levelSource = i_levelSource; }
    LevelSource GetLevelSource() { return m_levelSource; }
    void ShowDirtyAccountScreen();
    void ShowJoustDashboardScreen();
    void ShowJoustDashboardScreenAfterDashboardFetch(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowJoustOrAdventureLandingScreen(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowJoustTournamentEndScreen(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowRiftTournamentEndScreen(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowDangerRoomSkipLevel();
    void ShowFestivalCenter(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowRechargeWelfare(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);// new icon
    void Show5thCenter(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowRichManScreen(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowNewPVPMainEntryScreen(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowNewPlantUIEntryScreen(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);

    void ShowRiftMap();
    void ShowArtifactCultivation(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
    void ShowPlantGeneEnhancement(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);

    void ShowPVZ1Map();
	void ShowNostalgiaPVZ(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
	void ShowCustomLevel(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);
	const MapEventItem* GetAndClearQueuedWorldMapDestination();
	const MapEventItem* GetQueuedWorldMapDestination();
    
	// If called, the next time we transition we will put a warp tunnel animation between fade out and fade in
	void QueueWarpTunnel();
	
	void ReturnFromBoard();
	
	void Draw(Graphics* i_g);
	
	// Removes us from our current gameplay state immediately
	void ShutDown();
    void                SetReturnFromBoardType(ReturnFromBoardType i_type) { m_returnFromBoardType = i_type; }
    ReturnFromBoardType GetReturnFromBoardType() const { return m_returnFromBoardType; }
public:
    bool                        getCurrentLevelIsBoss(){return m_bCurrentLevelIsBoss;}
    void                        setCurrentLevelIsBoss(bool isBoss){m_bCurrentLevelIsBoss = isBoss;}
    void                        setCurrentLevelIsHardMode(bool isHardMode) {m_bCurrentLevelIsHardMode = isHardMode;}
    bool                        getCurrentLevelIsHardMode()const {return m_bCurrentLevelIsHardMode;}
    void                        setFirstCompleteHardLevel(bool isFirst){m_bCurrentHardLevelIsFirstComplete = isFirst;}
    bool                        getFirstCompleteHardLevel()const {return m_bCurrentHardLevelIsFirstComplete;}
    void                        setFirstCompleteEasyLevel(bool isFirst){m_bCurrentEasyLevelIsFirstComplete = isFirst;}
    bool                        getFirstCompleteEasyLevel()const {return m_bCurrentEasyLevelIsFirstComplete;}
protected:
	DECLARE_STATE_FUNCTIONS(GameState, Initializing);
	DECLARE_STATE_FUNCTIONS(GameState, LogoScreen);
    DECLARE_STATE_FUNCTIONS(GameState, DirtyAccount);
	DECLARE_STATE_FUNCTIONS(GameState, MainMenu);
    DECLARE_STATE_FUNCTIONS(GameState, Game);
    DECLARE_STATE_FUNCTIONS(GameState, WorldMap);
    DECLARE_STATE_FUNCTIONS(GameState, DangerRoom);
	DECLARE_STATE_FUNCTIONS(GameState, Almanac);
	DECLARE_STATE_FUNCTIONS(GameState, Store);
    DECLARE_STATE_FUNCTIONS(GameState, Lottery);
    DECLARE_STATE_FUNCTIONS(GameState, LevelUp);
    DECLARE_STATE_FUNCTIONS(GameState, PlantAvatar);
    DECLARE_STATE_FUNCTIONS(GameState, Lantern);
    DECLARE_STATE_FUNCTIONS(GameState, RedPack);
    DECLARE_STATE_FUNCTIONS(GameState, PlantTrial);
    DECLARE_STATE_FUNCTIONS(GameState, Consumption);
    DECLARE_STATE_FUNCTIONS(GameState, DailyAchievement);
    DECLARE_STATE_FUNCTIONS(GameState, ActiveCenter);
    DECLARE_STATE_FUNCTIONS(GameState, PVPMap);
    DECLARE_STATE_FUNCTIONS(GameState, PlantAdventure);
    DECLARE_STATE_FUNCTIONS(GameState, PVPEntry);
    DECLARE_STATE_FUNCTIONS(GameState, PVPLab);
	DECLARE_STATE_FUNCTIONS(GameState, WaitForNetworkLoad);
	DECLARE_STATE_FUNCTIONS(GameState, DangerRoomSkipLevel);
    DECLARE_STATE_FUNCTIONS(GameState, PlantFamily);
    DECLARE_STATE_FUNCTIONS(GameState, FestivalCenter);
    DECLARE_STATE_FUNCTIONS(GameState, RechargeWelfare);// new icon
    DECLARE_STATE_FUNCTIONS(GameState, GenericGameState);
    DECLARE_STATE_FUNCTIONS(GameState, 5thCenter);
    DECLARE_STATE_FUNCTIONS(GameState, ArtifactCultivation);
    DECLARE_STATE_FUNCTIONS(GameState, NostalgiaPVZ);
    DECLARE_STATE_FUNCTIONS(GameState, CustomLevel);
    DECLARE_STATE_FUNCTIONS(GameState, PlantGeneEnhancement);

private:
    void showMainMenuWithoutLoadingData(GameTransitionType i_out = GAMETRANSITION_None, GameTransitionType i_in = GAMETRANSITION_None);

	void buildStateTable();
	void buildGenericStateTable();
	void setState(GameState i_state);
	
	void onLevelLoaded();
	void onWorldMapLoaded();
    void onNetworkError(int erroId);
    
    void onWWANDialogCancel();
    void onWWANDialogOK();
    void onNotConnectedDialogOK();
	
    
	void transitionToState(GameState i_targetState, GameTransitionType i_out, GameTransitionType i_in);
	
	void onGetLoginReward();
    
    void onRiftNetworkResponse(int i_context, int i_status);
    void onSuccessResponse();
    
    void onPVZ1NetworkResponse(int i_context, int i_status);

    GameStateTransitionController* m_transitionController;

	/// Private member variables
	StateDefinition<GameState> m_stateTable[GameState_CHILD_BEGIN];
	std::map<GameState, RtClass*> m_genericStateTable;
	StateMachine<GameState> m_stateMachine;
	
	// Transition handling
    GameState m_transitioningFromState;

	bool m_playingOpeningMusic;
	bool m_openingMusicStopped;
    bool m_bDangerRoomAllDone;
    std::string strDangerRoomAllDoneWorld;
	
	int m_loadedForFrameCount;
	std::string m_queuedLevel;
	std::string m_wldName;
    int         m_queuedActiveStarIndex;
    int         m_queuedPlantStoreTab;
    std::string m_queuedStorePanel;
    std::string m_queueWorldName;
    bool        m_queuedBool;
    
	bool m_queuedLevelFromSave;
	ObjectTypeDescriptorPtr m_queuedObjectForAlmanac;
	const class MapEventItem* m_queuedWorldMapDestination;
	std::vector<std::string> m_saveStateResourceGroups;

    bool m_bHasCheckedUpdates;
    
    //need for fix
    bool m_bCurrentLevelIsHardMode = false;
    bool m_bCurrentHardLevelIsFirstComplete = false;
    bool m_bCurrentEasyLevelIsFirstComplete = false;
    bool m_bCurrentLevelIsBoss = false;
    
    ReturnFromBoardType m_returnFromBoardType = ReturnFromBoard_Default;

    FestivalEventType m_eventType = Event_RedPack;
    LevelSource m_levelSource;
    class PVZGameState* m_activeGameState;
};

#endif
