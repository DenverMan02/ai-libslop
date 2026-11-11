/*
 * PlantAnimRig_CarrotLauncher.h
 *
 *  Created on: 2014-7-31
 *      Author: jianglc
 */

#ifndef PLANTANIMRIG_CARROTLAUNCHER_H_
#define PLANTANIMRIG_CARROTLAUNCHER_H_

#include "Precompile.h"
#include "PlantAnimRig.h"
#include "RtObject.h"

enum CarrotRocketState
{
	NONE_ATTACK,
	LEVEL1_FIRST_ATTACK,
	LEVEL1_SECOND_ATTACK,
	LEVEL1_THIRD_ATTACK,
	LEVEL1_LAST_ATTACK,
	LEVEL2_FIRST_ATTACK,
	LEVEL2_SECOND_ATTACK,
	LEVEL3_ATTACK
};

enum CarrotMissileState
{
	MISSILE_NOT_READY,
	MISSILE_LAUNCHED,
	MISSILE_FINDING_TARGET,
	MISSILE_DROPPED,
	MISSILE_PLANTED,
	MISSILE_EXPLODING,
};

class PlantAnimRig_CarrotLauncher : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_CarrotLauncher, PlantAnimRig, RtClass);

	/// Overrides
	virtual bool PlayIdleLooped() override;
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	//virtual bool playPlantFoodMain();

	void PlayPlantFoodAttack();
//	virtual bool PlayPlantFoodEnd();
//	virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0);

	/// Custom functionality

	bool PlayRecoverLooped();
	bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	void SetAttackState(CarrotRocketState i_state){ m_attackState = i_state; }
	CarrotMissileState GetMissileState() { return m_missileState; }
	void SetMissileState(CarrotMissileState i_state){ m_missileState = i_state; }
	void SetIsAvatar(bool i_avatar){ m_isAvatar = i_avatar; }
private:
	CarrotRocketState m_attackState;
	bool m_plantFoodAttacked;
	CarrotMissileState m_missileState;
	bool m_isAvatar;
protected:
	virtual void onPopAnimInitialized() override;
	virtual void onAnimStopped() override;
};


#endif /* PLANTANIMRIG_CARROTLAUNCHER_H_ */
