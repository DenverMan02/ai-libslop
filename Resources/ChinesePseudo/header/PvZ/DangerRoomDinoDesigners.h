//
//  DangerRoomDinoDesigners.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomDinoDesigners__
#define __PlantsVersusZombies2__DangerRoomDinoDesigners__

#include "DangerRoomLevelDesigner.h"
#include "DinoTimeWaveAction.h"
#include "InitialGridItemPlacer.h"
#include "Utils.h"

class DangerRoomDinoDesigner : public DangerRoomLevelDesigner
{
public:
	RT_CLASS_DEFINE(DangerRoomDinoDesigner, DangerRoomLevelDesigner, RtClass);
	DangerRoomDinoDesigner()
	{
		LevelRange = ValueRange(1, 100);
	}
	virtual ~DangerRoomDinoDesigner() {}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void GenerateEvents(const int i_level, Sexy::MTRand& io_rand, WaveManagerProperties* io_props) const override;
	
	ValueRange LevelRange;
	ValueRange FirstDinoWavesMin;
	ValueRange FirstDinoWavesMax;
	ValueRange NextDinoWavesMin;
	ValueRange NextDinoWavesMax;
	ValueRange DinoTypesMin;
	ValueRange DinoTypesMax;
	ValueRange DinoCountInWaveMin;
	ValueRange DinoCountInWaveMax;
	
private:
	DinoSpawnType convertToDinoSpawnType(const std::string& i_type) const;

	int pickNextRow(std::vector<int>& io_rowsAllowed) const;
	void refillRowsAllowed(std::vector<int>& io_rowsAllowed) const;
	void ensureRowCountAvailable(std::vector<int>& io_rowsAllowed, int i_countNeeded) const;
};

#endif
