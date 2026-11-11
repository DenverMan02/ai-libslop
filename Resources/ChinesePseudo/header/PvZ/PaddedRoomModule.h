//
//  PaddedRoomModule.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/31/13
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PaddedRoomModule_h
#define PlantsVersusZombies2_PaddedRoomModule_h

#include "LevelModule.h"
#include "Core.h"

class PaddedRoomModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PaddedRoomModule, LevelModule, RtClass);
	
protected:
	virtual void registerForEvents() override;

private:
	void onLoadComplete();
};

class PaddedRoomProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PaddedRoomProperties, LevelModuleProperties, RtClass) {}
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return PaddedRoomModule::StaticGetClass();
	}
};

#endif
