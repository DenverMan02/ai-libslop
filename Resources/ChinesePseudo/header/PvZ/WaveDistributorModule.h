//
//  WaveDistributorModule.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/8/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WaveDistributorModule_h
#define PlantsVersusZombies2_WaveDistributorModule_h

#include <string>

#include "LevelModule.h"
#include "PVZTypes.h"
#include "RtObject.h"


enum WaveDistributorPattern
{
    WAVE_DISTRIBUTOR_EVEN,
    WAVE_DISTRIBUTOR_EARLY,
    WAVE_DISTRIBUTOR_SCATTERED
};

namespace WaveDistributor
{
	bool ShouldPerformNextDistribution(bool i_isFinalWave, int i_numDistributionsComplete, int i_numTotalDistributions, WaveDistributorPattern i_distributionPattern, float i_assumedLevelEndpoint = 0.8f);
}

class WaveDistributorModule : public LevelModule
{ 
public:
    RT_CLASS_DEFINE(WaveDistributorModule, LevelModule, RtClass);
	
protected:
    void registerForEvents() override;
	
	void postInitialize() override;
    
    void onWaveStart(int i_wave, WaveType::WaveType i_type, bool i_isFinal);
    
    void GatherRuntimeResourceRequirements(std::set<std::string>& io_resGroupNames) const override;
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

private:
    bool needsNextAddedWave(int i_wave, bool i_finalWave);
    void addWaveActions(int i_wave);
    WaveAction* createAction(WaveActionPropertiesPtr i_actionProps, int i_wave) const;
    
private:
    int m_wavesAdded = 0;
    
};


class WaveDistributorModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(WaveDistributorModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return WaveDistributorModule::StaticGetClass();
	}
	
	WaveDistributorModuleProperties()
	{
	}
	
    std::vector<WaveActionPropertiesPtr> WavesToDistribute;
    float             LevelEndpoint = 0.8f;
    int               Count = 1;
    WaveDistributorPattern  Pattern = WAVE_DISTRIBUTOR_EARLY;

};

#endif
