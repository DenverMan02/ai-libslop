//
//  ZombieBallon.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/4/21.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef ZombieBallon_h
#define ZombieBallon_h

#include "ZombieLostCityBug.h"

class ZombieBallon : public ZombieLostCityBug
{
public:
    RT_CLASS_DEFINE(ZombieBallon, ZombieLostCityBug, RtClass);
    
protected:
    std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_IMP_SHOCK"; }
    std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_IMP_ASH"; }
    
private:
    virtual void onDieCompleted() override;
    virtual void addBasicAshDeathEffect() override { return; }
};

#endif /* ZombieBallon_h */
