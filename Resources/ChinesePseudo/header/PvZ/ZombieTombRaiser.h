//
//  ZombieTombRaiser.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIETOMBRAISER_H__
#define __ZOMBIETOMBRAISER_H__

#include "Precompile.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "Projectile.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_TombRaiser, ZombieState)
	ZS_TR_Waiting,
	ZS_TR_Spawning,
STATE_ENUM_END(ZombieState_TombRaiser)

class TombraiserProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(TombraiserProjectile, Projectile, RtClass);
	
    TombraiserProjectile();
    
	void SetGridTarget(const Sexy::Point& i_targetGridLoc) { m_targetGridLoc = i_targetGridLoc; }
    void SetCreateZombie() { m_createZombieAtGrid = true; }
    void SetGridStoneHitPoint(float hitpoint) {m_gravestoneHitPoint = hitpoint;}
	virtual bool OnCollideGround() override;
	
private:
	Sexy::Point m_targetGridLoc;
    bool        m_createZombieAtGrid;
    float       m_gravestoneHitPoint;
};


class ZombieTombRaiser : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieTombRaiser, Zombie, RtClass);

protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;

	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, Waiting);
	DECLARE_STATE_FUNCTIONS(ZombieState, Spawning);
	
	virtual void startSpawnAnim();
	virtual void onSpawnAnimDone();
	virtual void onThrow();
	virtual void throwBone(const Sexy::Point& i_gridLoc);
	bool isPendingGraveAt(int i_gridX, int i_gridY);
	bool isTombraiserZombieAt(int i_gridX, int i_gridY);
	
	virtual bool findTargetPosition(Sexy::Point& o_targetPoint);
	bool isInExistPosition(const Point& i_point);
    
protected:
	int m_remainingAmmo;
	int m_remainingGravespawnAttempts;
	pvztime_t m_startThrowTime;
	Point m_throwingTarget;
	
	struct SpellBolt
	{
		float posX;
		float posY;
		float velX;
		float velY;
		int lifetime;
		int targetCellX;
		int targetCellY;
	};

	std::vector<SpellBolt> m_pendingGraves;
	std::vector<Point> m_throwingTargets;
};
#endif
