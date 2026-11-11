//
//  AirshipProgressMeter.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-6-12.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AirshipProgressMeter__
#define __PlantsVersusZombies2__AirshipProgressMeter__

#include "UIWidget.h"

class AirshipProgressMeter : public UIWidget
{
    
public:
	RT_CLASS_DEFINE(AirshipProgressMeter, UIWidget, RtClass);
    
	AirshipProgressMeter();
    
	// Public Interface (Inheritable)
    
	virtual void	Draw(Graphics* i_g) override;
    virtual void    AddToRenderQueue(class RenderQueue* i_queue) override;
    
	// Public Interface (Core)
    void            SetShield(bool i_shield);
	void            FlashDamage();
    
protected:
	// Protected Interface (Inheritable)
    
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
    
	virtual void		initLoadingResourcesGroupList() override;
	virtual void		registerForEvents() override;
    
    void                onAirshipTakeDamage(float i_amount);
    void                onAirshipSetPercentage(float i_percent);
    
private:
    
	// Event handling
	void				onGamePaused();
	void				onGameUnpaused();
    
	// Private Members (serialized)
	float                                   m_phasePercent;
	pvztime_t								m_damageFlashStartTime;
    bool                                    m_haveShield;
};

namespace Message
{
	void AirshipTakeDamage(float i_amount);
    void AirshipSetPercentage(float i_percent);
}

#endif /* defined(__PlantsVersusZombies2__AirshipProgressMeter__) */
