//
//  DailySignRewardWithTW.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16-09-08.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//


#ifndef __PlantsVersusZombies2__DailySignRewardWithTW__
#define __PlantsVersusZombies2__DailySignRewardWithTW__

#include "Precompile.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "Effect_PopAnim.h"

namespace Message
{
//	void GetCurrentDailyReward();
//	void DailySignRewardReceived(int i_id);
}

class TWRewardData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(TWRewardData, Sexy::RtObject, Sexy::RtClass);
public:
    int         iRewardType = 0;
    int         iCount = 0;
};

class TWRewardListData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(TWRewardListData, Sexy::RtObject, Sexy::RtClass);
    
public:
    std::vector<TWRewardData> rewardList;
};

class TWRewardContent : public Widget
{
public:
    TWRewardContent(bool i_hasGotReward);
    ~TWRewardContent();
    
    void InitView(const TWRewardData rData, bool i_bImageAmount);
    
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void Draw(Graphics *i_g);
    virtual void Update();
    
    void setGetReward();
    
private:
    
    Image *     m_rewardImage = nullptr;
    Image *     m_bgImage = nullptr;
    Image *     m_obtainImage = nullptr;
    
    Effect_PopAnim * m_getAnim = nullptr;
    Effect_PopAnim * m_bgAnim = nullptr;
    
    ImagePtr m_amountImage;
    SexyString m_titleStr;
    
    int  m_nRewardAmount;
    bool m_bImageAmount;
    
    int m_contentWidth;
    
    bool m_hasGotReward;
    
    float m_drawScale;
    
    std::string m_plantPieceType;
    
    void InitView();
};

class TWScrollPanel : public Widget
{
public:
    
	TWScrollPanel(Rect &i_rect, class DailySignRewardWithTW* pTw);
    ~TWScrollPanel();
    
    void    SetGetReward(int idx);
    
private:
    
    void	InitView();
    bool    m_bShowLastFrame;
    int     m_contentSize;
    
    std::vector<TWRewardContent*>   m_contentList;
    
    class DailySignRewardWithTW* pDailySignRewardWithTW;
};

enum TwSignButtonId
{
    BUTTON_ID_CLOSE = 0,
    BUTTON_ID_SHOWINPUT,
    BUTTON_ID_SEND_REQUEST,
};

class DailySignRewardWithTW : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
	DailySignRewardWithTW();
    ~DailySignRewardWithTW();
    
    virtual void ButtonDepress(int i_id);
    virtual void Update();
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    void getReward(const S2C_DailySignWithTW_RewardInfo& pReward);
    void onProcessSignRewardResult(bool i_success, const S2C_DailySignWithTW* pData);
    
    const TWRewardListData& getRewardListData() {return m_rewardListData;}

private:
    void InitView();
    
    TWScrollPanel*          m_TWScrollPanel = nullptr;
	PVZ2UIScrollingWidget* m_scrollingWidget= nullptr;
    PVZ2UIButton*           m_closeButton= nullptr;
    PVZ2UIButton*           m_requestButton= nullptr;
    
    class InputCodeWidget* m_inputWidget =nullptr;
    
    TWRewardListData     m_rewardListData;
    std::string          m_startTime="";
    std::string          m_endTime ="";
};

class InputCodeWidget : public Widget, public Sexy::EditListener, Sexy::ButtonListener
{
public:
    InputCodeWidget(DailySignRewardWithTW* pTw);
    ~InputCodeWidget();
    
    virtual void    ButtonDepress(int i_id);
    virtual void    Update();
    virtual void    Draw(Graphics *i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
    virtual void    EditWidgetText(int i_id, const SexyString& i_string);
    virtual bool    AllowChar(int i_id, SexyChar i_char);
    
    DailySignRewardWithTW* pDailySignRewardWithTW;
    PVZ2UIEditWidget* m_editWidget = nullptr;
    PVZ2UIButton*     m_requestButton= nullptr;
};

#endif /* defined(__PlantsVersusZombies2__DailySignReward__) */
