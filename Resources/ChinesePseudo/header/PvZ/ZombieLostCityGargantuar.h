//
//  ZombieLostCityGargantuar.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 4/30/2015.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieLostCityGargantuar_h
#define PlantsVersusZombies2_ZombieLostCityGargantuar_h

#include "ZombieGargantuar.h"
#include "ZombieAnimRig_Gargantuar.h"

class ZombieLostCityGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieLostCityGargantuar, ZombieGargantuar, RtClass);
    
    void onApplyCondition(ZombieConditions i_condition) override;
    void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
    void onTakeFatalDamage(const DamageInfo &i_lastDamageReceived) override;
    void onLostHead() override;
};

class ZombieAnimRig_LostCityGargantuar : public ZombieAnimRig_Gargantuar
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_LostCityGargantuar, ZombieAnimRig_Gargantuar, RtClass);
    
    ZombieAnimRig_LostCityGargantuar()
    {
        m_hasTorch = true;
    }
    
    void SetTorchLayers(bool i_visible);
    
private:
    bool m_hasTorch;
};

#endif
