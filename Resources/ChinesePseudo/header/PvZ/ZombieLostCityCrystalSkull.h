//
//  ZombieLostCityCrystalSkull.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 5/18/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLostCityCrystalSkull__
#define __PlantsVersusZombies2__ZombieLostCityCrystalSkull__

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "Zombie.h"

class StandaloneEffect;

STATE_ENUM_CHILD_BEGIN(ZombieState_CrystalSkull, ZombieState)
ZS_SKULL_Charging,
ZS_SKULL_Arming,
ZS_SKULL_Firing,
STATE_ENUM_END(ZombieState_CrystalSkull)

class ZombieCrystalSkull : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieCrystalSkull, Zombie, RtClass);
	
	void IncrementSunsClaimed(const int i_sunCurrency) override;
	void IncrementSunsCollected(const int i_sunCurrency) override;
	bool CanClaimSun() override;
	bool ShouldReleaseSun() override;
	SexyVector3 GetSunTarget() { return SexyVector3(-20.0, 0.0, 100.0) * GetConditionTracker().GetDrawScale(); }
	
protected:
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
private:
	
	DECLARE_STATE_FUNCTIONS(ZombieState, SKULL_Charging);
	DECLARE_STATE_FUNCTIONS(ZombieState, SKULL_Arming);
	DECLARE_STATE_FUNCTIONS(ZombieState, SKULL_Firing);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	void onArmingDone();
	void onLaserCooledDown();
	void onZombieInitialize() override;
	Rect calcLaserAttackRect() const;
	bool canFindLaserTarget();
	
	float m_timeToNextLaserAction = 0.0f;
	float m_timeLeftToCharge = PVZ_EOT();
};

//
//  Property sheet
//

class ZombieCrystalSkullProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieCrystalSkullProps, ZombiePropertySheet, RtClass);
	
	ZombieCrystalSkullProps()
	{
		ChargingTime = 10.f;
		ChargingTimeDecrementPerFiveSun = 0.1f;
		LaserBeamLength = 300.f;
		LaserBeamDamage = 150.f;
		LaserCooldownTime = 15.f;
	}
	
	float ChargingTime;
	float ChargingTimeDecrementPerFiveSun;
	float LaserBeamLength;
	float LaserBeamDamage;
	float LaserCooldownTime;
};

//
//  Anim rig
//

enum ZombieAnimRigState_CrystalSkull
{
	ZOMBIEANIM_SKULL_CHARGING_ON = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_SKULL_CHARGING,
	ZOMBIEANIM_SKULL_CHARGING_OFF,
	ZOMBIEANIM_SKULL_ATTACK_ON,
};

class ZombieAnimRig_CrystalSkull : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_CrystalSkull, ZombieAnimRig, RtClass) {}
	
	// Ra specific functionality
	virtual bool StartPowerSuck();
	virtual bool StopPowerSuck(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual bool StartFiring(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SetSkullGlow(float i_glowPct);
	
	SexyVector2 GetHeadOffset() override;
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
	void onAnimStopped() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieLostCityCrystalSkull__) */
