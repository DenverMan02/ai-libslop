//
//  WestStage.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WestStage_h
#define PlantsVersusZombies2_WestStage_h

#include "StageModule.h"

class WestStage : public StageModule
{
public:
	RT_CLASS_DEFINE(WestStage, StageModule, RtClass);
    
protected:

    virtual void				onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to) override;
	virtual void				stopZombieGroans() override;
	
};


class WestStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(WestStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return WestStage::StaticGetClass();
	}
};

#endif
