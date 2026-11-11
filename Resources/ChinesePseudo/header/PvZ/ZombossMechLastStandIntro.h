/*
 * ZombossMechLastStandIntro.h
 *
 *  Created on: 2014-3-19
 *      Author: jianglc
 */

#ifndef ZOMBOSSMECHLASTSTANDINTRO_H_
#define ZOMBOSSMECHLASTSTANDINTRO_H_

#include "LastStandMinigame.h"

class ZombossMechLastStandIntro : public LastStandMinigameModule
{
public:
	RT_CLASS_DEFINE(ZombossMechLastStandIntro, LastStandMinigameModule, RtClass);

	ZombossMechLastStandIntro();

	void AddReadySetPlantToAnimMgr(AnimationMgr* i_animMgr, float& io_endTime, Delegate0 i_delgateNameToCall, bool i_finishAfterSet = false) override;
	virtual void OnIntroDone() override;
    virtual bool isConsumableInstantPlant(PlantTypePtr i_plantTypePtr) override;

protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;

private:
	void showZomboss();
	void startHealthMeterFill();
	void continueReadySetPlant();
	void onUpdate();

	/// Transient
	Delegate0 m_callOnReadySetPlantDone;
	pvztime_t m_startHealthFillTime;
	pvztime_t m_endHealthFillTime;
	bool m_startedFill;
};

class ZombossMechLastStandIntroProperties : public LastStandMinigameProperties
{
public:
	RT_CLASS_DEFINE(ZombossMechLastStandIntroProperties, LastStandMinigameProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ZombossMechLastStandIntro::StaticGetClass();
	}
};


#endif /* ZOMBOSSMECHLASTSTANDINTRO_H_ */
