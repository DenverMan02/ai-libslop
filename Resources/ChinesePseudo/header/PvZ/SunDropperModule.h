//
//  SunDropperModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SunDropperModule_h
#define PlantsVersusZombies2_SunDropperModule_h

#include "LevelModule.h"
#include "Core.h"

class SunDropperProperties;

class SunDropperModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(SunDropperModule, LevelModule, RtClass);
	
	void SetPaused(bool i_paused);
	const SunDropperProperties* GetSunDropperProps();
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
	void calcNextSpawnTime();
	void startDroppingSun();
	void stopDroppingSun();
	void update();
	
	int m_numSunsDropped;
	pvztime_t m_nextSunDrop;
};


class SunDropperProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SunDropperProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return SunDropperModule::StaticGetClass();
	}
	
	SunDropperProperties()
	{
		InitialSunDropDelay = 0.f;
		SunCountdownBase = 0.f;
		SunCountdownRange = 0.f;
		SunCountdownMax = 0.f;
		SunCountdownIncreasePerSun = 0.f;
	}
	
	float InitialSunDropDelay;
	float SunCountdownBase;
	float SunCountdownRange;
	float SunCountdownMax;
	float SunCountdownIncreasePerSun;
};

#endif
