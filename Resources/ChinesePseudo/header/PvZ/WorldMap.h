//
//  WorldMap.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 7/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_h
#define PlantsVersusZombies2_WorldMap_h

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "Color.h"
#include "Effect_BouncingArrow.h"
#include "GameStateMgr.h"
#include "Image.h"
#include "KeyCodes.h"
#include "MapEventItem.h"
#include "MessageWidgetEnums.h"
#include "ObjectTypeDescriptor.h"
#include "PVZTypes.h"
#include "ParallaxCache.h"
#include "Point.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtId.h"
#include "RtObject.h"
#include "SexyAppBase.h"
#include "SexyString.h"
#include "SexyVector.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "UIWidget.h"
#include "Widget.h"
#include "WorldMapUtils.h"
//#include "WorldMap_QuestButton.h"
#include "WorldMapEditorFactory.h"
#include "core.h"
#include "dtypes.h"
#include "WorldMapActionManager.h"

class PopAnimRig;
class WorldData;
class WorldMapAction;
class WorldMapCamera;
class ActionWorldKeyRewardAnimation;
namespace Sexy
{
    class Graphics;
    class WidgetManager;
} // namespace Sexy

const int k_mapResourceGridSize = 600;
const int k_checkMapResourceGridRadius = 4;
constexpr const int8 k_noFilter = 0;

STATE_ENUM_BASE_BEGIN(WorldMapState)
WM_Loading,				// Hidden, non clickable
WM_Initializing,	  	// Hidden, sets up UI, non clickable
WM_BackgroundLoading,	// Visible, draws UI and stars, loading world, loader animation, non clickable
WM_BackgroundInit,		// Visible, draws UI and stars, sets up world, loader animation, non clickable
WM_Ready,			  	// Ready and clickable
WM_WaitingToDie,	  	// Waiting to be unloaded and transitioned to something else
STATE_ENUM_END(WorldMapState) class MapPopupDialog;

class PlayerInfo;
class UniverseMap;
class WorldMapPropertySheet;

enum MapResourceLoadingFlag
{
    PVZ_BEGIN_FLAG_ENUM(RES_LOAD_FLAG_),
    
    // UNLOADED
    //	- The resource group is not being loaded
    PVZ_FLAG(RES_LOAD_FLAG_UNLOADED),
    
    // LOADING
    //	- The resource group is loading
    PVZ_FLAG(RES_LOAD_FLAG_LOADING),
    
