//
//  GlacierModule.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 1/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GlacierModule__
#define __PlantsVersusZombies2__GlacierModule__

#include "LevelModule.h"
#include "ProbabilityTypeContainer.h"
#include "Utils.h"

namespace Message
{
	void PuddleSpawned(BoardEntity* i_entity);
}

class GlacierModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(GlacierModule, LevelModule, RtClass);

public:
	bool IsRoomForAdvance();
	void Advance();
	void Advance(int i_column);
    void Advance(int i_column, int i_row);
	int GetMaxAvailableColumn();
	
protected:
	void initializeModule() override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	
private:
	void onUpdate();
	void onLevelLoaded();
	void gameplayStarted();

	void spawnColumn(int i_column);
	bool isColumnAvailableToFill(int i_column);
	
	void destroyPlantsAt(int i_x, int i_y);
	
	void addZombieToBlock(GridItem* gridItem, int i_column);
	const ProbabilityTypeRecord& getZombieForColumn(int i_column);
    ZombiePtr GetBoss();
    
	ZombiePtr m_boss;
};

class GlacierModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(GlacierModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return GlacierModule::StaticGetClass();
	}
	GlacierModuleProperties()
	{
	}

	std::vector<ProbabilityTypeContainer> ZombieSpawnData;
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
};

#endif
