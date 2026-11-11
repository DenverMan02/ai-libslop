//
//  ZombieStrongBronze.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-12-30.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieStrongBronze__
#define __PlantsVersusZombies2__ZombieStrongBronze__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieStrongBronzeState, ZombieState)
ZS_StrongBronze_BecomeCrazy,
ZS_StrongBronze_Debut,
STATE_ENUM_END(ZombieStrongBronzeState);

class ZombieStrongBronze : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieStrongBronze, Zombie, RtClass);
    
	void onApplyCondition(ZombieConditions i_condition) override;
	virtual void takeBodyDamage(const DamageInfo& i_incomingDamage) override;
    
	virtual Sexy::Rect CalcZombieAttackRect() override;
    
    virtual bool CanBeFlickedOff() const override
	{
        return false;
	}
    
    virtual bool CanBeStabbed() const override
    {
        return false;
    }
    
protected:
    DECLARE_STATE_FUNCTIONS(ZombieState, BecomeCrazy);
    DECLARE_STATE_FUNCTIONS(ZombieState, Debut);
    //DECLARE_STATE_FUNCTIONS(ZombieState, Recover);
    
	virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    
    virtual std::string getElectrocutePAMName() const override;
	virtual std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BRONZE_ASH"; }

    SexyVector3 GetStunnedEffectOffset() const override;
    
    virtual ZombieParticle* DropArm() override;
    
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
    void onCrazyAnimDone(StandaloneEffect* i_effect);
    void onDebutAnimDone(StandaloneEffect* i_effect);
    
    virtual float getHeadDropFraction() const override;
	virtual float getArmDropFraction() const override;
    
private:
    
	bool m_bCrazy = false;
};

#endif /* defined(__PlantsVersusZombies2__ZombieStrongBronze__) */
