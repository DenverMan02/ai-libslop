//
//  TwoYearAchievement.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-10-8.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TwoYearAchievement__
#define __PlantsVersusZombies2__TwoYearAchievement__

//#include "PlatformAutodetect.h"
//#include "RtDb.h"
//#include "RtDelegate.h"
//#include "TimeMgr.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "PVZ2UIButton.h"

class TwoYearAchievement : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	TwoYearAchievement();
	virtual ~TwoYearAchievement();
	
	//virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void            setupScreen();
    
private:
    
};

#endif /* defined(__PlantsVersusZombies2__TwoYearAchievement__) */
