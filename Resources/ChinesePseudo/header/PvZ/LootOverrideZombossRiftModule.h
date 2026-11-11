//
//  SunDropperModule.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/31/14.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LootOverrideZombossRiftModule_h
#define PlantsVersusZombies2_LootOverrideZombossRiftModule_h

#include "LevelModule.h"
#include "PVZTypes.h"
#include "Loot.h"

class LootOverrideZombossRiftModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(LootOverrideZombossRiftModule, LevelModule, RtClass);

protected:
	void registerForEvents() override;
    void onRiftEnterLootPhase();

	void onZombieSpawned(class Zombie *i_zombie);
    
    void resetLootTimer(int i_index);
    Loot getLootFromBattery(int i_index);
    int getFirstReadyLootBattery();
    
    std::vector<serializable_time_t> LootTimeRemaining;
};


struct ZombossRiftLootEntry
{
    float MinSeconds;
    float MaxSeconds;
	Loot Drop;
};

class LootOverrideZombossRiftModuleProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LootOverrideZombossRiftModuleProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LootOverrideZombossRiftModule::StaticGetClass();
	}

	LootOverrideZombossRiftModuleProps()
	{
	}

	std::vector<ZombossRiftLootEntry> Entries;
};

#endif