    // LOADED
    //	- The resource group is loaded.
    PVZ_FLAG(RES_LOAD_FLAG_LOADED),
    PVZ_END_FLAG_ENUM(RES_LOAD_FLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(MapResourceLoadingFlag);

enum EndOfWorldSequenceState
{
    EOW_STATE_NONE,
    EOW_STATE_NORMAL,
    EOW_STATE_EGYPT_TUTORIAL,
    EOW_STATE_PIRATE_TUTORIAL,
    EOW_STATE_COWBOY_TUTORIAL
};

enum MapEditorModeAction
{
    EDITORMODE_ACTION_ISLAND_ROTATE,
    EDITORMODE_ACTION_ISLAND_FLIP,
    EDITORMODE_ACTION_ISLAND_SCALE,
    EDITORMODE_ACTION_ISLAND_ADD,
    EDITORMODE_ACTION_ISLAND_MOVE,
    EDITORMODE_ACTION_ISLAND_REMOVE,
    EDITORMODE_ACTION_DOODAD_ROTATE,
    EDITORMODE_ACTION_DOODAD_FLIP,
    EDITORMODE_ACTION_DOODAD_SCALE,
    EDITORMODE_ACTION_DOODAD_ADD,
    EDITORMODE_ACTION_DOODAD_MOVE,
    EDITORMODE_ACTION_DOODAD_REMOVE,
    EDITORMODE_ACTION_EVENT_ADD,
    EDITORMODE_ACTION_EVENT_EDIT,
    EDITORMODE_ACTION_EVENT_MOVE,
    EDITORMODE_ACTION_EVENT_REMOVE,
    EDITORMODE_ACTION_EVENT_SET_PARENT,
    EDITORMODE_ACTION_EVENT_SET_UNLOCKED,
    EDITORMODE_ACTION_EVENT_SET_VISIBLE,
    EDITORMODE_ACTION_SELECT,
    EDITORMODE_ACTION_SELECT_APPEND,
    EDITORMODE_ACTION_SELECT_PASTE,
    EDITORMODE_ACTION_PAN,
};

const int k_numOfUndoStates = 5;

enum MapEditorToolState
{
    METS_PAINT_TILE,
    METS_SELECT_TILE,
    METS_SELECT_COPY_REGION,
    METS_PASTE_SELECTION,
    METS_EVENT_ADD,
    METS_EVENT_REMOVE,
    METS_EVENT_EDIT,
};

enum EditorDialogType
{
    EDITOR_DIALOG_TYPE_NONE,
    EDITOR_DIALOG_TYPE_MAIN_MENU,
    EDITOR_DIALOG_TYPE_NEW_WORLD,
    EDITOR_DIALOG_TYPE_EDIT_WORLD,
    EDITOR_DIALOG_TYPE_EDIT_WORLD_DETAILS,
    EDITOR_DIALOG_TYPE_MINIMAP,
    EDITOR_DIALOG_TYPE_CLONE_WORLD,
    EDITOR_DIALOG_TYPE_EDITOR_MENU,
    EDITOR_DIALOG_TYPE_EDIT_EVENT,
};

enum EditorInputArea
{
    EDITOR_MAIN_MENU_WINDOW,
    EDITOR_MAIN_MENU_NEW_WORLD_BUTTON,
    EDITOR_MAIN_MENU_EDIT_WORLD_BUTTON,
    EDITOR_MAIN_MENU_MINIMAP_BUTTON,
    EDITOR_MAIN_MENU_EXIT_EDITOR_BUTTON,
    EDITOR_DIALOG_NEW_WORLD_WINDOW,
    EDITOR_DIALOG_NEW_WORLD_NAME,
    EDITOR_DIALOG_NEW_WORLD_NAME_AREA,
    EDITOR_DIALOG_NEW_WORLD_RESOURCES,
    EDITOR_DIALOG_NEW_WORLD_RESOURCES_AREA,
    EDITOR_DIALOG_NEW_WORLD_OKAY_BUTTON,
    EDITOR_DIALOG_NEW_WORLD_CANCEL_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_WINDOW,
    EDITOR_DIALOG_EDIT_WORLD_UP_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_LIST,
    EDITOR_DIALOG_EDIT_WORLD_DOWN_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_EDITMAP_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_CLONEMAP_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_CANCEL_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_WINDOW,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_NAME,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_NAME_AREA,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_PARENT,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_PARENT_AREA,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_OKAY_BUTTON,
    EDITOR_DIALOG_EDIT_WORLD_DETAILS_CANCEL_BUTTON,
    EDITOR_DIALOG_EDIT_MINIMAP_WINDOW,
    EDITOR_DIALOG_EDIT_MINIMAP_FRAME,
    EDITOR_DIALOG_EDIT_MINIMAP_OKAY_BUTTON,
    EDITOR_MENU_BAR,
    EDITOR_MENU_BAR_MODE_AREA,
    EDITOR_MENU_BAR_MODE_AREA_ISLANDS_BUTTON,
    EDITOR_MENU_BAR_MODE_AREA_DOODADS_BUTTON,
    EDITOR_MENU_BAR_MODE_AREA_EVENTS_BUTTON,
    EDITOR_MENU_BAR_MODE_AREA_SELECT_BUTTON,
    EDITOR_MENU_BAR_MODE_AREA_LABEL,
    EDITOR_MENU_BAR_MODE_DETAILS_AREA,
    EDITOR_MENU_BAR_MODE_DETAILS_PREV_IMAGE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_NEXT_IMAGE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_LAYER_CHANGE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_LAYER_VIEW_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_ROTATE_IMAGE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_SCALE_IMAGE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_FLIP_IMAGE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_ADD_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_MOVE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_REMOVE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_EVENT_TYPE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_EVENT_ADD_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_EVENT_EDIT_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_EVENT_MOVE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_EVENT_REMOVE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_SELECT_COPY_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_SELECT_PASTE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_SELECT_DELETE_BUTTON,
    EDITOR_MENU_BAR_MODE_DETAILS_SELECT_APPEND_BUTTON,
    EDITOR_MENU_BAR_EDIT_AREA,
    EDITOR_MENU_BAR_EDIT_PAN_BUTTON,
    EDITOR_MENU_BAR_EDIT_MAP_ONLY_BUTTON,
    EDITOR_MENU_BAR_EDIT_SHOW_GRID_BUTTON,
    EDITOR_MENU_BAR_EDIT_SNAP_BUTTON,
    EDITOR_MENU_BAR_MENU_BUTTON,
    EDITOR_PARALLAX_BAR,
    EDITOR_PARALLAX_BAR_INCREMENT_LAYER_BUTTON,
    EDITOR_PARALLAX_BAR_CURRENT_LAYER_LABEL,
    EDITOR_PARALLAX_BAR_DECREMENT_LAYER_BUTTON,
    EDITOR_PARALLAX_BAR_SHOW_CURRENT_LAYER_ONLY_BUTTON,
    EDITOR_DIALOG_MENU_WINDOW,
    EDITOR_DIALOG_MENU_SAVE_BUTTON,
    EDITOR_DIALOG_MENU_LOAD_BUTTON,
    EDITOR_DIALOG_MENU_RETURN_BUTTON,
    EDITOR_DIALOG_MENU_MAIN_MENU_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_WINDOW,
    EDITOR_DIALOG_EDIT_EVENT_NAME,
    EDITOR_DIALOG_EDIT_EVENT_NAME_AREA,
    EDITOR_DIALOG_EDIT_EVENT_TYPE,
    EDITOR_DIALOG_EDIT_EVENT_TYPE_AREA,
    EDITOR_DIALOG_EDIT_EVENT_SILHOUETTE_BOX,
    EDITOR_DIALOG_EDIT_EVENT_SILHOUETTE,
    EDITOR_DIALOG_EDIT_EVENT_DATA_STRING,
    EDITOR_DIALOG_EDIT_EVENT_DATA_STRING_AREA,
    EDITOR_DIALOG_EDIT_EVENT_TOGGLE,
    EDITOR_DIALOG_EDIT_EVENT_TOGGLE_AREA,
    EDITOR_DIALOG_EDIT_EVENT_COST,
    EDITOR_DIALOG_EDIT_EVENT_COST_AREA,
    EDITOR_DIALOG_EDIT_EVENT_DISPLAY_TEXT,
    EDITOR_DIALOG_EDIT_EVENT_DISPLAY_TEXT_AREA,
    EDITOR_DIALOG_EDIT_EVENT_UNLOCKED_NARRATION_ID,
    EDITOR_DIALOG_EDIT_EVENT_UNLOCKED_NARRATION_ID_AREA,
    EDITOR_DIALOG_EDIT_EVENT_COMPLETED_NARRATION_ID,
    EDITOR_DIALOG_EDIT_EVENT_COMPLETED_NARRATION_ID_AREA,
    EDITOR_DIALOG_EDIT_EVENT_PARENT,
    EDITOR_DIALOG_EDIT_EVENT_PARENT_TEXT_AREA,
    EDITOR_DIALOG_EDIT_EVENT_PARENT_TEXT_SET_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_PARENT_TEXT_CLEAR_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_UNLOCKED,
    EDITOR_DIALOG_EDIT_EVENT_UNLOCKED_TEXT_AREA,
    EDITOR_DIALOG_EDIT_EVENT_UNLOCKED_TEXT_SET_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_UNLOCKED_TEXT_CLEAR_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_VISIBLE,
    EDITOR_DIALOG_EDIT_EVENT_VISIBLE_TEXT_AREA,
    EDITOR_DIALOG_EDIT_EVENT_VISIBLE_TEXT_SET_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_VISIBLE_TEXT_CLEAR_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_AUTO_VISIBLE,
    EDITOR_DIALOG_EDIT_EVENT_AUTO_VISIBLE_TEXT_AREA,
    EDITOR_DIALOG_EDIT_EVENT_IS_FLIPPED,
    EDITOR_DIALOG_EDIT_EVENT_IS_FLIPPED_TEXT_AREA,
    EDITOR_DIALOG_EDIT_EVENT_LEVEL_NODE_TYPE,
    EDITOR_DIALOG_EDIT_EVENT_LEVEL_NODE_TYPE_TEXT_AREA,
    EDITOR_DIALOG_EDIT_EVENT_SAVE_BUTTON,
    EDITOR_DIALOG_EDIT_EVENT_CANCEL_BUTTON,
    EDITOR_SET_EVENT_CANCEL_BUTTON,
    EDITOR_ART_ROTATION_INCREMENT_BUTTON,
    EDITOR_ART_ROTATION_DECREMENT_BUTTON,
    EDITOR_ART_ROTATION_RESET_BUTTON,
    EDITOR_ART_ROTATIONVEL_INCREMENT_BUTTON,
    EDITOR_ART_ROTATIONVEL_DECREMENT_BUTTON,
    EDITOR_ART_ROTATIONVEL_RESET_BUTTON,
    EDITOR_ART_ROTATION_OKAY_BUTTON,
    EDITOR_ART_SCALEX_INCREMENT_BUTTON,
    EDITOR_ART_SCALEX_DECREMENT_BUTTON,
    EDITOR_ART_SCALEX_RESET_BUTTON,
    EDITOR_ART_SCALEY_INCREMENT_BUTTON,
    EDITOR_ART_SCALEY_DECREMENT_BUTTON,
    EDITOR_ART_SCALEY_RESET_BUTTON,
    EDITOR_ART_SCALEXY_INCREMENT_BUTTON,
    EDITOR_ART_SCALEXY_DECREMENT_BUTTON,
    EDITOR_ART_SCALEXY_RESET_BUTTON,
    EDITOR_ART_SCALE_OKAY_BUTTON,
    EDITOR_INCREMENT_FILTER_BUTTON,
    EDITOR_DECREMENT_FILTER_BUTTON,
    EDITOR_CURRENT_FILTER_LABEL,
    NUM_OF_EDITOR_INPUT_AREAS,
};

typedef RtWeakPtr<class WorldMap> WorldMapPtr;

struct WorldResourceLoadState
{
    int WorldID;
    MapResourceLoadingFlag LoadState;
    std::vector<std::string> Resources;
};

struct MapPath
{
    MapPath()
    {
        PathIsActive = false;
        PathRevealStartTime = PVZ_EOT();
        PathRevealEndTime = PVZ_EOT();
        DestinationEvent = nullptr;
        BeamAnimRig = NULL;
    };
    ~MapPath()
    {
    }
    
    bool PathIsActive;				// Specify that the path is active (beam is expanding)
    pvztime_t PathRevealStartTime;  // Time at which the path starts being revealed
    pvztime_t PathRevealEndTime;	// Time at which the path ends being revealed
    MapEventItem* DestinationEvent; // Map event that the path ends on
    PopAnimRig* BeamAnimRig;		// Anim rig for the beam being displayed
};

struct MapPathGroup
{
    MapPathGroup()
    {
        SourceEvent = NULL;
    }
    
    std::vector<MapPath> Paths; // Group of paths that spawn in this group
    MapEventItem* SourceEvent;  // Map event that trigger's this map path group
};

struct MapNarrativeInfo
{
    bool Valid = false;
    std::string ID;
    std::string Event;
};

struct MapTutorialInfo
{
    bool Valid = false;
    std::string Name;
    MapTutorialState State = TUTORIAL_NONE;
};

class WorldMapTransitionDecider
{
public:
    static void PickTutorialOrWorldMap();
};

class WorldMap : public Widget
{
public:
    RT_CLASS_DEFINE(WorldMap, Widget, RtClass)
    {
    }
    
    WorldMap();
    virtual ~WorldMap();
    
    // Public Interface (Inheritable)
    
    void Draw(Graphics* i_g) override;
    virtual void DrawPopanimRig(Graphics* i_g, WorldMapCamera* i_camera, const int16 i_popAnimID, float i_posX, float i_posY, float i_scaleX = 1.0f, float i_scaleY = 1.0f, float i_rotation = 0.0f);
    virtual void DrawZombossHologram(Graphics* i_g, WorldMapCamera* i_camera, float i_posX, float i_posY);
    virtual void DrawWorldPopanimRig(Graphics* i_g, WorldMapCamera* i_camera, const int16 i_worldPopAnimID, WorldData* i_worldData, float i_posX, float i_posY, float i_scaleX = 1.0f, float i_scaleY = 1.0f, float i_rotation = 0.0f);
    virtual void DrawSeedPacket(Graphics* i_g, WorldMapCamera* i_camera, const PlantTypePtr i_plantType, float i_posX, float i_posY);
    void MouseMove(const int i_mouseX, const int i_mouseY) override;
    void TouchBegan(const Sexy::Touch& i_touch) override;
    void TouchMoved(const Sexy::Touch& i_touch) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;
    void TouchesCanceled() override;
    void KeyChar(SexyChar i_char) override;
    void KeyDown(KeyCode i_key) override;
    void Update() override;
    void OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta) override;
    bool OnBackButtonPressed() override;
    void RemovedFromManager(Sexy::WidgetManager* i_widgetManager) override;
    
    // Public Interface (Core)
    void ScrollToPosition(const Sexy::FPoint i_centerPoint);
    bool CanBeClosed();
    void QueueForTransition(const GameState i_gameState);
    void QueueForLoadLevel(const std::string& i_levelName, const LevelSource i_levelSource);
    void CenterOnMapEvent(const std::string& i_mapEventName, const bool i_preventScroll = false);
    void CenterOnMapEvent(const MapEventItem* i_mapEventItem, const bool i_preventScroll = false);
    void CenterOnPoint(const Sexy::FPoint i_centerPoint, const bool i_ignoreCameraBounds = false);
    void ZoomIn(bool i_isCentered = false);
    void ZoomOut();
    void ZoomOutNoAnimation();
    void ResetCameraVelocity();
    void SetCameraBoundsToWorld(WorldData* i_world);
    void SetCameraPosition(float i_positionX, float i_positionY, const bool i_ignoreCameraBounds = false);
    void SetAdviceText(SexyString i_text, MessageStyle i_messageStyle);
    void CalculateMinMaxZoomForWorld(WorldData* i_world);
    
    void ActivateMapPathGroupWithEvent(const MapEventItem* i_triggeringEvent, const bool i_triggerPaths = false);
    void PurgeWorldMapActions();
    
    void EditorMouseMove(const int i_mouseX, const int i_mouseY);
    void EditorMouseDown(const int i_mouseX, const int i_mouseY, const int i_clickCount);
    void EditorMouseUp(const int i_mouseX, const int i_mouseY, const int i_clickCount);
    void DrawEditorButton(Graphics* i_g, const Sexy::Rect& i_rect, const SexyString& i_label, const bool i_isDown);
    void DrawEditorLabel(Graphics* i_g, const SexyString& i_labelText, const EditorInputArea& i_labelArea);
    void DrawEditorTextField(Graphics* i_g, const SexyString& i_labelText, const EditorInputArea& i_labelArea);
    void EditorHandleDialogInput(const int i_mouseX, const int i_mouseY);
    void EditorHandleMenuBarInput(const int i_mouseX, const int i_mouseY);
    MapEventItem* EditorGetMapEventItemAtLocation(const int& i_mouseX, const int& i_mouseY, const MapEventType& i_eventType);
    MapEventItem* EditorGetAnyMapEventAtLocation(const int& i_mouseX, const int& i_mouseY);
    MapEventItem* EditorGetAnyMapArtEventAtLocation(const int& i_mouseX, const int& i_mouseY);
    MapEventItem* EditorGetAnyMapEventAtLocationOnAnyMap(const int& i_mouseX, const int& i_mouseY);
    void EditorRemoveEvent(const MapEventItem* i_removeEvent, bool i_decoupleEvent = true);
    void EditorRemoveEvents(std::vector<MapEventItem*> i_eventsToRemove, bool i_decoupleEvent = true);
    void EditorDecoupleEvent(const MapEventItem* i_removeEvent);
    void EditorEditCurrentMapEvent();
    void EditorFinalizeEditCurrentMapEvent();
    void EditorRenameEvent(MapEventItem* i_event, const std::string& i_newName);
    void EditorRenameWorld(WorldData* i_worldData, const std::string i_newWorldName);
    void EditorSelectAllEventsInRect(const int& i_startX, const int& i_startY, const int& i_endX, const int& i_endY);
    void EditorAppendToSelectionGroup(MapEventItem* i_event);
    void EditorClearSelectionGroup();
    std::string EditorGetEventNamePrefix(const MapEventType i_eventType);
    std::string EditorGetEventNamePrefix(const uint8 i_eventTypeID);
    
    void PrepForLoading();
    void StartLoad();
    bool IsLoaded();
    void CompleteLoad();
    void UnloadResources();
    void OnLoadingWorldAssets();
    static void DoSharedHUDWidgetCreation(std::string i_metricsUILocation);
    
    void SwitchToGameLevel(const std::string& i_levelName, const LevelSource i_levelSource, const bool i_useTimeTravel = false);
    void SwitchToAlmanac();
    void SwitchToAlmanacFromPlantInfoPopup();
    void SwitchToStore(std::string i_focusPanel = "");
    void SwitchToLevelUp();
    void SwitchToPlantAvatar();
    void SwitchToPlantFamily();
    void SwitchToLottery();
    void SwitchToArtifact();
    void SwitchToPlantGeneEnhancement();
    void SwitchToNostalgiaPVZGameView();
    void SwitchToCustomLevelView();
    void LoadSandboxLevel(const std::string i_levelname);
    void DoRewardUpgradeDialog(MapEventItem* i_event);
    void DoWorldMapPlantRewardDialog(PlantTypePtr i_awardedPlant);
    
    PopAnimRig* GetPopAnimRigByID(const int16 i_popAnimID);
    float GetSpeedFactorNodeReveal();
    
    inline void KillTutorialInput();
    
    inline void SetUserInputEnabled(const bool i_isEnabled);
    const bool IsUserInputEnabled();
    
    bool IsInState(uint32 i_state) const;
    const bool IsValidStateForInput();
    
    inline void SetMouseDownPos(const Sexy::Point& i_mousePoint);
    inline const Sexy::Point& GetMouseDownPos();
    
    inline void SetStartingMouseDownPos(const Sexy::Point& i_mousePoint);
    inline const Sexy::Point& GetStartingMouseDownPos();
    
    inline void SetIsPressed(bool i_isPressed);
    inline bool IsPressed();
    
    inline void SetIsDragging(bool i_isDragging);
    inline bool IsDragging();
    
    inline void SetIsScrollLockedHorizontal(bool i_isLocked);
    inline bool IsScrollLockedHorizontal();
    
    inline void SetIsScrollLockedVertical(bool i_isLocked);
    inline bool IsScrollLockedVertical();
    
    inline void SetBaseOffset(const Sexy::Point i_offset);
    inline const Sexy::Point GetBaseOffset();
    
    void SetEditorEnabled(bool i_isEnabled);
    inline bool IsEditorEnabled();
    
    inline void SetEditorDrawmode(const MapEditorFlags i_drawMode);
    inline const MapEditorFlags GetEditorDrawmode();
    
    inline void SetEditorModeAction(const MapEditorModeAction i_action);
    inline const MapEditorModeAction GetEditorModeAction();
    
    virtual void OnUnlockAllLevels();
    
    inline bool IsZoomedIn() const;
    
    inline WorldMapCamera* GetCamera() const;
    inline float GetCameraZoom() const;
    inline SexyVector2 GetCameraPosition() const;
    inline WorldData* GetCurrentWorld() const;
    inline UniverseMap* GetUniverseMap() const;
    
    SexyVector2 GetMapSpaceOffsetFromCameraCenter(float i_x, float i_y);
    
    Rect GetWorldBoundingRect();
    bool IsLevelTransitioning()
    {
        return m_inLevelUnlockSequence;
    }
    
    virtual bool SetupTutorial(MapTutorialState i_tutorialName);
    virtual bool SetupTutorial(const MapEventItem* i_eventItem);
    virtual void CancelTutorial(MapTutorialState i_tutorialName);
    bool CheckTutorialFinished(MapTutorialState i_tutorial);
    
    void SetZoomButtonZoomedOut(const bool i_isZoomedOut);    
    
    void StartWorldKeyRewardAnimation(ActionWorldKeyRewardAnimation* i_animationAction);
    void EndWorldKeyRewardAnimation();
    
    bool IsYetiBadgeVisible();
    
    void SetTutorialState(MapTutorialState i_state) { m_tutorialState = i_state; }

    void PlayLevelOfTheDay();
    void SetShowLODExpiredNotice(bool i_x)
    {
        m_showLODExpiredNotice = i_x;
    }
    
    void PlacePathDestinationAnimationOnEvent(PopAnimRig* i_animation, MapEventItem* i_eventItem);
    void OnPathDestinationAnimationFinished(const std::string& i_animName);
    
    void ForceTutorialToFinish()
    {
        handleTutorialEnd(true);
    }
    
    bool IsActionQueued();
    
    void SetZombossHologramVisibility(bool i_visible)
    {
        m_zombossHologramVisible = i_visible;
    }
    void PlayRandomZombossTaunts();
    void PlayZombossSound(const std::string& i_sampleName);
    
    // TODO: Move this elsewhere
    static MapNarrativeInfo GetNarrativeToQueue(std::string i_worldName);
    static MapTutorialInfo GetTutorialToQueue(std::string i_worldName);
    
    void SetSuppressNodeUnlockCascading(bool i_suppress)
    {
        m_suppressNodeUnlockCascading = i_suppress;
    }
    
    std::vector<MapPathGroup>& GetMapPathGroups()
    {
        return m_mapPathGroups;
    }
    
    std::vector<PopAnimRig*>& GetPopAnimRigs()
    {
        return m_popAnimRigs;
    }
    
    void SetMapPathAnimationState(MapPath* i_mapPath, const bool i_isUnlocked);
    void        SetPreviousState(GameState state);
    GameState   GetPreviousState() const { return m_previousState; }
    void showPopup(const MapEventItem* checkEvent);
    
    WorldMapActionManager&  GetActionsMgr() { return m_actionsMgr; }
    static void             StopActions();
    
    void RefreshUIs();
    void  refreshMapPathGroups();
    void handleTutorialEnd(bool i_forced = false);
    void showLevelArrow(const std::string& i_levelEventName, const SexyString& i_strAdvice);
protected:
    // Protected Interface (Inheritable)
    virtual void loadMap(const std::string& i_worldName);
    virtual void setupMap();
    virtual void saveMap(int i_filter = k_noFilter);
    virtual void saveMapManifest();
    virtual void newMap(const std::string& i_worldName);
    
    virtual void updateMapEventsArt();
    void placeArrowOnLevelToPlayIfMultipleUnlockedLevelsExist();
    virtual void setupMapUI();
    //void handleTutorialEnd(bool i_forced = false);
    bool isTutorialDeprecated(MapTutorialState i_tutorial);
    virtual void calculateCameraY();
    virtual void snapToCurrentLocation();
    virtual void scrollScreens(const int i_screensToScroll);
    virtual void initLoadingResourcesGroupList();
    virtual void addToLoadingResourcesGroupList(const std::string& i_groupName);
    virtual void addToLoadedWorldResourcesGroupList(int i_worldID);
    void unloadFromLoadedWorldResourcesGroupList(int i_worldID);
    virtual void setState(const WorldMapState i_newState);
    
    DECLARE_STATE_FUNCTIONS(WorldMapState, Loading);
    DECLARE_STATE_FUNCTIONS(WorldMapState, Initializing);
    DECLARE_STATE_FUNCTIONS(WorldMapState, BackgroundLoading);
    DECLARE_STATE_FUNCTIONS(WorldMapState, BackgroundInit);
    DECLARE_STATE_FUNCTIONS(WorldMapState, Ready);
    DECLARE_STATE_FUNCTIONS(WorldMapState, WaitingToDie);
    
    // Protected Interface (Core)
    
    bool handledPopupDialogsMouseDown(const int i_mouseX, const int i_mouseY);
    bool handledPopupDialogsMouseUp(const int i_mouseX, const int i_mouseY);
    bool handledPopupDialogsMouseMove(const int i_mouseX, const int i_mouseY);
    
    void showPopup(const int i_mouseX, const int i_mouseY);
    
    void updateZoomBounce();
    void recalculateCameraBounds();
    void gatherRequiredResourcesFromMapEvents();
    
    void syncMapResourceGrid(const uint16 i_forceMapID = -1);
    void rebuildResourceGrid();
    void initLoadedWorldResources();
    
    bool checkLoadComplete();
    bool hasRequiredResources();
    
    void onContinueButtonPressed();
    void onYetiPlayLevelButtonPressed();
    void onPlayDangerLevelButtonPressed();
    void onPlayDangerLevelCheckpointButtonPressed();
    void onGoToEventButtonPressed();
    void onGateCancelButtonPressed();
    void onYetiNarrationFinished();
    void onYetiFUEDialogYesButton();
    void onLevelNodeUnlockAnimFinished(const std::string& i_animName);
    void onLevelNodeClearedAnimFinished(const std::string& i_animName);
    void onActivateStarGateAnimationFinished();
    void onFinalizeStarGateAnimationFinished();
    void onAppEnteredBackground();
    
    void updateStateMachine();
    void setStateHelper(const StateDefinition<WorldMapState>& i_newStateDefinition);
    WorldMapState getState() const;
    inline const pvztime_t getStateEnterTime();
    inline void setStateEnterTime(const pvztime_t i_newTime);
    
    void remapWorldMapEvents();
    void prepEditedWorld();
    
    void doRiftLevelPopup(MapEventItem* i_event);
	void showRiftOverNotice();
	void onRiftOverAcknowledged();
	void onStartRiftLevel(const std::string& i_levelName);

	void doPVZ1LevelPopup(MapEventItem* i_event);
	void onStartPVZ1Level(const std::string& i_levelName);

	void onStartPVZ1ModeLevel(const std::string& i_levelName);

	void doPVZ2UnchartedLevelPopup(MapEventItem* i_event);
	void onStartPVZ2UnchartedModeLevel(const std::string& i_levelName);

	void doCardGameLevelPopup(MapEventItem* i_event);

	void onStartCardGameLevel(const std::string& i_levelName);

    // Notifications
    void onNotificationConfirmButtonPushed();
    
private:
    // Private Interface
    void onFullyInitialized();
    void OnGotActActivityStates(bool i_success);
    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);
    bool shouldPlayUniverseIntroTutorial(PlayerInfo* i_playerInfo);
    bool shouldPlayWorldKeyTutorial(PlayerInfo* i_playerInfo);
    bool shouldPlayUnusableWorldKeyTutorial(PlayerInfo* i_playerInfo);
    bool lastLevelCompletedIsMinibossEvent();
    void testToClearUniverseTutorials(PlayerInfo* i_playerInfo);
    void initializeToWorldMap();
    void initializeToUniverseMap();
    WorldData* findBestWorldIntersection(const Rect& worldRect);
    void cleanUpCurrentEditEvent();
    //	void									unlockKeyGate(const MapEventItem* i_gateEvent, bool i_wasBypassed = false);
    Point snapWorldToGrid(const float i_worldX, const float i_worldY);
    SexyVector2 getWorldCoordinateFromGrid(const float i_gridX, const float i_gridY);
    void setCurrentWorld(WorldData* i_world);
    void setRiftPlayerBank();
    void showFlashingArrow(UIWidget* widget);
    //void showLevelArrow(const std::string& i_levelEventName, const SexyString& i_strAdvice);
//    void showQuestButtonFlashingArrow(WorldMap_QuestButton* widget);
    void showZenGardenReminder(const SexyString& i_adviceText, const std::string& i_narrationEventId);
    void queueQuestToastFeatureItemQuickStore();
    //EndOfWorldSequenceState queueEndOfWorldSequence();
    void closeMapPopups();
    std::string getPrevLevelOnPath(std::string i_eventName, bool i_isLevel = true);
    
