//
//  OutroModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_OutroModule_h
#define PlantsVersusZombies2_OutroModule_h

#include "LevelModule.h"


class OutroModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(OutroModule, LevelModule, RtClass);
	
	virtual void registerForEvents() override
	{}
	
private:
};

class OutroModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(OutroModuleProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return OutroModule::StaticGetClass();
	}
};

typedef RtWeakPtr<const OutroModuleProperties> OutroModulePropertiesPtr;

#endif
