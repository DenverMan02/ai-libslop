//
//  ZombiePirateBarrel.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEPIRATEBARREL_H__
#define __ZOMBIEPIRATEBARREL_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieStateBarrel, ZombieState)
	ZS_B_BarrelIdle,
	ZS_B_BarrelRoll,
STATE_ENUM_END(ZombieStateBarrel)

class ZombiePirateBarrel : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePirateBarrel, Zombie, RtClass);
	
	void SetPusherZombie(ZombiePtr i_pusher);
	void SetBeingPushed(bool i_pushed);
	bool IsCrushingPlant();
	
	bool CanBePushed();

	bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
	virtual SexyVector3 CalcProjectileTargetLocation(float i_inTime) override;

	virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;

	ZombiePtr GetPusherZombie() { return m_myPusher; }

protected:
	virtual void onApplyCondition(ZombieConditions i_condition) override;
	virtual void onInitialized() override;
	virtual void onPlaceOnStreet() override;
	virtual void onPlaceOnBoard() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	
    bool isImmuneToShrinking() override { return true; }
    
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
    
	virtual void onDestroy() override;
	virtual void onUpdate() override;

	virtual void chooseDeathState(const DamageInfo& i_deathBlow) override;
    
    DamageTypeFlags getEatingDamageType() const override;

	bool tryEating();

	DECLARE_STATE_FUNCTIONS(ZombieState, BarrelIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, BarrelRoll);

private:
	void spawnImp(const int i_row);
	
	bool m_beingPushed;
	bool m_ateSomethingLastFrame;
	ZombiePtr m_myPusher;
	pvztime_t m_burstTime;
};

#endif
