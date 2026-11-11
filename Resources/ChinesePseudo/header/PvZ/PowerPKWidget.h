//
//  PowerPKWidget.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-1-13.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerPKWidget__
#define __PlantsVersusZombies2__PowerPKWidget__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "LawnAppEnums.h"
#include "Board.h"


class PowerPKWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	PowerPKWidget();
	virtual ~PowerPKWidget();

    virtual void	MouseDown(int x, int y, int theClickCount);
    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
    void SetTotalPower(int i_power);
    void SetCurPower(int i_power);
    
private:
    
    int m_totalPower;
    int m_curPower;
};

#endif /* defined(__PlantsVersusZombies2__PowerPKWidget__) */
