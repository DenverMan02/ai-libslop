//
//  ZombieGong.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-20.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieGong__
#define __PlantsVersusZombies2__ZombieGong__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_Gong, ZombieState)
ZS_GONG_Gongging,
//ZS_GONG_Gongdone,
STATE_ENUM_END(ZombieState_Gong)

class ZombieGong : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieGong, Zombie, RtClass);
    
    virtual void onUpdate() override;
    
	void onApplyCondition(ZombieConditions i_condition) override;
    
protected:
	virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
	virtual void onLostHead() override;
    virtual void onLostArm() override;
    
    virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Die);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, Gongging);
    //DECLARE_STATE_FUNCTIONS_EMPTY(ZombieState, GONG_Gongdone);
    
private:
    bool m_hasGong;
    
    pvztime_t m_nextBehaviorTime;
    int m_nBehaviorTick;
    
    ValueRange m_actionInterval;
};

#endif /* defined(__PlantsVersusZombies2__ZombieGong__) */
