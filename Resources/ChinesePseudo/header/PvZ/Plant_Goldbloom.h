/*
 * Plant_Goldbloom.h
 *
 *  Created on: 2017-11-28
 *      Author: Administrator
 */

#ifndef PLANT_GOLDBLOOM_H_
#define PLANT_GOLDBLOOM_H_

#include <stdio.h>

#include <string>

#include "PopAnimRig.h"
#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "SunProducer.h"

struct PlantAction;

class GoldbloomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GoldbloomProps, PlantPropertySheet, RtClass);

	GoldbloomProps()
	{}
};

class PlantGoldbloom : public PlantFramework
{
private:
	enum GoldbloomState
	{
		STATE_GOLDBLOOM_PLANTING = STATE_FRAMEWORK_BEGIN,
		STATE_GOLDBLOOM_SUN_PRODUCTION,
		STATE_GOLDBLOOM_DONE
	};

public:
	RT_CLASS_DEFINE(PlantGoldbloom, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;

	void ProduceSun(const PlantAction& i_fromAction) override;
	bool HasShadow() override;

	bool IsInvincible() const override	{ return true; }
	bool CanBeShoveled() override		{ return false; }
	bool CanBeTargeted() override		{ return false; }
	void TakeSmashAttack(ZombiePtr i_srcZombie) override {}

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void onSunSpawnStopped(const std::string &i_animLabel);

private:
	int getState();
	void setState(int state);

	int m_state;
};

class PlantAnimRig_Goldbloom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Goldbloom, PlantAnimRig, RtClass);

	bool PlaySunSpawn(AnimStoppedReflectionDelegate i_onAnimStopped);
};


#endif /* PLANT_GOLDBLOOM_H_ */
