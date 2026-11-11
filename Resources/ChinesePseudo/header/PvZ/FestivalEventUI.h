/*
 * FestivalEventUI.h
 *
 *  Created on: 2018-1-5
 *      Author: Administrator
 */

#ifndef FESTIVALEVENTUI_H_
#define FESTIVALEVENTUI_H_

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "MagentoService.h"
#include "PlantAdventureConfig.h"
#include "BoxOpenUI.h"
#include "PopingWidget.h"
#include "UISingletonDialog.h"
#include "UIEditor/UIDialog.h"
#include "PlantBundleUI.h"
#include "DNode/DNodeWidget.h"
//#include "NationalHolidayUI.h"

enum FestivalTab : int
{
	NTab_Festival_Begin = 1,

	// NTab_ChildrenDay2019 = 1, // this activity will use vase breaker

	NTab_Carnival = 1,
	NTab_LimitedSummon = 2,
	NTab_StoneLottery = 3,
	NTab_WeeklyRecharge = 4,
	NTab_GroupBuy = 5,
	NTab_RenaissanceChallenge = 6,
	NTab_BossChallenge = 7,
	// NTab_DailySign = 8,
	NTab_PlantTrees = 8,

	NTab_VaseBreaker = 9,
	NTab_ConsumeGetGift = 10,
	NTab_ConsumeAndReceive = 11,
	NTab_LuckyLottery = 12,
	NTab_OneYuan = 13,
	NTab_ConsumeAndReceiveExtra = 14,
	NTab_PiggyBank = 15,
	NTab_RedPacket = 16,
	NTab_Crack = 17,
	NTab_SecretGacha = 18,
	NTab_RechargeDailySign = 19,
	NTab_DiscountShop = 20,
	NTab_CustomVoting = 21,
	
	NTab_MiniGame = 22,
	NTab_AnniversaryTreasure = 23,
	NTab_LuckyBag = 24,
	NTab_SecretStore = 25,
	NTab_RechargeReward = 26,
	Ntab_CallofWish = 27,
	Ntab_PlayerSurvey = 28,
	Ntab_FightZodiac = 29,
	Ntab_SpringFestivalGoldenEgg = 30,
	Ntab_ArborDay = 31,
	NTab_RichMan = 32,
	Ntab_BattleOrder = 33,
	NTab_WorldCup_Shop = 34,
	NTab_NewYearGoods = 35,
	NTab_TenYearRecord = 36,
	NTab_NewYearGiftBox = 37,

	NTab_Festival_End,
};

struct NetworkShopContentData
{
	NetworkShopContentData()
	{
		ItemId = 0;
		Amount = 0;
		Price = 0;
		SellOut = 0;
	}

	int ItemId;
	int Amount;
	int Price;
	int SellOut;
};

struct NetworkFestivalEntryData
{
	NetworkFestivalEntryData()
	{
		ActivityID = 0;
		Sequence = 0;
		Open = false;
	}

	int ActivityID;
	int Sequence;
	bool Open;
};

class NetworkFestivalEntryInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkFestivalEntryInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<NetworkFestivalEntryData>     entryInfos;
	std::string								  entryIcon;
	std::string								  titleText;
};

struct FestivalEntryData
{
	FestivalEntryData()
	{
		ActivityID = 0;
		Sequence = 0;
		Open = false;
	}

	int ActivityID;
	int Sequence;
	bool Open;
};

class NetworkLotteryInfo : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkLotteryInfo, Sexy::RtObject, Sexy::RtClass);

public:
    int plantIndex;
    int gemCost;
};

class NetworkRedPacketInfo : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkRedPacketInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<int> redPacketInfos;
    int gemPackCost;
};

struct RedPacketData
{
    int32 itemId = 0;
    int32 amount = 0;
};

class NetworkRedPacketReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkRedPacketReward, INetworkData, RtClass);

    std::vector<RedPacketData>   m_prizeInfos;
};

//shop
struct NetworkFShopContentData
{
	NetworkFShopContentData()
	{
		Amount = 0;
		ObjectId = 0;
		Cost = 0;
		LimitedBuy = 0;
	}

	int Amount;
	int ObjectId;
	int Cost;
	int LimitedBuy;
};

class NetworkFShopInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkFShopInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<NetworkFShopContentData>     shopInfos;
};

//shop
struct NetworkfthCostData
{
	NetworkfthCostData()
	{
		MaterialId = 0;
		Cost = 0;
	}

	int MaterialId;
	int Cost;
};

struct NetworkfthShopContentData
{
	NetworkfthShopContentData()
	{
		Amount = 0;
		ObjectId = 0;
		LimitedBuy = 0;
	}

	int Amount;
	int ObjectId;
	std::vector<NetworkfthCostData> Costs;
	int LimitedBuy;
};

class NetworkfthShopInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkfthShopInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<NetworkfthShopContentData>     shopInfos;
};

class NetworkShopInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkShopInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<NetworkShopContentData>     shopInfos;
};


class FestivalEventTabBase
{
public:
	FestivalEventTabBase(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~FestivalEventTabBase();

	virtual void		OnButtonClicked(int i_id);
	virtual void		SetSelect(bool setting);
    virtual void        DrawBackground(class Sexy::Graphics* i_g);
    virtual void        DrawForeground(class Sexy::Graphics* i_g);
    virtual void DrawSpecial(Sexy::Graphics* i_g) {}

    virtual std::string GetTabContainerImageName() const { return ""; }
    virtual SexyString  GetGoToButtonTitle();

	virtual void		Update() {}

	class PVZ2UIButton*	GetTabBtn() const;
	int					GetTabID()  const { return m_tabID; }
    Sexy::Widget*		GetTabContent();
    //virtual void SyncActivityData(const NetworkShopInfo& i_data) {}
    virtual void SyncActivityTime() {}
    virtual void AddExternalWidget(Widget* i_widget) {}
    virtual void SyncActivityData(const NetworkLotteryInfo& i_data, int i_endDate, bool i_open) {}
    virtual void SyncActivityData(const NetworkFShopInfo& i_data) {}
    virtual void SyncActivityData(const NetworkShopInfo& i_data) {}
    virtual void SyncActivityData(const NetworkfthShopInfo& i_data) {}
    virtual void SyncActivityData(int i_endDate) {}

protected:
	int						m_tabID;
	class UI::Dialog*		m_pCenterDlg;
	class PVZ2UIButton*     m_pTabBtn;
	class UIWidgetImage*	m_pTabContainer;
};

//shop widgets
struct FShopContentData
{
	FShopContentData()
	{
		Amount = 0;
		ObjectId = 0;
		Cost = 0;
		LimitedBuy = 0;
	}

	int Amount;
	int ObjectId;
	int Cost;
	int LimitedBuy;
};

class FestivalShopPanel : public Widget
{
public:
	FestivalShopPanel(Rect &i_rect, int i_contentSize, UIWidgetImage* i_container, std::vector<FShopContentData>& i_datas);
    ~FestivalShopPanel();

    void RefreshShopData(const std::vector<FShopContentData>& i_data);
private:

    void	InitView();
    void 	InitTestData();
    int     m_contentSize;

    std::vector<class FestivalShopContent*> m_contents;
    UIWidgetImage*	m_pTabContainer;
    std::vector<FShopContentData> m_shopContentDatas;
};

// shop ui
class FestivalShopUI : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:

	FestivalShopUI(UIWidgetImage* i_container, std::vector<FShopContentData>& i_datas);
    ~FestivalShopUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

	void InitView();
	void HideWidgets(bool i_hide);
	void RefreshShopData(const std::vector<FShopContentData>& i_data);
private:
	void InitTestData();
	PVZ2UIScrollingWidget* m_scrollingWidget;
	UIWidgetImage*	m_pTabContainer;
	std::vector<FShopContentData> m_shopContentDatas;
	FestivalShopPanel* m_panel;
	time_t m_endTime;
};

struct FShopItemData
{
	FShopItemData()
	{
		Amount = 0;
		ObjectId = 0;
	}

	int Amount;
	int ObjectId;
};

class FShopItemContent : public Sexy::Widget
{
public:

	FShopItemContent(const FShopItemData & data);
	virtual ~FShopItemContent();

	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    void RefreshContentData(const FShopItemData& i_data) { m_data = i_data; }

private:

    void            setupScreen();

private:

