/*
 * SchoolBusWaveAction.h
 *
 *  Created on: 2023-5-10
 *      Author: admin
 */

#ifndef SCHOOLBUSWAVEACTION_H_
#define SCHOOLBUSWAVEACTION_H_

#include "Wave.h"
#include "BoardConstants.h"
#include "GridItemSchoolBus.h"

struct SchoolBusDescription
{
	SchoolBusDescription()
	{
		Row = Rand() % BoardConstants::NUMBER_OF_ROWS();
		Type = "school_bus_normal";
    }

	int 					Row;
	std::string				Type;
	GriditemSchoolBusParams	Params;
};

class SchoolBusWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(SchoolBusWaveAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	void SpawnSchoolBus(SchoolBusDescription des);
};

class SchoolBusWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(SchoolBusWaveActionProps, WaveActionProperties, RtClass);

	SchoolBusWaveActionProps() {}
	RtClass* GetActionClass() const override { return SchoolBusWaveAction::StaticGetClass(); }

	SchoolBusDescription Des;
};


#endif /* SCHOOLBUSWAVEACTION_H_ */
