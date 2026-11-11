//
//  DaveClubUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/23.
//  Copyright (c) 2015�� PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NationalHolidayUI__
#define __PlantsVersusZombies2__NationalHolidayUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
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
#include "UIDoubleFestivalActivity.h"

namespace Message
{
	void NotifyInputEnable(bool enable);
}

enum NationalTab
{
	NTab_Begin = 1,

	NTab_Shop    = 1,
	NTab_BossRush = 2,
	NTab_NewLogin = 3,
	NTab_NationalLottery = 4,
	NTab_RechargeBundle = 5,
	NTab_7Day = 6,

	NTab_End,
};

struct NetworkNationalEntryData
{
	NetworkNationalEntryData()
	{
		ActivityID = 0;
		Sequence = 0;
		Open = false;
	}

	int ActivityID;
	int Sequence;
	bool Open;
};

//struct NetworkShopContentData
//{
//	NetworkShopContentData()
//	{
//		ItemId = 0;
//		Amount = 0;
//		Price = 0;
//		SellOut = 0;
//	}
//
//	int ItemId;
//	int Amount;
//	int Price;
//	int SellOut;
//};

class NetworkEntryInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkEntryInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<NetworkNationalEntryData>     entryInfos;
};



struct NationalEntryData
{
	NationalEntryData()
	{
		ActivityID = 0;
		Sequence = 0;
		Open = false;
	}

	int ActivityID;
	int Sequence;
	bool Open;
};

//class NetworkShopInfo : public Sexy::RtObject
//{
//public:
//    RT_CLASS_DEFINE(NetworkShopInfo, Sexy::RtObject, Sexy::RtClass);
//
//public:
//    std::vector<NetworkShopContentData>     shopInfos;
//};

class NationalHolidayTabBase
{
public:
	NationalHolidayTabBase(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~NationalHolidayTabBase();

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
    virtual void SyncActivityData(const NetworkShopInfo& i_data) {}
    virtual void SyncActivityTime() {}
    virtual void AddExternalWidget(Widget* i_widget) {}
    virtual void AddExternalWidget(Widget* i_widget, UIWidgetText* activityTime) {}

protected:
	int						m_tabID;
	class UI::Dialog*		m_pCenterDlg;
	class PVZ2UIButton*     m_pTabBtn;
	class UIWidgetImage*	m_pTabContainer;
};

class NationalHolidayUI : public UISingletonDialog<NationalHolidayUI>, public Sexy::ScrollWidgetListener
{
public:
	NationalHolidayUI();
	virtual ~NationalHolidayUI();
	virtual bool							OnCreate() override;
    virtual void                          OnClose() override;
	virtual std::string                     GetLayoutName() override { return "NationalHolidayUI"; }
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

	void loadData();
	void InitView();
	void SyncActivityData(const NetworkEntryInfo& i_info);
	bool HasTargetActivityOpen(NationalTab i_tabId);
	bool CheckTargetActivityItem(int i_activityId);
	int getWidth();
	int getMX();
protected:
	int                                               m_curTab;
	typedef std::map<int, class NationalHolidayTabBase*> MapTabs;
	MapTabs                                           m_mapTab;

public:
    static int                                        s_ShowTab;
    std::map<NationalTab, ActivityTypeID> m_activityList;
    std::vector<NationalEntryData> m_entryDatas;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onNotifyAwardPlantID(bool i_success);
	void onNotifyInputEnable(bool enable);

private:
	Widget* m_StoneLottery;
	class UILimitLotteryPage* m_LotteryPage;
	class DailySignUI* m_DailySignPage;
	class RechargeRewardPage* m_RechargeRewardPage;
public:
	Widget* getNDStoneLottery() const {return m_StoneLottery;};
};

class LotteryTabUI : public NationalHolidayTabBase//, public ButtonListener
{
public:
	LotteryTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~LotteryTabUI();

    virtual void SetSelect(bool setting) override;

    virtual void Update() override;
    virtual void DrawBackground(class Sexy::Graphics* i_g) override;
    virtual void DrawForeground(Sexy::Graphics* i_g) override;
    void SyncActivityTime() override;
    void AddExternalWidget(Widget* i_widget) override;

private:
    void InitView();

private:
    Image* m_background = nullptr;
    time_t m_expireTime;
    bool m_hasInit;
    Widget* m_innerWidget;
};

class BossRushTabUI : public NationalHolidayTabBase//, public ButtonListener
{
public:
	BossRushTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~BossRushTabUI();

