#ifndef __PLANT_RAPEFLOWER_H__
#define __PLANT_RAPEFLOWER_H__

#include "PlantFramework.h"
#include "PopAnimRig.h"
#include "PlantAnimRig.h"
#include "Zombie.h"
#include "Plant.h"
#include "Projectile.h"
#include "ZombieLaneChangingSubsystem.h"
#include "NewPVPUtils.h"
#include <vector>
#include "SexyMatrix.h"
#include "PlantGroup.h"

class PlantRapeflowerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantRapeflowerProps, PlantPropertySheet, RtClass);


    PlantRapeflowerProps()
    {
        bluefireRate = 0.4f;
        purplefireRate = 0.2f;
        yellowfireRate = 0.2f;
        ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
        BurnDamage = 150.0f;
        plantfoodBurnDamage = 300.0f;
		BurnDps = 50;
		plantfoodBurnDps = 180;
    }
	
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
    // float attackfireRate;
    // float levelfireRate;
    float bluefireRate;
    float purplefireRate;
    float yellowfireRate;
    float BurnDamage;
    float plantfoodBurnDamage;
    float BurnDps;
    float plantfoodBurnDps;
};




class PlantRapeflower : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantRapeflower, PlantFramework, RtClass);
    void Initialize() override;
    // void UpdateActions() override;
    // void onDestroy() override;

    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    void UpdatePlantfood() override;

	virtual void DoSpecial(int i_extraParam) override;
    virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual Projectile *Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    // virtual ZombiePtr FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams, Rect i_attackRect) override;
    ZombiePtr ConfirmZombieTarget();
    bool FindZombie();
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
    DamageInfo GetBurnDamage(const float BurnDamage, int i_scale);
    float GetBurnDps(const float BurnDps);

private:
};


class RapeflowerProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(RapeflowerProjectileProps, ProjectilePropertySheet, RtClass);
    
    RapeflowerProjectileProps()
    {
        burntime = 5.0f;
        Vulnerable = 0.1f;
        oiltime  = 15.0f;
    }
    float Vulnerable;
    float burntime;
    float oiltime;

};

class RapeflowerProjectile : public Projectile
{
    RT_CLASS_DEFINE(RapeflowerProjectile, Projectile, RtClass);
    bool                handleImpact(BoardEntity* i_impactedEntity = nullptr) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual bool OnCollideGround() override;

    virtual bool HasBurn(Zombie* zombie);
	void onProjectileInitialized() override;

public:

    void SetDamageInfo(DamageInfo i_burnDamage) {burnDamage =  i_burnDamage;}
    void Setprojectiletype(int i_projectiletype) { projectiletype = i_projectiletype;}
    void SetburnDps(float i_burnDps) { burnDps = i_burnDps;}
    void SetIsPlantFood(bool i_Isplantfood) { ISplantfood = i_Isplantfood;}
    void SetIsLevelskill(bool i_Levelskill) { Levelskill = i_Levelskill;}
    virtual void radiateSplashDamage(BoardEntity* i_impactedEntity) override;
	virtual void onUpdate(pvztime_t i_dt) override;

    void handleImpacteffect(BoardEntity* i_impactedEntity = nullptr);
    void handlerealize(BoardEntity* i_impactedEntity = nullptr);
    // void SetTargetZombie(ZombiePtr i_targetZombie) {m_targetZombie = i_targetZombie;}
    // std::string GetEffectPam(bool flag) {return flag ?  "POPANIM_EFFECTS_PLANTAIN_SUPERSKILL_PROJECTILE" : "POPANIM_EFFECTS_PLANTAIN_PROJECTILE_EXPLOSION";}
protected:
    DamageInfo burnDamage;
    int projectiletype;
    bool ISplantfood;
    float burnDps;
    bool Levelskill;
    // ZombiePtr m_targetZombie;
};

//skill

class PlantAnimRig_Rapeflower : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Rapeflower, PlantAnimRig, RtClass);
    PlantAnimRig_Rapeflower():attacktypr(0)
    {
    }
    void SetAttackType(int i) { attacktypr = i;}
protected:
    // std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;

private:
    int attacktypr;
};

//plantfood


//skill itemfire
enum GridItemfireState
{
	PVZ_BEGIN_ENUM(FIRESTATE_),
	FIRESTATE_UNKNOWN,
	FIRESTATE_SPAWNING,
	FIRESTATE_IDLE,
	FIRESTATE_FADING,
	FIRESTATE_DEAD,
	PVZ_END_ENUM(FIRESTATE_)
};
class GridItemfire : public GridItemAnimation
{
public:

	RT_CLASS_DEFINE(GridItemfire, GridItemAnimation, RtClass);
    GridItemfire()
    : DamagePerSecond(0)
    {}

	int CalcRenderOrder() const override;

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	virtual void setState(GridItemfireState i_state);

protected:  
    void causeDamage();
	void onAnimation(const std::string &i_animName);

public:
    void SetDamage(float i_damagePerSecond) { DamagePerSecond = i_damagePerSecond;}
    void ResetLifetime();

private:
    float DamagePerSecond;
    time_t Cooldown;
	Sexy::Point _position;// water mist grid position
    time_t Lifetime;
    GridItemfireState m_state;

};

class GridItemfireProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemfireProps, GridItemAnimationProps, RtClass);
    GridItemfireProps():Cooldowntime(1.0f),
    Lifetime(3.0f)
    {}
public:
    float Cooldowntime;
    float Lifetime;
    
};
#endif //__PLANT_RAPEFLOWER_H__
