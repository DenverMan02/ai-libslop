//
//  SpeedyLaneChallenge.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/4/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SpeedyLaneChallenge_h
#define PlantsVersusZombies2_SpeedyLaneChallenge_h

#include "Core.h"
#include "LevelModule.h"
#include "GameEventMgr.h"
#include "ZombieEnums.h"

struct SpeedyLaneEntry
{
	SpeedyLaneEntry()
	{
		CurrentRow = TargetRow = 0;
	}
	
	SpeedyLaneEntry(int i_row)
	{
		CurrentRow = TargetRow = i_row;
	}
	
	int CurrentRow;
	int TargetRow;
};

class SpeedyLaneChallengeModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(SpeedyLaneChallengeModule, LevelModule, RtClass);

protected:
	virtual void initializeModule();
	virtual void registerForEvents();
	
private:
	void onLevelInit();
	void onLevelEnded();
	void onGameplayStarted();
	void onUpdate();
	void addToRenderQueue(class RenderItem* i_renderQueue, int& io_renderQueueIndex);
	void drawSpeedyLaneMarkers(Graphics* i_g);
	void onZombieSpawned(class Zombie* i_zombie);
	
	ZombieConditions calcConditionFromModAmount(int i_modCount);
	
	void setAllZombieConditionsFromLaneValues();

	int pickNewSpeedyLane(bool i_allowAlreadySpeedyLane);

	std::vector<SpeedyLaneEntry> m_speedyLanes;
	pvztime_t	m_lastLaneSwitchTime;
};


class SpeedyLaneChallengeProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SpeedyLaneChallengeProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const
	{
		return SpeedyLaneChallengeModule::StaticGetClass();
	}
	
	SpeedyLaneChallengeProperties()
	{
		SpeedyLaneCount = 1;
		SpeedyLaneSwitchDelay = 0.f;
		SpeedyLaneIncreaseSpeedinessProbability = 0.25f;
		ConditionsFollowLaneChanges = true;
	}
	
	int 	SpeedyLaneCount;
	float 	SpeedyLaneSwitchDelay;
	float 	SpeedyLaneIncreaseSpeedinessProbability;
	
	bool	ConditionsFollowLaneChanges;
};



#endif