    void onServerTimeReceived();
    void onFirstYetiSpawned();
    void onYetiSpawned();
    void onWorldMapShown();
    void onNewVersionFound();
    void onAdBeginShowing();
    void onAdEnded(const std::string& i_placementOrigin, int i_coinsEarned, int i_videosWatched);
    
    ImagePtr getUpgradeImage(const std::string& i_upgradeType);
    
    void drawMapPaths(Graphics* i_g);
    void updateMapPaths();
    void rebuildMapPathGroups(WorldData* i_worldData);
    void purgeMapPathGroups();
    
    void initializeAudioRTPC(const MapEventItem* i_mapEventItem);
    void cleanupAudioRTPC(const MapEventItem* i_mapEventItem);
    void updateAudioRTPC(const MapEventItem* i_mapEventItem);
    
    void updateAllAudioRTPCs();
    void cleanupAllAudioRTPCs();
    
    void createZombossHologram();
    void updateZombossHologram();
    
    void initializeZombossSoundRTPC();
    void updateZombossSoundRTPC();
    void cleanupZombossSoundRTPC();
    
    void playLockedLevelNodeIdle(const std::string& i_animName);
    void activateStarGateAnimation();
    void finalizeStarGateAnimation();
    
    void pushUIStateAndDisableAll();
    void popUIState();
    
