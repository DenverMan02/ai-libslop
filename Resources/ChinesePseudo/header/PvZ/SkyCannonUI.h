//
//  SkyCannonUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-6-11.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SkyCannonUI__
#define __PlantsVersusZombies2__SkyCannonUI__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"

class SkyCannonUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(SkyCannonUI, UIWidget, RtClass);
	
	SkyCannonUI();
	virtual ~SkyCannonUI();
	
	// Public Interface (Inheritable)
	
	virtual void	Draw(Graphics* i_g) override;
	virtual bool	OnTouch(const Sexy::Touch& i_touch) override;
    
    void            SetCoolDownTime(float i_timeCoolDown);
    
protected:
	
	// Protected Interface (Inheritable)
    
	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_ONENTER(WidgetState, Pressed);
	OVERRIDE_STATE_ONEXIT(WidgetState, Pressed);
	
	virtual void	onCursorDestroyed(class BaseCursor* i_cursor);
	void 			onGameplayEnded();
	virtual void	onUpdate() override;
    
	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
    
    void            onSkyCannonUsed();
    void            onSkyCannonTouchOutside();
	
private:
	
	// Private Interface
	
	// Private Members (serialized)
    
    bool 			m_isCoolDown;
    bool 			m_levelEnded;
    float           m_timeRemaining;
    float           m_timeCoolDown;
};

namespace Message
{
	void SkyCannonPressed();
    void SkyCannonUsed();
    void SkyCannonTouchOutside();
}

#endif /* defined(__PlantsVersusZombies2__SkyCannonUI__) */
