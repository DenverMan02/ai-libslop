//
//  ZombieModernAllStar.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 11/25/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieModernAllStar__
#define __PlantsVersusZombies2__ZombieModernAllStar__

#include <stdio.h>

#include "StateMachine.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieEnums.h"

STATE_ENUM_CHILD_BEGIN(ZombieModernAllStarState, ZombieState)
ZMASZS_Running,
ZMASZS_Tackling,
ZMASZS_PuntTheImp,
STATE_ENUM_END(ZombieModernAllStarState);

class ZombieImp;

class ZombieModernAllStar : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieModernAllStar, Zombie, RtClass);
	
	SexyVector3 CalcPositionInTime(pvztime_t i_time) override;
	
protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, Running);
	DECLARE_STATE_FUNCTIONS(ZombieState, Tackling);
	DECLARE_STATE_FUNCTIONS(ZombieState, PuntTheImp);
	
	void onPlaceOnBoard() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }
	
private:
	void searchAndTackle();
	void searchAndPuntTheImp();
	ZombieImp* findImpToPunt(Rect i_attackRect);
	
	void onTackleAnimationStopped(const std::string& i_animStopped);
	void onPuntingAnimationStopped(const std::string& i_animStopped);

	int m_runningCount;
};

class ZombieModernAllStarProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieModernAllStarProps, ZombiePropertySheet, RtClass);
	
	ZombieModernAllStarProps()
	{
		SmashDamage = 1000.0f;
		RunningSpeedScale = 1.0f;
	}
	
	int		SmashDamage;
	float	RunningSpeedScale;
};

class ZombieAnimRig_ModernAllStar : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ModernAllStar, ZombieAnimRig, RtClass);
	
	bool PlayRunning();
	void TacklePlant(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PuntTheImp(AnimStoppedReflectionDelegate i_onAnimStopped);

private:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieModernAllStar__) */
