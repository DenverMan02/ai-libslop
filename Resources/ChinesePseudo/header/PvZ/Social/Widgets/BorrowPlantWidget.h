//
//  BorrowPlantWidget.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-7-18.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BorrowPlantWidget__
#define __PlantsVersusZombies2__BorrowPlantWidget__

#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "PVZTypes.h"
#include "PVZ2UIPlantCard.h"
#include "SocialInfo.h"

/*
typedef struct _BorrowFriendItem
{
    SexyString                      friendName;
    std::string                     plantTypeName;
    int32                           user_id;
} BorrowFriendItem;
*/

class BorrowPlantWidget : public PVZ2UIButton
{
public:
    BorrowPlantWidget(FriendInfo * friendInfo,int i_buttonId,ButtonListener* i_listener);
    virtual ~BorrowPlantWidget();
    
    virtual void                    Update();
    virtual void                    Draw(Graphics* i_g);
    virtual void                    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
    virtual void                    Resize(int theX, int theY, int theWidth, int theHeight);
    
    void                            SetBorrowButtonBorrowed(bool i_borrowed);
    
private:
    void                            drawPlant(Graphics* i_g);
    
private:
    Point                           m_posIcon;
    
    std::string                     m_PlantTypeName;
    
    bool                            m_IsBorrowed;
    
    //for ui
    SexyString                      m_labelFriendName;
    Rect                            m_rectFriendName;
    
    //SexyString                      m_labelStrongDesc;
    Rect                            m_rectStrongDesc;
    
    Rect                            m_rectHeadIcon;
};

#endif /* defined(__PlantsVersusZombies2__BorrowPlantWidget__) */
