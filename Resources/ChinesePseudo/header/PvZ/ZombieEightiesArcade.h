//
//  ZombieEightiesArcade.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 8/11/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEightiesArcade__
#define __PlantsVersusZombies2__ZombieEightiesArcade__

#include <stdio.h>
#include "ZombieEnums.h"
#include "ZombieWithPushingAction.h"

STATE_ENUM_CHILD_BEGIN(ZombieEightiesArcadeState, ZombieWithActionsState)
	ZS_EIGHTIES_ARCADE_PlayGame,
STATE_ENUM_END(ZombieEightiesArcadeState)

class ZombieEightiesArcade : public ZombieWithPushingAction
{
public:
	RT_CLASS_DEFINE(ZombieEightiesArcade, ZombieWithPushingAction, RtClass);
	ZombieEightiesArcade();
	
	bool TryJamAction(GridItem *item) override;
	
protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, PlayGame);

	void onZombieInitialize() override;
	void StartJamming() override;
	void StopJamming() override;
	std::string GetJamStyle()override;
	bool isMyJamPlaying() { return m_isMyJamOn; }
	
	void onPlaceOnStreet() override;
	
	void spawnGridItemThatZombiePushes(int32_t column) override;
	
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }
	
private:
	void startVideoGame();
	
	bool m_isMyJamOn;
	bool m_isStreetZombie;
};

class ZombieEightiesArcadeProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieEightiesArcadeProps, ZombieWithActionsProps, RtClass);
	
	ZombieEightiesArcadeProps()
		: JamStyle("jam_8bit")
	{
	}
	
	std::string JamStyle;
};

//
//  AnimRig!
//

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_EightiesArcade : public ZombieWithPushingActionAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EightiesArcade, ZombieWithPushingActionAnimRig, RtClass);
	
private:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getFlagHandLayerNames();
	const std::vector<std::string>& getNoFlagHandLayerNames();
	const std::vector<std::string>& getConeLayerNames();
	const std::vector<std::string>& getBucketLayerNames();
};

#endif /* defined(__PlantsVersusZombies2__ZombieEightiesArcade__) */
