//
//  FriendListView.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-7-16.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FriendListView__
#define __PlantsVersusZombies2__FriendListView__

#include "Precompile.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"

class FriendScroolPanel : public Widget {
public:
    FriendScroolPanel(Rect &i_rect);
    ~FriendScroolPanel();
    
private:
    void                            InitView();
};

enum FriendButtonId
{
    FRIEND_BUTTON_ID_CLOSE = 0,
    FRIEND_BUTTON_ID_INVITE
};

class FriendListView : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
    RT_CLASS_DEFINE(FriendListView, Widget, RtClass);

public:
    FriendListView();
    ~FriendListView();
    
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
	
private:
    void InitView();
    
	PVZ2UIScrollingWidget* m_scrollingWidget;
    PVZ2UIButton*           m_closeButton;
    PVZ2UIButton*           m_inviteButton;
    
    SexyString              m_strTitle;
    Rect                    m_rectTitle;
    SexyString              m_strHappiness;
};

#endif /* defined(__PlantsVersusZombies2__FriendListView__) */
