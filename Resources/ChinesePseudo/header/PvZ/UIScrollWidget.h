/*
 * UIScrollWidget.h
 *
 *  Created on: 2021-4-9
 *      Author: zhousen
 */

#ifndef UISCROLLWIDGET_H_
#define UISCROLLWIDGET_H_


#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "RechargeRewardUI.h"
#include "NetworkData.h"
#include "GameCommon.h"
#include "RechargeBundleUI.h"

class PVZ2UIScrollingWidget;

//////////////////////////////////////////
///     Scroll Display Widget Base
//////////////////////////////////////////
class UIScrollDisplayWidgetBase : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    UIScrollDisplayWidgetBase(int type, int activityID);
    virtual ~UIScrollDisplayWidgetBase();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int id) override;
    virtual void Update() override;

    virtual void InitView();
    virtual void SetMainBg(Image* img);
    virtual void ButtonClick();
    virtual void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) {}

protected:
    virtual void InitShinningAnim();
    
protected:
    Image* _MainBg;// main image
    int _activityID;
    bool _bPress;
    Effect_PopAnim* _bannerEffect;// banner effect
    int _type;// banner type
};

class FestivalEventDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
    FestivalEventDisplayWidget(int type, int id);

    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;
};

class SevenDayGuideDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
    SevenDayGuideDisplayWidget(int type, int id);
    ~SevenDayGuideDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;

protected:
    void UpdateProgress(int progress);

    int _curGuideProgress;// the current progress of seven guide
    int _progressMax;
};

class PennyClassroomDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	PennyClassroomDisplayWidget(int type, int id);
    ~PennyClassroomDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;

protected:
    void UpdateProgress(int progress);

    int _curGuideProgress;// the current progress of penny classroom
};

class UnchartedModeDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	UnchartedModeDisplayWidget(int type, int id);
    ~UnchartedModeDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;

protected:
    int _days;// activity left days
    int _hours;// activity left hours
    SexyString _leftStr;// activity left time str.
    Rect _rect;// activity countdown time.
};

class BattleOrderDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	BattleOrderDisplayWidget(int type, int id);
    ~BattleOrderDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;
    void CheckThemeVersion();

protected:
    void UpdateProgress(int progress);

};

class CarnivalDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	CarnivalDisplayWidget(int type, int id);
    ~CarnivalDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;

protected:
    void UpdateProgress(int progress);

};

class CornucopiaDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	CornucopiaDisplayWidget(int type, int id);
    ~CornucopiaDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;

protected:
    void UpdateProgress(int progress);

};

class PlantCultivateDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	PlantCultivateDisplayWidget(int type, int id);
    ~PlantCultivateDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;

protected:
    void UpdateProgress(int progress);

};

class GiftFoReturnDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	GiftFoReturnDisplayWidget(int type, int id);
    ~GiftFoReturnDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;
    void OnUpdateGiftFoReturnSignDays(int i_signDays);

protected:
    void UpdateProgress(int progress);
    int m_signedDays;
};

class PartyAssistDisplayWidget : public UIScrollDisplayWidgetBase
{
public:
	PartyAssistDisplayWidget(int type, int id);
    ~PartyAssistDisplayWidget();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void InitView() override;
    void ButtonClick() override;
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList) override;

protected:
    void UpdateProgress(int progress);

};
////////////////////////////////////////
///   Scroll Display Widget Factory
////////////////////////////////////////
class UIScrollDisplayWidgetFactory
{
public:
    enum WidgetType {
        TypeInvalid = -1,
        TypeFestivalEvent,// festival event banner
        TypeSevenGuide,// seven day guide banner
        TypePennyClassroom,// penny classroom
        TypeBattleOrder,// battle order
        TypeUnchartedMode,// uncharted mode
        TypeCornucopia,// cornucopia
        TypePlantCultivate,// plant cultivate
        TypeGiftFoReturn,// gift for return
        TypePartyAssist,// party assist
        TypeMax,
    };
    static UIScrollDisplayWidgetBase* CreateWidget(WidgetType type, int activityID);
};

//////////////////////////////////////
///    UIScrollWidget
//////////////////////////////////////
class UIScrollWidget : public PVZ2UIScrollingWidget
{
public:
    UIScrollWidget(Sexy::ScrollWidgetListener* i_listener);
    virtual ~UIScrollWidget();

