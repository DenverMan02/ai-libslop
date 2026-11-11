/*
 * RichManScreen.h
 *
 *  Created on: 2019-12-19
 *      Author: Administrator
 */

#ifndef RICHMANSCREEN_H_
#define RICHMANSCREEN_H_

#include "HotUIAdaptor.h"
#include "RtObject.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "Core.h"
#include "HotUIAnim.h"

namespace Message
{
    void NotifyBoardSetup();
    void NotifyDiceRoll();
}

struct AdaptorRichManEventEntryConfig
{
	AdaptorRichManEventEntryConfig()
	{
		Header = "";
		Description = "";
		IconImage = "";
		BackgroundImage = "";
	}

	std::string Header;
	std::string Description;
	std::string IconImage;
	std::string BackgroundImage;
};

class AdaptorRichManEventListConfig
{
public:

	std::vector<AdaptorRichManEventEntryConfig> Entries;
};

struct AdaptorBoardConfig
{
	AdaptorBoardConfig()
	{
		NumOfRow = 0;
		NumOfColumn = 0;
		Gap = 0;
		InitialX = 0;
		InitialY = 0;
	}

	int NumOfRow;
	int NumOfColumn;
	int Gap;
	int InitialX;
	int InitialY;
};

struct AdaptorEventConfig
{
	AdaptorEventConfig()
	{
		EventId = 0;
		Index = 0;
	}

	int EventId;
	int Index;
};

enum EventBgType
{
	Event_Top_Left,
	Event_Top_Right,
	Event_Bottom_Left,
	Event_Bottom_Right,
	Event_Column,
	Event_Row
};

namespace RichManUtils
{
	Point GetTargetLocation(int i_index, int i_column, int i_row);
	void GetInitialValue(Sexy::Rect& i_rect, const AdaptorBoardConfig& i_config, int i_boardWidth, int i_boardHeight);
	void GetTargetPosition(const Point& i_loc, const Sexy::Rect& i_rect, int i_gap, int& i_realX, int& i_realY, bool i_center = false);
	EventBgType GetTargetEventBgType(const Point& i_loc, int i_column, int i_row);
}

class AdaptorRichManEventEntry : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorRichManEventEntry, HotUIAdaptor, Sexy::RtClass);

	AdaptorRichManEventEntry();
	virtual ~AdaptorRichManEventEntry();

	void Configure(WidgetContainer* i_parent, const AdaptorRichManEventEntryConfig& i_config);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

private:
	WidgetContainer* m_parent;
	AdaptorRichManEventEntryConfig m_config;
};

class AdaptorRichManEventList : public HotUIAdaptor, Sexy::ScrollWidgetListener
{
public:
	RT_CLASS_DEFINE(AdaptorRichManEventList, HotUIAdaptor, Sexy::RtClass);

	AdaptorRichManEventList();
	virtual ~AdaptorRichManEventList();

	void Configure(WidgetContainer* i_parent, const AdaptorRichManEventListConfig& i_config);

	void ScrollerMoved( Sexy::ScrollWidget* i_scrollWidget ) {}
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

private:
	WidgetContainer* m_parent;
	std::vector<AdaptorRichManEventEntry*> m_eventEntries;

	AdaptorRichManEventListConfig m_config;
};

class EventUI : HotUIWidget
{
public:
    RT_CLASS_DEFINE(EventUI, HotUIWidget, RtClass);

    void SetRect(const Sexy::Rect i_rect) { m_initRect = i_rect; }
    void SetIconImage(ImagePtr i_image) { m_iconImage = i_image; }
    void SetBackgroundImage(ImagePtr i_image) { m_backgroundImage = i_image; }

protected:
    void onInitializeWidget() override;
    void onDraw(Sexy::Graphics* i_g) override;
    void onLayoutFinalized() override;

private:
    ImagePtr m_backgroundImage;
    Sexy::Rect m_initRect;
    ImagePtr m_iconImage;
};

class EventUIProperties : HotUIWidgetProperties
{
public:
    RT_CLASS_DEFINE(EventUIProperties, HotUIWidgetProperties, RtClass);

    RtClass* GetWidgetClass() const override
    {
        return EventUI::StaticGetClass();
    }

    std::string BackgroundImage;
};

class AdaptorRichManEvent : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRichManEvent, HotUIAdaptor, Sexy::RtClass);

public:
	AdaptorRichManEvent();
	virtual ~AdaptorRichManEvent();

	void Configure(WidgetContainer* i_parent, const AdaptorEventConfig& i_config, const AdaptorBoardConfig& i_boardConfig);
	void SetLocation(const Point& i_loc, bool i_resetPosition);
	void Locate();
	void SetInitialValue(const Sexy::Rect& i_rect);
	const Point& GetLocation() { return m_location; }
	void GetPosition(SexyVector2& i_pos);
	void setup();
	void refresh();
	void ResetEvent(const AdaptorEventConfig& i_config);

	Sexy::Rect GetInitRect() { return m_initRect; }
	const AdaptorEventConfig& GetConfig() { return m_config; }

protected:
	void Update() override;

	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

private:
	void SetBackground();

	WidgetContainer* m_parent;
	AdaptorEventConfig m_config;
	AdaptorBoardConfig m_boardConfig;
	Point m_location;
	Sexy::Rect m_initRect;
	HotUIWidget* m_event;
};

