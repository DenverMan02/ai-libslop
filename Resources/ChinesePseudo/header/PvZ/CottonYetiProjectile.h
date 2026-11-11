//
//  CottonYetiProjectile.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/11/9.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef CottonYetiProjectile_h
#define CottonYetiProjectile_h

#include "Projectile.h"

class CottonYetiProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(CottonYetiProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual bool OnCollideGround() override;
    virtual void onUpdate(pvztime_t i_dt) override;
    virtual void onProjectileInitialized() override;
    
    virtual void SetOwner(const BoardEntityPtr i_owner);
    
protected:
    BoardEntityPtr m_owner;
    float m_extraDpsModifier;
    
private:
    void GroundTouched();
    void dealAreaDamage(float i_damage);
    void onAnimStopped(const std::string &i_animName);
    std::vector<BoardEntityPtr> m_hitEntities;

    
};

class CottonYetiPlantfoodProjectile : public CottonYetiProjectile
{
public:
    RT_CLASS_DEFINE(CottonYetiPlantfoodProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual bool OnCollideGround() override;
    virtual bool OnCollideRoof() override;
    virtual void onProjectileInitialized() override;
    virtual void onUpdate(pvztime_t i_dt) override;
    
    void SetIsAvatarAttack(bool i_isAvatarAttack) { m_isAvatarAttack = i_isAvatarAttack; }
    void SetTargetLoc(const SexyVector2& i_grid) { m_targetGrid = i_grid; }
    
    void SetOwner(const BoardEntityPtr i_owner) override;
    
protected:
    BoardEntityPtr m_owner;
    float m_extraDpsModifier;

private:
    void dealAreaDamage();
    void onAnimStopped(const std::string &i_animName);
    
    bool m_isAvatarAttack;
    int m_damageDealIndex;
    SexyVector2 m_targetGrid;
    bool m_hasCollidRoof;
};

#endif /* CottonYetiProjectile_h */
