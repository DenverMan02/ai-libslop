//
//  Plant_Nightcap.h
//  PlantsVersusZombies2
//
//  Created by Sudheer, Alma on 04/06/22.
//  Copyright © 2022 PopCap Games. All rights reserved.
//

#ifndef Plant_Nightcap_h
#define Plant_Nightcap_h

#include "Plant.h"
#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "ProjectilePropertySheet.h"
#include "GameSubSystem.h"

class Zombie;

class NightcapProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(NightcapProps, PlantPropertySheet, RtClass);

    NightcapProps()
    {
        PlantFoodPushSpeed = 1;
        AttackRange = 1;
        PoisonDPS = 40;
        PoisonDuration = 2;
        NightDurations = 10;
        NightCDs = 10;
    }

    float PlantFoodPushSpeed;
    float AttackRange;
    float PoisonDPS;
    float PoisonDuration;
    float NightDurations;
    float NightCDs;
};


class NightNormalBallProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(NightNormalBallProjectileProps, ProjectilePropertySheet, RtClass);
    NightNormalBallProjectileProps() { }
    std::vector<RtWeakPtr<ProjectilePropertySheet> > splitBullets;
    float PoisonDamage;
};


class NightNormalProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(NightNormalProjectile, Projectile, RtClass);
protected:
    void InitialSetPosition(const float i_x, const float i_y, const float i_z) override;
    void onUpdate(pvztime_t i_dt) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void onSpawnProjectiles(BoardEntity* i_entity);
private:
    int m_validGridx = 0;
    std::vector<int> m_hitGridX;
    std::vector<BoardEntity*> m_hitZombies;
};

// class NightBigBallProjectile : public NightNormalProjectile
// {
// public:
//     RT_CLASS_DEFINE(NightBigBallProjectile, Projectile, RtClass);
// protected:
//     void onSpawnProjectiles(BoardEntity* i_entity) override;
// private:
//     std::vector<int> m_hitGridX;
// };

class NightSmallBallProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(NightSmallBallProjectile, Projectile, RtClass);
protected:
    void InitialSetPosition(const float i_x, const float i_y, const float i_z) override;
    void onUpdate(pvztime_t i_dt) override;
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
private:
    Point m_invalidGrid;
};

class PlantNightcap : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantNightcap, PlantFramework, RtClass);
    
    void Initialize() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    // bool IsInvincible() const override;
    bool CanBeTargeted() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    bool CanBeRangeTargeted() override;
    Sexy::Rect GetPlantAttackGridRect(PlantWeapon i_plantWeapon) override;
    Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    void UpdateActions() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    bool BlockRailcartMovement() const override;    
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
    void TakeSmashAttack(ZombiePtr i_srcZombie) override;
    void onApplyCondition(PlantConditions i_condition) override;
    bool CanBeConvertedByCondition() override;
    void onDestroy() override;
    void setNightMode();
    bool isNightMode() { return m_isInStealthMode; }
    bool canNightMode() { return !m_isInStealthMode && PVZ_T() > m_nightTimestamp; }
    bool OverrideProjectileCollision(Projectile* i_projectile) override;
    bool IsIgnoreControlAndDmg() override;
    void onSleeped(bool sleeped) override;
    // void onBeThrown() override;
    void poisonDamage();
    static bool WhetherCanBePulled(const Plant* i_plant, int i_endCol);
    static bool WhetherCanBePushed(const Plant* i_plant, int i_endCol);
protected:
    void registerForEvents() override;
    void unregisterForEvents() override;
    
private:
    void RepelledZombies();
    void onAnimStoppedCallback(const std::string&) override;
    void onPlantPlanted(/* Plant* i_plant */);
    DamageInfo getDamageInfo(PlantWeapon i_plantWeapon);
    bool damageTargets(PlantWeapon i_plantWeapon);
    void pushZombieAway(Zombie* i_zombie);
    void findTargets(PlantWeapon i_plantWeapon, std::vector<BoardEntity*> &o_targets);
    void stopStealth();
    void createProjectile(const std::string& i_animName, int i_row, const SexyVector3& i_position);
    void pfDamageTargets(bool i_isSecond, bool i_isFinal = false);
    void updateNightEffect();
        
    bool m_isInStealthMode = false;
    int m_extraX = 0;    
    pvztime_t m_nightCd;
    pvztime_t m_nightTimestamp;
    pvztime_t m_nightDurations;
    pvztime_t m_poisonTimestamp;    
};

//
//  Anim rig
//

class PlantAnimRig_Nightcap : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Nightcap, PlantAnimRig, RtClass);
    
    PlantAnimRig_Nightcap();
    
    // bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
    bool PlayPlantFoodStart(int i_mainAnimPlayCount) override;
    void PlayStealth();
    void PlayLandingAnimation(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopCallback);
    
protected:
    std::string getPlantFoodMainAnimName() override { return "pf_attack"; }
    
private:
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;    

    PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
};

class NightPoisonSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(NightPoisonSubSystem, GameSubSystem, RtClass);
    virtual void Update() override;
    void AddPlant(PlantPtr i_plant);
private:    
    std::vector<RtWeakPtr<Plant>> plants;
};


#endif /* Plant_Nightcap_h */