enum DiceState
{
    PVZ_BEGIN_ENUM(DICESTATE_),
    DICESTATE_IDLE,
    DICESTATE_ROLL,
    DICESTATE_ROLL_FINISH,
    PVZ_END_ENUM(DICESTATE_)
};

class Dice : public HotUIAnim
{
public:
	RT_CLASS_DEFINE(Dice, HotUIAnim, RtClass);

	Dice();
	virtual ~Dice();

	// state
	void setState(DiceState i_state);
	DiceState getState();

	void SetNextRollPoint(int i_point) { m_point = i_point; }

private:
	bool IsInState(uint32 state) const { return m_state == state; }
	void EnterIdle();
	void EnterRoll();

	void DoRoll(int i_point);
	void onAnimFinished(const std::string& i_animName);

	DiceState m_state;
	int m_point;
};

class DiceProperties : public HotUIAnimProperties
{
public:
	RT_CLASS_DEFINE(DiceProperties, HotUIAnimProperties, RtClass);

	RtClass* GetWidgetClass() const override
	{
		return Dice::StaticGetClass();
	}
};

class MainBoard : HotUIWidget
{
public:
    RT_CLASS_DEFINE(MainBoard, HotUIWidget, RtClass);

    MainBoard();
    virtual ~MainBoard();

    void SetBoardConfig(const AdaptorBoardConfig& i_config) { m_config = i_config; }
    void SetInitRect(Rect i_rect) { m_initRect = i_rect; }

    void CreatePiece();
    void SetPieceLocation(const Point& i_loc);
    void JumpToDestination(const std::vector<Point>& i_locations);

    Rect GetRect() { return m_initRect; }

protected:
    void onInitializeWidget() override;
    void onDraw(Sexy::Graphics* i_g) override;
    void onUpdate() override;

private:
    class RichManSquash* m_piece;
    AdaptorBoardConfig m_config;
    Rect m_initRect;
};

class MainBoardProperties : HotUIWidgetProperties
{
public:
    RT_CLASS_DEFINE(MainBoardProperties, HotUIWidgetProperties, RtClass);

    RtClass* GetWidgetClass() const override
    {
        return MainBoard::StaticGetClass();
    }
};

enum RichManState
{
    PVZ_BEGIN_ENUM(RICHMANSTATE_),
    RICHMANSTATE_CREATING,
    RICHMANSTATE_PLAYING,
    RICHMANSTATE_ROLLING,
    RICHMANSTATE_MOVING,
    RICHMANSTATE_MOVING_BACK,
    RICHMANSTATE_EVENT_HANDLING,
    PVZ_END_ENUM(RICHMANSTATE_)
};

class AdaptorRichManBoard : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRichManBoard, HotUIAdaptor, Sexy::RtClass);

public:
	AdaptorRichManBoard();
	virtual ~AdaptorRichManBoard();

	void Configure(WidgetContainer* i_parent, const AdaptorBoardConfig& i_config);

	void CreatePiece();
	void SetPieceLocation(const Point& i_loc);
	void CheatJumpRight(const Point& i_loc);

	void CreateDice();

	// state
	void setState(RichManState i_state);
	RichManState getState();

	bool CanRollDice();
	void Refresh();
	void SetCurrentLocation(int i_index) { m_currentLocation = i_index; }
	void SetPieceStartLocation(const Point& i_loc);

	MainBoard* GetMainBoard() { return m_board; }
	Rect GetInitRect();

protected:
	void Update() override;

	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

private:
	void setup();
	void onSetup();
	void init();
	bool IsInState(uint32 state) const { return m_state == state; }

	void Creating();
	void Rolling();
	void Moving(bool i_reverse);

	void onNotifyDiceRoll();
	void onNotifyMovingFinish(bool i_handleEvent);
	const AdaptorEventConfig& GetEventConfigByIndex(int i_index);

	WidgetContainer* m_parent;
	AdaptorBoardConfig m_config;
	std::vector<AdaptorRichManEvent*> m_events;
	//test
	std::vector<AdaptorEventConfig> m_eventConfigs;
	MainBoard* m_board;
	RichManState m_state;
	Dice* m_dice;
	int m_currentLocation;
};

class AdaptorRichManScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRichManScreen, HotUIAdaptor, Sexy::RtClass);

public:
	AdaptorRichManScreen();
	virtual ~AdaptorRichManScreen();

	void ButtonDepress(int i_buttonID) override;

	AdaptorRichManBoard* GetBoard() { return m_board; }

	void TryRollDice();

protected:
	void Update() override;

	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

private:
	bool canHandleInput();
	void setup();
	AdaptorRichManEventListConfig buildEventsBoard();
	void addEvents(AdaptorRichManEventListConfig& io_config);

	AdaptorBoardConfig buildMainBoard();

	void requestRollDice();
	void handleRollDice();
	void onHandleRollDice(int i_num);
	bool canRollDice(int i_num);
	void requestBackToMap();
	void OnConfirmBackToMap();
	void backToMap();
	void showShopConfirm();
	void OnConfirmQuickDiceStore();
	void enterDiceShop();
	void enterShop();
	void showOverview();
	void showBonusRollConfirm(bool i_best);
	void OnConfirmRollSmall();
	void OnConfirmRollMid();
	void OnConfirmRollLarge();
	void onNotifySetDice();

	AdaptorRichManEventList* m_eventsBoard;
	AdaptorRichManBoard* m_board;
};


#endif /* RICHMANSCREEN_H_ */