    FShopItemData  m_data;
};



class FestivalShopContent : public Widget, Sexy::ButtonListener
{
public:
	FestivalShopContent(FShopContentData &i_data, FestivalShopPanel* i_panel);
    ~FestivalShopContent();

    virtual void	Update() override;
    virtual void	Draw(Sexy::Graphics* i_g) override;
    virtual void	ButtonDepress(int i_id) override;
    void	InitView();
    void RefreshContentData(const FShopContentData& i_data);
    void onMaterialChanged();
private:
    FShopContentData     m_ShopContentData;
    FestivalShopPanel* m_panel;
    PVZ2UIButton* m_purchaseButton;
    Rect m_matBgPt;
    FShopItemContent* m_shopContent;
};

class FShopTabUI : public FestivalEventTabBase, public Sexy::ScrollWidgetListener//, public ButtonListener
{
public:
	FShopTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~FShopTabUI();

    virtual void SetSelect(bool setting) override;

    virtual void Update() override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void DrawForeground(Sexy::Graphics* i_g) override;
    virtual void DrawSpecial(Sexy::Graphics* i_g) override;

    void SyncActivityData(const NetworkFShopInfo& i_data);
    void RefreshShopData(const std::vector<FShopContentData>& i_data);

private:
    void InitView();
    void AddScrollingWidget();

private:
    FestivalShopUI* m_innerWidget = nullptr;
    //PVZ2UIScrollingWidget* m_scrollingWidget;
    Point m_textPt;
    Point m_panelPt;
    std::vector<FShopContentData> m_shopContentDatas;
    bool m_hasInit;
    time_t m_expireTime;
    Rect m_textRect;
};

// zhousen this tab is for currency change for gift
class CShopTabUI : public FestivalEventTabBase
{
public:
	CShopTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~CShopTabUI();

    virtual void SetSelect(bool setting) override;

    void SyncActivityData(const NetworkShopInfo& i_data) override;
    void RefreshShopData(const std::vector<NetworkShopContentData>& i_data);

private:
    void InitView();

private:
    class NationalShopUI* m_innerWidget = nullptr;
    Point m_panelPt;
    std::vector<NetworkShopContentData> m_shopContentDatas;
    bool m_hasInit;
    time_t m_expireTime;
};


class FestivalEventUI : public UISingletonDialog<FestivalEventUI>, public Sexy::ScrollWidgetListener
{
public:
	FestivalEventUI();
	virtual ~FestivalEventUI();
	virtual bool							OnCreate() override;
	virtual std::string                     GetLayoutName() override;
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							Update() override;

	// ButtonListener
	virtual void							ButtonDepress(int i_id) override;
	// implement of Sexy::ScrollWidgetListener
	virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void                                    SetCurrentTab(int iTab);
	int										GetCurrentTab() const { return m_curTab; }
	Sexy::Widget*                           GetTabContent();
	void                                    Layout();

	void                                    DisabledAllButtons();
	void                                    EnabledAllButtons();
	void									ChangeTabButtonImage(int i_tabID, Sexy::Image* i_normal, Sexy::Image* i_down);

	UIWidgetText*							GetCostTextWidget();

	void loadData();
	void InitView();
	void SyncActivityData(const NetworkFestivalEntryInfo& i_info);
	bool HasTargetActivityOpen(FestivalTab i_tabId);
	bool CheckTargetActivityItem(int i_activityId);
	int getWidth();
	int getMX();
	Rect GetFontRect() { return m_fontRect; }
	Widget* getStoneLottery() const {return m_StoneLottery;};
	static bool CheckActivityOpenAtLeastOne();// check at least one activity open

protected:
	int                                               m_curTab;
	typedef std::map<int, class FestivalEventTabBase*> MapTabs;
	MapTabs                                           m_mapTab;

public:
    static int                                        s_ShowTab;
    std::map<FestivalTab, int> m_activityList;
	std::vector<FestivalTab> m_eventPriorityList;// for sort btns
    std::vector<FestivalEntryData> m_entryDatas;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onNotifyAwardPlantID(bool i_success);

	void SortTabBtns(std::vector<PVZ2UIButton*>& btnList);
	virtual void InitActivityID();

protected:
	Rect m_fontRect;
	Widget* m_StoneLottery;
	SexyString m_title;
	
