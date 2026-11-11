//
//  TidalChangeWaveAction.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 5/21/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TidalChangeWaveAction__
#define __PlantsVersusZombies2__TidalChangeWaveAction__

#include "Wave.h"

enum TidalChangeType
{
	TIDALCHANGETYPE_ABSOLUTE,
	TIDALCHANGETYPE_RELATIVE,
};

struct TidalChangeDescription
{
	TidalChangeDescription()
	: ChangeType(TIDALCHANGETYPE_RELATIVE)
	, ChangeAmount(0.f)
	{}
	
	TidalChangeType ChangeType;
	float ChangeAmount;
};

class TidalChangeWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(TidalChangeWaveAction, WaveAction, RtClass);
	
	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
};

class TidalChangeWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(TidalChangeWaveActionProps, WaveActionProperties, RtClass);
	
	TidalChangeWaveActionProps() {}
	RtClass* GetActionClass() const override { return TidalChangeWaveAction::StaticGetClass(); }
	
	float GetFinalTidePosition(const float i_initialTidePosition) const;
	
	TidalChangeDescription	TidalChange;
};

#endif /* defined(__PlantsVersusZombies2__TidalChangeWaveAction__) */
