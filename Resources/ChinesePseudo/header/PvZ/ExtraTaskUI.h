//
//  ExtraTaskUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-1-13.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ExtraTaskUI__
#define __PlantsVersusZombies2__ExtraTaskUI__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "LawnAppEnums.h"

class ExtraTaskWidget : public Widget
{
public:
	ExtraTaskWidget();
	virtual ~ExtraTaskWidget();
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    
private:
    
	void InitView();
    
private:
    
    SexyString m_descriptionLabel;
};

class ExtraTaskUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
	ExtraTaskUI();
	virtual ~ExtraTaskUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void setupScreen();
    
    void drawShadedBox(Graphics* i_g, Rect extents);
    
private:
    
    Sexy::Rect                      m_rectDialog;
    
    SexyString						m_Title;
};

#endif /* defined(__PlantsVersusZombies2__ExtraTaskUI__) */
