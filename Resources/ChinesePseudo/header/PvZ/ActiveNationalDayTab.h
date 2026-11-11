//
//  ActiveNationalDayTab.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 2015.9.13.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _ActiveNationalDayTab_h_
#define _ActiveNationalDayTab_h_

#include "ActiveCenterTab.h"
#include "NationalDayRewardConfigInfo.h"
#include "TimeMgr.h"
#include "Effect_PopAnim.h"
#include "PrimeTextWidget.h"

class NationalDayRewardAnimWidget
: public Widget
{
    
public:
    
    NationalDayRewardAnimWidget(NationalDayRewardItem& item, pvztime_t iWait);
    
    ~NationalDayRewardAnimWidget();
    
    void Update() override;
    
    void Draw(Sexy::Graphics* i_g) override;
    
    bool IsComplete() { return !m_bScaling; }
    
private:
    
    void AnimUpdate();
    
    void AnimDraw(Sexy::Graphics* i_g);
    
    void CreateAnim();
    
    void DrawReward(Sexy::Graphics* i_g);
    
    bool IsPause();
    
private:
    
    Effect_PopAnim* m_pEffect_PopAnim;
    
    NationalDayRewardItem      m_stRewardItem;
    
    pvztime_t       m_iStartTime;
    
    pvztime_t       m_iWaitTime;
    
    bool            m_bScaling;
    
    Sexy::PrimeTextWidget* m_pDialogTextWidget;
    
};



class ActiveNationalDayTab : public ActiveCenterTabBase, public Sexy::ButtonListener
{
public:
    ActiveNationalDayTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~ActiveNationalDayTab();
	void	SetSelect(bool setting) override;
    void    DrawForeground(Sexy::Graphics* i_g) override;
    void    ButtonDepress(int i_id) override;
    void	Update() override;
private:
    
    void    DrawTimeCD(Sexy::Graphics *i_g);
    void    DrawIntro(Sexy::Graphics *i_g);
    void    DrawBanner(Sexy::Graphics *i_g);
    
    void    AddBuyDialog();
    
    void    CancelBuy();
    void    ConfirmBuy();
#ifdef HOST_ANDROID
    void    BuySuccess(const bool& i_success);
#else
    void    BuySuccess(const bool& i_success);
#endif
    void    CreateBuyButton();
    
    void    CreateStaticRewardAnim(NationalDayRewardItem* pNationalDayRewardItem);
    
private:
    
    NationalDayRewardAnimWidget* m_pNationalDayRewardAnimWidget;
    
    PVZ2UIButton* m_pGetButton;
    UIWidgetImage* m_pUIWidgetImage;
    
};

#endif
