//
//  NetConnectingUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-8-27.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NetConnectingUI__
#define __PlantsVersusZombies2__NetConnectingUI__

#include "Core.h"

class NetConnectingUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	NetConnectingUI(const std::string& i_tip);
	virtual ~NetConnectingUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    void 			SetTip(const std::string& i_tip) { m_tip = i_tip; }
	
	//virtual void	ButtonPress(int i_id);
	//virtual void	ButtonDepress(int i_id);
    
private:
    void setupScreen();
    
private:
    double m_Rot;
    pvztime_t m_refreshingTime;
    Image* m_waitImg;
    std::string m_tip;
};

#endif /* defined(__PlantsVersusZombies2__NetConnectingUI__) */
