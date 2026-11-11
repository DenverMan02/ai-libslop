/*
 * ZombieFairyTaleImp.h
 *
 *  Created on: 2022-3-16
 *      Author: admin
 */

#ifndef ZOMBIEFAIRYTALEIMP_H_
#define ZOMBIEFAIRYTALEIMP_H_

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieImp.h"
#include "ZombieAnimRig_Imp.h"

STATE_ENUM_CHILD_BEGIN(ZombieFairyTaleImpState, ZombieStateImp)
ZS_FAIRYTALE_IMP_Entering,
ZS_FAIRYTALE_IMP_Running,
STATE_ENUM_END(ZombieFairyTaleImpState);

class ZombieFairyTaleImpProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieFairyTaleImpProps, ZombiePropertySheet, RtClass);

	ZombieFairyTaleImpProps()
	{
		RunSpeed = 0;
		CallKnightDelay = 0;
		CallKnightType = "";
	}

	float RunSpeed;
	float CallKnightDelay;
	std::string CallKnightType;
};

class ZombieFairyTaleImp : public ZombieImp
{
public:
    RT_CLASS_DEFINE(ZombieFairyTaleImp, ZombieImp, RtClass);

protected:
    void onInitialized() override;
    void onZombieInitialize() override;
    bool canAttack() override;
    bool CanBeHypnotized() const override { return false; }
    void onPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params) override;

private:
	// states
	OVERRIDE_STATE_ONENTER(ZombieState, Walk);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Ash);
	DECLARE_STATE_FUNCTIONS(ZombieState, Entering);
	DECLARE_STATE_FUNCTIONS(ZombieState, Running);

	void onLandingAnimStopped(const std::string& i_animLabel) override;

private:
    bool CheckEdge();
    void onWalkAnimContinued(const std::string&, const std::string&, int);
    void callKnight();
    void spawnZombie(const std::string& i_typeName, const Point& i_grid);

    pvztime_t m_nextCallKnightTime;
};

class ZombieAnimRig_FairyTaleImp : public ZombieAnimRig_Imp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_FairyTaleImp, ZombieAnimRig_Imp, RtClass);

	ZombieAnimRig_FairyTaleImp();
	virtual ~ZombieAnimRig_FairyTaleImp();

	void SetRunning(bool i_running);

protected:
	virtual const std::string getWalkAnimationName() override;

private:
	bool m_running;
};


#endif /* ZOMBIEFAIRYTALEIMP_H_ */
