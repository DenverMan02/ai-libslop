//
//  TowerDefendUpgradeUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-12.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TowerDefendUpgradeUI__
#define __PlantsVersusZombies2__TowerDefendUpgradeUI__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PrimeTextWidget.h"

class TowerDefendUpgradeUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(TowerDefendUpgradeUI, UIWidget, RtClass);
	
	TowerDefendUpgradeUI();
	virtual ~TowerDefendUpgradeUI();
	
	// Public Interface (Inheritable)
	
	virtual void	Draw(Graphics* i_g) override;
    virtual bool	OnTouch(const Sexy::Touch& i_touch) override;
    virtual const   Sexy::Rect GetHitRect() override;
    
    void            SetPlantGridPosition(Point i_grid_pos);
    Point           GetPlantGridPosition(){ return m_PlantGridPosition; }
    void            SetSunCount(int i_sun);
    
protected:
	
	// Protected Interface (Inheritable)
    
	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;
    
    void 			onGameplayEnded();

private:
    Point               m_PlantGridPosition;
    
    PrimeTextWidget*    m_sunTextWidget;
    
    int                 m_nSun;
};

namespace Message
{
    void PlantTouch(const Point& i_pos);
	void PlantUpgradeTouch(const Point& i_pos);
}

#endif /* defined(__PlantsVersusZombies2__TowerDefendUpgradeUI__) */
