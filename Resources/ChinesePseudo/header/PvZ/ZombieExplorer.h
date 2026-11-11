//
//  ZombieExplorer.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 7/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieExplorer_h
#define PlantsVersusZombies2_ZombieExplorer_h

#include "Zombie.h"

class ZombieExplorer : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieExplorer, Zombie, RtClass);

	void onApplyCondition(ZombieConditions i_condition) override;

	virtual Sexy::Rect CalcZombieAttackRect() override;

	void setIsTorchBurning(bool i_isBurning);

protected:
	virtual void onZombieInitialize() override;
	virtual void onLostHead() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	void burnPlantGroup(PlantGroup* i_plantGroup);
    
	// void burnPlant(class Plant* targetPlant);
    void burnZombie(class Zombie* targetZombie);
    void onUpdate() override;

    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_ONEXIT(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Die);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    
private:
};

namespace Message
{
    void ExplorerTorchExtinguished(Zombie* i_zombie);
}

#endif
