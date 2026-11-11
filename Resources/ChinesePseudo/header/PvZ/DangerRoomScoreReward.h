//
//  DangerRoomScoreReward.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomScoreReward__
#define __PlantsVersusZombies2__DangerRoomScoreReward__

#include "PlatformAutodetect.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "core.h"
#include "ButtonListener.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"

namespace Message
{
	void NotifyScoreRewardClose();
}

class ScoreRewardItem : public Widget
{
public:
    ScoreRewardItem(Sexy::ButtonListener * i_listener,
                    int i_index,
                    int i_score);
    
    virtual ~ScoreRewardItem();
    
    void            setOpened(bool i_opened);
    
    virtual void	Draw(Sexy::Graphics* i_g);
    
private:
    int             m_nScore;
    bool            m_bOpened;
    PVZ2UIButton *  m_buttonGet;
};

///////////

class ScoreRewardScrollPanel : public Widget, Sexy::ButtonListener
{
public:
	ScoreRewardScrollPanel(Rect &i_rect);
    virtual ~ScoreRewardScrollPanel();
    
    float           InitView();
    
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    
    std::vector<class ScoreRewardItem*> m_contents;

    void OnShowBonus(bool i_success);

private:
    
    void    KillRewardDialog();
    
private:
    int m_OpenedId;
    bool m_opening;
};

////////////////////////

class DangerRoomScoreReward : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
    
	DangerRoomScoreReward();
	virtual ~DangerRoomScoreReward();
	
	//virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
    virtual void    ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void    ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
private:
    
    void            setupScreen();
    
};

#endif /* defined(__PlantsVersusZombies2__DangerRoomScoreReward__) */
