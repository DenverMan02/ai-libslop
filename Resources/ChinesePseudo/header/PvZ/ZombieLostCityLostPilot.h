//
//  ZombieLostCityLostPilot.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 5/4/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieLostCityLostPilot_h
#define PlantsVersusZombies2_ZombieLostCityLostPilot_h

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieWithActions.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_LostPilot, ZombieWithActionsState)
	ZS_LP_HangStart,
	ZS_LP_HangIdle,
	ZS_LP_HangEat,
	ZS_LP_HangCut,
	ZS_LP_HangBleed,
STATE_ENUM_END(ZombieState_LostPilot)

class ZombieLostCityLostPilotProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieLostCityLostPilotProps, ZombieWithActionsProps, RtClass);
	
	int	HangingAttackRectOffsetY;
	pvztime_t HangingNoEatTimeUntilDrop;
};

class ZombieLostCityLostPilot : public ZombieWithActions
{
public:
    RT_CLASS_DEFINE(ZombieLostCityLostPilot, ZombieWithActions, RtClass);

	void doFallFromSky();
	Sexy::Rect CalcZombieAttackRect() override;

	bool allowElectrocuteState() const override;
	bool allowAshState() const override;
	
	void OnBeforeBlown(BoardEntity* i_blowSource) override;
	void onMowedDown() override;

protected:
	void onExternalControlEvent() override;
	
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, HangStart);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangEat);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangCut);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangBleed);
	
	GroundEffectType GetTideEffect() const override { return GROUND_EFFECT_Tide_With_Tail; }
	
	void onStartBleeding() override;
	void immediatelyCutDown();
	bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;

private:
    void onZombieInitialize() override;

	void onHangStartCompleted(const std::string& i_animName);
	void onHangCutCompleted(const std::string& i_animName);

	pvztime_t m_TimeToFallFromHang = PVZ_EOT();
};

class ZombieAnimRig_LostCityLostPilot : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_LostCityLostPilot, ZombieAnimRig, RtClass);
	
	const std::string getRangedAttackAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	bool PlayHangStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayHangIdle();
	bool PlayHangEat();
	bool PlayHangCut(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	AnimHandle PlayDie() override;
	
	void SetIsHanging(bool i_hanging) { m_isHanging = i_hanging; }
	bool GetIsHanging() { return m_isHanging; }

private:
	bool m_isHanging = false;
};

#endif
