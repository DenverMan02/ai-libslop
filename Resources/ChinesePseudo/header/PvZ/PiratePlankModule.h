//
//  PiratePlankModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PiratePlankModule_h
#define PlantsVersusZombies2_PiratePlankModule_h

#include "LevelModule.h"

class PiratePlankModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PiratePlankModule, LevelModule, RtClass) {}
	
protected:
	virtual void registerForEvents() override;

private:
	void addPlanks();
};

class PiratePlankProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PiratePlankProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PiratePlankModule::StaticGetClass();
	}
	
	std::vector<int> PlankRows;
};

#endif