    void handleTouchMoved(const int i_mouseX, const int i_mouseY);
    void handleTouchBegan(const int i_mouseX, const int i_mouseY);
    void handleTouchEnded(const int i_mouseX, const int i_mouseY);
    void setCurrentMapEventItem(MapEventItem* i_item);
    
    void updateNormalNodeRenderStatusForEventItem(WorldData* i_worldData, MapEventItem* i_eventItem);
    void updateZombossNodeRenderStatusForEventItem(WorldData* i_worldData, MapEventItem* i_eventItem);
    void CheckPlantTrialButton(bool i_enabled);
    void PlayTransitionEffect();
    void UpdateTransitionEffect();
    void DrawTransitionEffect(Graphics* i_g);
    void onMonthlyCardQueryOrder(const std::string& codeId, int resultCode);

    void SetupRiftEventBar();
    void SetupUnchartedBirthdayEventBar();
    // Private Members (serialized)
    
    // Private Member (not serialized)
    pvztime_t m_stateEnterTime;
    StateMachine<WorldMapState> m_stateMachine;
    std::vector<std::string> m_loadingResourcesList;
    std::vector<WorldResourceLoadState> m_loadedWorldResourcesList;
    std::vector<PopAnimRig*> m_popAnimRigs;
    
    std::map<RtName, bool> m_pushedUIEnableState;
    
