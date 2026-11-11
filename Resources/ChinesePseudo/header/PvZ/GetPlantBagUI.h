//
//  GetPlantBagUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-8-6.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GetPlantBagUI__
#define __PlantsVersusZombies2__GetPlantBagUI__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "MagentoService.h"

class GetPlantBagUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	GetPlantBagUI(const MagentoProductPropsPtr& prpduct, bool isRewardCoins);
	virtual ~GetPlantBagUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    void setupScreen();
    
    void drawShadedBox(Graphics* i_g, Rect extents);
    
    void onGetCoins();
    
private:
	//PVZ2UIDialog*					m_dialog;
    MagentoProductPropsPtr          m_props;
    
    Sexy::Rect                      m_rectDialog;
    
    bool							m_presentsOpened;
    bool                            m_isRewardCoins;
};

#endif /* defined(__PlantsVersusZombies2__GetPlantBagUI__) */
