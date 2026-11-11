//
//  IwatchRewardUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-11-19.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IwatchRewardUI__
#define __PlantsVersusZombies2__IwatchRewardUI__

#include "Widget.h"
#include "RtObject.h"
#include "TimeMgr.h"

class IWatchRewardContent : public Widget
{
public:
    IWatchRewardContent(int iType, int iCount, std::string strPlantName = "");
	virtual ~IWatchRewardContent();
	virtual void Draw(Graphics *i_g);
    
private:
    
    Image* GetItemImage(int iType, std::string strName = "");
    
private:
    
    int         m_iType; // 0 money, 1 gem, 2 plant piece, 3 avatar piece, 4 acc piece
    std::string m_strPlantName;
    int         m_iCount;
};

//////

class IwatchRewardUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	IwatchRewardUI();
	virtual ~IwatchRewardUI();
	
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void SetupDatas();
    
    void CreateButton();
    
private:
    
    Sexy::Rect m_BaseRect;
};

#endif /* defined(__PlantsVersusZombies2__IwatchRewardUI__) */
