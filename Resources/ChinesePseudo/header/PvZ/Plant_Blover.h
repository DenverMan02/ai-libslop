//
//  Plant_Blover.h
//  PlantsVersusZombies2
//
//  Created by aseavy on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_BLOVER_H__
#define __PLANT_BLOVER_H__

#include <string>

#include "PlantFramework.h"
#include "RtObject.h"

/*
==============================================================
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

class PlantBlover : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBlover, PlantFramework, RtClass);

	virtual void	Initialize() override;
	virtual void	UpdateActions() override;

	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

    bool IsInvincible() const override { return true; }
    bool CanBeShoveled() override { return false; }
    bool CanBeTargeted() override { return false; }
    void TakeSmashAttack(ZombiePtr i_srcZombie) override {}

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	void BlowZombies();
};

namespace Message
{
	void PlantBloverWind();
}

#endif //__PLANT_WALLNUT_H__
