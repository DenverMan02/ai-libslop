//
//  NextWaveButton.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-7-16.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NextWaveButton__
#define __PlantsVersusZombies2__NextWaveButton__

#include "UIWidget.h"

class NextWaveButton : public UIWidget, public ButtonListener
{
public:
	RT_CLASS_DEFINE(NextWaveButton, UIWidget, RtClass) {}
    
	NextWaveButton();
	virtual ~NextWaveButton();
    
    // Public Interface (Inheritable)
    
	virtual void Draw(Graphics* i_g) override;
    virtual bool IsUsable();
    
    bool CanSetVisible() override;
    void SetCanSetVisible(bool i_canSetVisible) { m_canSetVisible = i_canSetVisible; }

    // Public Interface (Core)
    
    //void						InitializeTimer();
	//void						SetToReady();
    
protected:
	
	virtual void initLoadingResourcesGroupList() override;
    
    virtual void registerForEvents() override;
    
    void onGameplayEnded();
    
    // Protected Interface (Inheritable)
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
    
    /*
	OVERRIDE_STATE_ONEXIT(WidgetState,  Loading);
	OVERRIDE_STATE_ONENTER(WidgetState, NotReady);
	OVERRIDE_STATE_UPDATE(WidgetState,  NotReady);
	OVERRIDE_STATE_ONENTER(WidgetState, Ready);
	OVERRIDE_STATE_ONENTER(WidgetState, Pressed);
	OVERRIDE_STATE_ONEXIT(WidgetState,  Pressed);
    */
    
protected:
    
	pvztime_t					m_cooldownEndTime;
    
private:
	bool handleTouch(const Sexy::Touch& i_touch);
	void startTouch(Sexy::TouchID i_touchIdent);
	void cancelTouch();
    
	//class StretchableNewLawnButton* m_nextWaveButton;
	Sexy::TouchID m_touchIdent;
	bool m_instant;
	int m_leftCount;
	bool m_visible;
	bool m_canSetVisible;
};

namespace Message
{
	void NextWaveButtonPressed();
}

#endif /* defined(__PlantsVersusZombies2__NextWaveButton__) */
