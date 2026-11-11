/*
 * ZombieBumperCar.h
 *
 *  Created on: 2023-4-28
 *      Author: admin
 */

#ifndef ZOMBIEBUMPERCAR_H_
#define ZOMBIEBUMPERCAR_H_

#include <string>
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"

// These states for zombie transforms each mode
STATE_ENUM_CHILD_BEGIN(ZombieState_BumperCar, ZombieState)
	ZS_BUMPERCAR_ENTERING,
	ZS_BUMPERCAR_PREPARING,
	ZS_BUMPERCAR_PREPARE_BUMPING,
	ZS_BUMPERCAR_BUMPING,
	ZS_BUMPERCAR_PREPARE_CHARGE,
	ZS_BUMPERCAR_CHARGING,
	ZS_BUMPERCAR_IMPACT,
	ZS_BUMPERCAR_BUMPING_IMPACT,
	ZS_BUMPERCAR_START_SPIN,
	ZS_BUMPERCAR_SPINNING,
	ZS_BUMPERCAR_END_SPIN,
	ZS_BUMPERCAR_RETURN_NORMAL,
	ZS_BUMPERCAR_NORMAL,
STATE_ENUM_END(ZombieState_BumperCar)

enum BumperCarSkillSet
{
	SkillSet_Bump,
	SkillSet_Charge,
	SkillSet_Spin
};

struct ChargeDegreeRange
{
	ChargeDegreeRange()
	: MinDegree(0)
	, MaxDegree(0)
	{

	}

	float MinDegree;
	float MaxDegree;
};

struct ChargeInfo
{
	ChargeInfo()
	: Damage(0)
	{

	}

	float Damage;
	SexyVector3 InitialVelocity;
};

class ZombieBumperCarProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBumperCarProps, ZombiePropertySheet, RtClass);
	ZombieBumperCarProps()
	: EnterSpeed(0)
	, ChargeLocation(0)
	, TriggerSkillInterval(0)
	, LaneChangeInterval(0)
	, JuggledInterval(0)
	, SpinSpeed(0)
	, SpinInterval(0)
	, SpinDuration(0)
	, MinChargeDuration(0)
	, NumDamageStates(0)
	{}

	float EnterSpeed;
	float ChargeLocation;
	Sexy::Rect BumperHitRect;
	SexyVector3 BumpAcceleration;
	SexyVector3 InitialBumpVelocity;
	float TriggerSkillInterval;
	float LaneChangeInterval;
	float JuggledInterval;
	float SpinSpeed;
	float SpinInterval;
	float SpinDuration;

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

	std::vector<ChargeDegreeRange> DegreeRanges;
	std::vector<ChargeInfo> ChargeInfos;

	float MinChargeDuration;
	int NumDamageStates;
};

class ZombieBumperCar : public Zombie
{
public:
	enum ChargeDirection
	{
		Charge_Left,
		Charge_Right
	};

	enum EdgeType
	{
		EdgeType_None,
		EdgeType_LeftCol,
		EdgeType_RightCol,
		EdgeType_UpperRow,
		EdgeType_BottomRow
	};

	RT_CLASS_DEFINE(ZombieBumperCar, Zombie, RtClass);

	ZombieBumperCar();

	void Trigger(BumperCarSkillSet i_set);

protected:
	void onUpdate() override;
	void onPlaceOnBoard() override;
	// Some future zombies do not have proper anims electrocute/ash
	bool allowElectrocuteState() const override
	{
		return false;
	}
	bool allowAshState() const override
	{
		return false;
	}

	bool CanBeMowed() const override { return false; }

	void onDraw(class Sexy::Graphics* i_g) override;
	void onZombieInitialize() override;
	void onPostLoad() override;
	bool OverrideProjectileCollision(class Projectile* i_projectile) override;

	void onWalkAnimContinued(const std::string&, const std::string&, int);

	void onDrawRotation(class Sexy::Graphics* i_g, SexyTransform2D& i_transform) override;

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Entering);
	DECLARE_STATE_FUNCTIONS(ZombieState, Preparing);
	DECLARE_STATE_FUNCTIONS(ZombieState, PrepareBumping);
	DECLARE_STATE_FUNCTIONS(ZombieState, Bumping);
	DECLARE_STATE_FUNCTIONS(ZombieState, PrepareCharge);
	DECLARE_STATE_FUNCTIONS(ZombieState, Charging);
	DECLARE_STATE_FUNCTIONS(ZombieState, Impact);
	DECLARE_STATE_FUNCTIONS(ZombieState, BumpingImpact);
	DECLARE_STATE_FUNCTIONS(ZombieState, SpinStart);
	DECLARE_STATE_FUNCTIONS(ZombieState, Spinning);
	DECLARE_STATE_FUNCTIONS(ZombieState, SpinEnd);
	DECLARE_STATE_FUNCTIONS(ZombieState, ReturnNormal);
	DECLARE_STATE_FUNCTIONS(ZombieState, Normal);

