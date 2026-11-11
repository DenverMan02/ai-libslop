//
//  Plant_EMPea.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_EMPea_h
#define PlantsVersusZombies2_Plant_EMPea_h

#include "PlantFramework.h"
#include "ZombieEnums.h"

class Zombie;

class PlantEMPea : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantEMPea, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void UpdateActions() override;

	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;

	bool IsInvincible() const override { return true; }
	bool CanBeShoveled() override { return false; }
	bool CanBeTargeted() override { return false; }
	virtual void TakeSmashAttack(ZombiePtr i_srcZombie) override {}

	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

private:
	void setState(uint i_plantState);
	void startExploding();
	void fire();
	void stunZombie(Zombie* i_zombie);

	std::vector<ZombieTypePtr> m_affectedZombieTypes;
};

#endif
