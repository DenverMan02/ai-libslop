//
//  ZombieEightiesPunk.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 7/1/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEightiesPunk__
#define __PlantsVersusZombies2__ZombieEightiesPunk__

#include <stdio.h>
#include "DamageInfo.h"
#include "RtObject.h"
#include "Zombie.h"
#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_EightiesPunk, ZombieState)
    ZS_PUNK_Push,
	ZS_PUNK_Kick_Damage_Target,
STATE_ENUM_END(ZombieState_EightiesPunk)

class ZombieEightiesPunkProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieEightiesPunkProps, ZombiePropertySheet, RtClass);
	
	ZombieEightiesPunkProps()
	{
		JamStyle = "";
		PushCooldown = 2.0f;
		PushDamageToZombies = 100;
		KickFallbackDPS = 100;
	}
	
	std::string			JamStyle;
	float				PushCooldown;
	float				PushDamageToZombies;
	float				KickFallbackDPS;
	PlantRestrictionSet PlantsToKickInsteadOfPush;
};

class ZombieEightiesPunk : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieEightiesPunk, Zombie, RtClass);
	
protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);

	DECLARE_STATE_FUNCTIONS(ZombieState, Push);
	DECLARE_STATE_FUNCTIONS(ZombieState, Kick_Damage_Target);
	
	void onStartBleeding() override;
	void onZombieInitialize() override;
	void onPlaceOnBoard() override;
	void onPlaceOnStreet() override;
	
	void StartJamming() override;
	void StopJamming() override;
	std::string GetJamStyle() override;

private:
    bool shouldPush(const BoardEntity* i_target);
	bool shouldJamIneffectually(const BoardEntity* i_target);
	// bool shouldDamagePlant(const Plant* i_plant);
	bool shouldDamagePlantGroup(const PlantGroup* i_plant);
	void changeStatesBasedOnJams();

    void findAndPushTarget();
	void tryDamageZombie(BoardEntity *target);
	void tryPushPlant(BoardEntity *target);
	bool isMyJamPlaying() { return m_curIsMyJam; }
	
    bool				m_curIsMyJam;
	float				m_nextPushTime;
	bool				m_isAStreetZombie;
};

class ZombieAnimRig_EightiesPunk : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EightiesPunk, ZombieAnimRig, RtClass);
	
	ZombieAnimRig_EightiesPunk();
	
	void StartJamming();
	void StopJamming();
	
protected:
	const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	
private:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	bool m_isJamming;
};

#endif /* defined(__PlantsVersusZombies2__ZombieEightiesPunk__) */
