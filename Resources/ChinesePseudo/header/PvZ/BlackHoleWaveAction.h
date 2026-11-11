/*
 * BlackHoleWaveAction.h
 *
 *  Created on: 2022-5-6
 *      Author: admin
 */

#ifndef BLACKHOLEWAVEACTION_H_
#define BLACKHOLEWAVEACTION_H_

#include "Wave.h"
#include "GameSubSystem.h"
#include "GameEventMgr.h"
#include "WaveGenerator.h"

class BlackHoleWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(BlackHoleWaveAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

private:
	void triggerBlackHole();

	pvztime_t m_blackHoleTipTime;
	BlackHolePtr m_blackHole;
};

class BlackHoleWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(BlackHoleWaveActionProps, WaveActionProperties, RtClass);

	BlackHoleWaveActionProps()
	: ColNumPlantIsDragged(0)
	{

	}

	RtClass* GetActionClass() const override { return BlackHoleWaveAction::StaticGetClass(); }

	int ColNumPlantIsDragged;
};

#endif /* BLACKHOLEWAVEACTION_H_ */
