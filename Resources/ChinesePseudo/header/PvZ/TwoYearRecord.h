//
//  TwoYearRecord.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-28.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TwoYearRecord__
#define __PlantsVersusZombies2__TwoYearRecord__

//#include "PlatformAutodetect.h"
//#include "RtDb.h"
//#include "RtDelegate.h"
//#include "TimeMgr.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"


class RecordInfoPage : public Sexy::Widget
{
public:
    
	RecordInfoPage();
	virtual ~RecordInfoPage();
    
    int             GetPageIndex();
    void            SetPageIndex(int i_indexPage);
	
	//virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
    
    void GetWechatShareUrl(std::string& outUrl);
    
private:
    
    void            setupScreen();
    
private:
    
    int             m_indexPage;
    
    SexyString      m_Name;
    SexyString      m_TimeCreate;
    int             m_days;
    int             m_worldNum;
    SexyString      m_worldName;
    
    int             m_zombieNum;
    int             m_startNum;
    
    int             m_plantNum;
    SexyString      m_plantName;
    
    int             m_worldID;
    int             m_plantID;
    
};

///////

class TwoYearRecord : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	TwoYearRecord();
	virtual ~TwoYearRecord();
	
	//virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void            setupScreen();
    
private:
    RecordInfoPage * m_page;
};

#endif /* defined(__PlantsVersusZombies2__TwoYearRecord__) */
