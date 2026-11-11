//
//  ActiveSingleTab.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ActiveSingleTab__
#define __PlantsVersusZombies2__ActiveSingleTab__

#include "PlatformAutodetect.h"
#include "ActiveCenterTab.h"
#include "Effect_PopAnim.h"
#include "ActivityConfig.h"

class ActiveChristmasProtectTab : public ActiveCenterTabBase
{
public:
    
    ActiveChristmasProtectTab(int tab_id, class UI::Dialog* pCenterDlg);
    
    std::string GetTabContainerImageName() const override
    {
        return "IMAGE_UI_ACTIVETABCENTER_PROTECT_BG";
    }
    
    virtual void        DrawForeground(class Sexy::Graphics* i_g) override;
	virtual void		Update() override;
    
private:
    Rect        m_contentRect;
    
    ActivityTimeStatus m_StatusActivity;
    
    time_t      m_endTime;
    SexyString  m_daysDes;
    SexyString  m_timeDes;
};

class ActiveChristmasLanternTab : public ActiveCenterTabBase
{
public:
    
    ActiveChristmasLanternTab(int tab_id, class UI::Dialog* pCenterDlg);
    
    std::string GetTabContainerImageName() const override
    {
        return "IMAGE_UI_ACTIVETABCENTER_LANTERN_BG";
    }
};

#endif /* defined(__PlantsVersusZombies2__ActiveSingleTab__) */
