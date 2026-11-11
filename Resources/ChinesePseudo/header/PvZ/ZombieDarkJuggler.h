//
//  ZombieDarkJuggler.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/23/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieDarkJuggler__
#define __PlantsVersusZombies2__ZombieDarkJuggler__

#include "Zombie.h"
#include "Projectile.h"
#include "ZombiePropertySheet.h"

STATE_ENUM_CHILD_BEGIN(ZombieDarkJugglerState, ZombieState)
	ZS_JUGGLER_JuggleIdle,
	ZS_JUGGLER_JuggleWalk,
	ZS_JUGGLER_JuggleStop,
STATE_ENUM_END(ZombieDarkJugglerState)

class ZombieDarkJugglerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieDarkJugglerProps, ZombiePropertySheet, RtClass);

	ZombieDarkJugglerProps()
		: MaxProjectilesToJuggle(3)
		, JuggleLaunchDelay(2.0f)
		, MoveSpeedMultiplierWhileJuggling(0.8f)
		, CatchArcDegrees(120.0f)
	{}

	SexyVector3 LaunchVelocity;
	SexyVector3 LaunchAcceleration;
	ValueRange LaunchHeight;

	int MaxProjectilesToJuggle;
	float JuggleLaunchDelay;
	float MoveSpeedMultiplierWhileJuggling;
	float CatchArcDegrees;

	std::vector<std::string> JuggleableProjectiles;
	std::vector<std::string> UnthrowableProjectiles;
	std::vector<std::string> AngleAgnosticProjectiles;
};

struct JuggledProjectileTimer
{
public:
	ProjectilePtr JuggledProjectile;
	pvztime_t ReturnTime;
};

enum ZombieAnimRigState_Juggler
{
	ZOMBIEANIM_JUGGLER_START_SPIN = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_JUGGLER_SPINNING,
	ZOMBIEANIM_JUGGLER_STOP_SPIN,
	ZOMBIEANIM_JUGGLER_SPINNING_WALKING,
};

class ZombieAnimRig_DarkJuggler : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DarkJuggler, ZombieAnimRig, RtClass);

	ZombieAnimRig_DarkJuggler();

	bool PlayWalkAndSpin();
	bool PlaySpin();
	bool PlayStopSpin(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	void doWalkAndSpin();
	void doIdleAndSpin();
	void doSpinStop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;

	bool		m_DesireWalk;
};

class ZombieDarkJuggler : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieDarkJuggler, Zombie, RtClass);

	ZombieDarkJuggler();

	bool IsJuggling() const;

	bool OverrideProjectileCollision(class Projectile* i_projectile) override;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	DECLARE_STATE_FUNCTIONS(ZombieState, JuggleIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, JuggleWalk);
	DECLARE_STATE_FUNCTIONS(ZombieState, JuggleStop);

	void onInitialized() override;
	void onZombieInitialize() override;
	void onPostLoad() override;
	void onUpdate() override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void onEndCondition(ZombieConditions i_condition) override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	DamageTypeFlags getEatingDamageType() const override;

	bool canJuggleProjectile(Projectile* i_projectile);
	bool isProjectileArrivingAtCatchableAngle(Projectile* i_projectile);
	bool canThrowProjectile(Projectile* i_projectile);
	void storeProjectileInJuggleLimbo(Projectile* i_projectile);
	void launchProjectile(Projectile* i_projectile);
	void dropAllProjectiles();
	bool almostDoneJuggling();
	bool testForNeedToStartJuggling();

private:
	void onAnimationJuggleStopDone(const std::string& i_animName);
	void buildProjectileSets();

	void startSpinAudio();
	void stopSpinAudio();

	// Transient
	std::set<const ProjectilePropertySheet*> m_juggleableProjectiles;
	std::set<const ProjectilePropertySheet*> m_unthrowableProjectiles;
	std::set<const ProjectilePropertySheet*> m_angleAgnosticProjectiles;

	// Serialized
	std::vector<JuggledProjectileTimer> m_juggledProjectiles;
	pvztime_t m_accumulatedTime;
	bool m_playingSpinAudio;
};

#endif /* defined(__PlantsVersusZombies2__ZombieDarkJuggler__) */
