//
//  ZombieEightiesMC.h
//  PlantsVersusZombies2
//
//  Created by Mina, Elliott on 7/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEightiesMC__
#define __PlantsVersusZombies2__ZombieEightiesMC__

#include <stdio.h>
#include "DamageInfo.h"
#include "PlatformAutodetect.h"
#include "RtObject.h"
#include "Zombie.h"
#include "Plant.h"
#include "ZombieAnimRig_Basic.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_EightiesMC, ZombieState)
ZS_JamAttack,
STATE_ENUM_END(ZombieState_EightiesMC)

class ZombieEightiesMCProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieEightiesMCProps, ZombiePropertySheet, RtClass);
    
    ZombieEightiesMCProps()
    {
        JamStyle = "";
        JamAttackRadius = 0.0f;
        JamAttackDamage = 0.0f;
    }
    
    std::string JamStyle;
    float JamAttackRadius;
    float JamAttackDamage;
};

class ZombieEightiesMC : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieEightiesMC, Zombie, RtClass);
    ZombieEightiesMC();

    void StartJamming() override;
	void StopJamming() override;
	std::string GetJamStyle() override;
	BoardEntity* findTarget() override;
    bool CanBeGummed() const override { return false; }

protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    DECLARE_STATE_FUNCTIONS(ZombieState, JamAttack);

    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onAttackJamAnimComplete(const std::string&);

private:
    bool                        canJamAttack();
    std::vector<BoardEntity*>	findTargetsInJamAttackRange();
	std::vector<BoardEntity*>	findEntitiesInJamAttackRange();
	bool						isJamAttackablePlant(BoardEntity* entity);
	bool						isJamAttackableGridItem(BoardEntity* entity);
	void                        jamAttack();

    bool                        m_isJamming;
};

class ZombieAnimRig_EightiesMC : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EightiesMC, ZombieAnimRig, RtClass);
	ZombieAnimRig_EightiesMC()
	{
		m_jamActive = false;
	}
	void ActivateJam();
	void DeactivateJam();
	void PlayJamAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::string getWalkAnimationName() override;
	const std::string getIdleAnimationName() override;
	
private:
	bool m_jamActive;
};

#endif /* defined(__PlantsVersusZombies2__ZombieEightiesMC__) */
