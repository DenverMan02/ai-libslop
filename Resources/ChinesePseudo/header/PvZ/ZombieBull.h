//
//  ZombieBull.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/14/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieBull_h
#define PlantsVersusZombies2_ZombieBull_h

#include "Zombie.h"
#include "ZombieImp.h"

STATE_ENUM_CHILD_BEGIN(ZombieBullState, ZombieState)
	ZS_BULL_Entering,
	ZS_BULL_Pawing,
	ZS_BULL_PreRun,
	ZS_BULL_Running,
	ZS_BULL_Rearing,
STATE_ENUM_END(ZombieBullState);

class ZombieBull : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieBull, Zombie, RtClass);

	virtual std::string getElectrocutePAMName() const override;
    
    bool canPullDown();
    ZombieImp * takePullDown();

protected:
	virtual void onDestroy() override;
    void playDeathAnimation() override;
    void onApplyCondition(ZombieConditions i_condition) override;
	
private:
	// states
	OVERRIDE_STATE_ONENTER(ZombieState, Walk);
	OVERRIDE_STATE_ONEXIT(ZombieState, Electrocute);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Ash);
	DECLARE_STATE_FUNCTIONS(ZombieState, Entering);
	DECLARE_STATE_FUNCTIONS(ZombieState, Pawing);
	DECLARE_STATE_FUNCTIONS(ZombieState, PreRun);
	DECLARE_STATE_FUNCTIONS(ZombieState, Running);
	DECLARE_STATE_FUNCTIONS(ZombieState, Rearing);
	

	// anim callbacks
	void onPawingAnimDone(const std::string &i_animLabel);
	void onPreRunAnimDone(const std::string &i_animLabel);
	void onRearingAnimDone(const std::string &i_animLabel);
	void onWalkAnimContinued(const std::string&, const std::string&, int);

	virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params) override;
    
	// overridden from zombie base class
	virtual void onElectrocuted() override;

	virtual void onPlaceOnBoard() override;
	virtual void onUpdate() override;

	void launchImp();

	Rect calcBuckRect();

	bool m_hitEntity;
	bool m_walkCycled;
	int  m_damageState;
    
    bool m_IsRider;
};

#endif
