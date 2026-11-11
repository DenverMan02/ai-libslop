/*
 * RenaiWaveProgressMeter.h
 *
 *  Created on: 2019-9-10
 *      Author: zhousen
 */

#ifndef RENAIWAVEPROGRESSMETER_H_
#define RENAIWAVEPROGRESSMETER_H_

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "Wave.h"
#include "WaveProgressMeter.h"

class RenaiWaveProgressMeter : public WaveProgressMeter
{
public:
	RT_CLASS_DEFINE(RenaiWaveProgressMeter, WaveProgressMeter, RtClass);

	RenaiWaveProgressMeter();

	virtual void Draw(Graphics* i_g) override;

protected:
	void registerForEvents() override;

private:
	void setMoonWaveNumber(const int i_moon_wave_num);// which wave should we draw the moon img
	void setTotalWaveCount(const int i_wave_count);// total wave count

	void UpdateMoonSpacing();

	int m_MoonSpacing;// the offset one wave takes
	int m_MoonWaveNum;// which wave should draw moon
	int m_TotalWaveCount;// the stage wave count max
	ImagePtr m_MoonPtr;// the moon ptr
};


#endif /* RENAIWAVEPROGRESSMETER_H_ */
