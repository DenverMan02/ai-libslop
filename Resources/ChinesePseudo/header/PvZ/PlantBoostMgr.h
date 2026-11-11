//
//  PlantBoostMgr.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 10/28/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantBoostMgr__
#define __PlantsVersusZombies2__PlantBoostMgr__

#include <vector>

#include "PVZTypes.h"
#include "PlantBoostPropertySheet.h"
#include "PlantAccessoryPropertySheet.h"
#include "PlantPropertySheet.h"
#include "Singleton.h"


// For plant accessory and boost manager
class PlantBoostMgr : public LazySingleton<PlantBoostMgr>
{
public:
	
	PlantBoostMgr();

	// Boost Management
	float GetPlantBoostValue(int i_plantID, PlantBoostType i_boostType, int i_index = 0, float i_default = 0.0f);
    
    std::vector<std::vector<float>> GetPlantBoostValues(int i_plantID, PlantBoostType i_boostType);
};

#endif /* defined(__PlantsVersusZombies2__PlantBoostMgr__) */
