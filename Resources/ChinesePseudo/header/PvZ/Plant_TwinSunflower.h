//
//  Plant_TwinSunflower.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_TwinSunflower_h
#define PlantsVersusZombies2_Plant_TwinSunflower_h

#include "PlantFramework.h"
#include "Plant_Sunflower.h"
#include "GameEventMgr.h"

class PlantTwinSunflower : public PlantSunflower
{
public:
	RT_CLASS_DEFINE(PlantTwinSunflower, PlantSunflower, RtClass);
	
	virtual void	Initialize() override;
	virtual void	DoSpecial(int i_extraParam = 0) override;
	virtual void	ProduceSun(const PlantAction& i_fromAction) override;
	virtual void	onKilled(bool i_instantKill) override {}
};

#endif
