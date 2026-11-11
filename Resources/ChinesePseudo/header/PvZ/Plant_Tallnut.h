//
//  Plant_Tallnut.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Tallnut_h
#define PlantsVersusZombies2_Plant_Tallnut_h

#include "PlantFramework.h"
#include "RtObject.h"

class PlantTallnut : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantTallnut, PlantFramework, RtClass);
	
	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void PlayChewedOnSound() override;
	virtual DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
	float GetShieldHealth() { return m_shieldHealth; }

	virtual void TakeSmashAttack(ZombiePtr i_srcZombie) override;
	virtual bool TryBlockZombossRush(Zombie* i_zombie) override;
	virtual void onKilled(bool i_instantKill) override;
	virtual bool IsDelayDestroy() override;
	virtual bool CanBeTargeted() override;
	virtual bool CanBeShoveled() override;
	virtual void UpdateActions() override;
    bool CanBeWatered() override;
protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	virtual void updateShieldLayers();
	
	void DamageZombieAtGrid(int i_col, int i_row);

	float m_shieldHealth;
	int m_currentShieldDamageIndex;
	bool m_triggerSkill;
	pvztime_t m_damageTime;
	bool m_hasDamaged;
};

#endif
