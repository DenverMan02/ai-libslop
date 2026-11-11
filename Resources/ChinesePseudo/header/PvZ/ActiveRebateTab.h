//
//  ActiveRebateTab.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 2015.12.16.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _ActiveRebateTab_h_
#define _ActiveRebateTab_h_

#include "ActiveCenterTab.h"
#include "ConsumptionRewardDialog.h"


//-------------------------------------------ReBateNormalItem---------------------------------------------------------------------

class ReBateItemWidget : public Widget
{
    
public:
    
    ReBateItemWidget(std::string strPlantName, int iCharge, int iRewardCount, bool bSpecial);
    
    ~ReBateItemWidget();
    
    void Draw(Sexy::Graphics* i_g) override;
    
private:
    
    Image* GetPlantPieceImage();
    
    void DrawNormalContent(Sexy::Graphics* i_g);
    
    void DrawSpecialContent(Sexy::Graphics* i_g);
    
private:
    
    std::string m_strPlantName;
    int m_iChargeValue;
    bool m_bSpecialItem;
    int m_iRewardCount;
    
};

//-------------------------------------------RebateBGWidget---------------------------------------------------------------------

class RebateContentWidget : public Widget
{
    
public:
    
    RebateContentWidget();
    
    ~RebateContentWidget();
    
    void Draw(Sexy::Graphics* i_g) override;
    
private:
    
    void AddRewardItem();
    
};


//-------------------------------------------ActiveRebateTab---------------------------------------------------------------------


class ActiveRebateTab : public ActiveCenterTabBase, public Sexy::ButtonListener
{
public:
	ActiveRebateTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~ActiveRebateTab();
	void	OnButtonClicked(int i_id) override;
	void	SetSelect(bool setting) override;
    void    DrawForeground(Sexy::Graphics* i_g) override;
    void    Update() override;
    void    ButtonPress(int i_id) override;
    void    ButtonDepress(int i_id) override;
    
private:
    
    void    AddContent();
    
    void    AddGetRewardButton();
    
private:
    
    PVZ2UIButton* m_pGetButton = nullptr;
    
};

#endif
