//
//  Plant_LaserBean.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 12/12/11.
//  Copyright (c) 2011 PopCap Games. All rights reserved.
//

#ifndef __PLANT_LASERBEAN_H__
#define __PLANT_LASERBEAN_H__

#include "Precompile.h"
#include "PlantFramework.h"
#include "GridItem.h"
#include "PlantAnimRig.h"

class PlantLaserBean : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantLaserBean, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;
	virtual Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual void PlayAttackAnimation() override;
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual int CalcRenderOrder() override;

	DamageTypeFlags	GetDamageFlags(PlantWeapon i_plantWeapon) override { return DAMAGE_ELECTRIC; }
    
private:
	std::vector<RtWeakPtr<BoardEntity> > m_hitEntities;
	pvztime_t m_nextLaserDamageTime;
    float m_attackDamageRate;
	bool m_idlePostAttack;
    bool m_isFirstAttack;
};

////////


class PlantAnimRig_LaserBean : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_LaserBean, PlantAnimRig, RtClass);
    
    virtual bool playPlantFoodOn() override;
	virtual bool playPlantFoodMain() override;
	virtual bool playPlantFoodOff() override;
};

#endif // __PLANT_LASERBEAN_H__
