/*
 * Plant_Stephania.h
 *
 *  Created on: 2020-12-14
 *      Author: admin
 */

#ifndef PLANT_STEPHANIA_H_
#define PLANT_STEPHANIA_H_

#include <stdio.h>
#include "PlantFramework.h"
#include "Projectile.h"
#include "PlantAnimRig.h"
#include "PlantPropertySheet.h"
#include "GameSubSystem.h"

struct StephaniaHitInfo
{
	StephaniaHitInfo(Point i_point, RtWeakPtr<class Effect_PopAnim> i_effect, bool i_plantfood, int i_level, std::vector<int> i_infos, float i_rate)
	: Location(i_point)
	, Effect(i_effect)
	, Plantfood(i_plantfood)
	, Level(i_level)
	, GirdInfos(i_infos)
	, DamageRate(i_rate)
	{

	}

	StephaniaHitInfo()
	: Plantfood(false)
	, Level(1)
	, DamageRate(1.0f)
	{

	}

	Point Location;
	RtWeakPtr<class Effect_PopAnim> Effect;
	bool Plantfood;
	int Level;
	std::vector<int> GirdInfos;
	float DamageRate;
};

struct StephaniaMinorHitInfo
{
	StephaniaMinorHitInfo(Point i_point, RtWeakPtr<class Effect_PopAnim> i_effect, float i_rate)
	: Location(i_point)
	, Effect(i_effect)
	, DamageRate(i_rate)
	{

	}

	StephaniaMinorHitInfo()
	: DamageRate(1.0f)
	{

	}

	Point Location;
	RtWeakPtr<class Effect_PopAnim> Effect;
	float DamageRate;
};

struct JuggledProjectileTimer
{
public:
	ProjectilePtr JuggledProjectile;
	pvztime_t ReturnTime;
};

class StephaniaProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(StephaniaProps, PlantPropertySheet, RtClass);

    StephaniaProps()
    {
    	NormalDamage = 100.0f;
    	MinorDamage = 50.0f;
    }

    float NormalDamage;
    float MinorDamage;

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

class PlantStephania : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantStephania, PlantFramework, RtClass);

    void			Initialize() override;
    void            UpdateActions() override;
    bool			CanApplyPlantfood() override;
    void            ApplyPlantfood() override;
    void			CancelPlantfood() override;
    Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void 			UpdateUnconditionally() override;
    bool 			OverrideProjectileCollision(class Projectile* i_projectile) override;
    virtual bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;

protected:
    void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
    enum State
	{
		STATE_JUGGLE = STATE_FRAMEWORK_BEGIN
	};

    void setState(const uint i_state);

    Projectile* 	firePlantfoodProjectile(Zombie* i_targetZombie, PlantWeapon i_plantWeapon);
    Projectile*     normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);

    void buildProjectileSets();
    bool canJuggleProjectile(Projectile* i_projectile);
	bool isProjectileArrivingAtCatchableAngle(Projectile* i_projectile);
	bool canThrowProjectile(Projectile* i_projectile);
	void storeProjectileInJuggleLimbo(Projectile* i_projectile);
	void launchProjectile(Projectile* i_projectile);
	void dropAllProjectiles();
	bool almostDoneJuggling();
	bool testForNeedToStartJuggling();

    std::set<const ProjectilePropertySheet*> m_juggleableProjectiles;
	std::set<const ProjectilePropertySheet*> m_unthrowableProjectiles;
	std::set<const ProjectilePropertySheet*> m_angleAgnosticProjectiles;

	// Serialized
	std::vector<JuggledProjectileTimer> m_juggledProjectiles;
	pvztime_t m_accumulatedTime;
};

class PlantAnimRig_Stephania : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Stephania, PlantAnimRig, RtClass) {}

    std::string getPlantFoodMainAnimName() override;
    void Juggling(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

class StephaniaProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(StephaniaProjectileProps, ProjectilePropertySheet, RtClass);

    StephaniaProjectileProps()
    {

    }
};

class StephaniaProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(StephaniaProjectile, Projectile, RtClass);

    virtual void onProjectileInitialized() override;

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

class StephaniaPlantfoodProjectile : public StephaniaProjectile
{
public:
    RT_CLASS_DEFINE(StephaniaPlantfoodProjectile, StephaniaProjectile, RtClass);

    bool OnCollideEntity(BoardEntity* i_entity) override;
};

class StephaniaSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(StephaniaSubsystem, GameSubSystem, RtClass);

    StephaniaSubsystem();
    ~StephaniaSubsystem() override;

    void GenerateSplitHit(int i_col, int i_row, bool i_plantfood, int i_level, float i_rate);
    void GenerateMinorSplitHit(int i_col, int i_row, float i_rate);

private:
    RtWeakPtr<Effect_PopAnim> createSplitAttack(int i_col, int i_row, int i_level);
    RtWeakPtr<Effect_PopAnim> createMinorSplitAttack(int i_col, int i_row);
    void onSplitEffectFinishedCallback(class StandaloneEffect*);
    void onMinorSplitEffectFinishedCallback(class StandaloneEffect*);
    const StephaniaHitInfo& FindHitInfo(class StandaloneEffect* i_effect);
    void RemoveHitInfo(RtWeakPtr<Effect_PopAnim> i_effect);
    const StephaniaMinorHitInfo& FindMinorHitInfo(class StandaloneEffect* i_effect);
    void RemoveMinorHitInfo(RtWeakPtr<Effect_PopAnim> i_effect);
    void DoSplashDamage(const StephaniaHitInfo& i_info);
    void DoMinorSplashDamage(const StephaniaMinorHitInfo& i_info);
    void findTargets(std::vector<BoardEntity*>& targets, int i_x, int i_y);
    bool isTargetGridPierce(int i_index, std::vector<int> i_infos);
    void dealDamageTo(DamageInfo i_info, bool i_fullDmg, std::vector<BoardEntity*> targets);

    std::vector<StephaniaHitInfo> m_hitInfos;
    std::vector<StephaniaMinorHitInfo> m_minorHitInfos;
};

#endif /* PLANT_STEPHANIA_H_ */
