//
//  PennyPerkBossBusterCannon.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 7/16/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef PennyPerkBossBusterCannon_h
#define PennyPerkBossBusterCannon_h

#include "BasicPerks.h"
#include "ProjectilePropertySheet.h"
#include "Zombie.h"

class PennyPerkBossBusterCannonProperties : public PennyPerkProperties
{
	RT_CLASS_DEFINE(PennyPerkBossBusterCannonProperties, PennyPerkProperties, RtClass);

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<float> TimesBetweenStrikes;
	std::vector<int> NumberOfHitsPerStrike;
	std::vector<int> DamagePerHit;
	ProjectilePropertySheetPtr Projectile;
	std::vector<std::string> Resources;

	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkBossBusterCannon : public PennyPerkTimedEffect
{
public:
	RT_CLASS_DEFINE(PennyPerkBossBusterCannon, PennyPerkTimedEffect, RtClass);

protected:
	void onUpdate() override;
	pvztime_t calcNextUpdateTime() override;

	ZombiePtr findTarget();
	void fireProjectiles();
};

#endif /* PennyPerkBossBusterCannon_h */