    Sexy::FPoint GetScrollVelocity() { return mScrollVelocity; }
};

//////////////////////////////////////
///    UIScrollDotWidget
//////////////////////////////////////
class UIScrollDotWidget : public RechargeBundleDotWidget
{
public:
    UIScrollDotWidget(int dotsCount) : RechargeBundleDotWidget(dotsCount) {}
    void Draw(Graphics* i_g) override;
};

///////////////////////////////////////
///     UIScrollWidgetComponent
///////////////////////////////////////
class UIScrollWidgetComponent : public Sexy::Widget, Sexy::ScrollWidgetListener
{
    RT_CLASS_DEFINE(UIScrollWidgetComponent, Widget, RtClass);
public:
    typedef Delegate0 TouchEventCallback;// touch func

    enum ScrollState{
        StateInvalid = -1,
        StateIdle,
        StateTouchBegan,// manual touch
        StateTouchMoving,
        StateTouchEnd,
        StateBegan,// auto moving 
        StateScrolling,
        StateEnd,
        StateBounce,
        StateMax,
    };
    
    // explicit UIScrollWidgetComponent(Sexy::Widget* parent);
    UIScrollWidgetComponent();
    virtual ~UIScrollWidgetComponent();

    virtual void Update() override;
	virtual void Draw(Graphics* i_g) override;

    // initview func should call after set param and addwidget 
    virtual void InitView();
    virtual void InitDot();
    // use in update func
    virtual void UpdateScrollWidget();
    // set parems
    virtual void SetScrollParam();
    // maybe no use
    virtual void SetWidgetRect(Rect rect);
    virtual void SetScrollWidgetRect(Rect rect);
    virtual void SetScrollWidget(UIScrollWidget* widget);
    virtual void SetDotEnable(bool enable);
    virtual void SetManualEnable(bool enable);
    virtual void SetAutoScroll(bool enable);
    virtual void SetImmediateChangePage(bool enable);
    virtual int GetNearIndex();// get the near index
    virtual void AddDisplayWidget(UIScrollDisplayWidgetBase* widget);
    virtual void ImmediateChangePage();
    virtual void AutoScroll();

    // virtual void TouchBegan( const Sexy::Touch& touch ) override;
    // virtual void TouchMoved( const Sexy::Touch& touch ) override;
    // virtual void TouchEnded( const Sexy::Touch& touch ) override;

    void ScrollTargetReached( ScrollWidget* scrollWidget ) {};
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override;
    void ScrollTouchEnd( const Sexy::Touch& touch ) override;
    void ScrollTouchMotion( const Sexy::Touch& touch ) override;

    void SetTouchBeganCallback(TouchEventCallback func) { _touchBeganCallback = func; }
    void SetTouchMovedCallback(TouchEventCallback func) { _touchMovedCallback = func; }
    void SetTouchEndCallback(TouchEventCallback func) { _touchEndCallback = func; }

protected:
    Sexy::Widget* _scrollWidgetContainer;// this is a container of scroll widgets
    UIScrollWidget* _scrollWidget;// this is parent of the scrollwidgets container
    std::vector<UIScrollDisplayWidgetBase*> _widgetList;
    
    Rect _widgetRect;// the size of each widget in scrollwidgetcontainer
    Rect _scrollWidgetRect;// the size of all scrollwidget

    TouchEventCallback _touchBeganCallback;
    TouchEventCallback _touchMovedCallback;
    TouchEventCallback _touchEndCallback;
    
    ScrollState _state;// scroll widget state
    UIScrollDotWidget* _dotWidget;// dot widget
    
    int _widgetCounts;// max widget counts
    int _curIndex;// current index
    float _singleScrollWidth;// single scroll width

    pvztime_t _startMoveTime;// when to start move

    bool _isAutoScroll;// is auto scroll
    bool _isImmediateChangePage;// is immediate change page
    bool _isDotEnable;// is show dot img
    bool _isManual;// can control by manual

    pvztime_t _slideDelta;// slide delta time
    pvztime_t _autoSlideCooldownTime;// time params
    pvztime_t _oneSlideTime;// the time duraing one widget slide

    Sexy::FPoint _defaultScrollVelocity;// default scrollwidget speed
};

#endif /* UISCROLLWIDGET_H_ */
