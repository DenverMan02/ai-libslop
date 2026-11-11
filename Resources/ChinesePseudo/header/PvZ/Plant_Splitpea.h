//
//  Plant_Splitpea.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_SPLITPEA_H__
#define __PLANT_SPLITPEA_H__

#include "PlantFramework.h"
#include "PlantUtils.h"

class PlantSplitpea : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSplitpea, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;

    ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    GridItemPtr FindTargetDamageableGridItem(Rect& i_rect, PlantWeapon i_plantWeapon) override;

	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual void PlayAttackAnimation() override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void FireLeft();
    void FireRigtWithAvatarPlantFood();

private:
	void reverseProjectile(Projectile* projectile);
	void onAnimStoppedCallback(const std::string& name) override;
	
	enum States 
	{
		STATE_PLANTFOOD_FINALE  = STATE_FRAMEWORK_BEGIN,
	};

	PeashooterPlantfood m_forwardPlantfood;
	PeashooterPlantfood m_backwardPlantfood;
};

#endif
