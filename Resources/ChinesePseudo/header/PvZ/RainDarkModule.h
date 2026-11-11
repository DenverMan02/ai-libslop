//
//  RainDarkModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-18.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RainDarkModule__
#define __PlantsVersusZombies2__RainDarkModule__

#include "LevelModule.h"
#include "Core.h"

//////////

class RainDropper
{
public:
	RainDropper();
	
	void Start(pvztime_t i_duration, int i_shotTotal);
    void SetSnow(bool i_snow);
	void Update();
    
private:
    pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int       m_shotsFired;
	int       m_shotTotal;
	float     m_rotation;
	bool	  m_snow;
};

//////////

class RainDarkModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(RainDarkModule, LevelModule, RtClass);
	
	void SetPaused(bool i_paused);
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
	void calcNextSpawnTime();
	void startDroppingDark();
	void stopDroppingDark();
	void update();
	
	int         m_numDarkDropped;
	pvztime_t   m_nextDarkDrop;
    pvztime_t   m_nextRainDrop;
    
    RainDropper m_RainDropper;
};


class RainDarkProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(RainDarkProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return RainDarkModule::StaticGetClass();
	}
	
	RainDarkProperties()
	{
		InitialDarkDelay = 0.f;
		DarkCountdownBase    = 0.f;
		DarkCountdownRange   = 0.f;
		DarkCountdownMax     = 0.f;
		DarkCountdownIncreasePerDark = 0.f;
        Dark = true;
		Snow = false;
		Duration = 1.5f;
		ShotTotal = 100;
	}
	
	float InitialDarkDelay;
	float DarkCountdownBase;
	float DarkCountdownRange;
	float DarkCountdownMax;
	float DarkCountdownIncreasePerDark;
    bool  Dark;
	bool  Snow;
	float Duration;
	int ShotTotal;
};

#endif /* defined(__PlantsVersusZombies2__RainDarkModule__) */
