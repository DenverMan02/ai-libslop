//
//  ActiveConsumptionTab.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 2015.9.13.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _ActiveConsumptionTab_h_
#define _ActiveConsumptionTab_h_

#include "ActiveCenterTab.h"
#include "ConsumptionRewardDialog.h"

class ConsumptionScrollPanel : public Widget, Sexy::ButtonListener
{
public:
    ConsumptionScrollPanel(Rect &i_rect, TopicItem& stTopic);
    virtual ~ConsumptionScrollPanel();
    
    virtual void ButtonDepress(int i_id);
    
    void	InitView();
    
    std::vector<ItemButton*>& GetItemButtons() { return m_vItemButton; }
    
private:
    
    std::vector<ItemButton*> m_vItemButton;
    TopicItem   m_stCurrentTopicItem;
    
};

class ActiveConsumptionTab : public ActiveCenterTabBase, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	ActiveConsumptionTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~ActiveConsumptionTab();
	void	OnButtonClicked(int i_id) override;
	void	SetSelect(bool setting) override;
    void    DrawForeground(Sexy::Graphics* i_g) override;
    void    Update() override;
    void    CloseDialog();
    void    ButtonPress(int i_id) override;
    void    ButtonDepress(int i_id) override;
    
    void	ScrollTargetReached(ScrollWidget* scrollWidget) override {}
    void	ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
    
    void    OngetConsumptionRewardStat(bool i_success);
    void    OnGotConsumptionReward(bool i_success);
private:
    
    void AddScrollWidght();
    
    void DrawTips(Sexy::Graphics* i_g);
    
    void AddBuyTips();
    
    bool CanPress();
    
    bool IsAllAnimComplete();
    
    void RecvReward(int iIndex);
    
    void DrawConsumptionBanner(Sexy::Graphics* i_g);
    
    void AddScrollBg();
    
private:
    
    TopicItem   m_stCurrentTopicItem;
    TipsWidget* m_pTipsWidget;
    std::vector<RewardAnimWidget*> m_vRewardAnimWidget;
    pvztime_t m_iAnimEndTime;
    std::vector<ItemButton*> m_vItemButton;
    bool m_bValid;
    bool m_inited;
    bool m_scrollBgInited;
    bool m_scrollWidghtInited;
    bool m_buyTipsInited;
};

#endif
