#ifndef CardEffectComponents_H
#define CardEffectComponents_H


#include "GridItemAnimation.h"
#include "Projectile.h"

typedef RtWeakPtr<class Zombie> ZombiePtr;


class CardGameGridItemFireWall : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(CardGameGridItemFireWall, GridItemAnimation, RtClass);

    CardGameGridItemFireWall();

    virtual int CalcRenderOrder() const override;
   	virtual void onGridItemInitialize() override;

protected:
    virtual void onUpdate() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onAnimationDone(const std::string& i_tabel);
private:
    void takeEffect();

    pvztime_t m_endTime;
};

class CardGameGridItemMissileLeader : public GridItem
{
public:
    RT_CLASS_DEFINE(CardGameGridItemMissileLeader, GridItem, RtClass);

    CardGameGridItemMissileLeader();
   	virtual void onGridItemInitialize() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    virtual bool IsDamageable() const override { return false; }

protected:
    virtual void onUpdate() override;
    void launchMissile();
    
private:
    pvztime_t m_timer;
};

class CardGameMissileProjectileProperty : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(CardGameMissileProjectileProperty, ProjectilePropertySheet, RtClass);

    CardGameMissileProjectileProperty()
    :GridItemCardGameZombieDamageRate(1.0f)
    {

    }

    float GridItemCardGameZombieDamageRate;
};

class CardGameMissileProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(CardGameMissileProjectile, Projectile, RtClass);

protected:
    virtual void radiateSplashDamage(BoardEntity* i_impactedEntity) override;
    virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
};


class CardGameGridItemMagicMirror : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(CardGameGridItemMagicMirror, GridItemAnimation, RtClass);

    CardGameGridItemMagicMirror();

   	virtual void onGridItemInitialize() override;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }

protected:
    virtual void onUpdate() override;

    std::vector<ZombiePtr> m_cloneZombieList;
};


#endif