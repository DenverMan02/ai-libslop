//
//  LostCityStage.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 4/28/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LostCityStage_h
#define PlantsVersusZombies2_LostCityStage_h

#include "PVZTypes.h"
#include "RtObject.h"
#include "StageModule.h"
#include "WaveActionSpawnZombies.h"

class LostCityStage : public StageModule
{
public:
	RT_CLASS_DEFINE(LostCityStage, StageModule, RtClass);
	
protected:
	void registerForEvents() override;
	
private:
	void addForegroundToRenderQueue(RenderQueue* i_queue);
	void renderForeground(Graphics* i_g);
};


class LostCityStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(LostCityStageProperties, StageModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LostCityStage::StaticGetClass();
	}
};


class ParachuteRainZombieSpawner : public ZombieRainSpawner
{
	RT_CLASS_DEFINE(ParachuteRainZombieSpawner, ZombieRainSpawner, RtClass);
public:
	ParachuteRainZombieSpawner()
	{
		// Do nothing.
	}
	
	void PostSpawnZombieSetup(Zombie* i_zombie, SexyVector3 i_destination, float i_fallDuration, float i_startHeight) override;
	
};

class ParachuteRainZombieSpawnerProps : public ZombieRainSpawnerProps
{
	RT_CLASS_DEFINE(ParachuteRainZombieSpawnerProps, ZombieRainSpawnerProps, RtClass);
public:
	
	ParachuteRainZombieSpawnerProps()
	{
		WaveStartMessage = "[WARNING_PARACHUTERAIN]";
	}
	
	RtClass* GetActionClass() const override
	{
		return ParachuteRainZombieSpawner::StaticGetClass();
	}
	
};

#endif
