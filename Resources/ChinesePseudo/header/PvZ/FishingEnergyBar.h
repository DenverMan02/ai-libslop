//
//  FishingEnergyBar.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.15
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FishingEnergyBar__
#define __PlantsVersusZombies2__FishingEnergyBar__

#include "UIWidget.h"

class FishingEnergyBar : public UIWidget
{
public:
	RT_CLASS_DEFINE(FishingEnergyBar, UIWidget, RtClass);
	FishingEnergyBar();
    
	// Public Interface (Inheritable)
	virtual void		Draw(Graphics* i_g) override;

	void					InitEnergy(int curEnergy, int maxEnergy);
	void					SetEnergy(int val);
	int					GetCurrentEnergy() const { return m_curEnergy; }
	int					GetMaxEnergy() const { return m_maxEnergy; }

	Rect				CalcPlusButtonRect();
    
protected:
	// Protected Interface (Inheritable)
	virtual void		initLoadingResourcesGroupList() override;
	virtual void		registerForEvents() override;
    
protected:
	// Event handling
	void					onGamePaused();
	void					onGameUnpaused();
	bool					onHandleTouch(const Sexy::Touch& i_touch);
	void					onCancelTouch();
    
protected:
	Sexy::TouchID	m_touchIdent;
	int						m_curEnergy;
	int						m_maxEnergy;
};

namespace Message
{
	void FishingEnergyNeedReset();
}

#endif /* defined(__PlantsVersusZombies2__FishingEnergyBar__) */
