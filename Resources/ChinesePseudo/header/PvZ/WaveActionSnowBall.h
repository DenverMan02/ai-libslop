/*
 * WaveActionSnowBall.h
 *
 *  Created on: 2022-11-16
 *      Author: admin
 */

#ifndef WAVEACTIONSNOWBALL_H_
#define WAVEACTIONSNOWBALL_H_

#include "Wave.h"

struct SnowBallData
{

	SnowBallData(){
		Column = 8;
		Row = 2;
	}

	int 	Column;
	int		Row;
};


class WaveActionSnowBall : public WaveAction
{
public:
	RT_CLASS_DEFINE(WaveActionSnowBall, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
	void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class WaveActionSnowBallProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WaveActionSnowBallProps, WaveActionProperties, RtClass);

	WaveActionSnowBallProps() {}
	RtClass* GetActionClass() const override { return WaveActionSnowBall::StaticGetClass(); }

	std::vector<SnowBallData> SnowBalls;
};

#endif /* WAVEACTIONSNOWBALL_H_ */