	class DailySignUI* m_DailySignPage;
};

// new icon : for recharge welfare ui
class RechargeWelfareUI : public UISingletonDialog<RechargeWelfareUI>, public Sexy::ScrollWidgetListener
{
public:
	RechargeWelfareUI();
	virtual ~RechargeWelfareUI();
	
	virtual bool							OnCreate() override;
	virtual std::string GetLayoutName() override { return "WelfareEventUI"; };
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							Update() override;

	// ButtonListener
	virtual void							ButtonDepress(int i_id) override;
	// implement of Sexy::ScrollWidgetListener
	virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void                                    SetCurrentTab(int iTab);
	int										GetCurrentTab() const { return m_curTab; }
	Sexy::Widget*                           GetTabContent();
	void                                    Layout();

	void                                    DisabledAllButtons();
	void                                    EnabledAllButtons();

	UIWidgetText*							GetCostTextWidget();

	void loadData();
	void InitView();
	void SyncActivityData(const NetworkFestivalEntryInfo& i_info);
	bool HasTargetActivityOpen(FestivalTab i_tabId);
	bool CheckTargetActivityItem(int i_activityId);
	int getWidth();
	int getMX();
	Rect GetFontRect() { return m_fontRect; }
	Widget* getStoneLottery() const {return m_StoneLottery;};
	static bool CheckActivityOpenAtLeastOne();// check at least one activity open
	static bool CheckAnyNotReceivedReward();

protected:
	int                                               m_curTab;
	typedef std::map<int, class FestivalEventTabBase*> MapTabs;
	MapTabs                                           m_mapTab;

public:
    static int                                        s_ShowTab;
    std::map<FestivalTab, int> m_activityList;
	std::vector<FestivalTab> m_eventPriorityList;// for sort btns
    std::vector<FestivalEntryData> m_entryDatas;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onNotifyAwardPlantID(bool i_success);

	void SortTabBtns(std::vector<PVZ2UIButton*>& btnList);
	virtual void InitActivityID();

protected:
	Rect m_fontRect;
	Widget* m_StoneLottery;
	SexyString m_title;
	
	class DailySignUI* m_DailySignPage;
};

class FestivalDayConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(FestivalDayConfig, RtObject, RtClass);
	FestivalDayConfig() {}

public:
	bool isFestivalDaysBossRushOpen;
	bool isFestivalDaysLotteryOpen;
	bool isFestivalDaysLoginRewardOpen;
	bool isFestivalDaysBundleSaleOpen;
};

class OneYuanTabUI : public FestivalEventTabBase//, public ButtonListener
{
public:
	OneYuanTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~OneYuanTabUI();

    virtual void SetSelect(bool setting) override;

    virtual void Update() override;
    virtual void DrawBackground(class Sexy::Graphics* i_g) override;
    virtual void DrawForeground(Sexy::Graphics* i_g) override;
    void SyncActivityTime() override;
    void AddExternalWidget(Widget* i_widget) override;
	void SyncActivityData(int i_endDate) override;
	std::string GetTabContainerImageName() const override;

private:
    void InitView();
    void InitTestData();

private:
    Image* m_background = nullptr;
    time_t m_expireTime;
    bool m_hasInit;
    Widget* m_innerWidget;
    time_t m_endTime;
	std::string m_containerBG;
};

class CrackerTabUI : public FestivalEventTabBase//, public ButtonListener
{
public:
	CrackerTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~CrackerTabUI();

    virtual void SetSelect(bool setting) override;

    virtual void Update() override;
    virtual void DrawBackground(class Sexy::Graphics* i_g) override;
    virtual void DrawForeground(Sexy::Graphics* i_g) override;
    virtual void SyncActivityTime() override;
    void AddExternalWidget(Widget* i_widget) override;
	virtual void SyncActivityData(int i_endDate) override;
	bool IsInit() { return m_hasInit; }
	virtual std::string GetTabContainerImageName() const override
	{
		return "";
	}
	Widget* GetExternalWidget() { return m_innerWidget; }
	void RemoveExternalWidget();

protected:
    void InitView();
    void InitTestData();

protected:
    Image* m_background = nullptr;
    time_t m_expireTime;
    bool m_hasInit;
    Widget* m_innerWidget;
    time_t m_endTime;
};

