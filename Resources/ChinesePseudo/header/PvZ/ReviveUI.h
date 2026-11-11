//
//  ReviveUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-4-28.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ReviveUI__
#define __PlantsVersusZombies2__ReviveUI__

#include "Widget.h"
#include "RtObject.h"
#include "TimeMgr.h"

enum ReviveMode
{
	ReviveMode_SingleHanded,
	ReviveMode_OakTrain,
	ReviveMode_SnakeHitBlock,
	ReviveMode_SnakeHeadHitBody,
	ReviveMode_SnakeRunOutBorder,
	ReviveMode_SnakeCreateMower,
	ReviveMode_RiverCrossingDodoRiderDiedOut,
	ReviveMode_Eliminate,
	ReviveMode_PooyanShooterDiedOut,
    ReviveMode_FishingFailed,
    ReviveMode_AirShipCrash,
    ReviveMode_BesiegeFailed,
    ReviveMode_MazeStatueFailed,
    ReviveMode_Count
};

namespace Message
{
	void ReviveSucceed();
    void ReviveClose();
}

class ReviveUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	ReviveUI(ReviveMode i_mode);
	virtual ~ReviveUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    void            OnServerGemCallBack(const bool& i_Success);
    void            OnServerGemCallBack_Android_Convert_Ios(const bool& i_Success);
    
    ReviveMode      m_mode;
    
    SexyString		m_headerLabel;
    
    Sexy::Rect      m_rectDialog;
    bool            m_bExit;
    
    Sexy::Rect      m_rectImgBg;
    
    SexyString      m_strDesc;
    Sexy::Rect      m_rectDesc;
};

#endif /* defined(__PlantsVersusZombies2__ReviveUI__) */
