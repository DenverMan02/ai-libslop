//
//  DaveClubUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/23.
//  Copyright (c) 2015�� PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__OppoNewerEventUI__
#define __PlantsVersusZombies2__OppoNewerEventUI__

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

enum OppoNewerTab
{
	OTab_Begin = 1,

	OTab_NewLogin = 1,
	OTab_RechargeBundle = 2,

	OTab_End,
};

class OppoNewerEventUI;

typedef void(OppoNewerEventUI::*TabFunc)();

class OppoNewerTabBase
{
public:
	OppoNewerTabBase(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~OppoNewerTabBase();

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
    virtual void AddExternalWidget(Widget* i_widget) {}

protected:
	int						m_tabID;
	class UI::Dialog*		m_pCenterDlg;
	class PVZ2UIButton*     m_pTabBtn;
	class UIWidgetImage*	m_pTabContainer;
};

class OppoNewerEventUI : public UISingletonDialog<OppoNewerEventUI>, public Sexy::ScrollWidgetListener
{
public:
	OppoNewerEventUI();
	virtual ~OppoNewerEventUI();
	virtual bool							OnCreate();
	virtual std::string                     GetLayoutName() { return "OppoNewerEventUI"; }
	virtual void							Draw(Sexy::Graphics* i_g);
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g);
	virtual void							Update();

	// ButtonListener
	virtual void							ButtonDepress(int i_id) override;
	// implement of Sexy::ScrollWidgetListener
	virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

	void                                    SetCurrentTab(int iTab);
	int										GetCurrentTab() const { return m_curTab; }
	Sexy::Widget*                           GetTabContent();
	void                                    Layout();

	void                                    DisabledAllButtons();
	void                                    EnabledAllButtons();

	UIWidgetText*							GetCostTextWidget();

	void loadData();
	void InitView();
	int getWidth();
	int getMX();
protected:
	int                                               m_curTab;
	typedef std::map<int, class OppoNewerTabBase*> MapTabs;
	MapTabs                                           m_mapTab;

public:
    static int                                        s_ShowTab;

    std::map<OppoNewerTab, TabFunc> m_TabFunc;

protected:
	void onRechargeRewardTab();
	void onDailyRewardTab();
};

class OppoNewerRechargeTabUI : public OppoNewerTabBase
{
public:
	OppoNewerRechargeTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~OppoNewerRechargeTabUI();

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget);

private:
    Widget* m_innerWidget;
    bool m_hasInit;
};

class OppoNewerNewLoginTabUI : public OppoNewerTabBase
{
public:
	OppoNewerNewLoginTabUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~OppoNewerNewLoginTabUI();

    virtual void SetSelect(bool setting) override;
    void AddExternalWidget(Widget* i_widget);

private:
    Widget* m_innerWidget;
    bool m_hasInit;
};

#endif /* defined(__PlantsVersusZombies2__DaveClubUI__) */