private:
	void onPreparingAnimDone(const std::string& i_animLabelName);
	void onPrepareChargedAnimDone(const std::string& i_animLabelName);
	void onImpactAnimDone(const std::string& i_animLabelName);
	void onBumpingImpactAnimDone(const std::string& i_animLabelName);
	void onPrepareBumpingAnimDone(const std::string& i_animLabelName);
	void onBumpingBackStopAnimDone(const std::string& i_animLabelName);
	void onSpinStartAnimDone(const std::string& i_animLabelName);
	void onSpinEndAnimDone(const std::string& i_animLabelName);

	void bump();
	void bumpingBack();
	void doBumpingImpact();
	void fixDegree(float& i_degree);
	void updateBumping(pvztime_t i_dt);
	void updateBumpingEdge();
	EdgeType checkBumpingEdge(bool i_return);
	EdgeType checkBumpingCollision();
	void charge(float i_degree, ChargeDirection i_direction);
	void updateCharge(pvztime_t i_dt);
	EdgeType checkEdge();
	EdgeType checkCollision();
	void createImpactEffect(const SexyVector3& i_position);
	void updateEdge();
	void updateCollision();
	Rect calcHitRect();
	void resetCharge();
	void doImpact();
	void resetBumping();
	void updateBumpingBack(pvztime_t i_dt);
	void updateBumpingBackEdge();
	void enterNormal();
	void triggerRandomSkill();
	bool moveToDestination(pvztime_t i_dt, const float i_destX, const float i_destY);
	void updateChargeReturn(pvztime_t i_dt);
	void findChargeReturnLocation();
	int getDegreeIndex(float i_degree);

	void prepareBumping();
	void prepareCharge();
	void preparing();
	void prepareSpin();
	void spinning();
	void doSpinning();
	void checkEnterCollision();

	void buildProjectileSets();
	bool canJuggleProjectile(class Projectile* i_projectile);
	bool isProjectileArrivingAtCatchableAngle(class Projectile* i_projectile);
	bool canThrowProjectile(class Projectile* i_projectile);
	void storeProjectileInJuggleLimbo(class Projectile* i_projectile);
	void updateJunggle();
	void dropAllProjectiles();
	void launchProjectile(class Projectile *i_projectile);

	void addChargeCount() { m_chargeCount += 1;}
	int getChargeCount() { return m_chargeCount; }
	void resetChargeCount() { m_chargeCount = 0; }
	float getChargeDamage();
	SexyVector3 getChargeVelocity();

	void setImmuneControl(bool i_enable, pvztime_t i_duration = PVZ_EOT());
	void updateDamageState();

	SexyVector3 m_chargeVelocity;
	bool m_walkCycled;
	ChargeDirection m_currentDirection;
	float m_currentDegree;
	Point m_previousPoint;
	bool m_chargeFirstStage;
	EdgeType m_cacheEdgeType;
	SexyVector3 m_bumpVelocity;
	pvztime_t m_nextSkillTime;
	pvztime_t m_nextJuggledTime;
	SexyVector3 m_chargeReturnLocation;
	pvztime_t m_spinEndTime;
	int m_chargeCount;
	float m_chargeDuration;
	float m_chargeStartTime;
	bool m_forceCharge;
	int m_damageState;

	// Transient
	std::set<const class ProjectilePropertySheet*> m_juggleableProjectiles;
	std::set<const class ProjectilePropertySheet*> m_unthrowableProjectiles;
	std::set<const class ProjectilePropertySheet*> m_angleAgnosticProjectiles;

	// Serialized
	std::vector<RiftProjectileTimer> m_juggledProjectiles;
	pvztime_t m_accumulatedTime;
};

class ZombieAnimRig_BumperCar : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_BumperCar, ZombieAnimRig, RtClass) {}

    const std::string getIdleAnimationName() override;
    const std::string getWalkAnimationName() override;

    void PlayPrepareBumping(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayPrepareCharge(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayCharging(ZombieBumperCar::ChargeDirection i_direction, bool i_firstStage, int i_degreeIndex);
    void PlayImpact(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayBumpingImpact(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayPreparing(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayBumping();
    void PlayBumpingBack();
    void PlayStop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayNormal();
    void PlaySpinning();
    void PlaySpinStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlaySpinEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void SetDamageState(int i_state);

protected:
    void onPopAnimInitialized() override;
};


#endif /* ZOMBIEBUMPERCAR_H_ */
