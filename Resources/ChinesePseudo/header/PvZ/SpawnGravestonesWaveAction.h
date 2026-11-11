//
//  SpawnGravestonesWaveAction.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 8/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __SPAWN_GRAVESTONES_WAVE_ACTION__
#define __SPAWN_GRAVESTONES_WAVE_ACTION__

#include <set>
#include <string>
#include <vector>

#include "PVZTypes.h"
#include "PlatformAutodetect.h"
#include "Point.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Wave.h"

namespace Sexy {
class MTRand;
}  // namespace Sexy

class GridItem;

struct GridItemPoolEntry
{
	GridItemPoolEntry()
	{
		Count = 1;
	}

	GridItemTypePtr		Type;
	int32				Count;
};

class SpawnGridItemsWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(SpawnGridItemsWaveAction, WaveAction, RtClass);
	
	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void onGridItemSpawn(GridItem* i_gridItem) {};
	virtual std::vector<GridItemTypePtr> generateSpawnPool() { return std::vector<GridItemTypePtr>(); };
	
	virtual bool MatchSpecialCondition(const Point& i_point) { return false; }

private:
	
	void initializeAction(MTRand& i_random, int i_waveNumber) override;
	void spawnGridItem(Point i_gridLocation, GridItemTypePtr i_type, std::string i_spawnAnimationID, std::string i_spawnSoundID);
	void movePlant(const Point& i_gridLocation);
};

class SpawnGravestonesWaveAction : public SpawnGridItemsWaveAction
{
public:
	RT_CLASS_DEFINE(SpawnGravestonesWaveAction, SpawnGridItemsWaveAction, RtClass);

protected:
	void onGridItemSpawn(GridItem* i_gridItem) override;
	std::vector<GridItemTypePtr> generateSpawnPool() override;
};

class SpawnModernPortalsWaveAction : public SpawnGridItemsWaveAction
{
public:
	RT_CLASS_DEFINE(SpawnModernPortalsWaveAction, SpawnGridItemsWaveAction, RtClass);

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	void onGridItemSpawn(GridItem* i_gridItem) override;
	std::vector<GridItemTypePtr> generateSpawnPool() override;

	bool MatchSpecialCondition(const Point& i_point) override;
};


class SpawnGridItemsWaveActionProps : public WaveActionProperties
{
	RT_CLASS_DEFINE(SpawnGridItemsWaveActionProps, WaveActionProperties, RtClass);
public:
	
	SpawnGridItemsWaveActionProps()
	{
		DisplacePlants = true;
		IgnoreGraveStone = false;
	}
	
	RtClass* GetActionClass() const override
	{
		return SpawnGridItemsWaveAction::StaticGetClass();
	}

	// Note: Function retains compatibility with existing json wave props names
	virtual std::vector<GridItemPoolEntry>		GetGridItemPool() const { return std::vector<GridItemPoolEntry>(); }
	virtual std::vector<Point>					GetSpawnPositionsPool() const { return std::vector<Point>(); }
	
	std::string							SpawnEffectAnimID;
	std::string							SpawnSoundID;
	bool								DisplacePlants;
	bool 								IgnoreGraveStone;

};

class SpawnGravestonesWaveActionProps : public SpawnGridItemsWaveActionProps
{
	RT_CLASS_DEFINE(SpawnGravestonesWaveActionProps, SpawnGridItemsWaveActionProps, RtClass);
public:

	RtClass* GetActionClass() const override
	{
		return SpawnGravestonesWaveAction::StaticGetClass();
	}

	std::vector<GridItemPoolEntry>		GetGridItemPool() const override { return GravestonePool; }
	std::vector<Point>					GetSpawnPositionsPool() const override;
	
	std::vector<GridItemPoolEntry>		GravestonePool;
	std::vector<Point>					SpawnPositionsPool;
	Rect                                SpawnPositionsRect;
};

class SpawnModernPortalsWaveActionProps : public SpawnGridItemsWaveActionProps
{
	RT_CLASS_DEFINE(SpawnModernPortalsWaveActionProps, SpawnGridItemsWaveActionProps, RtClass);
public:
	SpawnModernPortalsWaveActionProps()
	{
		PortalZombieCountOverride = -1;
		PortalZombieRandomListStartOverride = -1;
		PortalZombieRandomListEndOverride = -1;
	}
	
	RtClass* GetActionClass() const override
	{
		return SpawnModernPortalsWaveAction::StaticGetClass();
	}

	std::vector<GridItemPoolEntry>		GetGridItemPool() const override;
	std::vector<Point>					GetSpawnPositionsPool() const override;
	
	int									PortalRow;
	int									PortalColumn;
	std::string							PortalType;
	int									PortalZombieCountOverride;
	int									PortalZombieRandomListStartOverride;
	int									PortalZombieRandomListEndOverride;
};

#endif