    WorldMapPropertySheet* m_propSheet;
    
    Sexy::Point m_startingMouseDownPos;
    Sexy::Point m_mouseDownPos;
    uint8 m_mouseStationaryCount;
    bool m_mouseDown;
    bool m_dragging;
    bool m_scrollLockHorizontal;
    bool m_scrollLockVertical;
    SexyVector2 m_cameraPosition;
    Rect m_cameraBounds;
    SexyVector2 m_cameraVelocity;
    const MapEventItem* m_interactingEvent;
    Sexy::Point m_baseOffset;
    pvztime_t m_snapScreenStartTime;
    SexyVector2 m_snapToPositionStart;
    SexyVector2 m_snapToPositionEnd;
    bool m_waitingForLevel;
    bool m_waitingForAd;
    bool m_disableInput;
    Sexy::TouchID m_currentTouchIdent;
    std::map<MapEventType, Sexy::Rect> m_eventHitRect;
    class ShowAdvice* m_showAdvice;
    Effect_BouncingArrow* m_bouncingArrowEffect;
    bool m_bouncingArrowInScreenSpace;
    MapPopupDialog* m_popupDialog;
//    class EventAlertManager* m_eventAlertManager;
    UniverseMap* m_universeMap;
    std::map<std::string, ImagePtr> m_upgradeIcons;
    int m_currentResDataGridID;
    WorldData* m_currentWorld;
    bool m_verifyResourceSync;
    bool m_quitWhenResourcesLoad;
    GameState m_queuedGameState;
    ObjectTypeDescriptorPtr m_queuedAlmanacObject;
    std::string m_queueLevelToLoad;
    LevelSource m_queueLevelSource;
    std::string m_queuedStorePanel;
    MapEventItem* m_queuedMapPathEvent;
    WorldMapCamera* m_camera;
    float m_cameraZoomMin;
    float m_cameraZoomMax;
    float m_cameraZoom;
    bool m_zooming;
    pvztime_t m_zoomBounceStartTime;
    pvztime_t m_zoomBounceStartScale;
    FPoint m_zoomStartLocation;
    bool m_zoomBounceToMin;
    bool m_zoomBounceToMax;
    bool m_hasSavedStartLocation;
    bool m_showLODExpiredNotice;
    
