//
//  WorldMap_NavBar.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 1/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_EventBar_h
#define PlantsVersusZombies2_WorldMap_EventBar_h

#include "ButtonListener.h"
#include "HotUIAdaptor.h"
#include "ResourceHelpers.h"
#include "RtObject.h"
#include "SexyString.h"
#include "UIWidget.h"
#include "sys/types.h"
#include "PinataStyleChooser.h"
#include "EASquared.h"

class PVZ2UIButton;
namespace Sexy {
class Graphics;
class Image;
class PrimeTextWidget;
}  // namespace Sexy

class WorldMap_EventBar : public UIWidget, public Sexy::ButtonListener
{
public:
	enum EventBarType
	{
		EVENT_BAR_UNINITIALIZED,
		EVENT_BAR_NONE,
		EVENT_BAR_YETI,
		EVENT_BAR_LOD,
		EVENT_BAR_LOD_RESUME,
		EVENT_BAR_LOD_UPCOMING,
        EVENT_BAR_LOD_CONNECTION_REQUIRED,
        EVENT_BAR_RIFT,
        EVENT_BAR_RIFT_ZOMBOSS_READY,
        EVENT_BAR_UNCHARTED_BIRTHDAY,
		EVENT_BAR_MAX
	};

private:
	enum ControlID
	{
		EVENT_BAR_ID_PLAY_NOW,
		EVENT_BAR_ID_RETRY,
        EVENT_BAR_ID_REPLAY,
        EVENT_BAR_ID_RIFT_HOW_TO_PLAY
	};

public:
	RT_CLASS_DEFINE(WorldMap_EventBar, UIWidget, RtClass) {}

	WorldMap_EventBar();
	virtual ~WorldMap_EventBar();

	void                Draw(Graphics* i_g) override;

	void                ButtonDepress(int i_id) override;

	void                UpdateEventType();

	void                OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	void                OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	void                OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	bool				IsMouseOver(const int i_mouseX, const int i_mouseY) override;

	static EventBarType GetBannerTypeOverride();
	static void SetBannerTypeOverride(EventBarType i_type);
	static void SetBannerRedrawOverride();
	
    bool                TryStartRiftZombossLevel() { return doRiftPlayZomboss(); }
    void				SetZPSPlaying(bool i_playing);
    
protected:

	void                onUpdate() override;

	void				initLoadingResourcesGroupList() override;

	void				onVisibleStateChange(bool i_visible) override;

private:

	// Private Interface (Core)

	void onServerTimeChanged();
    void onAppResumeFocus();
    void forceLODCheck();

	void setEventType(EventBarType i_eventBarType);

    void createYetiEventBar();
    
    void createUnchartedBirthdayText(SexyString& headerText, SexyString& descText);
    void createUnchartedBirthdayEventBar();
    void createRiftEventBar();
    void createRiftText(SexyString& headerText, SexyString& descText);
    void createRiftHowToPlayButton(SexyString& i_buttonText);
    void updateRiftCountdownText();
    void updateRiftText();
    void drawRiftExtras(Sexy::Graphics* i_g);
    void drawRiftSeedPacket(Graphics* i_g);
    bool doRiftPlayZomboss();
    void doRiftHowToPlay();
    void onStartRiftLevelCallback(const std::string& i_levelName);
    void showRiftOverNotice();
    void onRiftOverAcknowledged();

    void createPlayNowButton(SexyString buttonText, EventBarType i_eventType, int i_coinCost);
    
    void prepareLODDisplayUpcoming(bool shouldCreatePlayButton, EventBarType i_eventBarType);
    void prepareLODDisplayCommon();
	void createLODText(std::string& headerText, std::string& descText, Color i_textColorOverride = Color(0,0,0,0));
	void createLODUpcomingText(std::string& headerText, std::string& descText);
    
	void deleteAllText();

	void drawBackground(Sexy::Graphics* i_g, ImagePtr i_backStretchImage, ImagePtr i_backTileImage, PinataStyleChooser::EventBackgroundDraw i_backgroundDrawTechnique, int i_barWidth);
	void drawZombieLeft(Sexy::Graphics* i_g, ImagePtr i_zombieImage);
	void drawZombieRight(Sexy::Graphics* i_g, ImagePtr i_zombieImage);
	void drawPlayNowButton(Sexy::Graphics* i_g);
	void drawCountdown(Sexy::Graphics* i_g);
	bool drawProgressBar(Sexy::Graphics* i_g);
	void drawUnchartedBirthdayExtras(Sexy::Graphics* i_g);

	void doPlayNow();
    void onAdToReplayLODComplete(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);

    void updateCountdownText();
    time_t getCurrentEventTimeRemaining();
    time_t getNextEventTimeRemaining();
	
	void lodReplayForCoinsCallback();
	void lodReplayForAdCallback();

	bool canUpdateEventType();

private:
    void doMouseDownButton(PVZ2UIButton* i_buttonPtr, const int i_localX, const int i_localY);
    void doMouseUpButton(PVZ2UIButton* i_buttonPtr, const int i_localX, const int i_localY);
    void doMouseMoveButton(PVZ2UIButton* i_buttonPtr, const int i_localX, const int i_localY);
    
    void ShowZombossLevelSetupScreenOne();
    void ShowZombossLevelSetupScreenTwo();

	// Private Members (not serialized)

	ImagePtr  m_backgroundStretchImage;
	ImagePtr  m_backgroundTileImage;
	PinataStyleChooser::EventBackgroundDraw         m_backgroundDrawTechnique;
	ImagePtr  m_capImage;
	ImagePtr  m_leftZombieImage;
	ImagePtr  m_rightZombieImage;
	//const class EventScheduleEntry*      m_upcomingSchedule;
	bool                        m_leftZombieImageVisible;
	int                         m_leftZombieLeftY;
	bool                        m_rightZombieImageVisible;
	bool                        m_capImageVisible;
	bool                        m_activeForDrawing;
	bool                        m_forceSaveWhenCountdownZero;
	bool                        m_backgroundTileUseClipRect;
	EventBarType                m_eventBarType;
	PVZ2UIButton*               m_playNowButton;
	int							m_coinCost;
	int                         m_eventBarWidth;

	PrimeTextWidget*            m_headerText;
	PrimeTextWidget*            m_descText;
	PrimeTextWidget*            m_countdownText;
    PVZ2UIButton*               m_riftHowToPlayButton;
    PrimeTextWidget*            m_countdownZombossText;
	HotUIAdaptor*				m_zpsMeter;

    uint64                      m_timeLastForcedLODTimeCheck;
	
	int							m_lodReplayButtonSource;
};


#endif
