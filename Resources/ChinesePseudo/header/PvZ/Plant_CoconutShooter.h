/*
 * Plant_CoconutShooter.h
 *
 *  Created on: 2017-8-31
 *      Author: Administrator
 */

#ifndef PLANT_COCONUTSHOOTER_H_
#define PLANT_COCONUTSHOOTER_H_

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"

class PlantCoconutShooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCoconutShooter, PlantFramework, RtClass);

	PlantCoconutShooter();
    virtual ~PlantCoconutShooter();

    void UpdateActions() override;

    void Initialize() override;

    bool			CanApplyPlantfood() override;
	void			ApplyPlantfood() override;
	void			CancelPlantfood() override;

    Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    virtual bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;

private:
    BoardEntityPtr  FindClosetTarget(PlantWeapon i_plantWeapon, bool i_zombie);
};


#endif /* PLANT_COCONUTSHOOTER_H_ */
