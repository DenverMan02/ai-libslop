//
//  ZombieModifierModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieModifierModule_h
#define PlantsVersusZombies2_ZombieModifierModule_h

#include "LevelModule.h"
#include "GameEventMgr.h"

class ZombieModifierModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ZombieModifierModule, LevelModule, RtClass) {}
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;

private:
	void onZombieSpawned(class Zombie* i_zombie);
};

class ZombieModifierProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombieModifierProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return ZombieModifierModule::StaticGetClass();
	}
	
	ZombieModifierProperties()
	{
		Speedy = false;
	}
	
	bool Speedy;
	// TODO -- Lots more!
};


#endif
