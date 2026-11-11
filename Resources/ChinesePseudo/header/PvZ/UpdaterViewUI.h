//
//  UpdaterViewUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-5-15.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UpdaterViewUI__
#define __PlantsVersusZombies2__UpdaterViewUI__

#include "Widget.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "PVZ2UIButton.h"

class UpdaterViewUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	UpdaterViewUI(bool i_needBaseRSB);
	virtual ~UpdaterViewUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void            SetRollPercent(float percent);
    
private:
    
    Sexy::Rect     m_rectDialog;
    
    PVZ2UIButton * button_close;
    PVZ2UIButton * button_install;

    class PVZ2UIProgressBar * m_progressBar;
    
    bool           m_checkInstall;
    bool           m_needBaseRSB;
	bool			  m_bShowReward;
    
    float          m_roll_pos;
    float          m_roll_rot;
    float          m_roll_increment;
    float          m_roll_max_distance;
    float          m_roll_cur_percent;
};

#endif /* defined(__PlantsVersusZombies2__UpdaterViewUI__) */
