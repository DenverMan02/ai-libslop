//
//  ZombiePVPSeagull.h
//  PlantsVersusZombies2
//
//  Created by  cao shuai on 3/7/16.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEPVPSEAGULL_H__
#define __ZOMBIEPVPSEAGULL_H__

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombiePropertySheet.h"
#include "RestrictionSet.h"
#include "Projectile.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_PVPSeagull, ZombieState)
    ZS_PVPSeagull_Fire,
STATE_ENUM_END(ZombieState_PVPSeagull)

class ZombiePVPSeagullProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombiePVPSeagullProps, ZombiePropertySheet, RtClass);
    
    ZombiePVPSeagullProps()
    {}

    ValueRange TimeBeforeFirstFire;
    ValueRange TimeBetweenFire;
    ValueRange GridLimit;
    
    ProjectilePropertySheetPtr          Projectile;
};

class ZombiePVPSeagull : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePVPSeagull, Zombie, RtClass);
	
	inline void SetSplineFollower(bool i_followingSpline)
	{
		m_followingSpline = i_followingSpline;
	}
	
    virtual void ApplyZombieFood() override;
    virtual void CancelZombieFood() override;
    
protected:
    
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	virtual void onZombieInitialize() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	virtual bool hasHeadParticle() const override;
	virtual class BoardEntity* findTarget() override;
	
	virtual std::string getElectrocutePAMName() const override;
	
private:
	OVERRIDE_STATE_ONEXIT(ZombieState, Electrocute);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Ash);
	DECLARE_STATE_FUNCTIONS(ZombieState, BigFire);
    
    void onBigFireAnimStopped(const std::string& i_animLabel);
    
    virtual void onApplyCondition(ZombieConditions i_condition) override;
	void playBirdLossAnimation(bool i_birdExplodes);
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

    Projectile* NewFire();
    
	bool m_followingSpline;
	bool m_butteredWhileDying;
	bool m_hasHeadParticle;
    
    pvztime_t m_nextFireTime;
    
    SexyVector3 m_fireEndPosition;
};

#endif
