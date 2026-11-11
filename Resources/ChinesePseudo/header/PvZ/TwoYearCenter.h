//
//  TwoYearCenter.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-25.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TwoYearCenter__
#define __PlantsVersusZombies2__TwoYearCenter__

#include "PlatformAutodetect.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "core.h"
#include "ButtonListener.h"
#include "PVZ2UIButton.h"
#include "Effect_PopAnim.h"

class TwoYearCenter : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	TwoYearCenter();
	virtual ~TwoYearCenter();
	
	virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void            setupScreen();
    
    void            setCakeOpening(bool i_opening);

    void            onCakeCommand(const std::string& i_animName,
                                  pvztime_t i_time,
                                  const std::string& i_command,
                                  const std::string& i_params);
    
private:
    
    Effect_PopAnim *           m_popAnimEffect;
    
    bool                       m_bOpening;
    bool                       m_bDroping;
    
    std::vector<PVZ2UIButton*> m_nBtns;
    
    Rect m_dialogRect;
    Rect m_internalRect;
    Rect m_contentRect;
};

#endif /* defined(__PlantsVersusZombies2__TwoYearCenter__) */
