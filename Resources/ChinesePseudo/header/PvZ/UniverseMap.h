//
//  UniverseMap.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 1/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_UniverseMap_h
#define PlantsVersusZombies2_UniverseMap_h

#include "core.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "GameNotify.h"
#include "WorldData.h"
#include "UIWidget.h"
#include "UIWidgetPrimeText.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "Widget.h"
#include "EASquared.h"

class PopAnimRig;

#ifndef RELEASEFINAL

// Comment this line to compile and run a little bit faster ...
// and disable the editor, of course.
#define UNIVERSE_EDITOR_ENABLED

#endif

STATE_ENUM_BASE_BEGIN(UniverseMapState)
	UM_Loading,							// Loading assets
	UM_Initializing,					// Assets are loaded, setting up the map
	UM_Ready,							// Map is in a ready state (can interact with it)
	UM_TransitionToWorldIntro,			// Transition intro runs and we start loading the world map
	UM_TransitionToWorldWaiting,		// Transition intro is finished and we wait till the world map is ready
	UM_TransitionToWorldOutro,			// Transition outro runs and we dump onto the world map
	UM_TransitionToUniverseIntro,		// Transition intro runs and we start loading anything the universe map needs
	UM_TransitionToUniverseWaiting,		// Transition intro is finished and we wait till the universe is loaded
	UM_TransitionToUniverseOutro,		// Transition outro runs and we dump onto the universe map
	UM_TransitionBetweenWorldsIntro,	// Transition intro runs and we don't do loading yet...
	UM_TransitionBetweenWorldsWaiting,	// Transition intro is finished, we kill off the old world and start loading the new and wait till it's done
	UM_TransitionBetweenWorldsOutro,	// Transition outro runs and we dump onto the world map
    UM_UnlockTutorial,
STATE_ENUM_END(UniverseMapState)

enum UniverseMapEditorFlags
{
	PVZ_BEGIN_FLAG_ENUM(UNIVERSE_EDITORFLAG_),

	// ENABLED
	//	- Sets the editor to enabled
	PVZ_FLAG(UNIVERSE_EDITORFLAG_ENABLED),

