//
//  ZombieLostCityJane.h
//  PlantsVersusZombies2
//
//  Created by Schneider, Aaron on 4/29/15
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLostCityJane__
#define __PlantsVersusZombies2__ZombieLostCityJane__

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig.h"
#include "Zombie.h"

class ZombieLostCityJaneProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieLostCityJaneProps, ZombiePropertySheet, RtClass);
    
    ZombieLostCityJaneProps()
    {
        ProjectileBounceHeight = 600;
        ProjectileBounceTime = 1.3f;
        ProjectileBounceDistance = 800;
    }
    
    int ProjectileBounceHeight;
    float ProjectileBounceTime;
    int ProjectileBounceDistance;
    
    std::vector<ProjectilePropertySheetPtr> BounceableProjectiles;
};

class ZombieAnimRig_LostCityJane : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_LostCityJane, ZombieAnimRig, RtClass) {}
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

class ZombieLostCityJane : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieLostCityJane, Zombie, RtClass);
    
    ZombieLostCityJane();
    
    bool OverrideProjectileCollision(class Projectile* i_projectile) override;
protected:
    std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_LOSTCITY_JANE_SHOCK"; }
    std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_LOSTCITY_JANE_ASH"; }
};

#endif /* defined(__PlantsVersusZombies2__ZombieLostCityJane__) */
