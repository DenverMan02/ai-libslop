//
//  Plant_Maybee.h
//  PlantsVersusZombies2
//
//  Created by emoss on 2/2/23.
//  Copyright © 2023 PopCap Games. All rights reserved.
//

#ifndef Plant_Maybee_h
#define Plant_Maybee_h

#include "BoardEntity.h"
#include "Curve.h"
#include "EntityFinder.h"
#include "PlantFramework.h"
#include "RestrictionSet.h"
#include "RtObject.h"
#include "Zombie.h"
#include "GameSubSystem.h"

class MaybeeProps : public PlantPropertySheet
{
    RT_CLASS_DEFINE(MaybeeProps, PlantPropertySheet, RtClass);
    
    MaybeeProps()
    {
        BeeTriggerRadiusSquares = 2.f;
        BeeDuration = 10.f;
        BeeSpeed = 1.f;
        BeeCount = 3;
        PlantfoodBeeCount = 9;
        BeeDamage = 350;        
        BeePoweredDamageMultiplier = 1.5f;
        BeeSlowPercentage = 25.f;
        AttackRechargeTime = 30.f;
        PlantfoodRechargeTime = 30.f;
        StunTime = 3.f;
        PlantfoodBeeStunTime = 3.f;
        MinBeeSpawnDist = 80;
        MaxBeeSpawnDist = 120;
        AttackRange = 3;
        Lv5Boost = 0.25f;
        Lv5PlantBoost = 0.7f;
        PFBaseDamage = 12;
        // PFAvatarBaseDamage = 80;
        AvatarPlantfoodBeeCount = 8;
    }
    
    float BeeTriggerRadiusSquares;
    float BeeDuration;
    float BeeSpeed;
    int BeeCount;
    int PlantfoodBeeCount;
    int BeeDamage;    
    float BeePoweredDamageMultiplier;
    float BeeSlowPercentage;
    
    float AttackRechargeTime;
    float PlantfoodRechargeTime;
    float StunTime;
    float PlantfoodBeeStunTime;
    PlantRestrictionSet BeeElectrifyingPlants;
    
    float MinBeeSpawnDist;
    float MaxBeeSpawnDist;
    int AttackRange;
    float Lv5Boost;
    float Lv5PlantBoost;
    int PFBaseDamage;
    // int PFAvatarBaseDamage;
    int AvatarPlantfoodBeeCount;
};

enum MaybeeState
{
    MAYBEESTATE_IDLE = STATE_FRAMEWORK_BEGIN,
    MAYBEESTATE_ATTACK,
    MAYBEESTATE_RECHARGE,
    MAYBEESTATE_PLANTFOOD,
};

class PlantMaybee : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantMaybee, PlantFramework, RtClass);
    
    void Initialize() override;
    void UpdateActions() override;
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
    
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    int GetPlantFoodPlayCount() override;
    
protected:
    void onAnimStoppedCallback(const std::string& i_animLabel) override;
    
private:
    bool hasTargetInRange();
    class MaybeeBee* createBee(bool i_isPlantfoodBee);
    void setState(uint i_plantState);
    void attackCallback(pvztime_t i_atTime);
    void plantfoodCallback(pvztime_t i_atTime);
    
    void onInitialized();
    
    int m_beesToRelease;
    pvztime_t m_beeReleaseTime;
    pvztime_t m_rechargeTime;
    ValueRange m_beeSpawnDistRange;
};

class PlantAnimRig_Maybee : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Maybee, PlantAnimRig, RtClass);
    
    PlantAnimRig_Maybee();
    
    void PlayCooldownStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayCooldownLooped();
    void PlayCooldownEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
private:
    std::string getPlantFoodMainAnimName() override;
};

class MaybeeBee : public BoardEntity
{
public:
    enum Bee_State
    {
        STATE_BEE_UNINITIALIZED,
        STATE_BEE_IDLE,
        STATE_BEE_MOVING,
        STATE_BEE_ATTACKING,
        STATE_BEE_DYING,
        STATE_BEE_COLLISION,        
    };
    
public:
    RT_CLASS_DEFINE(MaybeeBee, BoardEntity, RtClass);
    
    MaybeeBee();
    
    void Draw(Graphics* i_g) override;
    
