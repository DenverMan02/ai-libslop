/*
 * Plant_BoomFlower.h
 *
 *  Created on: 2021-7-13
 *      Author: admin
 */

#ifndef PLANT_BOOMFLOWER_H_
#define PLANT_BOOMFLOWER_H_

#include "PlantFramework.h"
#include "ComponentPlantLauncher.h"
#include "DamageLifetime.h"
#include "Projectile.h"


enum BoomFlowerCharge
{
	BOOM_FLOWER_CHARGE_NONE,
	BOOM_FLOWER_CHARGE_NORMAL
};

class BoomFlowerProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BoomFlowerProjectileProps, ProjectilePropertySheet, RtClass);

	BoomFlowerProjectileProps()
	{}

	int BalloonLifetime = 60;
	int BalloonMaxMerge = 1;
};

class BoomFlowerProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BoomFlowerProjectile, Projectile, RtClass);

	bool AddBalloon(int i_damage, int i_splashDamage);
	void onProjectileInitialized() override;
	int m_mergedBalloons = 1;
protected:
	void onUpdate(pvztime_t i_dt) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

private:
	pvztime_t m_explodeTime;
};

class ThemeBalloonProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ThemeBalloonProjectile, Projectile, RtClass);
	bool OnCollideGround() override;
	bool OnCollideEntity(BoardEntity* i_entity) override;
    int myrandom();
	int m_mergedBalloons = 1 ;
protected:
	void onUpdate(pvztime_t i_dt) override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	static ThemeBalloonProjectile* getThemeBalloonProjectile(Sexy::Point& i_gridPosition);
	static BoomFlowerProjectile* getBoomFlowerProjectile(Sexy::Point& i_gridPosition);

};

class BoomFlowerPlantfoodProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BoomFlowerPlantfoodProjectileProps, ProjectilePropertySheet, RtClass);

	BoomFlowerPlantfoodProjectileProps(){}
};

class BoomFlowerPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BoomFlowerPlantfoodProjectile, Projectile, RtClass);

	void onProjectileInitialized() override;
	void moveThroughTime(pvztime_t i_dt) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
};

class BoomFlowerAutoProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BoomFlowerAutoProjectileProps, ProjectilePropertySheet, RtClass);

	BoomFlowerAutoProjectileProps(){}

	float MaxRotationsPerSecond = 1.0;
};

class BoomFlowerAutoProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BoomFlowerAutoProjectile, Projectile, RtClass);

	enum
	{
		k_upperLimit = 100000,
	};

	 void FindNewTarget();
	 void SetOverrideTarget(BoardEntity* i_overrideTarget);

protected:
	 BoardEntity* FindTargetWithFlag(BoardEntityTypeFlag i_flag);
	 bool CanBeTarget(BoardEntity* i_entity);
	 void moveThroughTime(pvztime_t i_dt) override;
	 bool OnCollideEntity(BoardEntity* i_entity) override;
	 void onDeflection(class BoardEntity* i_deflector) override;
	 float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
	 SexyVector3 GetTargetPos(BoardEntity* i_target);

private:
	RtWeakPtr<BoardEntity> m_overrideTarget;
	bool m_deflected = false;
	float m_numbRate = 0.f;
	float m_numbDuration = 0.f;
};

class BoomFlowerAvatarProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BoomFlowerAvatarProjectileProps, ProjectilePropertySheet, RtClass);

	BoomFlowerAvatarProjectileProps()
	{
		StunDuration = 2.0f;
		StunDamage = 100.0f;
		ZombieLaunchTime = 1.0f;
		ZombieLaunchHeight = 300.0f;
	}

	float 		StunDamage;
	pvztime_t	StunDuration;
	pvztime_t 	ZombieLaunchTime;
	float 		ZombieLaunchHeight;
};

class BoomFlowerAvatarProjectile : public BoomFlowerPlantfoodProjectile
{
public:
	RT_CLASS_DEFINE(BoomFlowerAvatarProjectile, BoomFlowerPlantfoodProjectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	bool shouldStun(Zombie* i_zombie);
	bool shouldToss(Zombie* i_zombie);
	void stunZombie();
	void tossZombie();
};

class BoomFlowerProps : public PlantLauncherProps
{
public:
	RT_CLASS_DEFINE(BoomFlowerProps, PlantLauncherProps, RtClass);

	BoomFlowerProps()
	{
	}

	int BalloonSplashDamage = 0;
	int BalloonDamage = 0;
	int PFBalloonSplashDamage = 0;
	int PFBalloonDamage = 0;

	float NormalRechargeSeconds = 5;

	float Level2ReducedCd = 1.0f;
	float Level3ReducedCd = 1.0f;
	float Level2ReducedSunCost = 50.0f;
	float Level3ReducedSunCost = 50.0f;
	float Level5AutoRate = 0.15f;
};

class PlantBoomFlower : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBoomFlower, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	void registerForEvents() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual void onPostLoad() override;

protected:

	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void onKilled(bool i_instantKill) override;
    void onPlantfoodEnded() override;

private:

	void SetupLevelBasedProjectileProps(const BoomFlowerProps* props);
	bool OnSelected();
	void OnDeselected();
	bool OnFiring();
	static void OnFiredProjectile(Projectile& projectile, const PlantLauncherProps* props);
    bool OnAboutToFireProjectile(SexyVector3& i_position, const PlantLauncherProps* props);
    static ThemeBalloonProjectile* getThemeBalloonProjectile(Sexy::Point& i_gridPosition);
	static BoomFlowerProjectile* getBoomFlowerProjectile(Sexy::Point& i_gridPosition);

    void onReloaded();
    void Reload();

	void setChargeState(BoomFlowerCharge i_newChargeState);
	void updateCharging();
	bool hasCharges();
	void firePlantfoodBalloon();
    bool shouldStopPlantfoodState();

    bool hasTarget();
    void fireAutoBalloon();
    void setAutoFlag();
    bool CanBeTarget(BoardEntity* i_entity);

	enum State
	{
		STATE_START_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_ATTACK,
		STATE_FINISH_ATTACK
	};

	void setState(const uint i_state);

private:
	BoomFlowerCharge m_chargeState = BOOM_FLOWER_CHARGE_NONE;
	pvztime_t m_normalChargeTime;
    RtWeakPtr<Projectile> m_activePlantfoodProjectile;

	int m_damagePhase;
	bool m_hasTarget = false;
    bool m_isReloading = false;
    bool m_plantfoodProjectileFired = false;
    bool m_isAutoBalloon = false;

    BoardEntityPtr m_target;
    RtWeakPtr<ComponentPlantLauncher> m_launcherComponent;
    std::vector<RtWeakPtr<BoardEntity>> m_pfTargets;
};

class PlantAnimRig_BoomFlower : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_BoomFlower, PlantAnimRig, RtClass);

	PlantAnimRig_BoomFlower() {}
	void onPopAnimInitialized() override;
	void onPopAnimCommand(pvztime_t i_atTime, const std::string &i_command, const std::string &i_param) override;

	void UpdateIdleAnims(BoomFlowerCharge state);
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;

    bool PlayPlantFoodWithCallback(AnimStoppedReflectionDelegate i_onAnimEnded);

    std::string getIdleAnimationName() override;

	static const std::string IdleNotReadyAnims[];
    static const std::string IdleReadyAnims[];

private:
    bool m_isReadyToFire = true;
};

class PlantTypeBoomFlower : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeBoomFlower, PlantType, RtClass);
    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
    virtual int GetCost(int level) const;
};



#endif /* PLANT_BOOMFLOWER_H_ */
