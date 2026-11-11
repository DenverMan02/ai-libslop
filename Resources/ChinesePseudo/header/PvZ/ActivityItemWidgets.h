//
//  ActivityItemWidgets.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.10.27
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _ActivityItemWidgets_h_
#define _ActivityItemWidgets_h_

#include "Widget.h"
#include "UISingletonDialog.h"
#include "Curve.h"

//-----------------------------------------------------
// ChallengeRankItem
//-----------------------------------------------------
class ChallengeRankItem : public Sexy::Widget
{
public:
    ChallengeRankItem();
    virtual void Draw(Graphics* i_g) override;
    void Refresh();
public:
    int         m_profileID = 0;
    int         m_rankOrder = 0;
    SexyString  m_name;
    int         m_score = 0;
    int         m_headID = 0;
    bool		m_hasEffect = false;
    int			m_color = 0;
    int			m_rank_avatar_id = 0;
};


class MonthlyCardItem : public Sexy::Widget
{
public:
	MonthlyCardItem();
    void Draw(Graphics* i_g) override;
public:
    int m_type;
    SexyString  m_content;
};


//-----------------------------------------------------
// LoadingWidget
//-----------------------------------------------------
class LoadingWidget : public Sexy::Widget
{
public:
    LoadingWidget();
    virtual void Draw(Graphics* i_g) override;
protected:
    double       m_Rot = 0.0;
};


//-----------------------------------------------------
// ChallengeRewardDlg
//-----------------------------------------------------
class ChallengeRewardDlg : public UISingletonDialog<ChallengeRewardDlg>
{
    struct RewardInfo
    {
        Sexy::Image*    m_rewardImg;
        int             m_num;
        bool            m_delete;
        
        RewardInfo()
        {
            m_rewardImg = nullptr;
            m_num = 0;
            m_delete = false;
        }
    };
public:
    virtual bool        OnCreate() override;
    virtual void		OnClose() override;
    virtual std::string GetLayoutName() override { return "ChallengeReward"; }
    virtual void        Update() override;
    
    // ButtonListener
    virtual void        ButtonDepress(int i_id) override;
    
    void                SetHeadshot(int i_headID);
    void                AddReward(const std::string& i_image, int i_value);
    void                AddReward(Sexy::Image* i_image, int i_value, bool delImg = false);
    void                SetHeadString(const SexyString& i_sexystr);
    void                SetText(const SexyString& i_sexystr);
    void                Refresh();
    
private:
    class UIHeadshotIcon*   m_pHeadshot = nullptr;
    std::vector<RewardInfo>   m_rewardList;
    bool                m_bDirty = true;
};

//--------------------------------------------------------
// NumberWidget
//--------------------------------------------------------
class NumberWidget : public Sexy::Widget
{
public:
    enum ShowFormat
    {
        ShowFormat_Default = 0,
        ShowFormat_FullDigits = 1<<0,
        ShowFormat_WithOperator = 1<<1,
    };
public:
    virtual void        Draw(Sexy::Graphics* i_g) override;
    virtual void        Update() override;
    
    int                 GetNumber() const { return m_targetNumber; }
    void                SetNumber(int i_num, bool i_bAnim = true);
    void                SetAlign(int i_align);      // DrawStringJustification
    void                SetImagePrefix(const std::string i_str) { m_imagePrefix = i_str; }
    void                SetFontMode(Sexy::PrimeTypeface* i_font, Color i_color = Color::White);
    void                SetFontMode(class PrimeText_PotentialTypeface* i_font, Color i_color = Color::White);
    void                SetNumberColor(const Color& i_clr) { m_color = i_clr; }
    void                SetShowFormat(uint32 i_fmt) { m_showFormat = i_fmt; }
    void                StartFade(int i_fromAlpha, int i_toAlpha, float i_duration);
protected:
    void                DrawImageNumber(Sexy::Graphics* i_g);
protected:
    int                 m_targetNumber = 0;
    int                 m_animNumber = 0;
    float               m_animStep = 0.0f;
    int                 m_align = 0;
    std::string         m_imagePrefix = "IMAGE_UI_ADS_NUM";
    Sexy::PrimeTypeface* m_pFont = nullptr;
    Color               m_color = Color::White;
    uint32              m_showFormat = ShowFormat_Default;
    int                 m_digitNum = 1;
    
    int                 m_fromAlhpa = 255;
    int                 m_toAlpha = 255;
    float               m_timeStart = -1.0f;
    float               m_timeDuration = -1.0f;
};

//--------------------------------------------------------
// SlidingController
//--------------------------------------------------------
class SlidingController
{
public:
    void Update();
    
    void StartSlide(Sexy::Widget* i_widget, SexyVector2 i_from, SexyVector2 i_to,
                    float i_duration, CurveType i_curve = CURVE_EASE_OUT);
    
protected:
    float                   m_slideTimeStart = -1.0f;
    float                   m_slideTimeDuration = -1.0f;
    CurveType				m_curveType = CURVE_EASE_OUT;
    SexyVector2				m_startPosition;
    SexyVector2				m_endPosition;
    std::string				m_audioOnSlide;
    Sexy::Widget*           m_pWidget = nullptr;
};

#endif
