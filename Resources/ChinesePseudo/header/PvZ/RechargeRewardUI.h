//
//  RechargeRewardUI.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/8/29.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef RechargeRewardUI_h
#define RechargeRewardUI_h

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "RechargeRewardConfig.h"
#include "NetworkData.h"
#include "StoneLottery.h"

class RechargeRewardItem : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(RechargeRewardItem, Sexy::RtObject, Sexy::RtClass);
    
public:
    std::vector<int>     itemStatus;
    int                  totalRechargeNum = 0;
};


//================================================
//              RechareRewardContent
//================================================

class RechargeRewardContent : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    enum
    {
        RechargeContent_btnObtain,
    };
    
    RechargeRewardContent(bool i_hasObtained, bool i_canObtain);
    virtual ~RechargeRewardContent();
    virtual void ButtonPress(int theId, int theClickCount)override;

    virtual void ButtonMouseLeave(int theId)override;
    void Draw(Graphics* i_g) override;
    void Resize(int theX, int theY, int theWidth, int theHeight) override;
    void ButtonDepress(int i_id) override;
    StoneLotteryItemTipUI* m_tipUI;
    SexyString          m_description;
    
    void setRechargeContentConfig(RechargeRewardContentConfig* i_config, int i_index);
    
    void onRechargeRewardGot(bool i_success, const S2C_ICloud_GetChargeRewardInfo* data);   //used for ios
    
private:
    void getRechargeReward();   //used for android
    void onRechargeRewardCurrencyChanged(int num);
    
    bool m_hasObtained;
    bool m_canObtain;
    PVZ2UIButton* m_obtainButton;
    RechargeRewardContentConfig* m_config;
    int m_index;
};



//================================================
//              RechargeRewardProgress
//================================================
class RechargeRewardProgressBar : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
    RechargeRewardProgressBar(int i_currentRechargeAmount, const std::vector<int>& i_rechargeStatus);
    
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void Draw(Graphics* i_g) override;
    
    void Init();
    void setCurrentRechargeAmount(int i_amount) { m_currentRechargeAmount = i_amount; }
    
    int calcucateProgressBarWidth(int i_width);

private:
    int m_barWidth;
    
    int m_currentRechargeAmount = 0;
    int m_maxRechargeAmount;
    
    std::vector<int> m_rechargeStatus;
    std::vector<RechargeRewardContentConfig> m_configList;
    
};

//================================================
//         RechargeRewardProgressBarWidget
//================================================

class RechargeRewardProgressBarWidget : public Sexy::Widget
{
public:
    RechargeRewardProgressBarWidget();
    void Draw(Graphics* i_g) override;
    void setBar(RechargeRewardProgressBar* m_bar);
private:
    void DrawCashAmount(Graphics* i_g, int i_amount, int i_x, int i_y);

    RechargeRewardProgressBar* m_bar;
    std::vector<RechargeRewardContentConfig> m_configList;
};


class RechargeRewardProgress : public Sexy::Widget, Sexy::ButtonListener
{
public:
	enum
	{
		RechargeReward_hideRecharge,
	};

    RechargeRewardProgress();
    virtual ~RechargeRewardProgress();

    void Draw(Graphics* i_g) override;
    
    void Init();
    void setCurrentRechargeAmount(int i_amount);

    virtual void	ButtonPress(int i_id);

    SexyString          m_description;
    StoneLotteryItemTipUI* m_tipUI;

    virtual void	ButtonDepress(int i_id);

    void onHideBtnChanged();

private:
    RechargeRewardProgressBar* m_progressBar;
    
    int m_currentRechargeAmount = 0;
    std::vector<int> m_rewardObtainStatus;
    PVZ2UIButton* m_hideBtn;
    bool m_hideRecharge;
};


//================================================
//              RechargeRewardUI
//================================================

class RechargeRewardUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    enum
    {
        RechargeReward_btnClose,
        RechargeReward_btnCharge,
    };
    
    RechargeRewardUI();
    virtual ~RechargeRewardUI();
    
    void createFromNetworkResponse();
    void onRechargeRewardCurrencyChanged(int num);
    
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
    static void requestNetwork();

private:
    ImagePtr getBannerImage();
    
    RechargeRewardProgress* m_rewardProgress;
    
    std::vector<RechargeRewardContent> m_rewardContentList;
    Rect m_dialogRect;

    PVZ2UIButton* m_closeButton;
    PVZ2UIButton* m_chargeButton;
    
    ImagePtr m_bannerImage;
    
    bool m_firstRechargeObtained;
    
    bool m_receivedResponse;
    
    int m_currentRechargeAmount = 0;
};

#endif /* RechargeRewardUI_h */
