//
//  FrostWindWaveAction.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/16/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FrostWindWaveAction__
#define __PlantsVersusZombies2__FrostWindWaveAction__

#include "Wave.h"

enum FrostWindDirection
{
	WIND_LEFT,
	WIND_RIGHT,
};

struct FrostWindDescription
{
	FrostWindDescription()
	: Direction(WIND_LEFT)
	, Row(0)
	{}
	
	FrostWindDirection Direction;
	int Row;
};

class FrostWindWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(FrostWindWaveAction, WaveAction, RtClass);
	
	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
	void SpawnWind(const FrostWindDescription& i_wind);
	static void SpawnWindStatic(const FrostWindDescription& i_wind);
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
private:
	int m_lastWind;
	float m_nextWindTime;
};

class FrostWindWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(FrostWindWaveActionProps, WaveActionProperties, RtClass);
	
	FrostWindWaveActionProps() {}
	RtClass* GetActionClass() const override { return FrostWindWaveAction::StaticGetClass(); }
	
	std::vector<FrostWindDescription>  Winds;
};

#endif /* defined(__PlantsVersusZombies2__FrostWindWaveAction__) */
