//
//  IceAgeStage.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 11/19/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IceAgeStage__
#define __PlantsVersusZombies2__IceAgeStage__

#include "StageModule.h"

class IceAgeStage : public StageModule
{
public:
	RT_CLASS_DEFINE(IceAgeStage, StageModule, RtClass);
};

class IceAgeStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(IceAgeStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return IceAgeStage::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__IceAgeStage__) */
