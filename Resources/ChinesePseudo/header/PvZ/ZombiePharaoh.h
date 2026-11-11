//
//  ZombiePharaoh.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePharaoh_h
#define PlantsVersusZombies2_ZombiePharaoh_h

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombiePharaohState, ZombieState)
    ZS_Pharaoh_BustingOut,
STATE_ENUM_END(ZombiePharaohState);

class ZombiePharaoh : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombiePharaoh, Zombie, RtClass);

    virtual void onApplyCondition(ZombieConditions i_condition) override;
    virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
    
private:
    // states
    DECLARE_STATE_FUNCTIONS(ZombieState, BustingOut);

    // dispatches from parent class.
	virtual void onZombieInitialize() override;
    class ZombieParticle* onHelmDropped(HelmType i_oldHelmType, int i_helmHitpoints) override;
    
    // animation callbacks. 
    void onBustingOutAnimDone(StandaloneEffect* i_effect);
	
	int m_helmDamageIndex = 0;
    
};

#endif
