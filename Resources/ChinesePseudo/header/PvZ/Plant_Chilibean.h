//
//  Plant_Chilibean.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/18/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_CHILIBEAN_H__
#define __PLANT_CHILIBEAN_H__

#include "PlantFramework.h"

class PlantChilibean : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantChilibean, PlantFramework, RtClass){}

    virtual void	Initialize() override;
    
public:
	virtual bool	CanApplyPlantfood() override;
	virtual DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual void OnRelocationComplete() override;

	virtual void ApplyPlantfood() override;
    
    void onSetDuplicate(bool i_duplicate) override { };
    //void onBeThrown() override {};
	
private:
	void flyThroughAir(Sexy::SexyVector2 i_startPixelLoc, Sexy::SexyVector2 i_destPixelLoc);
	void fireMines();
};

#endif

