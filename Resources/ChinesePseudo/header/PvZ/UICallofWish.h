#ifndef UICallofWish_H
#define UICallofWish_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"

enum CallofWishTab
{
    Tab_Start = 0,
    Tab_CallofWish,
    Tab_Task,
    Tab_DailyBundle,
    Tab_LimitBundle,
    Tab_AccumReward,
    Tab_TrainReward,
};

class GeneralTask;

struct CallofWishReward
{
    int Goal;
    bool Obtained;
    std::vector<S2C_BonusInfo> BonusList;
};

struct CallofWishBundle
{
    int Limit;
    bool Available;
};

class CallofWishData : public INetworkData
{
public:
	RT_CLASS_DEFINE(CallofWishData, INetworkData, RtClass);

    int TargetWishPlant;
    std::vector<int> WishPlantList;

    int m_Integral;
    std::vector<int> TaskFinishList;
    std::vector<int> TaskBlackList;

    std::vector<int> DailyBundle;
    std::vector<int> LimitBundle;

    int AccumTimes;
    std::vector<CallofWishReward> AccumCallReward;
    int TargetTrainPlant;
    std::vector<CallofWishReward> TrainPlantReward;
};

class CallofWishTabBase
{
public:
	CallofWishTabBase(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~CallofWishTabBase();

    int GetTabID() const { return m_tabID; }
    PVZ2UIButton* GetTabBtn() const;
    Sexy::Widget* GetTabContent();
	void SetSelect(bool setting);
    virtual void AddExternalWidget(Widget* i_widget);
    bool HasInit() { return m_hasInit; }
    Widget* GetInnerWidget() { return m_innerWidget; }

protected:
    int m_tabID;
    PVZ2UIButton* m_pTabBtn;
    UI::Dialog* m_pCenterDlg;

    bool m_hasInit;
    Widget* m_innerWidget;
};

class UICallofWish : public UISingletonDialog<UICallofWish>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UICallofWish();
    virtual ~UICallofWish();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UICallofWish"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void SetCurrentTab(int iTab);

protected:
    typedef std::map<int, class CallofWishTabBase*> MapTabs;

	int m_curTab;
	MapTabs m_mapTab;

private:
    void showDescriptionWidget();
    void closeDescriptionWidget();
    class ActivityDescriptionUI* m_descriptionUI;
};

class CallofWishManager : public LazySingleton<CallofWishManager>
{
public:
    void Initdata();
    int GetAccumLadder();
    int GetPrograssValue(CallofWishTab i_value);

    CallofWishData m_cacheData;
};

#define gCallofWishManager (CallofWishManager::GetInstancePtr())


class CallofWishPage : public UISingletonDialog<CallofWishPage>
{
public:
    CallofWishPage();
    virtual ~CallofWishPage();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "CallofWishPage"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;

    void InitView();

private:
    void SetUpPlantWishDisplay(int i_mainPlantId, const std::vector<int>& i_otherPlantId);
    void SetUpAccumText(int i_accum, int i_ladder);
    void SetUpButtons();
    void SetUpTicket();

    void SelectPlant();
    void determineSelect(class UIMessageBox* box, int buttonID);
    void CallWishs(class UIMessageBox* box, int buttonID);

    int m_callType;
    int m_callTimes;
    int m_ticketCache;
};

class CallofWishTaskPage : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
    CallofWishTaskPage();
    ~CallofWishTaskPage();

    void Draw(Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(int i_width, int i_height);

};

class CallofWishTaskWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RT_CLASS_DEFINE(CallofWishTaskWidget, Sexy::Widget, RtClass);

    CallofWishTaskWidget();
    virtual ~CallofWishTaskWidget();

    //For Cheat
    virtual void TouchBegan(const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch ) override;

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;

    void SetTask(GeneralTask* i_task);
    void InitView();
    void UpdateButtonState();
    void InitTimer();
    void DrawTimer(Sexy::Graphics* i_g);
protected:
    void RequestReward();

    int32 m_iTouch;
    GeneralTask* m_pTask;
    Sexy::Image* m_iBackground;
    PVZ2UIButton* m_btnButton;
    EffectAnim_UIAnim m_eTimer;
    SexyString m_strName;
    SexyString strProgress;
    Rect m_rName;
    Rect m_rBanner;
    Rect m_rProgress;
    Rect m_rButton;
};

class CallofWishBundlePage : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
    CallofWishBundlePage();
    ~CallofWishBundlePage();

    void Update() override;
    void Draw(Graphics* i_g) override;

    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void InitView(CallofWishTab i_tab, int i_width, int i_height);

private:
    CallofWishTab m_tab;
    SexyString m_timer;
    SexyString m_dayTimer;
};

class CallofWishBundleItem : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    CallofWishBundleItem();
    ~CallofWishBundleItem();

    void Draw(Graphics* i_g) override;
    void ButtonDepress(int i_id) override;

    void InitView(CallofWishTab i_tab, int i_index, int i_limit);
    void onBuyGacha(int id);
private:
    int m_index;
    int m_limit;
    CallofWishTab m_tab;
    Sexy::Image* m_image;
    PVZ2UIButton* m_btnButton;
    int m_identify;
    std::string m_purchase;
};

class CallofWishTrainPage : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
    CallofWishTrainPage();
    ~CallofWishTrainPage();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void ButtonDepress(int i_id) override;

    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}  
    void InitView(CallofWishTab i_tab, int i_width, int i_height);

private:
    CallofWishTab m_tab;
    SexyString m_timer;
    PVZ2UIButton* m_btnJump;
};

class CallofWishTrainItem : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    CallofWishTrainItem();
    ~CallofWishTrainItem();

    void Update() override;
    void Draw(Graphics* i_g) override;
    void ButtonDepress(int i_id) override;

    void InitView(CallofWishTab i_tab, int i_index, CallofWishReward i_data);
    void RequestReward();

private:
    bool m_obtained;
    int m_index;
    int m_ladder;
    CallofWishTab m_tab;
    SexyString m_strName;
    PVZ2UIButton* m_btnButton;
};

namespace Message
{
    void CallWishTimes(int i_times);
    void CollectIntegralTaskFinish();
    void UpdateCallofWishTask();
}

#endif