    bool m_almanacOpenedFromPlantInfo;
    bool m_inLevelUnlockSequence;
//    ActionWorldKeyRewardAnimation* m_worldKeyAction;
    bool m_userInputEnabled;
    
    bool m_queuedBackButton;
    WorldMapActionManager   m_actionsMgr;
    
    bool m_suppressNodeUnlockCascading;
    
    PopAnimRig* m_mapPathBeamOpen;
    PopAnimRig* m_mapPathUnlockPulse;
    std::vector<MapPathGroup> m_mapPathGroups;
    bool m_mapPathActive;
    Rect m_mapPathBeamSize;
    PopAnimRig* m_mapPathDestinationOverlayRig;
    MapEventItem* m_mapPathDestinationOverlayRigOwner;
    
    class EffectAnimRig_ZombossHologram* m_zombossHologram;
    bool m_zombossHologramVisible;
    pvztime_t m_zombossNextTauntTime;
    void* m_zombossSoundID;
    
    ParallaxCache m_parallaxCache;
    
    SexyVector2 m_snapGridVectorX;
    SexyVector2 m_snapGridVectorY;
    
    pvztime_t m_tutorialTimeEnd;
    bool m_tutorialPreventsInput;
    MapEventItem* m_tutorialRequiresEventInput;
    bool m_tutorialRequiresPopupInput;
    bool m_tutorialRequiresNavInput;
    MapTutorialState m_tutorialState;
    SexyVector2 m_tutorialScrollStart;
    SexyVector2 m_tutorialScrollEnd;
    pvztime_t m_tutorialScrollTimeStart;
    pvztime_t m_tutorialScrollTimeEnd;
    
