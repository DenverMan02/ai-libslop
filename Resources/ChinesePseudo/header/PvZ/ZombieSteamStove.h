/*
 * ZombieSteamStove.h
 *
 *  Created on: 2017-12-12
 *      Author: Administrator
 */

#ifndef ZOMBIESTEAMSTOVE_H_
#define ZOMBIESTEAMSTOVE_H_

#include <string>
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"

// These states for zombie transforms each mode
STATE_ENUM_CHILD_BEGIN(ZombieState_Stvoe, ZombieState)
	ZS_RAISING_TEMP,
	ZS_FULL_TEMP,
	ZS_EXPLODE,
STATE_ENUM_END(ZombieState_Stvoe)

// Inner states
enum StoveState
{
    PVZ_BEGIN_ENUM(STOVESTATE_),
    STOVESTATE_UNKNOWN,
    STOVESTATE_READY_TO_RAISE_TEMP,
    STOVESTATE_TEMP_RASING,
    STOVESTATE_FULL_TEMP,
    STOVESTATE_ZERO_TEMP,
    PVZ_END_ENUM(STOVESTATE_)
};

class ZombieSteamStoveProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieSteamStoveProps, ZombiePropertySheet, RtClass);
	ZombieSteamStoveProps()
		: MaxTemp(100.0f),
		  TempPerSecond(10.0f),
		  ExplodeDamage(5000.0f),
		  ChillTempReduced(5.0f),
		  FrozenTempReduced(40.0f)
	{}
	float MaxTemp;
	float TempPerSecond;
	float ExplodeDamage;
	float ChillTempReduced;
	float FrozenTempReduced;
};

class ZombieSteamStove : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieSteamStove, Zombie, RtClass);

	ZombieSteamStove();

	void setState(StoveState i_state);
	StoveState getState();
	void updateState();

protected:
	void onUpdate() override;
	void onPlaceOnBoard() override;

	virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onZombieInitialize() override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void onEndCondition(ZombieConditions i_condition) override;

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, RaisingTemp);
	DECLARE_STATE_FUNCTIONS(ZombieState, FullTemp);
	DECLARE_STATE_FUNCTIONS(ZombieState, Explode);


private:
	bool CanRaiseTemp();
	// Transform states
	void onSkipRaisingTempAnimDone();
	void onSkipFullTempAnimDone();

	void onRaisingTempAnimDone(const std::string& i_animLabelName);
	void onFullTempAnimDone(const std::string& i_animLabelName);
	void onExplodeAnimDone(const std::string& i_animLabelName);

	bool IsInState(uint32 state) const { return m_state == state; }

	bool shouldExplode();
	void findAndExplodePlant();
	void doExplode(int i_sourceCol, int i_sourceRow, bool i_special);

	pvztime_t m_nextFullTempTime;
	StoveState m_state;
	float m_tempSpeed;
	pvztime_t m_frozenTime;
};

enum ZombieAnimRigState_SteamStoveTruck
{
	ZOMBIEANIM_STEAMSTOVE_LOW_LEVEL_TEMP = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_STEAMSTOVE_HIGH_LEVEL_TEMP,
	ZOMBIEANIM_STEAMSTOVE_EXPLODE
};

class ZombieAnimRig_SteamStoveTruck : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_SteamStoveTruck, ZombieAnimRig, RtClass);

    void PlayRaisingTemp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayFullTemp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayExplode(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SetTempState(int i_tempState);
	void SetState(ZombieAnimRigState_SteamStoveTruck state);
protected:
	void onPopAnimInitialized() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::string getWalkAnimationName() override;
	const std::string getDieAnimationName() override;
private:
	ZombieAnimRigState_SteamStoveTruck m_customState;
};


#endif /* ZOMBIESTEAMSTOVE_H_ */
