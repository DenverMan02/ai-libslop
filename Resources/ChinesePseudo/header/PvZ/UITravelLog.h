#ifndef UITRAVELLOG_H
#define UITRAVELLOG_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "TravelLogMgr.h"
#include "Image.h"

class TaskWidget : public Widget, public ButtonListener
{
public:
    RT_CLASS_DEFINE(TaskWidget, Widget, RtClass);

    TaskWidget();
    virtual ~TaskWidget();

    virtual void			Resize(const Rect& i_Rect) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;

    //For Cheat
    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;

    virtual void            Init();

    //if you do not want to draw some modules, override them and set it empty
    virtual void            DrawNameAndDescription(Sexy::Graphics* i_g);
    virtual void            DrawReward(Sexy::Graphics* i_g);
    virtual void            DrawPrograss(Sexy::Graphics* i_g);
    virtual void            DrawTimer(Sexy::Graphics* i_g);

    virtual void            InitTimer();
    virtual void            UpdateTimer();

    TravelLogTask*          GetTask();
    int                     GetTaskID();
    void                    SetTask(TravelLogTask* i_task);

protected:
    TravelLogTask*          m_pTask;
    Rect                    m_rName;
    SexyString              m_sName;
    Rect                    m_rDescription;
    SexyString              m_sDescription;
    Sexy::Image*            m_iBackground;
    Rect                    m_rReward;
    Rect                    m_rPrograss;
    Rect                    m_rTimerBG;
    Rect                    m_rTimer;
    SexyString              m_sTimer;
    EffectAnim_UIAnim       m_eTimer;
    int32                   m_iTouch;
};

class BasicTaskWidget : public TaskWidget
{
public:
    RT_CLASS_DEFINE(BasicTaskWidget, TaskWidget, RtClass);

    BasicTaskWidget();
    virtual ~BasicTaskWidget();

    virtual void            Init() override;
    virtual void            Update() override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
};

class BeatZombiesTaskWidget : public BasicTaskWidget
{
public:
    RT_CLASS_DEFINE(BeatZombiesTaskWidget, BasicTaskWidget, RtClass);

    BeatZombiesTaskWidget();
    virtual ~BeatZombiesTaskWidget();
    virtual void            Init() override;
};

class WorldTaskWidget : public TaskWidget
{
public:
    RT_CLASS_DEFINE(WorldTaskWidget, TaskWidget, RtClass);

    WorldTaskWidget();
    virtual ~WorldTaskWidget();

    virtual void            Init() override;

    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void			ButtonDepress(int theId) override;

    //World task has no timer
    virtual void            DrawTimer(Sexy::Graphics* i_g) override {};
    virtual void            InitTimer() override {};
    virtual void            UpdateTimer() override {};

protected:
    PVZ2UIButton* m_btnGotoWorld;
};

class EpicTaskWidget : public TaskWidget
{
public:
    RT_CLASS_DEFINE(EpicTaskWidget, TaskWidget, RtClass);
    EpicTaskWidget();
    virtual ~EpicTaskWidget();

    virtual void            Init() override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void			ButtonDepress(int theId) override;

    virtual void            DrawPrograss(Sexy::Graphics* i_g) override;
protected:
    PVZ2UIButton*           m_btnStartLevel;
    int                     m_gridStartX;
    int                     m_gridStartY;
    int                     m_gridNumberHor;
    int                     m_gridNumberVer;
    int                     m_gridWidth;
    int                     m_gridHeight;
};

enum TravelLogRewardState{
    TL_GIVE_REWARD_IDLE,
    TL_GIVE_REWARD_LOOP,
    TL_GIVE_REWARD_POPING,
};

class TravelLogBonusUI : public PopingWidget, public ButtonListener
{
public:
	TravelLogBonusUI();
    ~TravelLogBonusUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void InitView();
    void SetTask(TravelLogTask* i_task);
    int WhichChestToRequest();
    void CalIndexByWorldName();

    void OnTravelLogIntegralChestFinish(bool i_success, TravelLogRewardData* i_data);
    void OnTravelLogWolrdChestFinish(bool i_success, TravelLogRewardData* i_data);

private:
    void InitShiningAnims();

private:
    TravelLogTask*          m_task;
    bool                    m_IsDrawBonus;
    Rect                    m_bonusRect;
    Rect                    m_rewardRect;
    Rect                    m_titleImgRect;
    Rect                    m_titleRect;
    SexyString              m_title;
    Rect                    m_submitRect;
    PVZ2UIButton*           m_submit;
    EffectAnim_UIAnim       m_openAnimRig;
    EffectAnim_UIAnim       m_backAnimRig;
   
    int bt;
    int ct;
};

class UITravelLog : public UISingletonDialog<UITravelLog>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UITravelLog();
	virtual ~UITravelLog();
	virtual bool							OnCreate() override;
	virtual std::string                     GetLayoutName() override { return "UITravelLog"; }
    virtual void							Draw(Sexy::Graphics* i_g) override;
    virtual void							Update() override;
    
	//Listener
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            TabSelectionChanged(int tabID) override;
    virtual void                            ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void                            ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void                                    InitView();
    void                                    InitTab(int i);
    
    void                                    ShowBonus();
    void                                    CheckReward();                              
    void                                    StartReward();
    void                                    EndReward();
    void                                    UpdateCompletedUI();
    void                                    GiveRewardFinish(TravelLogTask* i_task);
    void                                    SetNeedRefresh(bool flag);

private:
    TravelLogRewardState                    m_rewardState;
    TravelLogBonusUI*                       m_bonusUI;
    pvztime_t                               m_nextPop;
    bool                                    m_needRefresh;
};

namespace Message
{
    void TravelLogIntegralChestFinish(bool i_success, TravelLogRewardData* i_data);
    void TravelLogWolrdChestFinish(bool i_success, TravelLogRewardData* i_data);
};

#endif