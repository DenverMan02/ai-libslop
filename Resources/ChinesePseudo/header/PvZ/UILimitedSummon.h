#ifndef __UI_Limited_Summon_H__
#define __UI_Limited_Summon_H__

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"


struct LimitedSummonGrowData
{
    int Require;
    std::vector<S2C_BonusInfo> Reward;
    int Obtained;
};

struct LimitedSummonRankItemData
{
    std::string PlayerName;
    int HeadshotID;
    int SummonTimes;
    int Rank;
};

struct LimitedSummonRankPriviewItemData
{
    int Min;
    int Max;
    int Limited;
    std::vector<S2C_BonusInfo> Award;
};

struct LimitedSummonRankPriviewData
{
    std::vector<S2C_BonusInfo> Guarante;
    std::vector<LimitedSummonRankPriviewItemData> PriviewList;
};

class LimitedSummonData : public INetworkData
{
public:
	RT_CLASS_DEFINE(LimitedSummonData, INetworkData, RtClass);

    int Tickets;
    int SummonTimes;
    int IsVIP;
    bool CanBuyVIP;
    int ReceivedVIP;
    int VIPBuyTimer = 0;
    std::vector<std::vector<S2C_BonusInfo>> BundleInfo;
    std::vector<int> BundleLimit;
    std::vector<LimitedSummonGrowData> GrowthReward;
    LimitedSummonRankPriviewData DailyRankPrivewData;
    LimitedSummonRankPriviewData TotalyRankPrivewData;

    std::vector<LimitedSummonRankItemData> DailyRankData;
    std::vector<LimitedSummonRankItemData> TotalyRankData;
    int DailyRankNumber;
    int TotalyRankNumber;
    bool IsOnDailyRank;
    bool IsOnTotalyRank;
    int RSBVersion;
};

class LimitedSummonRewardData : public INetworkData
{
public:
	RT_CLASS_DEFINE(LimitedSummonRewardData, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> DailyRewardData;
    std::vector<S2C_BonusInfo> TotalyRewardData;
};


enum LimitedSummonTab : int
{
    SummonTab_Start = 0,
    SummonTab_LimitedSummon,
    SummonTab_VIP,
    SummonTab_SummonBundle,
    SummonTab_AccumSummon,
    SummonTab_SummonRank,
};

class LimitedSummonTabBase
{
public:
	LimitedSummonTabBase(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~LimitedSummonTabBase();

    int GetTabID() const { return m_tabID; }
    bool HasInit() { return m_hasInit; }
    PVZ2UIButton* GetTabBtn() const { return m_pTabBtn; }
    Widget* GetInnerWidget() { return m_innerWidget; }
    virtual void AddExternalWidget(Widget* i_widget);
	void SetSelect(bool setting);

protected:
    int m_tabID;
    PVZ2UIButton* m_pTabBtn;
    UI::Dialog* m_pCenterDlg;

    bool m_hasInit;
    Widget* m_innerWidget;
};

class UILimitedSummon : public UISingletonDialog<UILimitedSummon>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UILimitedSummon();
    virtual ~UILimitedSummon();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UILimitedSummon"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void SetCurrentTab(int iTab);

protected:
    typedef std::map<int, class LimitedSummonTabBase*> MapTabs;

	int m_curTab;
	MapTabs m_mapTab;

private:
    void showDescriptionWidget();
    void closeDescriptionWidget();
    class ActivityDescriptionUI* m_descriptionUI;
};


class LimitedSummonManager : public LazySingleton<LimitedSummonManager>
{
public:
    void LoadData();
    void RecalculTickets();

    void RequestDailyRank();
    void RequestTotalyRank();

    LimitedSummonData m_cacheData;
};

#define gLimitedSummonManager (LimitedSummonManager::GetInstancePtr())


class LimitedSummonPage : public UISingletonDialog<LimitedSummonPage>
{
public:
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "LimitedSummonPage"; }
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void Refresh();

private:
    void SummonConfirm1(class UIMessageBox* box, int buttonID);
    void SummonConfirm2(class UIMessageBox* box, int buttonID);
    void Summon(int i_type);
};


class LimitedSummonVIP : public UISingletonDialog<LimitedSummonVIP>
{
public:
    LimitedSummonVIP();
    virtual ~LimitedSummonVIP();
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "LimitedSummonVIP"; }
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;

    void InitView();
    void Refresh();

private:
    void Receive();
    void OnBuyVIPFinish(int i_index);

    time_t m_VIPEndTime;
    time_t m_createTime;
};


class LimitedSummonBundleItem : public Widget, public Sexy::ButtonListener 
{
public:
    LimitedSummonBundleItem();
    virtual ~LimitedSummonBundleItem();
    void InitView(int i_index);
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    int m_index = -1;
    int m_limit = 0;
    PVZ2UIButton* m_button;

private:
    void OnBuyLimitedSummonBundle(int i_index);
};

class LimitedSummonBundle : public UISingletonDialog<LimitedSummonBundle>, public Sexy::ScrollWidgetListener
{
public:    
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "LimitedSummonBundle"; }
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void Refresh();

private:

};


class LimitedSummonAddUpItem : public Widget, public Sexy::ButtonListener 
{
public:
    void InitView(int i_index);
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void UpdateButton();
private:
    int m_index = -1;
    SexyString m_title;
    SexyString m_progress;
    PVZ2UIButton* m_button;
};

class LimitedSummonAddUp : public UISingletonDialog<LimitedSummonAddUp>, public Sexy::ScrollWidgetListener
{
public:    
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "LimitedSummonAddUp"; }
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void Refresh();

private:

};



class LimitedSummonRankItem : public Widget
{
public:
    void InitView(bool i_isDaily, int i_index);
    virtual void Draw(Graphics* i_g) override;

private:
    bool m_daily;
    int m_index;
    int m_rank;
    SexyString m_name;
    int m_times;
};

class LimitedSummonRank : public UISingletonDialog<LimitedSummonRank>, public Sexy::ScrollWidgetListener, public UI::TabControlListener
{
public:    
    LimitedSummonRank();
    virtual ~LimitedSummonRank();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "LimitedSummonRank"; }
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void TabSelectionChanged(int tabID) override;
    void Update() override;

    void InitView();
    void Refresh();

private:
    void InitDailyInfo();
    void InitTotalyInfo();
    void AddItems(Widget* i_widget, const std::vector<S2C_BonusInfo>& i_reward);
    void OnRefreshLimitedSummonRank(int i_type);

    class PVZ2UIScrollingWidget* m_dailyScrollWidget;
    class PVZ2UIScrollingWidget* m_totalyScrollWidget;

    bool m_firstRequestDailyRank;
    bool m_firstRequestTotalyRank;
    bool m_requestedRank;
    bool m_canRequestDailyRank;
    bool m_canRequestTotalyRank;
};

namespace Message 
{
    void RefreshLimitedSummonRank(int i_type);
}

#endif