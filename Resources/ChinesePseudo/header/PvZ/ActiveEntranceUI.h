//
//  ActiveEntranceUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-18.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ActiveEntranceUI__
#define __PlantsVersusZombies2__ActiveEntranceUI__

#include "PlatformAutodetect.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "core.h"
#include "ButtonListener.h"
#include "PVZ2UIButton.h"
#include "LawnAppEnums.h"

class ActiveEntranceUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	ActiveEntranceUI(ActiveEntranceType i_type);
	virtual ~ActiveEntranceUI();
    
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void            setupScreen();
    
private:
    
    ActiveEntranceType m_type;
    
    Rect m_dialogRect;
    Rect m_internalRect;
    Rect m_contentRect;
};

#endif /* defined(__PlantsVersusZombies2__ActiveEntranceUI__) */
