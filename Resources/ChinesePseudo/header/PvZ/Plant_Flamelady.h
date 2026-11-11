//
//  Plant_Flamelady.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/7/22.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_Flamelady_h
#define Plant_Flamelady_h

#include "PlantFramework.h"
#include "ComponentWarmingRadius.h"
#include "Projectile.h"
#include "GridItemAnimation.h"

enum Flamelady_State
{
    FLS_BEGIN = STATE_FRAMEWORK_BEGIN,
    FLS_POWERATTACK,
    FLS_LEVEL5ATTACK,
};

enum FlameladyProjectileType
{
    FPT_Normal = 0,
    FPT_Blue,
    FPT_PFNormal,
    FPT_PFBlue,
    FPT_Level5Normal,
    FPT_Level5Blue,
    FPT_Level5Purple,
};

enum FlameladyFireType
{
    FFT_Normal,
    FFT_Blue,
    FFT_Purple,
};

struct EntityTarget
{
    int row;
    bool flameSpawned;
    pvztime_t flameSpawnTime;
    RtWeakPtr<BoardEntity> entity;
    
    EntityTarget()
    {
        row = -1;
        flameSpawned = false;
        entity = nullptr;
        flameSpawnTime = PVZ_EOT();
    }
};

class FlameladyProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(FlameladyProps, PlantPropertySheet, RtClass);
    
    FlameladyProps();
    
    int FlameMaxCol;
    int FlamePromotion;
    int FlameProLevel;
    int BlueFireLevel;
    int DefenceRange;
    int AvatarPlantfoodMaxTarget;
    
    float FlameDelay;
    float FlameDamageRate;
    float PlantfoodFlameDPS;
    float FlameDPS;
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    float PlantfoodFireballDelay;
    
    SexyVector2 FlameOffset;
    
    float Level5AttackTotalSpan;
    float Level5AttackSpan;
    ValueRange Level5AttackProjectileCount;
    float Level5OnFoodAttackTotalSpan;
    float Level5OnFoodAttackSpan;
    ValueRange Level5OnFoodAttackProjectileCount;
    
    ComponentWarmingRadiusProps NormalWarmingRadius;
    ComponentWarmingRadiusProps PlantfoodWarmingRadius;
};

class Effect_AngerFlame;

class PlantFlamelady : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantFlamelady, PlantFramework, RtClass);
    
    void Initialize() override;
    bool CanApplyPlantfood() override;
    void DoSpecial(int i_extraParam = 0) override;
    void CancelPlantfood() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    void ApplyPlantfood() override;
    
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    Projectile* SpawnFireBall(BoardEntityPtr i_target, int i_row, PlantWeapon i_plantWeapon);
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void SpawnFlame(int i_row, int i_col = BoardConstants::NUMBER_OF_COLUMNS() - 1);
    void CancelFlame();
    
    virtual void onKilled(bool i_instantKill) override;
    void onWatered(bool watered) override;
    void OnAnimStopped(const std::string &i_animName);
    void stopSpecialEffect() override;
    void Idle() override;
    
protected:
    void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
    
    void UpdateActions() override;
    void onDestroy() override;
    void setState(uint i_plantState);
    void Draw(Sexy::Graphics* i_g) override;
    
private:
    int GetMaxFlameCol();
    int GetFireState();
    bool NeedCombat(BoardEntityPtr i_target);
    bool IsTargettedEntity(BoardEntityPtr i_entity);
    void StartPowerAttack();
    void CancelPowerAttack();
    void ApplyFlameDamage(bool i_plantfood);
    bool IsSpawningFlame();
    
    void StartLevel5Attack();
    void UpdateLevel5Attack(BoardEntityPtr i_target);
    void CancelLevel5Attack();
    
    void UpdateLevel5OnFoodAttack();
    
    Rect GetFlameSpreadingRect();
    BoardEntityPtr FindBestTarget();
    BoardEntityPtr FindCombatTarget();
    BoardEntityPtr FindBestTargetInRow(int i_row);
    BoardEntity* FindLeftmostTargetType(BoardEntityTypeFlag i_flag, int i_row);
    
private:
    bool m_powerAttacking = false;
    bool m_powerCancelling = false;
    RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
    std::vector<RtWeakPtr<Effect_AngerFlame>> m_flameEffects;
    std::vector<EntityTarget> m_entityTargets;
    
    bool m_level5Attacking;
    bool m_level5Cancelling;
    float m_level5AttackTime;
    float m_level5AttackSpan;
    float m_level5AttackProjectileCount;
    pvztime_t m_attackInterval;
};

class PlantAnimRig_Flamelady : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Flamelady, PlantAnimRig, RtClass);
    PlantAnimRig_Flamelady();
    void SetFireState(int i_blue) {m_fireState = i_blue;}
    
    void PlayPowerAttack(AnimStoppedDelegate i_onStopDelegate);
    void LoopPowerAttack();
    void StopPowerAttack(AnimStoppedDelegate i_onStopDelegate);
    
    std::string getPowerAttackOnAnimation();
    std::string getPowerAttackLoopAnimation();
    std::string getPowerAttackOffAnimation();
    
    void PlayLevel5Attack(AnimStoppedDelegate i_onStopDelegate);
    void LoopLevel5Attack();
    void StopLevel5Attack(AnimStoppedDelegate i_onStopDelegate);
    
    std::string getLevel5AttackOnAnimation();
    std::string getLevel5AttackLoopAnimation();
    std::string getLevel5AttackOffAnimation();
    
protected:
    void onPopAnimInitialized() override;
    std::string getAttackAnimationName() override;
    
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;
    
    std::string getIdleAnimationName() override;
    std::string getWaterAnimName() override;
    
private:
    int m_fireState;
};

class FlameladyProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(FlameladyProjectile, Projectile, RtClass);
    FlameladyProjectile();
    
protected:
    void onPostUpdate() override;
    
private:
    void UpdateFadeOut();
    
private:
    pvztime_t m_fadeTime;
};

class Effect_AngerFlame : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(Effect_AngerFlame, PopAnimRig, RtClass);
    
    Effect_AngerFlame();
    
    
    void SetFireState(int i_blue) {m_fireState = i_blue;}
    void SetFlameCol(int i_col);
    void SetFlameRow(int i_row);
    void SetFlameDelay(pvztime_t i_delay);
    void SetOwningEffect(class Effect_PopAnim* i_effect);
    void EndFlame();
    
    bool IsSpread();
    int GetFlameCol();
    int GetFlameRow();
    
protected:
    virtual void onPopAnimInitialized() override;
    virtual void onUpdate() override;
    
private:
    
    std::string getFlameBeginAnim();
    std::string getFlameLoopAnim();
    std::string getFlameEndAnim();
    
    void StartFlame();
    void OnFlameBegin(const std::string& i_anim, const std::string& i_nextAnim, int i_playCount);
    void OnFlameEnd(const std::string& i_anim, const std::string& i_nextAnim, int i_playCount);
    
private:
    int m_fireState;
    bool m_spread;
    bool m_fadingOut;
    int m_col;
    int m_row;
    pvztime_t m_activationTime;
    RtWeakPtr<class Effect_PopAnim> m_owningEffect;
};

#endif /* Plant_Flamelady_h */
