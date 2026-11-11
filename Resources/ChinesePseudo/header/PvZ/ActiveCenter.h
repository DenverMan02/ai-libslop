//
//  ActiveCenter.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.13.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _ActiveCenter_h_
#define _ActiveCenter_h_

#include "UIEditor/UISingletonDialog.h"
#include "PVZ2UIButton.h"

enum ActiveCenterTab
{
	ACTab_Begin = 1,
    
    /*
	ACTab_Boss = 1,
	ACTab_DangerRoom = 2,
	ACTab_DoublePlantPiece = 3,
	ACTab_DoubleAvatarPiece = 4,
	ACTab_DailyAchievement = 5,
	ACTab_Recharge = 6,
	ACTab_ConsumptionReward = 7,
	ACTab_NationalDayDraw = 8,
    */
    
    ACTab_ChristmasProtect = 1,
	ACTab_ChristmasLottery = 2,
    ACTab_ChristmasGoldEgg = 3,
    ACTab_ChristmasGift    = 4,
    ACTab_ChristmasRebates = 5,
    ACTab_ChristmasLantern = 6,
    
	ACTab_End,
};

class ActiveCenter : public UISingletonDialog<ActiveCenter>, public Sexy::ScrollWidgetListener
{
public:
	ActiveCenter();
	virtual ~ActiveCenter();
	virtual bool							OnCreate();
	virtual std::string                     GetLayoutName() { return "ActiveCenter"; }
	virtual void							Draw(Sexy::Graphics* i_g);
    virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g);
	virtual void							Update();

	// ButtonListener
	virtual void							ButtonDepress(int i_id);
    // implement of Sexy::ScrollWidgetListener
    virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) {}
    virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

	void                                    SetCurrentTab(int iTab);
	int										GetCurrentTab() const { return m_curTab; }
	Sexy::Widget*                           GetTabContent();
    void                                    Layout();
    
    void                                    DisabledAllButtons();
    void                                    EnabledAllButtons();

protected:
	int                                               m_curTab;
	typedef std::map<int, class ActiveCenterTabBase*> MapTabs;
	MapTabs                                           m_mapTab;
    
public:
    static int                                        s_ShowTab;
};

#endif