	PVZ_END_FLAG_ENUM(UNIVERSE_EDITORFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(UniverseMapEditorFlags);

STATE_ENUM_BASE_BEGIN(MapAnimState)
	Anim_Scorlling,
	Anim_Unlocking,
	Anim_Winnie_Moving,
	Anim_Gate_Scorlling,
	Anim_Gate_Activing,
	Anim_After_Unlocking,
	Anim_Finished,
STATE_ENUM_END(MapAnimState);

//class RenderItem;
//struct MapRenderItem
//{
//	MapEventItem* m_mapEventItem;
//};

class MapPopupDialog;
class UniverseWorldButton;
class UniverseUnlockGate;

//class MapEventItem;

class SnapHandler
{
public:
    virtual ~SnapHandler() {}
    virtual void OnDoSnap(UniverseWorldButton* i_worldButton) = 0;
};

class UniverseMapScrollSnapper: public ScrollSnapper
{
public:
    UniverseMapScrollSnapper();
    virtual void DoSnap(ScrollWidget* i_scrollWidget);
    void SnapToIndex(int i_index, Sexy::ScrollWidget* i_scrollWidget, bool animated);
    virtual void SelectSnapTarget(Sexy::ScrollWidget *i_scrollWidget);
    void SetWorldButtons(std::vector<UniverseWorldButton*> i_worldButtons);
    UniverseWorldButton* GetSelectedButton();
    void SetSnapHandler(SnapHandler* i_snapHandler);
    int GetSelectedIndex();
    void UpdateVisualStates(ScrollWidget* i_scrollWidget);
    
private:
    int getWorldButtonCenterPoint(UniverseWorldButton* i_worldButton, Sexy::ScrollWidget* i_scrollWidget);
    std::vector<UniverseWorldButton *> mWorldButtons;
    UniverseWorldButton* mSelectedButton;
    int mSelectedIndex;
    SnapHandler* mSnapHandler;
};

class UniverseMap : SnapHandler, public Renderable, public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
	
public:
	RT_CLASS_DEFINE(UniverseMap, RtObject, RtClass) {}
	
	UniverseMap();
	virtual ~UniverseMap();

    bool IsActived() const { return mVisible; }
    void EnterWorldByName(std::string i_mapName);
	
	// Public Interface (Inheritable)
	void								OnDoSnap(UniverseWorldButton* i_selectedButton) override;
    
    void                                        HideWorlds();
    void                                        ShowWorlds();    
    void                                        DrawUI(Sexy::Graphics *i_g);
    
	virtual void								Draw(Graphics* i_g) override;
	virtual void								DrawOverlay(Graphics* i_g) override;
	virtual void								MouseMove(const int i_mouseX, const int i_mouseY) override;
	void										TouchBegan(const Sexy::Touch& touch) override;
	void										TouchMoved(const Sexy::Touch& touch) override;
	void										TouchEnded(const Sexy::Touch& touch) override;
	void										TouchesCanceled() override;
	virtual void								KeyChar(SexyChar i_char) override;
	virtual void								KeyDown(KeyCode i_key) override;
	virtual void								Update() override;
	virtual void								SetVisible(bool i_isVisible) override;
    
    virtual void								ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) override;
    virtual void								ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) override;

	// Public Interface (Core)
	void										DrawStarBackground(const int i_alpha);
	bool										CanBeClosed();
	void										TransitionToUniverse(bool i_dangerRoom = false);
	void										TransitionBetweenWorlds(const std::string& i_levelToCenterOn);
	void										TransitionToWorld();
    bool										IsTransitioning();
	
	void										LoadSandboxLevel(const std::string i_levelname);
	void										UnlockAllLevels();
	
	static void									SlideInWorldBank();
	static void									SlideOutWorldBank();
	
	void										PrepForLoading();
	void										StartLoad();
	bool										IsLoaded();
	void										CompleteLoad();
	void										UnloadResources();
    UniverseWorldButton*						GetButtonForWorld(const std::string& i_worldName);
	
	inline void									SetMouseDownPos(const Sexy::Point& i_mousePoint);
	inline const Sexy::Point&					GetMouseDownPos();

	inline void									SetStartingMouseDownPos(const Sexy::Point& i_mousePoint);
	inline const Sexy::Point&					GetStartingMouseDownPos();

	inline void									SetIsPressed(bool i_isPressed);
	inline bool									IsPressed();
	
	inline void									SetBaseOffset(const Sexy::Point i_offset);
	inline const Sexy::Point					GetBaseOffset();
	
	inline void									SetEditorEnabled(bool i_isEnabled);
	inline bool									IsEditorEnabled();

	inline const PVZ2UIScrollingWidget*			GetScrollingWidget() const;
	inline const class UniverseScrollingArea*	GetScrollingAreaWidget() const;
	
	inline const int							GetInteractingWorldID() const;

	// Tutorial hooks
	void										ClearEnteredUniverseFlag();
	bool										GetHasEnteredUniverseFlag() const;
    
    //PVZ2_CHINESE_BEGIN
    void                                        SetLevelToCenterOn(const std::string& i_levelToCenterOn)
	{
        m_levelToCenterOn = i_levelToCenterOn;
    }
    
    void                                        TransToWorldByName(std::string i_worldName);
    void                                        enterWorld(const int i_worldID);
    void                                        enterWorldAction(const int i_worldID);
    void                                        loadImageResource(bool i_dangerRoom);
	void                                        unloadImageResource();
	void                                        imageResourceInitialize(bool i_dangerRoom);
	void                                        imageResourceUninitialize();
	bool										isInDangerRoom(const std::string& i_world);
    //PVZ2_CHINESE_EDN
	void										DrawMapLines(Graphics* i_g);

	bool										isInState(uint32 i_state) const;

	bool										NeedPlayTargetWorldUnlockAnim(const std::string& i_world);
	bool										NeedPlayTargetWorldRevealedAnim(const std::string& i_world);

	void        								setState(MapAnimState i_newState);
	bool        								isInState(MapAnimState i_state) const;

	void										HideAnims();
    
    static bool                             HasFinishedTargetWorld(const std::string& i_world);

