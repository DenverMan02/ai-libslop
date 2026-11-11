// BowlingGameTools.h
// create by lfy
// 2023.07.13

#include "Plant_BowlingBulb.h"
#include "Plant_Jackfruit.h"
#include "ZombieMechDisco.h"
#include "ZombieCamel.h"
#include "AudioMgr.h"

/// bowling projectiles

class BowlingWallnutProjectileProps : public BowlingBulbProjectileProps
{
public:
    RT_CLASS_DEFINE(BowlingWallnutProjectileProps, BowlingBulbProjectileProps, RtClass);
    int LootInrementCount;
};


class BowlingWallnutProjectile : public BowlingBulbProjectile
{
public:
    RT_CLASS_DEFINE(BowlingWallnutProjectile, BowlingBulbProjectile, RtClass);
    void SetNotFirst() { m_firstHit = false; }
protected:
    void dropLoot(BoardEntity* i_impactedEntity);
    void damageEntity(BoardEntity* i_entity);
    virtual void onProjectileInitialized();
    bool handleImpact(BoardEntity* i_impactedEntity) override;
    void onDrawShadow(Sexy::Graphics *i_graphics);
private:
    int m_lootCount = 1;
    bool m_firstHit = true;
    std::vector<BoardEntity*> m_alreadyHitTargetsForLoot;
    std::vector<BoardEntity*> m_alreadyHitTargetsForDmg;
};


class BowlingBigWallnutProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(BowlingBigWallnutProjectile, Projectile, RtClass);
protected:    
    void damageEntity(BoardEntity* i_entity);
    virtual void onProjectileInitialized()  { gAudioMgr->SendEvent("Bowling_bowling");  }
    void onDrawShadow(Sexy::Graphics *i_graphics);
};


class BowlingWallnutBoomProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(BowlingWallnutBoomProjectile, Projectile, RtClass);
protected:    
    void damageEntity(BoardEntity* i_entity);
    void onDrawShadow(Sexy::Graphics *i_graphics);
    virtual void onProjectileInitialized()  { gAudioMgr->SendEvent("Bowling_bowling");  }
};


class BowlingPrimevalWallnutProjectile : public BowlingBulbSuperProjectile
{
public:
    RT_CLASS_DEFINE(BowlingPrimevalWallnutProjectile, BowlingBulbSuperProjectile, RtClass);
protected:    
    void damageEntity(BoardEntity* i_entity);
    bool OnCollideEntity(BoardEntity* i_entity);
    virtual void onProjectileInitialized()  { gAudioMgr->SendEvent("Bowling_bowling");  }
    void onDrawShadow(Sexy::Graphics *i_graphics);
private:
    std::vector<BoardEntity*> m_alreadyHitTargetsForDmg;
};


class BowlingJackfruit : public GridItemJackFruit
{
public:
    RT_CLASS_DEFINE(BowlingJackfruit, GridItemJackFruit, RtClass);
protected:
    void onGridItemInitialize() override;    
};

class BowlingJackfruitProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(BowlingJackfruitProjectile, Projectile, RtClass);
protected:        
    bool OnCollideEntity(BoardEntity* i_entity);
    void onProjectileInitialized();
    void onDrawShadow(Sexy::Graphics *i_graphics);
private:
    std::vector<RtWeakPtr<BoardEntity>> m_hits;
};

/// new bowling zombies

class BowlingMechDisco : public ZombieMechDisco
{
public:
    RT_CLASS_DEFINE(BowlingMechDisco, ZombieMechDisco, RtClass);
protected:
    void onEnterState_Dancing(ZombieState i_fromState) override;
    void onEnterState_DanceCooldown(ZombieState i_fromState) override;
    void updateState_DanceCooldown() override;
    void updateState_Walk() override;
    void updateDancers() override;
    void onEnterState_Walk(ZombieState i_fromState) override;
    void updateState_Dancing() override;
};

class BowlingCamel : public ZombieCamel
{
public:
    RT_CLASS_DEFINE(BowlingCamel, ZombieCamel, RtClass);
protected:
    void onCamelStateChange() override;
    // bool canBecomeUncamel() override;
};