class CrackerTabUI_PlantTree : public CrackerTabUI
{
public:
	CrackerTabUI_PlantTree(int i_tab, class UI::Dialog* pCenterDlg);
	virtual ~CrackerTabUI_PlantTree();

	std::string GetTabContainerImageName() const override { return "IMAGE_UI_FESTIVALCENTER_LOTTERY_BG"; }
    void DrawForeground(Sexy::Graphics* i_g) override;
	void SyncActivityTime() override;
	void SyncActivityData(int i_endDate) override;
    void SetSelect(bool setting) override;
};

struct New_S2C_Lottery
{
    int32 itemId = 0;
    int32 amount = 0;
};

class New_S2C_LotteryReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_LotteryReward, INetworkData, RtClass);

    int32                         m_plantIndex;
    std::vector<New_S2C_Lottery>   m_prizeInfos;
};

class UILotteryResult:public DNodeWidget
{
public:
    static UILotteryResult* create(const std::map<int,int>& reward,const std::vector<int>& list,bool focus = true);
    static UILotteryResult* create(bool focus = true);

    virtual ~UILotteryResult();

    virtual void Initialize() override;

    virtual void UserInit() override;

public:
    static UILotteryResult* s_pWidgetHandler;
    std::map<int,int>         m_mergeItemInfo;
    std::vector<int>          m_list;
};

class FestivalLotteryTab : public FestivalEventTabBase
{
public:
	FestivalLotteryTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~FestivalLotteryTab();

	enum EventStatus
	{
		EventStatus_Open,
		EventStatus_Closed
	};

    std::string GetTabContainerImageName() const override
    {
        return "IMAGE_UI_FESTIVALCENTER_LOTTERY_EVENT_BG";
    }
    SexyString  GetGoToButtonTitle() override;

	virtual void		OnButtonClicked(int i_id) override;
	virtual void		SetSelect(bool setting) override;
	virtual void        DrawForeground(class Sexy::Graphics* i_g) override;
	virtual void		Update() override;
	void SyncActivityData(const NetworkLotteryInfo& i_data, int i_endDate, bool i_open) override;
	void DisableTabs(bool i_disable);

protected:
	void                setupScreen();

    void                DoLottery();
    //void                PickGachaReward(const std::vector<GachaRewardItem>& rewards);

    void                onAnimCommand(const std::string& i_animLabel,
                                      pvztime_t i_timeStamp,
                                      const std::string& i_animCommand,
                                      const std::string& i_animCommandParam);

    void                onGotChristmasLottery(bool i_success,int32 i_chipid,int32 i_count);

private:
    Rect                m_contentRect;
    Effect_PopAnim *    m_popAnimEffect;
    bool                m_bButtonCanClicked;

    EventStatus  		m_StatusActivity;

    time_t              m_endTime;
    SexyString          m_daysDes;
    SexyString          m_timeDes;

    int32               m_chipid;
    int32               m_count;

    // New lottery
    int32				m_gemCost;
    int32				m_plantIndex;
    int32				m_endDate;
    bool				m_open;
};


class SpringLoginTabUI : public FestivalEventTabBase//, public ButtonListener
{
public:
	SpringLoginTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~SpringLoginTabUI();

    virtual void SetSelect(bool setting) override;

    virtual void Update() override;
    virtual void DrawBackground(class Sexy::Graphics* i_g) override;
    virtual void DrawForeground(Sexy::Graphics* i_g) override;
    void SyncActivityTime() override;
    void AddExternalWidget(Widget* i_widget) override;

private:
    void InitView();
    void InitTestData();

private:
    Image* m_background = nullptr;
    time_t m_expireTime;
    bool m_hasInit;
    Widget* m_innerWidget;
};

class MonthlyCardTab: public FestivalEventTabBase
{
public:
	MonthlyCardTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~MonthlyCardTab();

	std::string GetTabContainerImageName() const override
	{
		return "IMAGE_UI_FESTIVALCENTER_MONTHLY_CARD_BG";
	}
	SexyString  GetGoToButtonTitle() override;

