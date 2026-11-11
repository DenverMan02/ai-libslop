//
//  BambooProjectile.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-7-9.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BambooProjectile__
#define __PlantsVersusZombies2__BambooProjectile__

#include "Projectile.h"

class BambooProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BambooProjectile, Projectile, RtClass);
    
    BambooProjectile();
    ~BambooProjectile();
    
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void onDestroy() override;
    void tossZombie(class Zombie *i_zombie);
    void setShouldTossZombie(bool i_shouldToss) {m_shouldTossZombie = i_shouldToss; }
    void setAttackDone(bool i_done) { m_attackDone = i_done; }
protected:
	virtual void onUpdate(pvztime_t i_dt) override;
    
private:    
    std::vector<BoardEntityPtr> m_hitEntities;
    bool m_shouldTossZombie;
    bool m_attackDone = false;
};

class BambooPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BambooPlantfoodProjectile, Projectile, RtClass);
    
    BambooPlantfoodProjectile();
    ~BambooPlantfoodProjectile();
    
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void onDestroy() override;
    void setAttackDone(bool i_done) { m_attackDone = i_done; }
    
protected:
	virtual void onUpdate(pvztime_t i_dt) override;
    
private:
    std::vector<BoardEntityPtr> m_hitEntities;
    bool m_attackDone = false;
};



#endif /* defined(__PlantsVersusZombies2__BambooProjectile__) */
