//
//  WaveDuplicator.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 4/5/2019.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WaveDuplicator_h
#define PlantsVersusZombies2_WaveDuplicator_h

#include "LevelModule.h"
#include "Wave.h"

class WaveDuplicatorModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(WaveDuplicatorModule, LevelModule, RtClass);
	
    WaveDuplicatorModule();
	
protected:

private:

    void createExtraZombieWaves(WaveManagerProperties *i_waveProps);
    
};

class WaveDuplicatorModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(WaveDuplicatorModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return WaveDuplicatorModule::StaticGetClass();
	}

	WaveDuplicatorModuleProperties()
	{
        WaveSetsToAppend = 2;
        PeriodOfWavesToLoop = 5;
	}
	
    int WaveSetsToAppend;
    int PeriodOfWavesToLoop;
};

#endif
