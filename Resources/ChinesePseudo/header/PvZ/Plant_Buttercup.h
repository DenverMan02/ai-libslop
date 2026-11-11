//
//  Plant_Buttercup.h
//  PlantsVersusZombies2
//
//  Created by Sudheer, Alma on 09/21/21.
//  Copyright 漏 2021 PopCap Games. All rights reserved.
//

#ifndef Plant_Buttercup_h
#define Plant_Buttercup_h

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RestrictionSet.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"
#include "GridItemAnimation.h"
#include "PlantPropertySheet.h"

namespace Sexy {
class SexyVector3;
}

class PlantButtercup : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantButtercup, PlantFramework, RtClass);

    bool CanApplyPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void DoSpecial(int i_extraParam = 0) override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void DoFortifyAttack();
    void PlayAttackAnimation() override;

    //don't target grid items
    GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon) override { return GridItemPtr(); }
protected:
    void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, const PultProjectileProps& launchProps);
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
    void SetPopAnimDelegates(class PlantAnimRig *i_rig) override ;
    void TakeSmashAttack(ZombiePtr i_srcZombie)    override;
    void onDestroy() override;
//    bool TryBlockPush() override;
    bool TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction) override;
//    void onKilled(DamageTypeFlags i_lastDamageType, BoardEntity* i_instigator = nullptr) override;

private:
    Projectile* launchFortifyProjectile(SexyVector3 i_targetesLoc, ZombiePtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
    void launchSpecialProjectile(SexyVector3 i_targetesLoc, ZombiePtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
    const bool isValidButterLocation(const int i_gridX, const int i_gridY);
    std::vector<RtWeakPtr<Zombie>> m_targetZombies;
    void onUseActionAnimCommand(pvztime_t i_timeStamp);
    void onUseSpecialAnimCommand(pvztime_t i_timeStamp);
    void doInstantDamage(Zombie* i_target);
    void onButterGridCreated();
    Delegate0 m_onGridButterCreatedDelegate;
    bool m_plantNextFortifyAttack = false;
};

class ButtercupProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ButtercupProps, PlantPropertySheet, RtClass);

    float AmountToAimLeftOfZombie = 0.33;
    ClassRestrictionSet ZombiesExcludeList;
    PultProjectileProps NormalLaunchProps;
    PultProjectileProps PlantfoodLaunchProps;
    float NormalProjectileDamageAmount = 35.f;
    float PlantfoodProjectileDamageAmount = 300.f;
    float AvatarPlantfoodProjectileDamageAmount = 350.f;
    float ButterLifetime = 5.f;
    float PFButterLifetime = 5.f;
    float APFButterLifetime = 5.f;
    float ButterConditionDuration = 5.f;
    float PFButterConditionDuration = 5.f;
    float APFButterConditionDuration = 5.f;
    int ButterLeftZombieNumStepIn = 1;
    int ButterLeftZombieNumStepInLv2 = 2;
    int ButterLeftZombieNumStepInLv3 = 3;
    int PFButterLeftZombieNumStepIn = 1;
    int AVButterLeftZombieNumStepIn = 2;
    float FortifyAttackRateOnLevel5 = 0.15;
    float NormalButterPitDamageAmount = 100.f;
    float PlantfoodButterPitDamageAmount = 300.f;
    float AvatarPlantfoodButterPitDamageAmount = 350.f;
};

class PlantAnimRig_Buttercup : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Buttercup, PlantAnimRig, RtClass);

    std::string getPlantFoodMainAnimName() override { return "plantfood"; }
    std::string getAttackAnimationName() override;

    void setNextFortifyAttack() { m_nextFortifyAttack = true; }

    bool m_nextFortifyAttack = false;
};

class ButtercupProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(ButtercupProjectileProps, ProjectilePropertySheet, RtClass);

    ButtercupProjectileProps()
    {
        ButterItemName = "butter";
        RenderImageForTity = "";
        RenderImageAvatar = "";
    }

    std::string ButterItemName;
    std::string RenderImageForTity;
    std::string RenderImageAvatar;
};

enum ButtercupProjectileType
{
	BUTTERCUP_PROJECTILE_TYPE_NORMAL,
	BUTTERCUP_PROJECTILE_TYPE_LEVEL2,
	BUTTERCUP_PROJECTILE_TYPE_LEVEL3,
	BUTTERCUP_PROJECTILE_TYPE_LEVEL5_FORTIFY,
	BUTTERCUP_PROJECTILE_TYPE_PLANTFOOD,
	BUTTERCUP_PROJECTILE_TYPE_AVATAR,
};

class ButtercupProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ButtercupProjectile, Projectile, RtClass);
    bool OnCollideGround() override;

    SexyVector3 m_TargetPosition;
    void SetButterDuration(float i_butterLifetime, float i_butterConditionDuration){ m_butterLifetime = i_butterLifetime; m_butterConditionDuration = i_butterConditionDuration;}
    void SetTarget(RtWeakPtr<Zombie> i_target){ m_target = i_target;}
    void SetOnGridButterCreatedDelegate(Delegate0 i_onGridButterCreatedDelegate){m_onGridButterCreatedDelegate = i_onGridButterCreatedDelegate;}
    void SetButterLeftZombieNumStepIn(int i_leftZombieNumStepIn) { m_butterLeftZombieNumStepIn = i_leftZombieNumStepIn; }
    void SetButterProjectileType(ButtercupProjectileType i_type);
    void AutoSetAppropriateButterType(class GridItemButter * i_butter);

    void SetButterDamageRate(float i_butterDamageRate) { m_butterDamageRate = i_butterDamageRate; }

protected:
	bool canTargetZombie(const Zombie* i_zombie);

private:
    float m_butterLifetime;
    float m_butterConditionDuration;
    RtWeakPtr<Zombie> m_target;
    Delegate0 m_onGridButterCreatedDelegate;
    int m_butterLeftZombieNumStepIn;

    ButtercupProjectileType m_buttercupProjectileTYpe;
    float m_butterDamageRate = 1.f;
};


enum GridItemButterState
{
    PVZ_BEGIN_ENUM(BUTTERSTATE_),
    BUTTERSTATE_UNKNOWN,
    BUTTERSTATE_SPAWNING,
    BUTTERSTATE_RESETTING,
    BUTTERSTATE_IDLE,
    BUTTERSTATE_FADING,
    BUTTERSTATE_DEAD,
    PVZ_END_ENUM(BUTTERSTATE_)
};

enum GridItemButterType
{
	BUTTER_TYPE_NORMAL,
	BUTTER_TYPE_LEVEL2,
	BUTTER_TYPE_LEVEL3,
	BUTTER_TYPE_LEVEL5_FORTIFY,
	BUTTER_TYPE_PLANTFOOD,
	BUTTER_TYPE_AVATAR,
};

class GridItemButter : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemButter, GridItemAnimation, RtClass);

    GridItemButter();
    int CalcRenderOrder() const override;

    void ReinitButter(float i_butterLifeTime, float i_butterDamage, float i_butterConditionDuration, RtWeakPtr<Zombie> i_target);

    void SetResistancePiercing(float i_resistancePiercing) { m_resistancePiercing = i_resistancePiercing; }
    void InitButter(float i_butterLifeTime, float i_butterDamage, float i_butterConditionDuration, RtWeakPtr<Zombie> i_target);
    void SetDamageFlags(DamageTypeFlags i_damageFlags) { m_damageFlags = i_damageFlags; }

    void SetLeftZombieNumStepIn(int i_leftZombieNumStepIn) { m_leftZombieNumStepIn = i_leftZombieNumStepIn; }
    void SetButterType(GridItemButterType i_type);

    void SetDamageRate(float i_damageRate) { m_damageRate = i_damageRate; }

protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemButterState i_state);
    bool targetNewZombies();

    void onButterSplatFinished(const std::string &i_animName);
    void onButterSplatFaded(const std::string &i_animName);
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }


private:
    bool canTargetZombie(const Zombie* i_zombie);
    void applyButter(RtWeakPtr<Zombie> i_zombiePtr);
    void damageTarget(Zombie* i_zombie);
    void setButterProps(float i_butterLifeTime, float i_butterDamage, float i_butterConditionDuration, RtWeakPtr<Zombie> i_target);


    pvztime_t m_creationTime;
    GridItemButterState m_state;
    float m_resistancePiercing = 0.f;
    float m_butterDamage = 0.f;
    float m_butterLifetime = 0.f;
    float m_butterConditionDuration = 0.f;
    DamageTypeFlags m_damageFlags = (DamageTypeFlags) 0;
    int m_leftZombieNumStepIn = 1;
    GridItemButterType m_butterType = BUTTER_TYPE_NORMAL;
    float m_damageRate = 1.f;
};

class GridItemButterProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemButterProps, GridItemAnimationProps, RtClass);
    GridItemButterProps()
    {}

//    ClassRestrictionSet ZombiesExcludeList;
//    std::string ParentPlantType;
//    std::vector<ZombieConditionEntry> ZConditions;
//    std::vector<ZombieConditionEntry> ZConditionsLv5Fortify;
    std::string PopAnimLevel2;
    std::string PopAnimLevel3;
    std::string PopAnimFortify;
    std::string PopAnimAvatar;
};

#endif /* Plant_Buttercup_h */