protected:
	
	// Protected Interface (Inheritable)
	virtual void							initLoadingResourcesGroupList();
	virtual void							addToLoadingResourcesGroupList(const std::string& i_groupName);
	void									unloadFromLoadedWorldResourcesGroupList(int i_worldID);
	virtual void							setState(const UniverseMapState i_newState);
	
	DECLARE_STATE_FUNCTIONS(UniverseMapState, Loading);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, Initializing);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, Ready);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionToWorldIntro);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionToWorldWaiting);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionToWorldOutro);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionToUniverseIntro);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionToUniverseWaiting);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionToUniverseOutro);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionBetweenWorldsIntro);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionBetweenWorldsWaiting);
	DECLARE_STATE_FUNCTIONS(UniverseMapState, TransitionBetweenWorldsOutro);
    DECLARE_STATE_FUNCTIONS(UniverseMapState, UnlockTutorial);
	// Protected Interface (Core)
	
	DECLARE_STATE_FUNCTIONS(MapAnimState, Scorlling);
	DECLARE_STATE_FUNCTIONS(MapAnimState, Unlocking);
	DECLARE_STATE_FUNCTIONS(MapAnimState, Winnie_Moving);
	DECLARE_STATE_FUNCTIONS(MapAnimState, Gate_Scorlling);
	DECLARE_STATE_FUNCTIONS(MapAnimState, Gate_Activing);
	DECLARE_STATE_FUNCTIONS(MapAnimState, After_Unlocking);
	DECLARE_STATE_FUNCTIONS(MapAnimState, Finished);

	bool									checkLoadComplete();
	void									setupMapUI();
	void									syncButtonStates();
	void									updateButtonStates(const int i_screenX, const int i_screenY, const bool i_isPressed);
	void									showPopup(const int i_mouseX, const int i_mouseY);
	
	void									onWorldPreviewButtonPressed();
	void									onStargatePurchased(const MapEventItem* i_props);
	
	void									updateStateMachine();
	void									setStateHelper(const StateDefinition<UniverseMapState>& i_newStateDefinition);
	UniverseMapState						getState() const;
    //bool									isInState(uint32 i_state) const;
	inline const pvztime_t					getStateEnterTime();
	inline void								setStateEnterTime(const pvztime_t i_newTime);

private:
	void ShowPromptToPatch();
	void OnConfirmPatchDownload();
	void OnRejectPatchDownload();

	void handleTouchBegan(const int i_mouseX, const int i_mouseY);
	void handleTouchMoved(const int i_mouseX, const int i_mouseY);
	void handleTouchEnded(const int i_mouseX, const int i_mouseY);
    
    virtual void ScrollTouchEnd(const Sexy::Touch& touch) override;
	
    void                                    DrawTitle(Graphics* i_g, int alpha);

    void InitializeMapObjects();

    bool CheckNewWorldsFinished();

    

    bool HasPlayedTargetWorldAnim(const std::string& i_world);

    void InitializeWorldUnlockedAnim();

    void ResetAnimData();

    std::string DecideGateActivtingAnim();
    std::string DecideGateFullUnlockAnim();

    void onGateActivited(const std::string& i_animLabelName);
    void onGateUnlocked(const std::string& i_animLabelName);

    void SetRevealedWorlds();

    void SetPlayUnlockedWorlds();
    void SetPlayRevealedWorlds();
    
    void									initializeWorldButtonState();
    void onNarrationFinished();

    // for advertisement
    void SetupAdvertisement();
    bool IsAdvertisementEnable();
    void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    void RemoveAdvertisement();
    void EnterDangerRoomTrainingLevel();
    void OnSelectClearTraining();

	// Private Members (serialized)
	
	// Private Member (not serialized)
	pvztime_t								m_stateEnterTime;
	StateMachine<UniverseMapState>			m_stateMachine;
	StateMachine<MapAnimState> 				m_animState;
	std::vector<std::string>				m_loadingResourcesList;
	Sexy::Point								m_startingMouseDownPos;
	Sexy::Point								m_mouseDownPos;
	uint8									m_mouseStationaryCount;
	bool									m_mouseDown;
	bool									m_dragging;
	Sexy::Point								m_baseOffset;
	Sexy::TouchID							m_currentTouchIdent;
	std::string								m_levelToCenterOn;
	MapPopupDialog*							m_popupDialog;
	int										m_interactingWorldID;
	bool                                    m_resourceLoaded;
	
	enum FirstGateTutorialState
	{
		GTS_INACTIVE,
		GTS_TAP_PIRATE,
		GTS_TAP_EGYPT,
	};
	bool									m_hasEnteredUniverse;
	FirstGateTutorialState					m_firstGateState;

	class UniverseScrollingArea*			m_worldScrollingArea;
	class PVZ2UIScrollingWidget*			m_scrollingWidget;
	
	//std::vector<UniverseWorldButton*>		m_worldButtons;

	UniverseMapEditorFlags					m_editorFlags;
	
    class PrimeTextWidget*                  m_universeMapTitle;

    // Anim related
    float 									m_autoScrollAccumulation;
    //int										m_gateToUnlock;
    std::vector<std::string>				m_currentWorldAnims;
    bool									m_currentCompletesAllWorlds;
    int										m_unlockedWorldTarX;
    //pvztime_t 								m_animStartTime;
    
    UniverseMapScrollSnapper				m_scrollSnapper;
    bool m_scrollAutoTarget;