    pvztime_t m_autoTestLevelTimeEnd;
    
    MapEditorFlags m_editorDrawMode;
    bool m_editorIgnoreMouseUp;
    EditorDialogType m_editorShowDialog;
    EditorInputArea m_editorCurrentInput;
    std::string* m_editorEditedText;
    uint32* m_editorEditedTextNumber;
    bool m_editorEditingText;
    bool m_editorEditingTextNumber;
    int m_editorEditedTextMinSize;
    std::string m_editorNewWorldName;
    std::string m_editorNewParentName;
    uint16 m_editorNewWorldResourceID;
    int m_editorEditWorldIndex;
    int m_editorEditWorldScrollOffset;
    int m_editorEditWorldMaxScrollOffset;
    WorldData* m_editorWorldData;
    MapEditorModeAction m_editorModeAction;
    MapEventItem* m_editorCurrentMapEventItem;
    MapEventItem m_editorCurrentEditEvent;
    bool m_editorAddingEvent;
    uint16 m_editorImageBackgroundID;
    uint16 m_editorImageForegroundID;
    uint8 m_editorEventType;
    std::vector<MapEventType> m_editorEventTypeList;
    std::vector<std::string> m_editorEventTypeNameList;
    Sexy::Rect m_editorRects[NUM_OF_EDITOR_INPUT_AREAS];
    Sexy::Point m_editorSelectionStart;
    Sexy::Point m_editorSelectionEnd;
    Sexy::Point m_editorSelectionAnchorPoint;
    std::vector<MapEventItem*> m_editorSelectionGroup;
    bool m_editorSelectionMoving;
    bool m_editorSelectionVisible;
    bool m_editorHideEvents;
    bool m_editorFutureLevel;
    int m_editorMinimapWorldSelected;
    Point m_editorMinimapWorldOrigin;
    Point m_editorMinimapWorldPrevOrigin;
    bool m_editorSnapEvents;
    bool m_editorDrawSnapGrid;
    bool m_editorIsRotatingArt;
    bool m_editorIsScalingArt;
    int8 m_previousFilter;
    pvztime_t m_visibleTime;
    GameState m_previousState;
    PopAnimRig* m_fullScreenTransitionEffect;
    bool m_worldMapRiftEventBarInitialized;
};

