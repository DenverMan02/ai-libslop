//
//  FriendCard.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-7-16.
//  Copyright (c) 2013骞�PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FriendCard__
#define __PlantsVersusZombies2__FriendCard__

#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "Image.h"

struct FriendCardInfo
{
	int32 		userId;
    SexyString  strName;
    int         star;
    int         imageId;
    int         leftTime;
};

class FriendCard : public Widget, Sexy::ButtonListener
{
public:
    FriendCard(FriendCardInfo &i_FriendCardInfo);
    void InitView();
    
    void RefreshTimeUI();
    
    void UpdateTime();
    
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void Update();
    virtual void Draw(Graphics* i_g);
    
    virtual void ButtonDepress(int i_id);
    
private:
    void                            RegisterForMsg();
    void                            UnregisterForMsg();
    
    PVZ2UIButton*   m_btnGift;
    FriendCardInfo  m_FriendCardInfo;
    
    SexyString  m_strName;
    SexyString  m_strStar;
    SexyString  m_strTimer;
    Image*      m_imgIconBg;
    Image*      m_imgStar;
    Image*      m_imgTimer;
    
    Rect        m_rectName;
    Rect        m_rectStarNum;
    Rect        m_rectTimerLabel;
    Rect        m_rectIconBg;
    Rect        m_rectStar;
    Rect        m_rectTimer;
    
    uint64   m_updateTime;
};
#endif /* defined(__PlantsVersusZombies2__FriendCard__) */
