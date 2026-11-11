//
//  ZombieSelfExplode.h
//  PlantsVersusZombies2
//
//  Created by Zhangxy on 11/14/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieSelfExplode_h
#define PlantsVersusZombies2_ZombieSelfExplode_h

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_SelfExplode, ZombieState)
ZS_SelfExplode_Detonate,
STATE_ENUM_END(ZombieState_SelfExplode)

class ZombieSelfExplode : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieSelfExplode, Zombie, RtClass);

	void onApplyCondition(ZombieConditions i_condition) override;

	virtual Sexy::Rect CalcZombieAttackRect() override;
    
    bool GetIsBombing()
    {
        return m_IsBombing;
    }

protected:
    
	virtual void onZombieInitialize() override;
	virtual void onLostHead() override;
    virtual void onLostArm() override;
    
    //virtual void DropArm();
    
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
    
	void findAndBurnAPlant();
    
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    DECLARE_STATE_FUNCTIONS(ZombieState, Detonate);
    
    virtual void onEnterState_Eat(ZombieState i_fromState) override;
    virtual void updateState_Eat() override;
    virtual void onExitState_Eat(ZombieState i_toState) override;
    
protected:
    
    void onBigBangAnimationDone(StandaloneEffect* i_effect);
    
    void setIsBombBurning(bool i_isBurning);
    void TryDetonatedBomb();
protected:
    
    bool m_HaveBomb;
    
    bool m_IsBombing;
    
    bool m_IsEating;
};

#endif