	virtual void SetSelect(bool setting) override;
	virtual void DrawForeground(Sexy::Graphics* i_g) override;
	void SyncActivityData(int i_endDate) override;
	time_t m_expireTime;
};

class YuanBaoEventTab: public FestivalEventTabBase
{
public:
	YuanBaoEventTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~YuanBaoEventTab();

	std::string GetTabContainerImageName() const override
	{
		return "IMAGE_UI_FESTIVALCENTER_YUANBAO_EVENT_BG";
	}
	SexyString  GetGoToButtonTitle() override;

	virtual void SetSelect(bool setting) override;
	virtual void DrawForeground(Sexy::Graphics* i_g) override;
	void SyncActivityData(int i_endDate) override;
	time_t m_endTime;
};

class SecretGachaTab: public YuanBaoEventTab
{
public:
	SecretGachaTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~SecretGachaTab();

	std::string GetTabContainerImageName() const override
	{
		return "IMAGE_UI_FESTIVALCENTER_SECRET_GACHA_EVENT";
	}

	virtual void DrawForeground(Sexy::Graphics* i_g) override;
	void SyncActivityData(int i_endDate) override;
};

enum RedPacketType
{
	Type_Free,
	Type_Gem,
	Type_Vip,
	Type_Count
};

enum RedPacketIndex
{
	R_Free_1,
	R_Free_2,
	R_Free_3,
	R_Gem,
	R_Vip
};

class RedPacketWidget : public PVZ2UIButton, public ButtonListener
{
public:
	RedPacketWidget(RedPacketType i_type, int i_id, bool i_open, RedPacketIndex i_index);
    ~RedPacketWidget();
public:
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonPress(int i_id) override;
    virtual void ButtonDepress(int i_id) override;
    void SetHasOpen(bool i_open) { m_hasOpened = i_open; }
    void requestOpenRedPacket(int num, int i_index);
    bool CheckOpenCondition();
    void SetCost(int i_cost) { m_cost = i_cost; }
private:
    bool m_hasOpened;
    RedPacketType m_type;
    RedPacketIndex m_index;
    int m_cost;
};

class RedPacketTab: public FestivalEventTabBase
{
public:
	RedPacketTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~RedPacketTab();

	std::string GetTabContainerImageName() const override
	{
		return "IMAGE_UI_FESTIVALCENTER_YUANBAO_EVENT_BG";
	}
	SexyString  GetGoToButtonTitle() override;

	virtual void SetSelect(bool setting) override;
	virtual void DrawForeground(Sexy::Graphics* i_g) override;
	void DrawGemLabel(Sexy::Graphics* i_g);
	void DrawVipLabel(Sexy::Graphics* i_g);
	void InitView();
	void ResetWidgets();
	void RefreshRedPackets();
	void SetWidgetsVisible(bool i_visible);
	void SyncActivityData(const NetworkRedPacketInfo& i_data, int i_endDate, bool i_open);
	void ResetDatas();
	bool HasTargetRedPacketOpen(RedPacketIndex i_index);
	time_t m_endTime;
	//RedPacketWidget* m_innerWidget = nullptr;
	std::vector<RedPacketWidget*> m_redpackets;
	bool m_hasInit;
	std::vector<int> m_packetsState;
	int m_gemPacketCost;
};

class FestivalRechargeTabUI : public FestivalEventTabBase
{
public:
	FestivalRechargeTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~FestivalRechargeTabUI();

    std::string GetTabContainerImageName() const override
	{
		return "";
	}

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget) override;

private:
    Widget* m_innerWidget;
    bool m_hasInit;
};

class WeeklyRechargeRewardPage : public UISingletonDialog<WeeklyRechargeRewardPage>
{
public:
	WeeklyRechargeRewardPage();
	virtual ~WeeklyRechargeRewardPage();

	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIWeeklyRechargeRewardPage"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void showGemStore();
	void Update() override;
	void defalutUI();
	void InitView();
protected:

	const int c_chargeLevel = 5;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	// for tga log
	int _plantID;
	int _rechargeMoney;
	int _gemsReward;
	int _pieceRewardCount;
};

class FestivalGameTabUI : public FestivalEventTabBase//, public ButtonListener
{
public:
	FestivalGameTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~FestivalGameTabUI();

	std::string GetTabContainerImageName() const override
	{
		return "";
	}

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget) override;

