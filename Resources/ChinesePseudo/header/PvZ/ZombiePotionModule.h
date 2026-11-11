//
//  ZombiePotionModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombiePotionModule__
#define __PlantsVersusZombies2__ZombiePotionModule__

#include "LevelModule.h"
#include "Utils.h"

class ZombiePotionModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ZombiePotionModule, LevelModule, RtClass);

protected:
	void initializeModule() override;
	void registerForEvents() override;

private:
	void onUpdate();
	void onLevelLoaded();

	Point pickSpotForNewPotion();
	GridItemTypePtr pickRandomPotionType();
	void resetSpawnTimer();
	void stopSpawnTimer();
	int countPotionsOnBoard();

	pvztime_t m_nextPotionSpawnTime = PVZ_EOT();
};

class ZombiePotionModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombiePotionModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return ZombiePotionModule::StaticGetClass();
	}
	ZombiePotionModuleProperties()
	{
		MaxPotionCount = 15;
		InitialPotionCount = 3;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	ValueRange PotionSpawnTimer;
	int MaxPotionCount;
	int InitialPotionCount;
	std::vector<std::string> PotionTypes;
};

#endif /* defined(__PlantsVersusZombies2__ZombiePotionModule__) */