    virtual void SetSelect(bool setting) override;
    virtual void Update() override;
    void SyncActivityTime() override;

private:
    void InitView();

private:
    Image* m_background = nullptr;
    time_t m_expireTime;
    UIWidgetText* m_pTimeTxt;
    int m_OriginalWidth;
    int m_OriginalHeight;
};

class RechargeTabUI : public NationalHolidayTabBase//, public ButtonListener
{
public:
	RechargeTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~RechargeTabUI();

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget) override;

private:
    Widget* m_innerWidget;
    bool m_hasInit;
};

class NationalShopPanel : public Widget
{
public:
	NationalShopPanel(Rect &i_rect, int i_contentSize, UIWidgetImage* i_container, std::vector<NetworkShopContentData>& i_datas);
    ~NationalShopPanel();

    void RefreshShopData(const std::vector<NetworkShopContentData>& i_data);

    void Draw(Sexy::Graphics* i_g) override;
private:

    void	InitView();
    int     m_contentSize;

    std::vector<class NationalShopContent*> m_contents;
    UIWidgetImage*	m_pTabContainer;
    std::vector<NetworkShopContentData> m_shopContentDatas;
};

// shop ui
class NationalShopUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	NationalShopUI(UIWidgetImage* i_container, std::vector<NetworkShopContentData>& i_datas, float expireTime);
    ~NationalShopUI();

    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	void InitView();
	void RefreshShopData(const std::vector<NetworkShopContentData>& i_data);
private:
	float m_expireTime;
	PVZ2UIScrollingWidget* m_scrollingWidget;
	UIWidgetImage*	m_pTabContainer;
	std::vector<NetworkShopContentData> m_shopContentDatas;
	NationalShopPanel* m_panel;
};

class NationalShopContent : public Widget, Sexy::ButtonListener
{
public:
	NationalShopContent(NetworkShopContentData &i_data, NationalShopPanel* i_panel);
    ~NationalShopContent();

    virtual void	Update() override;
    virtual void	Draw(Sexy::Graphics* i_g) override;
    virtual void	MouseUp(int x, int y) override;
    void	InitView();
    void RefreshContentData(const NetworkShopContentData& i_data);
    void UpdateExchangeItemLog(int i_itemId, int i_itemAmount, int i_materialCost, int i_materialBeforeBuy);

protected:
	void onNotifyShopBuyFinish(bool success, int shop);
    void BuyItem();

private:
    NetworkShopContentData m_ShopContentData;
    NationalShopPanel* m_panel;
    class UIRewardFrame* m_reward;
    SexyString m_strName;
    class UIWidgetImage* m_soldout;
    bool m_purchasing;
    int m_matNumBeforeBuy;
};

class ShopTabUI : public NationalHolidayTabBase
{
public:
	ShopTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~ShopTabUI();

    virtual void SetSelect(bool setting) override;

    void SyncActivityData(const NetworkShopInfo& i_data) override;
    void RefreshShopData(const std::vector<NetworkShopContentData>& i_data);

private:
    void InitView();

private:
    NationalShopUI* m_innerWidget = nullptr;
    Point m_panelPt;
    std::vector<NetworkShopContentData> m_shopContentDatas;
    bool m_hasInit;
    time_t m_expireTime;
};

class NewLoginTabUI : public NationalHolidayTabBase//, public ButtonListener
{
public:
	NewLoginTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~NewLoginTabUI();

    void Update() override;

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget, UIWidgetText* activityTime) override;

private:
    Widget* m_innerWidget;
    bool m_hasInit;
    UIWidgetText* m_pActivityTime;
};

class StoneLotteryTabUI : public NationalHolidayTabBase//, public ButtonListener
{
public:
	StoneLotteryTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~StoneLotteryTabUI();

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget) override;

private:
    Widget* m_innerWidget;
    bool m_hasInit;
};

class RechargeRewardPage : public UISingletonDialog<RechargeRewardPage>
{
public:
	RechargeRewardPage();
	virtual ~RechargeRewardPage();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIRechargeRewardPage"; }
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
	UIWidgetText* m_pRefrashTime;
	SexyString m_timeLabel = _S("");
	SexyString m_refrashTimeLabel = _S("");
	Color m_timeColor = Color::White;
};

#endif /* defined(__PlantsVersusZombies2__DaveClubUI__) */