    void SetBeeSpeed(float i_speed) { m_beeSpeed = i_speed; }
    void SetExpireTime(pvztime_t i_expireTime) { m_expireTime = i_expireTime; }
    bool IsPastExpiry(pvztime_t i_testTime) { return i_testTime >= m_expireTime; }
    void SetOwner(BoardEntityPtr i_owner);
    void SetTarget(ZombiePtr i_target);
    ZombiePtr GetTarget() { return m_target; }
    bool HasTarget();
    void SetDamage(float i_damage, float i_poweredDamage) { m_damage = i_damage; m_poweredDamage = i_poweredDamage; }
    void SetSlowPercent(float i_slow) { m_slowPercent = i_slow; }
    void SetStunTime(float i_stun) { m_stunTime = i_stun; }
    void SetResistancePiercing(float i_resistancePiercing) { m_resistancePiercing = i_resistancePiercing; }
    bool ShouldDrawShadow() const override { return false; }
    void SetPowerUpPlants(PlantRestrictionSet i_powerUpPlants) { m_plantsThatBoost = i_powerUpPlants; }
    void SetPowered();
    bool IsPowered() { return m_powered; }
    void SetLevel5Boost(bool i_boost) { m_level5Boost = i_boost; }
    void SetLevel(int i_level) { m_level = i_level;}
    int  GetLevel() { return m_level; }
    void SetLevel5BoostRate(float i_lv5BoostRate) { m_lv5BoostRate = i_lv5BoostRate; }
    void SetIsPlantfooded() { m_isPlantfoodBee = true; refreshAnimation(); }
    void Die();
    void SetPFDistance(int i_dis) { m_pfDistance = i_dis; }
    
    void OnAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string &i_animCommand, const std::string &i_animCommandParam);
    
    BoardEntityTypeFlag GetBoardEntityType() override { return ENTITYTYPE_OTHERBOARDENTITIES; }
    // std::vector<std::string> GetPlantFamiliesForAttack() {return m_plantFamiliesForAttack; }
    std::string GetPlantFamiliesForAttack() {return m_plantFamiliesForAttack; }
    float GetResistancePiercing() { return m_resistancePiercing; }

    void SetCollision();
    
protected:
    void onUpdate() override;
    void onDestroy() override;
    void onInitialized() override;
    void onDraw(Graphics* i_g) override;
    void onDieFinished(const std::string &i_animName);
    
    bool isWithinStingRange();
    bool shouldStartSting();
    void moveTowardTarget();
    void moveOutOfRange();
    void refreshAnimation();
    bool useSmallerRange();
    
    std::string getIdleName();
    std::string getAttackName();
    std::string getMoveName();
    std::string getCollisionName();
    
    
    DamageTypeFlags getDamageTypeFlags();
    
    void setState(uint i_beeState);
    
    PopAnimRigPtr m_animRig;
    
    DamageInfo createDamage();
    void updateBee();
    
private:
    BoardEntityPtr m_owner;
    ZombiePtr m_target;
    pvztime_t m_expireTime;
    bool m_powered = false;
    bool m_isPlantfoodBee = false;
    bool m_level5Boost = false;
    int m_level = 1;
    float m_lv5BoostRate = 0.0f;
    float m_pfDistance = 0.0f;
    
    float m_beeSpeed;
    float m_damage;
    float m_poweredDamage;
    float m_resistancePiercing;
    float m_slowPercent;
    float m_stunTime = 0;
    uint m_state;
    // std::vector<std::string> m_plantFamiliesForAttack;
    std::string m_plantFamiliesForAttack;
    PlantRestrictionSet m_plantsThatBoost;
    std::vector<BoardEntity*> m_hitTargets;
};

enum BeePlantfoodGroup
{
    PF_Plant,
    PF_House,
    PF_HP,
    Normal,
};

class BeeTargetEntry
{
public:
    BeeTargetEntry()
    : Group(Normal)
    {}
    
    RtWeakPtr<MaybeeBee> Bee;
    BeePlantfoodGroup Group;
    PlantPtr Plant;
};

class PlantMaybeeSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PlantMaybeeSubSystem, GameSubSystem, RtClass);
    
    void Update() override;
    void AddBee(MaybeeBee* i_bee, PlantPtr i_plant, BeePlantfoodGroup i_group);
    
protected:
    bool isBeeExpired(MaybeeBee* i_bee);
    void assignBeeTarget(BeeTargetEntry i_bee);
    void reassignBeeTarget(BeeTargetEntry i_bee);
    bool isViableTarget(Zombie* i_zombie);
    bool isPreviouslySelected(Zombie* i_zombie);

    bool checkFullBeeAttack(Zombie* i_zombie);
    void findTarget(std::vector<BoardEntity*> i_viableTargets, BeeTargetEntry i_bee);

    void registerForEvents() override;
    void unregisterForEvents() override;
    void onZombieDamageTakenRaw(Zombie *i_zombie, const DamageInfo &i_damage);
    
private:
    std::vector<BeeTargetEntry> m_bees;
};


#endif /* Plant_Maybee_h */
