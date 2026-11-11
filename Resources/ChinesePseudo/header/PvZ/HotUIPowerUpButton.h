//
//  HotUIPowerUpButton.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/28/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIPowerUpButton__
#define __PlantsVersusZombies2__HotUIPowerUpButton__

#include "ButtonListener.h"
#include "HotUIWidget.h"

class PowerUpUIButton;

// HotUI Wrapper for PowerUpButton widget, used in the ArcadeMenu
// It would be nice if this wrappers stayed as thin as possible
class HotUIPowerUpButton : public HotUIWidget, public ButtonListener
{
public:
	RT_CLASS_DEFINE(HotUIPowerUpButton, HotUIWidget, RtClass);
	HotUIPowerUpButton();
	virtual ~HotUIPowerUpButton();
	
	PowerUpUIButton* GetWrappedWidget() const { return m_wrappedWidget; }
	
protected:
	void	onInitializeWidget() override;
	void	onLayoutFinalized() override;
	
private:
	PowerUpUIButton*	m_wrappedWidget;
};

class HotUIPowerUpButtonProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIPowerUpButtonProperties, HotUIWidgetProperties, RtClass);
	
	HotUIPowerUpButtonProperties()
	{
		
	}
	
	RtClass* GetWidgetClass() const override
	{
		return HotUIPowerUpButton::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__HotUIPowerUpButton__) */
