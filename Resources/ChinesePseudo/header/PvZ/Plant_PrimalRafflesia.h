//
//  Plant_PrimalRafflesia.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 16/11/22.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_PrimalRafflesia_h
#define Plant_PrimalRafflesia_h

#include "PlantFramework.h"
#include "Projectile.h"
#include "GridItemAnimation.h"
#include "GameSubSystem.h"

enum ExplodeLevelType
{
    LEVEL_NO_EXPLODE,
    LEVEL_ADVANCED,    
    LEVEL_AVATAR
};

struct ZombieExplodeInfo
{
    ZombieExplodeInfo()
    {
        HasAvatarBuff = false;
    }
    
    RtWeakPtr<class Zombie> Zombie;
    bool HasAvatarBuff;
};

class PlantPrimalRafflesia : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPrimalRafflesia, PlantFramework, RtClass);
    
    bool CanApplyPlantfood() override;
    void ApplyPlantfood()override;
    void UpdatePlantfood() override;
    void CancelPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void DoSpecial(int i_extraParam = 0) override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;    
    
protected:
    void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance
                            , bool i_avatar, bool i_plantfood);
    
private:
    Projectile* launchSpecialProjectile();
    Projectile* launchProjectile(Zombie* targetZombie, GridItem* targetGridItem);
    bool		isValidTargetGridItem(BoardEntityPtr target);
    bool		isValidTargetZombie(BoardEntityPtr target);
    BoardEntityPtr  findNextPlantfoodTarget();
    void		makeSureWeStillHaveAPlantFoodTarget();
    
    std::vector<RtWeakPtr<BoardEntity>> m_entitiesHitDuringPlantfood;
    RtWeakPtr<BoardEntity> m_nextPlantFoodTarget;
};

class PrimalRafflesiaProps : public CabbagepultProps
{
public:
    RT_CLASS_DEFINE(PrimalRafflesiaProps, CabbagepultProps, RtClass);
    
    PrimalRafflesiaProps()
    {
        AmountToAimLeftOfZombie = 0.33;
        ExplodeDamage = 20000;
        ExplodeRadius = 32;
        SplashDamage = 200;
        InstantExplodeDamage = 200;
        InstantExplodeRadius = 32;
    }
    
    float AmountToAimLeftOfZombie;
    ZombieRestrictionSet TargetableZombieTypes;
    std::vector<float> ExplodeRate;
    int ExplodeDamage;
    int ExplodeRadius;
    int SplashDamage;
    int InstantExplodeDamage;
    int InstantExplodeRadius;
};

class PrimalRafflesiaProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PrimalRafflesiaProjectileProps, ProjectilePropertySheet, RtClass);
    
    PrimalRafflesiaProjectileProps()
    {
        SlimeItemName = "slime";
    }
    
    std::string SlimeItemName;
};

class PrimalRafflesiaProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PrimalRafflesiaProjectile, Projectile, RtClass);
    PrimalRafflesiaProjectile()
    : m_avatar(false)
    {}
    SexyVector3 m_TargetPosition;
    
    void SetIsAvatar(bool i_avatar) { m_avatar = i_avatar; }
    void SetIsPlantfood(bool i_plantfood) { m_plantfood = i_plantfood; }
protected:
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void removeMarkedForDeathFromTargetedZombie();
    virtual bool isZombieValidToKill(BoardEntity* i_entity);
    virtual bool hasZombieBeenKilled(Zombie* zombie);

    bool m_avatar;
    bool m_plantfood;
private:
    void MarkSpecialProjectile(BoardEntity* i_entity);
};

class PrimalRafflesiaPlantfoodProjectile : public PrimalRafflesiaProjectile
{
public:
    RT_CLASS_DEFINE(PrimalRafflesiaPlantfoodProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
private:
    void DoInstantExplosion(const SexyVector2& i_position);
};

class ZombieToxicosis
{
public:
    ZombieToxicosis()
    : StartTime(0.0f)
    , Advanced(false)
    , hasExploded(false)
    {}
    
    ZombiePtr Zombie;
    pvztime_t StartTime;
    bool Advanced;
    bool hasExploded;
};

struct SpecialProjectileInfo
{
    SpecialProjectileInfo()
    {
        Col = 0;
        Row = 0;
        StartTime = 0.0f;
    }
    
    int Col;
    int Row;
    pvztime_t StartTime;
};

class PrimalRafflesiaSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PrimalRafflesiaSubsystem, GameSubSystem, RtClass);
    
    PrimalRafflesiaSubsystem();
    ~PrimalRafflesiaSubsystem() override;
    
    virtual void Update() override;
    void MarkZombieExplode(Zombie* zombie, bool hasAvatarBuff);
    void ExplodeInstantly(Zombie* zombie);
    void MarkSpecialProjectile(int i_col, int i_row);
    
private:
    void onZombieDeath(Zombie* zombie);
    void onZombieDestroyed(Zombie* zombie);
    void onZombieDropHead(Zombie* zombie);
    ExplodeLevelType shouldZombieExplode(Zombie* zombie);
    void tryExplodeZombie(Zombie* zombie, ExplodeLevelType i_type);
    void CauseZombieToxicosis(Zombie* i_zombie, ExplodeLevelType i_type);
    void DoExplosion(const SexyVector2& i_position, bool i_advanced);
    void DoSplashDamage(int i_sourceCol, int i_sourceRow);
    
    std::vector<ZombieExplodeInfo> m_zombiesToExplode;
    std::vector<ZombieToxicosis> m_zombieStates;
    std::vector<SpecialProjectileInfo> m_projectileInfo;
};

enum GridItemSlimeState
{
    PVZ_BEGIN_ENUM(SLIMESTATE_),
    SLIMESTATE_UNKNOWN,    
    SLIMESTATE_RESETTING,
    SLIMESTATE_IDLE,
    SLIMESTATE_DEAD,
    PVZ_END_ENUM(SLIMESTATE_)
};

class GridItemSlime : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemSlime, GridItemAnimation, RtClass);
    
    GridItemSlime();
    int	CalcRenderOrder() const override;
    
    void ResetTimer();
    void SetAdvanced(bool i_advanced) { m_advanced = i_advanced; }
    void SetIdle() { setState(SLIMESTATE_IDLE); }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;
    
    void setState(GridItemSlimeState i_state);
    void applySlime();
    
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    
private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    GridItemSlimeState m_state;
    bool m_advanced;
};

class GridItemSlimeProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemSlimeProps, GridItemAnimationProps, RtClass);
    GridItemSlimeProps()
    : Lifetime(1.0)
    , SlimeTime(2.0)
    , EffectRectRight(0)
    , EffectRectLeft(0)
    , EffectRectTop(0)
    , EffectRectBottom(0)
    {}
    
    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;
    
    pvztime_t Lifetime;
    pvztime_t SlimeTime;    
    std::vector<std::string> ZombieBlacklist;
};

#endif /* Plant_PrimalRafflesia_h */