private:
    Widget* m_innerWidget;
    bool m_hasInit;
};

class FestivalGamePage : public UISingletonDialog<FestivalGamePage>
{
public:
	FestivalGamePage();
	virtual ~FestivalGamePage();

	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIFestivalGamePage"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void showFestivalGameEntrance();
	void Update() override;
	void InitView();
protected:
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
};

// another same page for different activity open at same time
class FestivalGamePageExtra : public UISingletonDialog<FestivalGamePageExtra>
{
public:
	FestivalGamePageExtra();
	virtual ~FestivalGamePageExtra();

	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIFestivalGamePageExtra"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	virtual void 				Update() override;

	virtual void 				showFestivalGameEntrance();
	virtual void 				InitView();
	virtual void 				ShowErrorDialog();

protected:
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};

// new icon
class FestivalGamePageMiniGame : public UISingletonDialog<FestivalGamePageMiniGame>
{
public:
	FestivalGamePageMiniGame();
	virtual ~FestivalGamePageMiniGame();

	std::string         GetLayoutName() override { return "UIFestivalGamePageMiniGame"; }
	virtual void 				showFestivalGameEntrance();

	virtual bool                OnCreate() override;
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	virtual void 				Update() override;

	virtual void 				InitView();
	virtual void 				ShowErrorDialog();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};

class FestivalGamePageAnniversaryTreasure : public UISingletonDialog<FestivalGamePageAnniversaryTreasure>
{
public:
	FestivalGamePageAnniversaryTreasure();
	virtual ~FestivalGamePageAnniversaryTreasure();

	std::string         GetLayoutName() override { return "UIFestivalGamePageAnniversaryTreasure"; }
	virtual void 				showFestivalGameEntrance();

	virtual bool                OnCreate() override;
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	virtual void 				Update() override;

	virtual void 				InitView();
	virtual void 				ShowErrorDialog();

protected:
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};

class FestivalGamePageLuckyBag : public UISingletonDialog<FestivalGamePageLuckyBag>
{
public:
	FestivalGamePageLuckyBag();
	virtual ~FestivalGamePageLuckyBag();

	std::string         GetLayoutName() override { return "UIFestivalGamePageLuckyBag"; }
	virtual void 				showFestivalGameEntrance();

	virtual bool                OnCreate() override;
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	virtual void 				Update() override;

	virtual void 				InitView();
	virtual void 				ShowErrorDialog();

protected:
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};

class FestivalGamePageSecretStore : public UISingletonDialog<FestivalGamePageSecretStore>
{
public:
	FestivalGamePageSecretStore();
	virtual ~FestivalGamePageSecretStore();

	std::string         GetLayoutName() override { return "UIFestivalGamePageSecretStore"; }
	virtual void 				showFestivalGameEntrance();
	
	virtual bool                OnCreate() override;
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	virtual void 				Update() override;

	virtual void 				InitView();
	virtual void 				ShowErrorDialog();

protected:
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};

class FestivalGamePageFightZodiac : public UISingletonDialog<FestivalGamePageFightZodiac>
{
public:
	FestivalGamePageFightZodiac();
	virtual ~FestivalGamePageFightZodiac();

	std::string         GetLayoutName() override { return "UIFestivalGamePageFightZodiac"; }
	virtual void 				showFestivalGameEntrance();

	virtual bool                OnCreate() override;
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	virtual void 				Update() override;

	virtual void 				InitView();
	virtual void 				ShowErrorDialog();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};

class FestivalGamePageBattleOrder : public UISingletonDialog<FestivalGamePageBattleOrder>
{
public:
	FestivalGamePageBattleOrder();
	~FestivalGamePageBattleOrder();
	std::string GetLayoutName() override { return "FestivalGamePageBattleOrder"; }
	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void Update() override;
	virtual void ButtonDepress(int i_id) override;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	bool m_thisRequest;
};

class FestivalGamePageLimitedSummon : public UISingletonDialog<FestivalGamePageLimitedSummon>
{
public:
	FestivalGamePageLimitedSummon();
	~FestivalGamePageLimitedSummon();
	std::string GetLayoutName() override { return "FestivalGamePageLimitedSummon"; }
	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void Update() override;
	virtual void ButtonDepress(int i_id) override;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	bool m_thisRequest;
};

