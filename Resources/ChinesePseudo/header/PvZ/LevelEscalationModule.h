//
//  LevelEscalationModule.h
//  PlantsVersusZombies2
//
//  Was originally part of LevelOfTheDay but we needed to use
//  the functionality separate from the LOD-specific code.
//
//  Created by Jason Emery on 1/21/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelEscalationModule_h
#define PlantsVersusZombies2_LevelEscalationModule_h

#include <vector>

#include "LevelModule.h"
#include "RtDb.h"
#include "RtObject.h"

class WaveManagerProperties;
class ZombieType;
namespace Sexy {
class MTRand;
}  // namespace Sexy


class LevelEscalationModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(LevelEscalationModule, LevelModule, RtClass);
	
	LevelEscalationModule();
	virtual ~LevelEscalationModule();
	
	// Public Interface (Inheritable)

protected:
	
	// Protected Interface (Inheritable)
	
	void postInitialize() override;
	
	// Protected Interface (Core)
	
private:
	
	// Private Interface (Inheritable)
	
	// Private Interface (Core)
	
	void onLevelEnded();
	
	void configureJitteredWaves(int i_level, Sexy::MTRand &i_rand, struct RandomJitteredWaveConfig *o_config);
	void generateRandomEvents(int i_level, MTRand &i_random, class WaveManagerProperties *o_props);
	
	virtual std::vector<RtWeakPtr<ZombieType>> getPossibleZombies();

};

class LevelEscalationModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelEscalationModuleProperties, LevelModuleProperties, RtClass);
	
	LevelEscalationModuleProperties()
	{
		FlagCount = 1;
		WavesPerFlag = 1;
		PlantfoodToSpawnCount = 1;
		PointIncrementPerWave = 10;
		StartingPoints = 600;
	}
	
	RtClass* GetModuleClass() const override
	{
		return LevelEscalationModule::StaticGetClass();
	}
	
	RtWeakPtr<WaveManagerProperties> WaveManagerProps;
	std::vector<RtWeakPtr<ZombieType> > ZombiePool;
	int FlagCount = 1;
	int WavesPerFlag = 1;
	int PlantfoodToSpawnCount = 1;
	int PointIncrementPerWave = 10;
	int StartingPoints = 600;
};

#endif