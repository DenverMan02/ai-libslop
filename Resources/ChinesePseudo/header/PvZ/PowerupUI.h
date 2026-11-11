//
//  PowerupUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/17/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupUI__
#define __PlantsVersusZombies2__PowerupUI__

#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PowerupType.h"
#include "PrimeTextWidget.h"

class PowerupUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(PowerupUI, UIWidget, RtClass);

	PowerupUI();
    virtual ~PowerupUI();

	virtual void				Draw(Graphics* i_g) override;

	void						SetPowerupType(PowerupTypePtr i_powerupType);
	inline class PowerupType*	GetPowerupType();
	
	inline ImagePtr				GetPowerupImage();
	inline ImagePtr				GetPowerupDownImage();
	inline ImagePtr				GetPowerupWarningImage();
    
    void						SetIsLocked(bool i_isLocked);
	bool						GetIsLocked() const { return m_isLocked; }

	void						onGameplayEnded();
	//PVZ2_CHINESE_START
    void                        OnLevelLoadComplete();
	//PVZ2_CHINESE_END
	
protected:
	virtual void				registerForEvents() override;

	bool						m_levelEnded;

private:
    void						drawLockIcon(Sexy::Graphics* i_g);
    
	PowerupTypePtr				m_powerupType;
	ImagePtr					m_powerupImage;
	ImagePtr					m_powerupDownImage;
	ImagePtr					m_powerupWarningImage;
    PrimeTextWidget*            m_costTextWidget;
    bool						m_isLocked;
};

inline class PowerupType* PowerupUI::GetPowerupType()
{
	return m_powerupType;
}

inline ImagePtr PowerupUI::GetPowerupImage()
{
	return m_powerupImage;
}

inline ImagePtr PowerupUI::GetPowerupDownImage()
{
	return m_powerupDownImage;
}

inline ImagePtr PowerupUI::GetPowerupWarningImage()
{
	return m_powerupWarningImage;
}
#endif /* defined(__PlantsVersusZombies2__PowerupUI__) */