class FestivalGamePageCarnival : public UISingletonDialog<FestivalGamePageCarnival>
{
public:
	FestivalGamePageCarnival();
	~FestivalGamePageCarnival();
	std::string GetLayoutName() override { return "FestivalGamePageCarnival"; }
	
	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void Update() override;
	virtual void ButtonDepress(int i_id) override;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	bool m_thisRequest;
};

class FestivalGamePageNewYearGoods : public UISingletonDialog<FestivalGamePageNewYearGoods>
{
public:
	FestivalGamePageNewYearGoods();
	~FestivalGamePageNewYearGoods();
	std::string GetLayoutName() override { return "FestivalGamePageNewYearGoods"; }
	
	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void Update() override;
	virtual void ButtonDepress(int i_id) override;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	bool m_thisRequest;
};

class DefaultTabUI : public FestivalEventTabBase
{
public:
	DefaultTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~DefaultTabUI();

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget) override;

private:
    Widget* m_innerWidget;
    bool m_hasInit;
};

struct ConsumeAndReceiveReward
{
    int PlantId;
    int Amount;
    int Gems;
    int Received;
};

class NetworkConsumeAndReceive : public INetworkData
{
RT_CLASS_DEFINE(NetworkConsumeAndReceive, INetworkData, RtClass);

    int BannerId;
    std::vector<ConsumeAndReceiveReward> List;
    int Number;
};

class ConsumeAndReceiveItemWidget : public Widget
{
public:
    ConsumeAndReceiveItemWidget();
    virtual ~ConsumeAndReceiveItemWidget();
public:
    virtual void			Resize(const Rect& i_Rect) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;

	void 					LoadData(int i_pos, int i_id, int i_amount, int i_gems, bool i_canAward);
    void                    SetMask(Widget* i_mask);
	
private:
    int32                   m_touchId;
	int						m_pos;
	int						m_awardId;
    int                     m_amount;
    int                     m_gems;
    bool                    m_canAward;
	ImagePtr				m_image;
    Sexy::Widget*           m_mask;
};

class ConsumeAndReceivePage : public UISingletonDialog<ConsumeAndReceivePage>
{
public:
	ConsumeAndReceivePage();
	virtual ~ConsumeAndReceivePage();
public:
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIConsumeAndReceivePage"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void 				Update() override;

	void 						InitView();
	void						InitTestData(NetworkConsumeAndReceive& i_data);
	void						UpdateTimer();
	void						UpdateInfo();
	void						OnNotifiedReceiveMessage(bool flag,const S2C_PiggyBankReward * pdata);

    static bool                 HasAnyNotReceivedReward();

protected:
	const int c_chargeLevel = 5;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	std::vector<ConsumeAndReceiveItemWidget*> m_widgetVec;
};

class LimitGroupBuyPage : public UISingletonDialog<LimitGroupBuyPage>
{
public:
	LimitGroupBuyPage();
	virtual ~LimitGroupBuyPage();

	virtual void 				Update() override;
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIFestivalGroupBuy"; }
	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
};

class CustomVotingPage : public UISingletonDialog<CustomVotingPage>
{
public:
	CustomVotingPage();
	virtual ~CustomVotingPage();

	virtual void 				Update() override;
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIFestivalCustomVoting"; }
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
private:
	bool m_notifyFlag;
};

class GenericFestivalPage : public UISingletonDialog<GenericFestivalPage>
{
public:
	GenericFestivalPage();
	virtual ~GenericFestivalPage();

	virtual void 				Update() override;
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIGenericFestivalPage"; }
	virtual void                ButtonDepress(int i_id) override;

	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void setData(int i_activityId, bool i_needRequest = false);

private:
	void doAction();

	int m_activityId;
	bool m_needRequest;
	bool m_notifyFlag;
};


class GoldenEggPage : public UISingletonDialog<GoldenEggPage>
{
public:
	GoldenEggPage();
	virtual ~GoldenEggPage();

	virtual void 				Update() override;
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "GoldenEggPage"; }
	virtual void                ButtonDepress(int i_id) override;

	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
	bool m_notifyFlag;
};

#endif /* FESTIVALEVENTUI_H_ */
