//
//  Plant_PerfumeShroom.h
//  PlantsVersusZombies2
//
//  Created by Mina, Elliot on 9/11/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PLANT_PERFUMESHROOM_H__
#define __PLANT_PERFUMESHROOM_H__

#include "PlantFramework.h"
#include "ComponentPropagatedBurst.h"
#include "RtObject.h"

class PlantPerfumeShroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantPerfumeShroomProps, PlantPropertySheet, RtClass);
	
	PlantPerfumeShroomProps()
	{
        EffectLoopCountDelta1 = 1;
        EffectLoopCountDelta2 = 2;
	}
    ComponentPropagatedBurstProps CharmBurstProps;
    int EffectLoopCountDelta1;
    int EffectLoopCountDelta2;
};

class PlantPerfumeShroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPerfumeShroom, PlantFramework, RtClass) {}

	void	Initialize() override;
	void	UpdateActions() override;

	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;

	bool CanBeShoveled()		override { return false; }
	bool CanBeTargeted()		override { return false; }
	bool IsInvincible() const	override { return true; }
	void TakeSmashAttack(ZombiePtr i_srcZombie) override		{}
	
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_anim) override;

private:
	void	explode();
};

#endif //__PLANT_PERFUMESHROOM_H__
