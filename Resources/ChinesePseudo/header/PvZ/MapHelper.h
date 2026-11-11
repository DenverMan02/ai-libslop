//
//  MapHelper.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 2/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MapHelper__
#define __PlantsVersusZombies2__MapHelper__

#include "MagentoService.h"

MagentoProductPropsPtr FindGateMagentoInformation(const class MapEventItem* i_gateEvent);
const MapEventItem* GetStargateUnlockedByEvent(const MapEventItem* i_eventItem);
const MapEventItem* GetExitStargateLinkedToStartStargate(const MapEventItem* i_eventItem);
void UnlockStargate(const MapEventItem* i_startStargate, const bool i_wasBypassed);

#endif /* defined(__PlantsVersusZombies2__MapHelper__) */
