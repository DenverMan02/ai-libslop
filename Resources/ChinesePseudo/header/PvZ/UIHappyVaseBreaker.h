#ifndef UIHAPPYVASEBREAKER_H
#define UIHAPPYVASEBREAKER_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "Singleton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"


#pragma mark - HappyVaseAnimWidget

enum HappyVaseEnum
{
    HappyVase_Invalid = -1,
    HappyVase_Normal,
    HappyVase_Breaking,
    HappyVase_Broken,
};

class HappyVaseAnimWidget : public Widget
{
public:
    HappyVaseAnimWidget();
    virtual ~HappyVaseAnimWidget();

    virtual void Update() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void Init(int i_index, bool i_isBroken);
    bool IsBroken();
    void StartBreak();
    void OnBroken(const std::string& i_animLabel);
    void BreakConfirm(class UIMessageBox* box, int buttonID);

    void onVaseAnimStartOrEnd(bool i_soe);
private:
    int m_index;
    bool m_isJackPot;
    bool m_shieldTouch;
    int32 m_iTouch;
    HappyVaseEnum m_state;
    EffectAnim_UIAnim m_vaseEffect;
    std::vector<std::pair<int,int>> m_rewards;
};


#pragma mark - HappyVaseDisplayItem

class HappyVaseDisplayItem : public Widget
{
public:
    HappyVaseDisplayItem();
    virtual ~HappyVaseDisplayItem();

    virtual void Draw(Graphics* i_g) override;
    void DrawItem(Graphics* i_g);

    void Init(int i_itemId, int i_amount);
    int GetItemID();
    int GetItemAmount();
    void SetIsObtained(bool i_flag);

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void TouchesCanceled() override;
private:
    int m_touchId;
    SexyString m_des;
    class StoneLotteryItemTipUI* m_tipUI;
    int m_itemId;
    int m_amount;
    int m_itemType;
    bool m_obtained;
    Sexy::Image* m_image;
    Sexy::Image* m_backImage;
};


#pragma mark - HappyVaseTaskWidget

class GeneralTask;
class HappyVaseTaskWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RT_CLASS_DEFINE(HappyVaseTaskWidget, Sexy::Widget, RtClass);

    HappyVaseTaskWidget();
    virtual ~HappyVaseTaskWidget();

    //Only for Cheat
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitTask(GeneralTask* i_task);

protected:
    void UpdateButtonState();
    void RequestReward();

    Sexy::Image* m_iBackground;
    SexyString m_strName;
    Sexy::Rect m_rName;
    Sexy::Rect m_rReward;
    SexyString strProgress;
    Sexy::Rect m_rProgress;
    Sexy::Rect m_rBanner;
    Sexy::Rect m_rButton;
    PVZ2UIButton* m_btnButton;
    GeneralTask* m_pTask;
    int32 m_iTouch;
    int m_rewardNum;
};


#pragma mark - ShowHappyVaseDescriptionUI

class ShowHappyVaseDescriptionUI : public Widget, public ButtonListener
{
public:
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void InitView();
};


#pragma mark - UIHappyVaseBreaker

class UIHappyVaseBreaker : public UISingletonDialog<UIHappyVaseBreaker>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIHappyVaseBreaker();
    virtual ~UIHappyVaseBreaker();
    
    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIHappyVaseBreaker"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void TabSelectionChanged(int tabID) override;

    void InitView();
    
    int GetHammerNum();
    int GetResetHammerNeed();
    int GetVaseBreakHammerNeed();

    bool IsJackPotId(int i_id);
    void SetJackPotId(const std::vector<int>& i_id);
    void SetHammerNum(int i_num);
    void SetResetHammerNeed(int i_reset);
  
    void CheckReset();
    void SetRewardGet(int i_rewardId);

    void LockOperation();
    void UnlockOperation();

    void showDescription();
    void closeDescription();

    void InitVases(const std::vector<class HappyVaseItem>& i_rewardList,const std::vector<int>& i_gainedList, const std::vector<int>& i_vaseStateList);
    void InitTasks();

private:
    void VaseReset(int i_isFree);
    void ResetConfirm(class UIMessageBox* box, int buttonID);

    void UpdateTimer();    
    void SwitchTaskWidget(int i_tab);
  
private:
    //Tab1s
    std::vector<HappyVaseAnimWidget*> m_vaseList;
    std::vector<HappyVaseDisplayItem*> m_itemList;
    //Tab2s
    int m_tabID;//for task
    //common
    std::vector<int> m_jackPot;
    int m_resetNeed;
    int m_currentHammer;
    int m_currentTabTask;//for main tab
    pvztime_t m_countdown;
    ShowHappyVaseDescriptionUI* m_desUI;
};


#pragma mark - HappyVaseBreakerData

struct HappyVaseItem
{
    int ItemId;
    int Amount;
};

struct HappyVaseSpecialTaskItem
{
    int TaskId;
    int Number;
};

class HappyVaseBreakerData : public INetworkData
{
public:
	RT_CLASS_DEFINE(HappyVaseBreakerData, INetworkData, RtClass);

    int                                         Hammer;
    int                                         Version;
    std::vector<int>                            Jackpot;
    std::vector<int>                            VaseStateList;
    std::vector<HappyVaseItem>                  RewardList;
    std::vector<int>                            GainedList;
    std::vector<int>                            FirstTaskList;
    std::vector<int>                            FirstTaskFinishedList;
    std::vector<HappyVaseSpecialTaskItem>       SecondTaskList;
    std::vector<int>                            SecondTaskFinishedList;
    std::vector<HappyVaseSpecialTaskItem>       ThirdTaskList;
    std::vector<int>                            ThirdTaskFinishedList;
    std::vector<int>                            BreakNeed;
    int                                         ResetNeed;
    int                                         DailyGemsRecharge;
    int                                         MonthGemsRecharge;
};

class HappyVaseBreakerResetData : public INetworkData
{
public:
	RT_CLASS_DEFINE(HappyVaseBreakerResetData, INetworkData, RtClass);

    std::vector<HappyVaseItem>                  RewardList;
    int                                         ResetNeed;
    int                                         Hammer;
};

namespace Message
{
    void BreakVaseStartOrEnd(bool i_soe);
};

#endif