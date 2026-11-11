//
//  PassionFlowerProjectile.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/1/19.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PassionFlowerProjectile_h
#define PassionFlowerProjectile_h

#include "Projectile.h"
#include "Plant.h"

class PassionFlowerProjectile : public Projectile
{
public:
    enum PassionFlowerProjectileStatus
    {
        PassionFlowerStatus_Flying,
        PassionFlowerStatus_Hitting,
    };
    PassionFlowerProjectile() : m_bShouldStun(false), m_bIsStoped(false), m_bIsFoodProj(false), m_bIsCatapult(false), m_isAlreadyCollide(false) {}
    RT_CLASS_DEFINE(PassionFlowerProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void onUpdate(pvztime_t i_dt) override;
    virtual void onProjectileInitialized() override;
    virtual void onDestroy() override;
    
    void SetLevelAttack(int i_plantLevel);

    
	void setShouldStun(bool stun);
	bool getShouldStun() const;

	void setBoardTarget(BoardEntityPtr i_entity);

	void setIsFoodProj(bool isFoodProj);
	bool getIsFoodProj() const;

	void setFoodTargetPos(const SexyVector3& pos);
	SexyVector3 getFoodTargetPos() const;

private:
    void dealAreaDamage();
    uint32 m_state;


    pvztime_t m_damageTime; //For dealing damage with interval
    pvztime_t m_aliveTime; //For life period
    
    int m_plantLevel;
	bool m_bShouldStun;
	BoardEntityPtr m_boardTarget;
	bool m_bIsStoped;
	SexyVector3 m_foodTargetPos;
	bool m_bIsFoodProj;
	bool  m_bIsCatapult;
	bool m_isAlreadyCollide;
};


class PassionFlowerProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(PassionFlowerProjectileProps, ProjectilePropertySheet, RtClass);

	PassionFlowerProjectileProps() : i_damageTime(1.0f), i_aliveTime(3.f)
	{

	}

	RtWeakPtr<ProjectilePropertySheet>  smallBullets;
	pvztime_t i_damageTime;
	pvztime_t i_aliveTime;
};


class PassionFlowerLV5SmallProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PassionFlowerLV5SmallProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;

	void SetNoCollEntity(BoardEntityPtr i_entity);
private:
	BoardEntityPtr  m_pNoCollEntity;
};

#endif /* PassionFlowerProjectile_h */
