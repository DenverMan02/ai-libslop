//
//  BossProgressMeterRift.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 1/13/20.
//  Copyright (c) 2020 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BossProgressMeterRift__
#define __PlantsVersusZombies2__BossProgressMeterRift__

#include <vector>

#include "BossProgressMeter.h"
#include "Image.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "UIWidget.h"

class BossProgressMeterRift : public BossProgressMeter
{
	
public:
	RT_CLASS_DEFINE(BossProgressMeterRift, BossProgressMeter, RtClass);
	
	BossProgressMeterRift();
	
	void	Draw(Graphics* i_g) override;
	
protected:
	
	void		initLoadingResourcesGroupList() override;
	void		registerForEvents() override;
    
    float       drawCalcFillPercent(int i_phaseNumber, float i_prevPhasePercentage) override;
    ImagePtr    getMeterFillImage() override;

private:
    
    void        onEnterLootPhase();
	
    bool        m_lootPhaseActive;
    
};

#endif
