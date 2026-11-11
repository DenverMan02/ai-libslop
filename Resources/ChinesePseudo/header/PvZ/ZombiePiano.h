//
//  ZombiePiano.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_PIANO_H__
#define __ZOMBIE_PIANO_H__

#include "Zombie.h"

class ZombiePiano : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePiano, Zombie, RtClass);
	
protected:
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	virtual void onInitialized() override;
    void onLostArm() override;
    void onRegrowArm() override;
    virtual void onTakeFatalDamage(const DamageInfo &i_lastDamageReceived) override;
    virtual void onUpdate() override;
    
    DamageTypeFlags getEatingDamageType() const override;
};

#endif
