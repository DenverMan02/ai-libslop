//
//  EightiesStage.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 7/2/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EightiesStage__
#define __PlantsVersusZombies2__EightiesStage__

#include "AudioMgr.h"
#include "PVZTypes.h"
#include "RtObject.h"
#include "StageModule.h"
#include "WaveActionSpawnZombies.h"
#include "JamApplier.h"
#include "JamStageMechanic.h"

class StageForeground : public RtObject
{
public:
	RT_CLASS_DEFINE(StageForeground, RtObject, RtClass);
	
	virtual void Begin() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
	
	virtual void Draw(Graphics* i_g) = 0;
};

class EightiesStage : public StageModule
{
public:
	RT_CLASS_DEFINE(EightiesStage, StageModule, RtClass);
	void StartMusic() override;
	
protected:
	void initializeModule() override;
	
private:
	RtWeakPtr<JamStageMechanic> m_JamStageMechanic;
	JamListener m_jamListener;
};


class EightiesStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(EightiesStageProperties, StageModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return EightiesStage::StaticGetClass();
	}
};

class BassRainZombieSpawner : public ZombieRainSpawner
{
    RT_CLASS_DEFINE(BassRainZombieSpawner, ZombieRainSpawner, RtClass);
public:
    BassRainZombieSpawner()
    {
        // Do nothing.
    }
    
    void PostSpawnZombieSetup(Zombie* i_zombie, SexyVector3 i_destination, float i_fallDuration, float i_startHeight) override;
    
};

class BassRainZombieSpawnerProps : public ZombieRainSpawnerProps
{
    RT_CLASS_DEFINE(BassRainZombieSpawnerProps, ZombieRainSpawnerProps, RtClass);
public:
    
    BassRainZombieSpawnerProps()
    {
        WaveStartMessage = "[WARNING_BASSRAIN]";
    }
    
    RtClass* GetActionClass() const override
    {
        return BassRainZombieSpawner::StaticGetClass();
    }
    
};

#endif /* defined(__PlantsVersusZombies2__EightiesStage__) */