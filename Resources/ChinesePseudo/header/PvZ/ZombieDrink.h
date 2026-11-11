//
//  ZombieDrink.h
//  PlantsVersusZombies2
//
//  Created by Zhangxy on 11/14/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieDrink_h
#define PlantsVersusZombies2_ZombieDrink_h

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieDrinkState, ZombieState)
ZS_Drink_BecomeCrazy,
ZS_Drink_Recover,
STATE_ENUM_END(ZombieDrinkState);

class ZombieDrink : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieDrink, Zombie, RtClass);

	void onApplyCondition(ZombieConditions i_condition) override;
	virtual void takeBodyDamage(const DamageInfo& i_incomingDamage) override;

	virtual Sexy::Rect CalcZombieAttackRect() override;

protected:
    DECLARE_STATE_FUNCTIONS(ZombieState, BecomeCrazy);
    DECLARE_STATE_FUNCTIONS(ZombieState, Recover);    
    
	virtual void onZombieInitialize() override;
    
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
    void onCrazyAnimDone(StandaloneEffect* i_effect);
    void onRecoverAnimDone(StandaloneEffect* i_effect);
    virtual float getHeadDropFraction() const override;
	virtual float getArmDropFraction() const override;

private:

	bool m_bCrazy = false;
};

#endif
