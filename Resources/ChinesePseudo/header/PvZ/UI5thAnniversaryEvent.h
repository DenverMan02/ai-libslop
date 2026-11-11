//
//  UI5thAnniversaryEvent.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UI5thAnniversaryEvent_h_
#define _UI5thAnniversaryEvent_h_

#include "UISingletonDialog.h"
#include "FestivalEventUI.h"

enum UI5thTab
{
	NTab_Shop5th,
	NTab_BossRush5th,

};

class UI5thAnniversaryEvent : public UISingletonDialog<UI5thAnniversaryEvent>, public Sexy::ScrollWidgetListener
{
public:
	UI5thAnniversaryEvent();
	virtual ~UI5thAnniversaryEvent();
	virtual bool							OnCreate() override;
	virtual std::string                     GetLayoutName() override { return "UI5thAnniversary"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							Update() override;

	// ButtonListener
	virtual void							ButtonDepress(int i_id) override;
	// implement of Sexy::ScrollWidgetListener
	virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	virtual void                                    SetCurrentTab(int iTab);
	int										GetCurrentTab() const { return m_curTab; }
	Sexy::Widget*                           GetTabContent();
	void                                    Layout();

	void                                    DisabledAllButtons();
	void                                    EnabledAllButtons();

	UIWidgetText*							GetCostTextWidget();

	void loadData();
	virtual void InitView();
	void SyncActivityData(const NetworkFestivalEntryInfo& i_info);
	virtual bool HasTargetActivityOpen(UI5thTab i_tabId);
	bool CheckTargetActivityItem(int i_activityId);
	int getWidth();
	int getMX();
	Rect GetFontRect() { return m_fontRect; }
protected:
	int                                               m_curTab;
	typedef std::map<int, class FestivalEventTabBase*> MapTabs;
	MapTabs                                           m_mapTab;

public:
    static int                                        s_ShowTab;
    std::map<UI5thTab, ActivityTypeID> m_activityList;
    std::vector<FestivalEntryData> m_entryDatas;

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onNotifyAwardPlantID(bool i_success);
	Rect m_fontRect;
private:
};

class BossRushTabUI5th : public FestivalEventTabBase//, public ButtonListener
{
public:
	BossRushTabUI5th(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~BossRushTabUI5th();

    virtual void SetSelect(bool setting) override;

    virtual void Update() override;
    virtual void DrawBackground(class Sexy::Graphics* i_g) override;
    virtual void DrawForeground(Sexy::Graphics* i_g) override;
    void SyncActivityTime() override;
    void AddExternalWidget(Widget* i_widget) override;
	void SyncActivityData(int leftDays) override;
	std::string GetTabContainerImageName() const override
	{
		return "IMAGE_UI_5THANNIVERSARY_ACTIVITY_BG";
	}

private:
    void InitView();
    void InitTestData();

private:
    Image* m_background = nullptr;
    time_t m_expireTime;
    bool m_hasInit;
    Widget* m_innerWidget;
    time_t m_endTime;
	int m_nLeftDays;
	bool m_bIsFixed;
};

//shop widgets
struct fthShopContentData
{
	fthShopContentData()
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

class fthShopPanel : public Widget
{
public:
	fthShopPanel(Rect &i_rect, int i_contentSize, UIWidgetImage* i_container, std::vector<fthShopContentData>& i_datas);
    ~fthShopPanel();

    void RefreshShopData(const std::vector<fthShopContentData>& i_data);
private:

    void	InitView();
    void 	InitTestData();
    int     m_contentSize;

    std::vector<class fthShopContent*> m_contents;
    UIWidgetImage*	m_pTabContainer;
    std::vector<fthShopContentData> m_shopContentDatas;
};

// shop ui
class fthShopUI : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:

	fthShopUI(UIWidgetImage* i_container, std::vector<fthShopContentData>& i_datas);
    ~fthShopUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

	void InitView();
	void HideWidgets(bool i_hide);
	void RefreshShopData(const std::vector<fthShopContentData>& i_data);
private:
	void InitTestData();
	PVZ2UIScrollingWidget* m_scrollingWidget;
	UIWidgetImage*	m_pTabContainer;
	std::vector<fthShopContentData> m_shopContentDatas;
	fthShopPanel* m_panel;
	time_t m_endTime;
};

struct fthShopItemData
{
	fthShopItemData()
	{
		Amount = 0;
		ObjectId = 0;
	}

	int Amount;
	int ObjectId;
};

class fthShopItemContent : public Sexy::Widget
{
public:

	fthShopItemContent(const fthShopItemData & data);
	virtual ~fthShopItemContent();

	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    void RefreshContentData(const fthShopItemData& i_data) { m_data = i_data; }

private:

    void            setupScreen();

private:

    fthShopItemData  m_data;
};

class fthShopContent : public Widget, Sexy::ButtonListener
{
public:
	fthShopContent(fthShopContentData &i_data, fthShopPanel* i_panel);
    ~fthShopContent();

    virtual void	Update() override;
    void DrawTargetMaterial(Sexy::Graphics* i_g, int i_x, int i_y, int i_id, int i_index);
    virtual void	Draw(Sexy::Graphics* i_g) override;
    virtual void	ButtonDepress(int i_id) override;
    void	InitView();
    void RefreshContentData(const fthShopContentData& i_data);
    void onMaterialChanged();
    bool CheckEnoughMaterials();
    void ConsumeMaterials();
private:
    fthShopContentData     m_ShopContentData;
    fthShopPanel* m_panel;
    PVZ2UIButton* m_purchaseButton;
    Rect m_matBgPt;
    fthShopItemContent* m_shopContent;
};

class fthShopTabUI : public FestivalEventTabBase, public Sexy::ScrollWidgetListener//, public ButtonListener
{
public:
	fthShopTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~fthShopTabUI();

    virtual void SetSelect(bool setting) override;

    virtual void Update() override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void DrawForeground(Sexy::Graphics* i_g) override;
    virtual void DrawSpecial(Sexy::Graphics* i_g) override;

    void SyncActivityData(const NetworkfthShopInfo& i_data);
    void RefreshShopData(const std::vector<fthShopContentData>& i_data);

private:
    void InitView();
    void AddScrollingWidget();

private:
    fthShopUI* m_innerWidget = nullptr;
    //PVZ2UIScrollingWidget* m_scrollingWidget;
    Point m_textPt;
    Point m_panelPt;
    std::vector<fthShopContentData> m_shopContentDatas;
    bool m_hasInit;
    time_t m_expireTime;
    Rect m_textRect;
};


#endif