public:
    // interact with world buttons
    std::vector<UniverseWorldButton*>		m_worldButtons;
    std::vector<UniverseUnlockGate*>		m_unlockGates;
    pvztime_t 								m_animStartTime;
    int										m_gateToUnlock;

    // Training Room
    bool									m_isDangerRoom;
    std::string								m_currentSelectWorld;
};

class MapEventItem;
namespace Message
{
	void WorldMapWorldLoaded();
    void UniverseMapOpened();
    void UniverseMapReady();
}

inline const pvztime_t UniverseMap::getStateEnterTime()
{
	return m_stateEnterTime;
}

inline void UniverseMap::setStateEnterTime(const pvztime_t i_newTime)
{
	m_stateEnterTime = i_newTime;
}

inline void UniverseMap::SetMouseDownPos(const Sexy::Point& i_mousePoint)
{
	m_mouseDownPos = i_mousePoint;
}

inline const Sexy::Point& UniverseMap::GetMouseDownPos()
{
	return m_mouseDownPos;
}

inline void UniverseMap::SetStartingMouseDownPos(const Sexy::Point& i_mousePoint)
{
	m_startingMouseDownPos = i_mousePoint;
	m_mouseStationaryCount = 0;
	SetMouseDownPos(i_mousePoint);
	SetIsPressed(true);
}

inline const Sexy::Point& UniverseMap::GetStartingMouseDownPos()
{
	return m_startingMouseDownPos;
}

inline void UniverseMap::SetIsPressed(bool i_isPressed)
{
	m_mouseDown = i_isPressed;
}

inline bool	UniverseMap::IsPressed()
{
	return m_mouseDown;
}

inline void UniverseMap::SetBaseOffset(const Sexy::Point i_offset)
{
	m_baseOffset = i_offset;
}

inline const Sexy::Point UniverseMap::GetBaseOffset()
{
	return m_baseOffset;
}

inline const PVZ2UIScrollingWidget* UniverseMap::GetScrollingWidget() const
{
	return m_scrollingWidget;
}

inline const UniverseScrollingArea* UniverseMap::GetScrollingAreaWidget() const
{
	return m_worldScrollingArea;
}

inline void UniverseMap::SetEditorEnabled(bool i_isEnabled)
{
	SetFlag(m_editorFlags, UNIVERSE_EDITORFLAG_ENABLED, i_isEnabled);
/*
	if (i_isEnabled)
	{
		m_editorShowDialog = EDITOR_DIALOG_TYPE_MAIN_MENU;
	}
	else
	{
		m_editorShowDialog = EDITOR_DIALOG_TYPE_NONE;
	}
*/	
	// Hide/Show game UI
	UIWidget::GetWidgetBySheetName("UIScreen")->SetVisible(!i_isEnabled);
}

inline bool	UniverseMap::IsEditorEnabled()
{
	return TestFlag(m_editorFlags, UNIVERSE_EDITORFLAG_ENABLED);	
}

inline const int UniverseMap::GetInteractingWorldID() const
{
	return m_interactingWorldID;
}

