//
//  ZombieHeianSushi.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEHEIANSUSHI_H__
#define __ZOMBIEHEIANSUSHI_H__

#include "Precompile.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "Projectile.h"
#include "ZombieAnimRig.h"
#include "GridItemBreakableTarget.h"

class ZombieHeianSushiProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieHeianSushiProps, ZombiePropertySheet, RtClass);
	
	ZombieHeianSushiProps()
	{
		TimeBetweenCasts = 0.f;
		TimeBetweenRaisings = 6.0f;
	}
	
	float TimeBetweenCasts;
	float TimeBetweenRaisings;
	ProjectilePropertySheetPtr Projectile;
};


class GridItemSushiProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemSushiProps, GridItemBreakableTargetProps, RtClass);

	GridItemSushiProps()
	{
		SpeedUpTimer = 4;
	}

	float SpeedUpTimer;
	std::vector<std::string> BlackList;
};

class GridItemSushi : public GridItemBreakableTarget
{
public:
    RT_CLASS_DEFINE(GridItemSushi, GridItemBreakableTarget, RtClass);

    GridItemSushi();

    virtual int CalcRenderOrder() const override;
	virtual void TakeDamage(const DamageInfo& i_damage) override;
    virtual bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override { return true; }
	virtual void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons) const override;

protected:
	virtual void onUpdate() override;
    virtual void onGridItemInitialize() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override;

};

class HeianSushiProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(HeianSushiProjectile, Projectile, RtClass);
	
    HeianSushiProjectile();
    
	void SetGridTarget(const Sexy::Point& i_targetGridLoc) { m_targetGridLoc = i_targetGridLoc; }
    void SetCreateZombie() { m_createZombieAtGrid = true; }
    void SetGridStoneHitPoint(float hitpoint) {m_gravestoneHitPoint = hitpoint;}
	virtual bool OnCollideGround() override;
	
private:
	Sexy::Point m_targetGridLoc;
    bool        m_createZombieAtGrid;
    float       m_gravestoneHitPoint;
};


STATE_ENUM_CHILD_BEGIN(ZombieState_Sushi, ZombieState)
	ZS_SS_Waiting,
	ZS_SS_Spawning,
STATE_ENUM_END(ZombieState_Sushi)

class ZombieHeianSushi : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieHeianSushi, Zombie, RtClass);

protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, Waiting);
	DECLARE_STATE_FUNCTIONS(ZombieState, Spawning);
	
	virtual void startSpawnAnim();
	virtual void onSpawnAnimDone();
	virtual void onThrow();
	virtual void throwSushi(const Sexy::Point& i_gridLoc);
	
	virtual bool findTargetPosition(Sexy::Point& o_targetPoint);

	virtual std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }
    
protected:
	pvztime_t m_startThrowTime;
	Point m_throwingTarget;
};


class ZombieAnimRig_HeianSushi : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_HeianSushi, ZombieAnimRig, RtClass);
	
	typedef RtReflectionDelegate<Delegate0> TossAnimDoneReflectionDelegate;
	typedef RtReflectionDelegate<Delegate0> TossSushiReflectionDelegate;

	// New functionality
	virtual bool PlayTossAnim(TossAnimDoneReflectionDelegate i_onAnimDone, TossSushiReflectionDelegate i_onThrow);
		
protected:
	virtual void onAnimStopped() override;
	virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	TossAnimDoneReflectionDelegate m_onAnimDone;
	TossSushiReflectionDelegate m_onThrow;
};

#endif
