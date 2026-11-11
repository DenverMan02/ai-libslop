#ifndef __PLANT_ELAEOCARPUS_H__
#define __PLANT_ELAEOCARPUS_H__

#include "Plant.h"
#include "Projectile.h"
#include "PlantFramework.h"
#include "GameSubSystem.h"
#include "Precompile.h"
#include "GridItemAnimation.h"
#include "EffectObject.h"

#pragma mark - ElaeocarpusProps

class ElaeocarpusProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ElaeocarpusProps, PlantPropertySheet, RtClass);

    ElaeocarpusProps()
    {
        ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
        PlantFoodAttackBoostTime = 10.0f;
        PercentKillLowHP = 0.1f;
        PercentKillLowHPBoost = 0.2f;
        WindDamge = 50;
    }
    float WindDamge;
    float PlantFoodAttackBoostTime;
    float PercentKillLowHP;
    float PercentKillLowHPBoost;
    float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

#pragma mark - PlantElaeocarpus

class PlantElaeocarpus : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantElaeocarpus, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
    virtual void ApplyPlantfood() override;
	virtual void DoSpecial(int i_extraParam) override;
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
protected:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
private:
    int m_attackMode;
    pvztime_t m_plantfoodTime;
    int m_jumpTimes;
};

#pragma mark - PlantAnimRig_Elaeocarpus

class PlantAnimRig_Elaeocarpus : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Elaeocarpus, PlantAnimRig, RtClass);

    PlantAnimRig_Elaeocarpus();

    void SetAttackMode(int i_attackMode){ m_attackMode = i_attackMode; }

private:
    std::string getAttackAnimationName() override;

    int m_attackMode;
};

#pragma mark - ElaeocarpusDefaultProjectile

class ElaeocarpusDefaultProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ElaeocarpusDefaultProjectile, Projectile, RtClass);

    ElaeocarpusDefaultProjectile();

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual bool OnCollideGround() override;

    void FillSomeInfo(float i_height, float i_timeToTarget, int i_row);
    void SetJumpTimes(int i_times);

private:
    bool DoBounce();
    BoardEntity* findNextTarget();
    BoardEntity* findNearestTargetType(BoardEntityTypeFlag i_flag);
    

    float m_initialLobHeightThisBounce;
	float m_initialTimeOfFlightThisBounce;
    int m_rowBeingFiredAt;
    int m_jumpTimes;

    std::vector<BoardEntityPtr>	m_targetsAlreadyHit;
};


#pragma mark - ElaeocarpusSmashProjectile

class ElaeocarpusSmashProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ElaeocarpusSmashProjectile, Projectile, RtClass);

    ElaeocarpusSmashProjectile();

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

    void SetPercent(float i_percent) { m_percentBelow = i_percent; }
    void SetIsAreaDamage(bool i_flag) { m_isAreaDamage = i_flag; }
private:
    bool m_isAreaDamage;
    float m_percentBelow;
};


#pragma mark - ElaeocarpusPlantFoodProjectile

class ElaeocarpusPlantFoodProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ElaeocarpusPlantFoodProjectile, Projectile, RtClass);

    ElaeocarpusPlantFoodProjectile();

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

    void SetIsAvatar(bool i_flag) { m_isAvatar = i_flag; }
    void SetWindDamage(float i_damage) { m_windDamge = i_damage; }

private:
    bool m_isAvatar;
    float m_windDamge;
};


#pragma mark - ElaeocarpusWind

class ElaeocarpusWind : public BoardEntity
{
public:
    RT_CLASS_DEFINE(ElaeocarpusWind, BoardEntity, RtClass);

    ElaeocarpusWind();
    virtual ~ElaeocarpusWind();
    
    void initialize(int i_toGridX, float i_damage);
    virtual void onUpdate() override;

protected:
    float m_damage;
    float m_speed;
    int m_targetX;
    pvztime_t m_nextTime;
    StandaloneEffectPtr m_renderEffect;
};

#endif // __PLANT_CABBAGEPULT_H__
