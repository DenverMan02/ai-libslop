//
//  AgaveSwordLight.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/12/3.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef AgaveSwordLight_h
#define AgaveSwordLight_h

#include "Projectile.h"

class AgaveSwordLight : public Projectile
{
public:
    RT_CLASS_DEFINE(AgaveSwordLight, Projectile, RtClass);
    virtual void onProjectileInitialized() override;
    void SetOwner(BoardEntityPtr i_owner) { m_owner = i_owner; }

protected:
    virtual void	onUpdate(pvztime_t i_dt) override;
    virtual bool    OnCollideEntity(BoardEntity* i_entity) override;
    virtual void    Draw(Graphics* i_g) override;
    virtual void    InitialSetPosition(const float i_x, const float i_y, const float i_z) override;
    void            onAnimationDone(const std::string& i_animName);
    
private:
    void dealAreaDamage();
    
    std::vector<BoardEntityPtr> m_hitEntities;
    Rect m_collisionRect;
    int m_movingHeight = 0;
    pvztime_t m_damageTime = PVZ_EOT();
    BoardEntityPtr m_owner;
};


class AgaveSwordQi : public Projectile
{
public:
    RT_CLASS_DEFINE(AgaveSwordQi, Projectile, RtClass);
    virtual void onProjectileInitialized() override;
    void InitSwordQi(int i_type, int i_gridLength);

protected:
    virtual void	onUpdate(pvztime_t i_dt) override;
    virtual bool    OnCollideEntity(BoardEntity* i_entity) override;
    void            onAnimationDone(const std::string& i_animName);
    
    int m_type;
    bool m_destroyed;
    int m_disappearX;
    std::vector<BoardEntityPtr> m_hitEntities;
};


#endif /* AgaveSwordLight_h */
