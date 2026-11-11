//
//  VaseBreakerArcadeModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 8/8/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__VaseBreakerArcadeModule__
#define __PlantsVersusZombies2__VaseBreakerArcadeModule__

#include "ArcadeModule.h"

class VaseBreakerArcadeModule : public ArcadeModule
{
public:
	RT_CLASS_DEFINE(VaseBreakerArcadeModule, ArcadeModule, RtClass) {}
	
	void GetEndlessState(int& o_sun, int& o_plantFood);
	void SetEndlessState(int i_remainingSun, int i_remainingPlantFood);
};

class VaseBreakerArcadeModuleProperties : public ArcadeModuleProperties
{
public:
	RT_CLASS_DEFINE(VaseBreakerArcadeModuleProperties, ArcadeModuleProperties, RtClass) {}
	virtual RtClass* GetModuleClass() const override { return VaseBreakerArcadeModule::StaticGetClass(); }
};

class VaseBreakerMiniGameArcadeModule : public VaseBreakerArcadeModule
{
public:
	RT_CLASS_DEFINE(VaseBreakerMiniGameArcadeModule, VaseBreakerArcadeModule, RtClass) {}
protected:
	 virtual void addPowerUpsToBoard() override;
};

class VaseBreakerMiniGameArcadeModuleProperties : public VaseBreakerArcadeModuleProperties
{
public:
	RT_CLASS_DEFINE(VaseBreakerMiniGameArcadeModuleProperties, VaseBreakerArcadeModuleProperties, RtClass) {}
	virtual RtClass* GetModuleClass() const override { return VaseBreakerMiniGameArcadeModule::StaticGetClass(); }
};

#endif /* defined(__PlantsVersusZombies2__VaseBreakerArcadeModule__) */