namespace Message
{
    void WorldMapLoadComplete();
    void PurchaseWorld(const MapEventItem* i_gateEvent);
    void WorldMapSwitchedWorlds(WorldData* i_world);
    void WorldMapMapPathStarted();
    void WorldMapMapPathEnded();
    void WorldMapTutorialFinished();
    void WorldMapEventBarImpression(const std::string& i_barType, const std::string& i_holiday, int currencyCost);
    void PlantTrialDialogClosed();
    void NotifyLoadedWorldResources();
    void HardLevelRewardClosed();
    void ActionLoginRewardEnd();
    void ActivePopupUIClosed();
    void PushUIStateAndDisableAll();
    void PopUIState();
}

inline const pvztime_t WorldMap::getStateEnterTime()
{
    return m_stateEnterTime;
}

inline void WorldMap::setStateEnterTime(const pvztime_t i_newTime)
{
    m_stateEnterTime = i_newTime;
}

inline void WorldMap::SetMouseDownPos(const Sexy::Point& i_mousePoint)
{
    m_mouseDownPos = i_mousePoint;
}

inline const Sexy::Point& WorldMap::GetMouseDownPos()
{
    return m_mouseDownPos;
}

inline void WorldMap::SetStartingMouseDownPos(const Sexy::Point& i_mousePoint)
{
    m_startingMouseDownPos = i_mousePoint;
    m_mouseStationaryCount = 0;
    SetMouseDownPos(i_mousePoint);
    SetIsPressed(true);
    SetIsDragging(false);
    SetIsScrollLockedHorizontal(false);
    SetIsScrollLockedVertical(false);
}

inline const Sexy::Point& WorldMap::GetStartingMouseDownPos()
{
    return m_startingMouseDownPos;
}

inline void WorldMap::SetIsPressed(bool i_isPressed)
{
    m_mouseDown = i_isPressed;
}

inline bool WorldMap::IsPressed()
{
    return m_mouseDown;
}

inline void WorldMap::SetIsDragging(bool i_isDragging)
{
    m_dragging = i_isDragging;
}

inline bool WorldMap::IsDragging()
{
    return m_dragging;
}

inline void WorldMap::SetIsScrollLockedHorizontal(bool i_isLocked)
{
    m_scrollLockHorizontal = i_isLocked;
}

inline bool WorldMap::IsScrollLockedHorizontal()
{
    return false; //m_scrollLockHorizontal;
}

inline void WorldMap::SetIsScrollLockedVertical(bool i_isLocked)
{
    m_scrollLockVertical = i_isLocked;
}

inline bool WorldMap::IsScrollLockedVertical()
{
    return false; //m_scrollLockVertical;
}

inline void WorldMap::SetBaseOffset(const Sexy::Point i_offset)
{
    m_baseOffset = i_offset;
}

inline const Sexy::Point WorldMap::GetBaseOffset()
{
    return m_baseOffset;
}

inline void WorldMap::SetUserInputEnabled(const bool i_isEnabled)
{
    m_userInputEnabled = i_isEnabled;
}

inline void WorldMap::KillTutorialInput()
{
    m_tutorialRequiresEventInput = NULL;
    m_tutorialRequiresNavInput = false;
    m_tutorialRequiresPopupInput = false;
}

inline bool WorldMap::IsEditorEnabled()
{
    return WorldMapEditorFactory::GetInstance().IsEditorEnabled();
}

inline void WorldMap::SetEditorDrawmode(const MapEditorFlags i_drawMode)
{
    m_editorDrawMode = i_drawMode;
}

inline const MapEditorFlags WorldMap::GetEditorDrawmode()
{
    return m_editorDrawMode;
}

inline void WorldMap::SetEditorModeAction(const MapEditorModeAction i_action)
{
    m_editorModeAction = i_action;
}

inline const MapEditorModeAction WorldMap::GetEditorModeAction()
{
    return m_editorModeAction;
}

inline WorldMapCamera* WorldMap::GetCamera() const
{
    return m_camera;
}

inline float WorldMap::GetCameraZoom() const
{
    return m_cameraZoom;
}

inline SexyVector2 WorldMap::GetCameraPosition() const
{
    return m_cameraPosition;
}

inline WorldData* WorldMap::GetCurrentWorld() const
{
    return m_currentWorld;
}

inline UniverseMap* WorldMap::GetUniverseMap() const
{
    return m_universeMap;
}

inline bool WorldMap::IsZoomedIn() const
{
    return (m_cameraZoom >= (m_cameraZoomMax - 0.02f));
}

#endif
