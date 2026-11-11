//
//  Plant_HypnoShroom.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 4/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PLANT_HYPNO_SHROOM_H__
#define __PLANT_HYPNO_SHROOM_H__

#include "DamageInfo.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "PlantAnimRig.h"
#include "RtObject.h"
#include "ZombieEnums.h"

namespace Message
{
    void ZombieHypnotized(Zombie* i_zombie);
}

class PlantHypnoShroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHypnoShroom, PlantFramework, RtClass);

	void Initialize() override;
	bool CanApplyPlantfood() override;
	DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	void ApplyPlantfood() override;

	void ChangeZombieTeam(Zombie* i_zombie) const;

private:
	void createFriendlyZombieFrom(Zombie* i_enemyZombie);
	bool isZombieBlacklisted(Zombie* i_zombie);
};

class PlantAnimRig_HypnoShroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HypnoShroom, PlantAnimRig, RtClass);
	
    virtual bool playPlantFoodOn() override;
	virtual bool playPlantFoodMain() override;
	virtual bool playPlantFoodOff() override;
    virtual bool PlayPlantFoodEnd() override;
};

#endif

