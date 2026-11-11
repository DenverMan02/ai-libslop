//
//  BirthdayRewardDialog.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 15-5-25.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_BirthdayRewardDialog_h
#define PlantsVersusZombies2_BirthdayRewardDialog_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PrimeTextWidget.h"

//---------------------------------------------------------------------------------


class BirthItem : public Widget
{
    
public:
    
    BirthItem(int iDayIndex);
    virtual ~BirthItem();
    
    void Draw(Sexy::Graphics* i_g) override;
    
    void DrawFlag(Sexy::Graphics* i_g);
    
private:
    
    Image*       m_pBgImage;
    int          m_iDayIndex;
    pvztime_t    m_iStartScaleTime;
    bool         m_bScaling;
    bool         m_bSmall;
    bool         m_bFlag;
    bool         m_bHighLight;
    bool         m_bFirst;
};


class BirthdayScrollPanel : public Widget
{
    
public:
    
    BirthdayScrollPanel(Rect &i_rect);
    
    virtual ~BirthdayScrollPanel();
    
    void	InitView();
    
};


//-----------------------------------------------------------------------------------

class BirthdayRewardDialog
: public Widget
, public Sexy::ButtonListener
, public Sexy::ScrollWidgetListener
{
public:
    
    BirthdayRewardDialog();
    ~BirthdayRewardDialog();
    void Update() override;
    void Draw(Sexy::Graphics* i_g) override;
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    
    void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
    void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

private:
    
    void InitView();
    
    void AddScrollWidght();

    void AddControlButton();

    void AddCloseButton();

private:
    
    int m_iBaseX;
    int m_iBaseY;

};

//---------------------------------------------------------------------------------

#endif
