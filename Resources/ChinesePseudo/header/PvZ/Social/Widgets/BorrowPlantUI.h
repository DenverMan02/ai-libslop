//
//  BorrowPlantUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-7-18.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BorrowPlantUI__
#define __PlantsVersusZombies2__BorrowPlantUI__

#include "Precompile.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "BorrowPlantWidget.h"

enum BorrowPlantButtons
{
    BORROWBUTTON_BORROW = -2,
	BORROWBUTTON_CLOSE  = -1,
    BORROWBUTTON_START  = 0
};

namespace Message
{
	void BorrowPlantButtonPressed(FriendInfo * i_friendinfo,int buttonIndex);
}

class BorrowPlantUI : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
    BorrowPlantUI(int LastbuttonIndex);
    virtual ~BorrowPlantUI();
    
    void InitView(int LastbuttonIndex);
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
private:
    
    //void onBorrowButtonPressed(BorrowPlantWidget * borrow_widget);
    
private:
    
    class PVZ2UIScrollingWidget*  m_scrollingWidget;
    
    class PVZ2UIButton*           m_closeButton;
    class PVZ2UIButton*           m_btnBorrow;
    
    std::vector<BorrowPlantWidget*> m_arrWidgets;
    int                             m_LastButtonID;
    
    std::vector<FriendInfo>         m_arrFriends;
};

#endif /* defined(__PlantsVersusZombies2__BorrowPlantUI__) */
