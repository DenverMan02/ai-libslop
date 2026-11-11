//
//  BeghouledArcadeModule.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 6/22/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BeghouledArcadeModule__
#define __PlantsVersusZombies2__BeghouledArcadeModule__

#include "ArcadeModule.h"

class BeghouledArcadeModule : public ArcadeModule
{
public:
	RT_CLASS_DEFINE(BeghouledArcadeModule, ArcadeModule, RtClass) {}
};

class BeghouledArcadeModuleProperties : public ArcadeModuleProperties
{
public:
	RT_CLASS_DEFINE(BeghouledArcadeModuleProperties, ArcadeModuleProperties, RtClass) {}
	RtClass* GetModuleClass() const override { return BeghouledArcadeModule::StaticGetClass(); }
};

#endif /* defined(__PlantsVersusZombies2__BeghouledArcadeModule__) */
