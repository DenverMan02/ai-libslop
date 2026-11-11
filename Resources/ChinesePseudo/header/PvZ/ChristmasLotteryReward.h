//
//  ChristmasLotteryReward.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-2.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ChristmasLotteryReward__
#define __PlantsVersusZombies2__ChristmasLotteryReward__

#include "PlatformAutodetect.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "core.h"
#include "ButtonListener.h"
#include "PVZ2UIButton.h"
#include "Effect_PopAnim.h"
#include "Effect_StaticImage.h"

class ChristmasLotteryReward : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	ChristmasLotteryReward(std::string i_plantName,bool i_IsPlant,int i_nRewardNum);
	virtual ~ChristmasLotteryReward();
	
	virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void            setupScreen();
    
    void onAnimCommand(const std::string& i_animLabel,
                       pvztime_t i_timeStamp,
                       const std::string& i_animCommand,
                       const std::string& i_animCommandParam);
    
private:
    
    Effect_PopAnim *           m_popAnimDialogBg;
    Effect_PopAnim *           m_popAnimRewardBg;
    Effect_PopAnim *           m_popAnimRewardFront;
    
    Effect_PopAnim *           m_popAnimRewardPlant;
    Effect_StaticImage *       m_popAnimRewardPiece;
    
    Rect                       m_dialogRect;
    
    std::string                m_plantName;
    bool                       m_IsPlant;
    int                        m_nRewardNum;
};

#endif /* defined(__PlantsVersusZombies2__ChristmasLotteryReward__) */
