//
//  Plant_CoffeeBean.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-4.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_CoffeeBean__
#define __PlantsVersusZombies2__Plant_CoffeeBean__

#include "PlantFramework.h"
#include "PlantAnimRig.h"

class PlantAnimRig_CoffeeBean : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_CoffeeBean, PlantAnimRig, RtClass);
	
	bool PlayWakeUp(AnimStoppedReflectionDelegate i_onAnimStopped);
};

///////

class PlantCoffeeBean : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCoffeeBean, PlantFramework, RtClass) {}
    
	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
    
    virtual int     CalcRenderOrder() override;
    
	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    
	bool CanBeShoveled() override { return false; }
	bool CanBeTargeted() override { return false; }
	bool IsInvincible() const override { return true; }
    
    virtual void onAnimStoppedCallback(const std::string &i_animLabel) override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
};

class PlantTypeCoffeeBean : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeCoffeeBean, PlantType, RtClass) {}
    
	bool CanPlantOnPlant(Plant* plant) const override { return true; }
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

#endif /* defined(__PlantsVersusZombies2__Plant_CoffeeBean__) */
