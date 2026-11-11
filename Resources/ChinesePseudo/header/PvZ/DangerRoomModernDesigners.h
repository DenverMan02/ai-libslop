//
//  DangerRoomModernDesigners.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 11/17/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomModernDesigners__
#define __PlantsVersusZombies2__DangerRoomModernDesigners__

#include "Curve.h"
#include "DangerRoomLevelDesigner.h"
#include "DinoTimeWaveAction.h"
#include "InitialGridItemPlacer.h"
#include "WeightedOption.h"

class DangerRoomModernDesigner : public DangerRoomLevelDesigner
{
public:
	RT_CLASS_DEFINE(DangerRoomModernDesigner, DangerRoomLevelDesigner, RtClass);
	DangerRoomModernDesigner()
	{
		LevelRange = ValueRange(1, 100);
	}
	virtual ~DangerRoomModernDesigner() {}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void GenerateEvents(const int i_level, Sexy::MTRand& io_rand, WaveManagerProperties* io_props) const override;
	
	ValueRange LevelRange;
	ValueRange FirstPortalWavesMin;
	ValueRange FirstPortalWavesMax;
	ValueRange NextPortalWavesMin;
	ValueRange NextPortalWavesMax;
	ValueRange PortalTypesMin;
	ValueRange PortalTypesMax;
	ValueRange PortalCountInWaveMin;
	ValueRange PortalCountInWaveMax;
	
	ValueRange ColumnToSpawnMin;
	ValueRange ColumnToSpawnMax;
	
	ValueRange ZombiesToSpawnMin;
	ValueRange ZombiesToSpawnMax;
	ValueRange ZombieRandomListStartMin;
	ValueRange ZombieRandomListStartMax;
	ValueRange ZombieRandomListEndMin;
	ValueRange ZombieRandomListEndMax;
	
	std::vector<StringWeightedOption> PortalTypePool;
	
private:
//	PortalSpawnType convertToPortalSpawnType(const std::string& i_type) const;

	int pickNextRow(std::vector<int>& io_rowsAllowed, Sexy::MTRand& i_rand) const;
	void refillRowsAllowed(std::vector<int>& io_rowsAllowed) const;
	void ensureRowCountAvailable(std::vector<int>& io_rowsAllowed, int i_countNeeded) const;
};

#endif
