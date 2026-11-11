//
//  Plant_Dandelion.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-8-21.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Dandelion__
#define __PlantsVersusZombies2__Plant_Dandelion__

#include <iostream>
#include "PlantFramework.h"
#include "PlantUtils.h"

class PlantDandelion : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantDandelion, PlantFramework, RtClass);
    
	virtual void			Initialize() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
protected:
    
    
private:
    
};

#endif /* defined(__PlantsVersusZombies2__Plant_Dandelion__) */
