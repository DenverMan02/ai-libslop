//
//  SeedRainModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-4-13.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SeedRainModule__
#define __PlantsVersusZombies2__SeedRainModule__

#include "LevelModule.h"
#include "TimeMgr.h"
#include "BoardConstants.h"
#include "CollectableSeedRain.h"

enum ESeedRainType
{
    eSeedRainType_Plant = 0,
    eSeedRainType_Zombie,
    eSeedRainType_PlantFood,
    eSeedRainType_Count,
};

struct SeedRainContentProperties
{
	SeedRainContentProperties()
	{
        MaxCount = 5;
        Weight   = 5;
        SeedRainType = eSeedRainType_Plant;
    }
    
    inline bool operator==(const SeedRainContentProperties& p) const
	{
		return ((p.PlantTypeName == PlantTypeName) && (p.ZombieTypeName == ZombieTypeName) && (p.SeedRainType == SeedRainType) && (p.MaxCount == MaxCount) && (p.Weight == Weight));
	}
    
	inline bool operator!=(const SeedRainContentProperties& p) const
	{
		return ((p.PlantTypeName != PlantTypeName) || (p.ZombieTypeName != ZombieTypeName) || (p.SeedRainType != SeedRainType) || (p.MaxCount != MaxCount) || (p.Weight != Weight));
	}
    
    std::string PlantTypeName;
	std::string ZombieTypeName;
    
    int         SeedRainType;
    int         MaxCount;
    int         Weight;
};

class SeedRainModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(SeedRainModule, LevelModule, RtClass);
    
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
	void onLoadComplete();
    void onGameplayStarted();
    void onUpdate();
    void onMissionFinish();
    
    void onCollectableSeedRainFinished(CollectableSeedRain * i_collectable);
    
    void takeRain();
    
private:
    pvztime_t   m_TimeRain;
    int         m_targetGridLoc[BoardConstants::NUMBER_OF_COLUMNS_RAW][BoardConstants::NUMBER_OF_ROWS_RAW-1];
    bool        m_playerWon;
};

class SeedRainProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SeedRainProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return SeedRainModule::StaticGetClass();
	}
	
	SeedRainProperties()
	{
        RainInterval = 5.0f;
	}
    
    std::vector<SeedRainContentProperties> SeedRains;
    pvztime_t                              RainInterval;
};

#endif /* defined(__PlantsVersusZombies2__SeedRainModule__) */
