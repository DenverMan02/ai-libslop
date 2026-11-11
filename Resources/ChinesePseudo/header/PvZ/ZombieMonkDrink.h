//
//  ZombieMonkDrink.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-1-2.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieMonkDrink__
#define __PlantsVersusZombies2__ZombieMonkDrink__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieMonkDrinkState, ZombieState)
ZS_MonkDrink_BecomeCrazy,
ZS_MonkDrink_Recover,
ZS_MonkDrink_ChargeAttack,
STATE_ENUM_END(ZombieMonkDrinkState);

class ZombieMonkDrink : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieMonkDrink, Zombie, RtClass);
    
	void onApplyCondition(ZombieConditions i_condition) override;
	virtual void takeBodyDamage(const DamageInfo& i_incomingDamage) override;
    
	virtual Sexy::Rect CalcZombieAttackRect() override;
    void ApplyZombieFood() override;
    void CancelZombieFood() override;
protected:
    DECLARE_STATE_FUNCTIONS(ZombieState, BecomeCrazy);
    DECLARE_STATE_FUNCTIONS(ZombieState, Recover);
    DECLARE_STATE_FUNCTIONS(ZombieState, ChargeAttack);
    
    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_ONEXIT(ZombieState,  Walk);
    
    OVERRIDE_STATE_ONENTER(ZombieState, Eat);
    
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

    void onEatAnimContinued(const std::string& i_endingAnimName, const std::string& i_newAnimName, int i_animEndCount);
    
	virtual void onZombieInitialize() override;
    
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
    void onCrazyAnimDone(StandaloneEffect* i_effect);
    void onRecoverAnimDone(StandaloneEffect* i_effect);
    
    virtual float getHeadDropFraction() const override;
	virtual float getArmDropFraction() const override;
private:
    void DamageTarget(BoardEntity* target, float baseDamage);
    void DamageTarget(const Rect& rect, int row, float baseDamage);
    bool CanTarget(BoardEntity* entity);
    void onAnimStopped(const std::string& i_animLabel);
    void PlayChargeAttackEffect();
    Rect CalcChargeAttackRect();
private:
    
	bool m_bCrazy = false;
};

#endif /* defined(__PlantsVersusZombies2__ZombieMonkDrink__) */
