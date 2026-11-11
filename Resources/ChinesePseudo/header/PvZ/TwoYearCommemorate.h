//
//  TwoYearCommemorate.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 15-5-25.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TwoYearCommemorate_h
#define PlantsVersusZombies2_TwoYearCommemorate_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PrimeTextWidget.h"
#include "UIEditor/UIWidgetImage.h"
#include "ActiveConsumptionTab.h"

//---------------------------------------------------------------------------------


class LevelUpSinger : public Widget, public Sexy::ButtonListener
{
public:
    LevelUpSinger();
    virtual ~LevelUpSinger();
    void    Draw(Sexy::Graphics* i_g) override;
    void    ButtonDepress(int i_id) override;
    void	Update() override;
private:
    
    void    DrawTimeCD(Sexy::Graphics *i_g);
    void    DrawIntro(Sexy::Graphics *i_g);
    void    DrawBanner(Sexy::Graphics *i_g);
    void    DrawBg(Sexy::Graphics *i_g);
    
    void    AddBuyDialog();
    
    void    CancelBuy();
    void    ConfirmBuy();
    void    BuySuccess();
    void    CreateBuyButton();
    
};

//----------------------------------------------------------------------------------

class SignSinger : public Widget, public Sexy::ButtonListener
{
public:
    SignSinger();
    virtual ~SignSinger();
    void    Draw(Sexy::Graphics* i_g) override;
    void    ButtonDepress(int i_id) override;
    void	Update() override;
private:
    void    DrawIntro(Sexy::Graphics *i_g);
    void    DrawBanner(Sexy::Graphics *i_g);
    void    DrawBg(Sexy::Graphics *i_g);
    
};

//----------------------------------------------------------------------------------



class AvatarSinger : public Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    AvatarSinger();
    virtual ~AvatarSinger();
    void    Draw(Sexy::Graphics* i_g) override;
    void    Update() override;
    
    void    ButtonPress(int i_id) override;
    void    ButtonDepress(int i_id) override;
    
    void	ScrollTargetReached(ScrollWidget* scrollWidget) override {}
    void	ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
    
private:
    
    void AddScrollWidght();
    
    void DrawTips(Sexy::Graphics* i_g);
    
    void AddBuyTips();
    
    bool CanPress();
    
    bool IsAllAnimComplete();
    
    void RecvReward(int iIndex);
    
    void DrawConsumptionBanner(Sexy::Graphics* i_g);
    
    void DrawScrollBg(Sexy::Graphics* i_g);
    
private:
    
    TopicItem   m_stCurrentTopicItem;
    TipsWidget* m_pTipsWidget;
    std::vector<RewardAnimWidget*> m_vRewardAnimWidget;
    pvztime_t m_iAnimEndTime;
    std::vector<ItemButton*> m_vItemButton;
    bool m_bValid;
};





//----------------------------------------------------------------------------------

class TwoYearCommemorate
: public Widget
, public Sexy::ButtonListener
{
public:
    
    TwoYearCommemorate();
    ~TwoYearCommemorate();
    void Update() override;
    void Draw(Sexy::Graphics* i_g) override;
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    
private:
    
    void InitView();
    
    void AddCloseButton();
    
    void CreateSubDialog();
    
    void ResetSubDialog();
    
    void CreateSubButton();
    
    void AddCommonLabel();
    
    void LinkSubButton();
    
private:

    int m_iBaseX;
    int m_iBaseY;
    
    LevelUpSinger* m_pLevelUpSinger;
    SignSinger* m_pSignSinger;
    AvatarSinger* m_pAvatarSinger;
    std::vector<PVZ2UIButton*> m_vPVZ2UIButton;
};

//---------------------------------------------------------------------------------

#endif
