//
//  Plant_DragonFruit.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/4/12.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_DragonFruit_h
#define Plant_DragonFruit_h

#include "PlantFramework.h"
#include "ComponentWarmingRadius.h"
#include "Projectile.h"
#include "GridItemAnimation.h"

class DragonFruitProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(DragonFruitProps, PlantPropertySheet, RtClass);
    
    DragonFruitProps();
    
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    ComponentWarmingRadiusProps NormalWarmingRadius;
    ComponentWarmingRadiusProps PlantfoodWarmingRadius;
};

class PlantDragonFruit : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantDragonFruit, PlantFramework, RtClass);
    
    void Initialize() override;
    bool CanApplyPlantfood() override;
    void DoSpecial(int i_extraParam) override;
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void CancelPlantfood() override;
    virtual pvztime_t GetTheLeastAttactDuration() override;

protected:
    void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
private:
    void launchSpecialProjectile();
    bool InBlueFireState();
    int GetActionIndex(bool i_plantfood);
private:
    RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
};

class PlantAnimRig_DragonFruit : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_DragonFruit, PlantAnimRig, RtClass);
    void SetBlueFire(bool blue);
    PlantAnimRig_DragonFruit();
protected:
    void onPopAnimInitialized() override;
    void onLevelUpdate() override;
    std::string getAttackAnimationName() override;
    std::string getPlantFoodMainAnimName() override;
private:
    std::string getAnimationName(bool i_plantfood);
    bool m_blueFire;
};

class DragonFruitProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(DragonFruitProjectile, Projectile, RtClass);
    void SpawnLave(bool spawn);
    DragonFruitProjectile();
protected:
    void onPostUpdate() override;
private:
    void UpdateLavaSpawn();
    void UpdateFadeOut();
private:
    bool m_spawnLava;
    pvztime_t m_fadeTime;
};

class DragonFruitLavaProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(DragonFruitLavaProps, GridItemAnimationProps, RtClass);
    DragonFruitLavaProps();
    
    pvztime_t Lifetime;
    float Damage;
    ComponentWarmingRadiusProps WarmingRadius;
};

class DragonFruitLava : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(DragonFruitLava, GridItemAnimation, RtClass);
    
    DragonFruitLava();
    int	CalcRenderOrder() const override;
    void OnWashedOut();
    int GetStyle();
    void SetStyle(int style);
    void SetDamageRate(float rate);
    void UpdateStyleAnimation();
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
private:
    void causeDamage();
private:
    int m_style;
    float m_damageRate;
    pvztime_t m_creationTime;
    pvztime_t m_fadeTime;
    RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
};

#endif /* Plant_DragonFruit_h */
