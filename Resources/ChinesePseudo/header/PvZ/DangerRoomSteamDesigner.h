/*
 * DangerRoomSteamDesigner.h
 *
 *  Created on: 2023-9-4
 *      Author: admin
 */

#ifndef DANGERROOMSTEAMDESIGNER_H_
#define DANGERROOMSTEAMDESIGNER_H_

#include "Curve.h"
#include "DangerRoomLevelDesigner.h"
#include "DinoTimeWaveAction.h"
#include "InitialGridItemPlacer.h"
#include "WeightedOption.h"

struct SmokeManholeSpawnInfo
{
	SmokeManholeSpawnInfo()
	: SmokeManholeStartRow(0)
	{

	}

	ValueRange SmokeManholeCountMin;
	ValueRange SmokeManholeCountMax;

	ValueRange SmokeManholeColMin;
	ValueRange SmokeManholeColMax;

	ValueRange SmokeManholeStartTimeMin;
	ValueRange SmokeManholeStartTimeMax;

	int SmokeManholeStartRow;
};

struct ManholePipelineSpawnInfo
{
	ManholePipelineSpawnInfo()
	: ManholePipelineOperationTimePerGrid(0.0f)
	, ManholePipelineStartRow(0)
	{

	}

	ValueRange ManholePipelineCountMin;
	ValueRange ManholePipelineCountMax;

	ValueRange ManholePipelineColStartMin;
	ValueRange ManholePipelineColStartMax;

	ValueRange ManholePipelineColEndMin;
	ValueRange ManholePipelineColEndMax;

	ValueRange ManholePipelineDamageMin;
	ValueRange ManholePipelineDamageMax;

	float ManholePipelineOperationTimePerGrid;
	int ManholePipelineStartRow;
};

class DangerRoomSteamDesigner : public DangerRoomLevelDesigner
{
public:
	RT_CLASS_DEFINE(DangerRoomSteamDesigner, DangerRoomLevelDesigner, RtClass);
	DangerRoomSteamDesigner()
	{
		LevelRange = ValueRange(1, 100);
	}
	virtual ~DangerRoomSteamDesigner() {}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void GenerateExtraModules(const int i_level, Sexy::MTRand& io_rand, class LevelModuleManager* i_levelModuleMgr) const override;

	ValueRange LevelRange;

	SmokeManholeSpawnInfo SmokeManholeInfo;
	ManholePipelineSpawnInfo ManholePipelineInfo;
};


#endif /* DANGERROOMSTEAMDESIGNER_H_ */
