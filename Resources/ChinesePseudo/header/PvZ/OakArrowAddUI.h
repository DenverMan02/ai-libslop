//
//  OakArrowAddUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-11-5.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__OakArrowAddUI__
#define __PlantsVersusZombies2__OakArrowAddUI__

#include "UIWidget.h"

class OakArrowAddUI : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(OakArrowAddUI, UIWidget, RtClass);
	
	OakArrowAddUI();
	virtual ~OakArrowAddUI();

	virtual void				Draw(Graphics* i_g) override;
    
protected:
    
	virtual void				onInitialized() override;
	virtual void 				registerForEvents() override;
    virtual void 				unregisterForEvents() override;
    
private:
    
	bool handleTouch(const Sexy::Touch& i_touch);
	void cancelTouch();
    
private:
   
	Sexy::TouchID           m_touchIdent;
	bool                    m_touchInitialized;
};

#endif /* defined(__PlantsVersusZombies2__OakArrowAddUI__) */