class UniverseScrollingArea : public Sexy::Widget
{
	RT_CLASS_DEFINE(UniverseScrollingArea, Widget, RtClass);
public:
	UniverseScrollingArea();
	UniverseScrollingArea(class UniverseMap* i_universe);
	virtual ~UniverseScrollingArea();
	
	virtual void TouchBegan(const Sexy::Touch& i_touch)
	{
		if((!m_universe->isInState(MapAnimState_INVALID) && !m_universe->isInState(Anim_Finished)) || m_isPlayingWinnie)
		{
			return;
		}

		Sexy::Widget::TouchBegan(i_touch);
        Sexy::Touch i_translatedTouch = i_touch;
		translateTouch(i_translatedTouch);
		m_universe->TouchBegan(i_translatedTouch);
	};
	virtual void TouchMoved(const Sexy::Touch& i_touch)
	{
		if((!m_universe->isInState(MapAnimState_INVALID) && !m_universe->isInState(Anim_Finished)) || m_isPlayingWinnie)
		{
			return;
		}

		Sexy::Widget::TouchMoved(i_touch);
        Sexy::Touch i_translatedTouch = i_touch;
        translateTouch(i_translatedTouch);
		m_universe->TouchMoved(i_translatedTouch);
	};
	virtual	void TouchEnded(const Sexy::Touch& i_touch)
	{
		if((!m_universe->isInState(MapAnimState_INVALID) && !m_universe->isInState(Anim_Finished)) || m_isPlayingWinnie)
		{
			return;
		}

		Sexy::Widget::TouchEnded(i_touch);
        Sexy::Touch i_translatedTouch = i_touch;
        translateTouch(i_translatedTouch);
		m_universe->TouchEnded(i_translatedTouch);
	};
	virtual void	TouchesCanceled()
	{
		Sexy::Widget::TouchesCanceled();
		m_universe->TouchesCanceled();
	};
	
	virtual void Draw(Graphics* i_g);
	void DrawMapLines(Graphics* i_g);
	virtual void DrawOverlay(Graphics* i_g);
	void DrawMapPorts(Graphics* i_g);
	void DrawFadeAnims(Graphics* i_g, Image* i_image, float i_length, float i_height);
	void DrawFadeAnimsForSpecial(Graphics* i_g, Image* i_image, int i_x, int i_y);
	void DrawFadeLinkEffect(Graphics* i_g, class Effect_PopAnim* i_effect);
	class Effect_PopAnim* FindAnimByPosition(const Sexy::Point& i_point);
	virtual void Update();

	void SetWinniePosition(std::string i_world);
	void InitializeWinnie();

	void UnlockTargetGate(int i_gate);

	void SetWinnieGatePosition();

	void InitializeLinkEffect();
	void HideAnims();

private:

	void translateTouch(Sexy::Touch& i_touch)
	{
		// We need to add our mX and mY to the touch, because we want the universe to
		// know exactly where we clicked, on ITS view.
		i_touch.location.mX += m_universe->GetScrollingWidget()->mX;
		i_touch.location.mY += m_universe->GetScrollingWidget()->mY;
	}
	
	void onWinnieDisappear(const std::string& i_animLabelName);
	void onWinnieAppear(const std::string& i_animLabelName);

	void onWinnieDisappearForGate(const std::string& i_animLabelName);
	void onWinnieAppearForGate(const std::string& i_animLabelName);

	class UniverseMap*	m_universe;
	Effect_PopAnim* m_WinnieAnim;
	Effect_PopAnim* m_LightAnim;
	std::string m_targetWinnieWorld;
	std::vector<Effect_PopAnim*> m_linkEffects;
	pvztime_t m_fadeStartTime;
	bool m_fadeIn;
	bool m_isPlayingWinnie;
	int m_animPosX;
	int m_animPosY;
	bool m_hideMapLine;
};

class MapOverlayWidget : public Sexy::Widget
{
public:
	MapOverlayWidget(UniverseMap* i_map);
	virtual ~MapOverlayWidget();

	virtual void Draw(Graphics* i_g);
	//virtual void DrawOverlay(Graphics* i_g);
	void DrawMapLines(Graphics* i_g);

	UniverseMap* m_map;
};

#endif
