//
//  WorldMap_PVPButton.h
//  PlantsVersusZombies2
//
//  Created by Cao Shuai on 15-10-15.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_PVPButton__
#define __PlantsVersusZombies2__WorldMap_PVPButton__

#include "UIEasyButtonWidget.h"
#include "GameEventMgr.h"

class WorldMap_PVPButton : public UIEasyButtonWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_PVPButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_PVPButton();
    virtual ~WorldMap_PVPButton();
    
    void WaitForTutorialClick()
    {
        m_clicked = false;
    }
    bool WasClickedForTutorial()
    {
        return m_clicked;
    }
    
    void            ShowMenuUI(bool bShow = true);
    void            DoPressButton();
    bool            CheckActivated();
    
protected:
    void            onNetworkError(int erroId);
    void            onPVPLogin(bool i_success);
    void            onWorldLoaded();
    
private:
    bool                IsNeedTips();
    
private:
    bool                m_clicked;
    bool                m_bCanShowMenuUI;

};

#endif /* defined(__PlantsVersusZombies2__WorldMap_PVPButton__) */
