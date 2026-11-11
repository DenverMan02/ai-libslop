//
//  LocalSaveDataEnums.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 8/13/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LocalSaveDataEnums__
#define __PlantsVersusZombies2__LocalSaveDataEnums__

#include "Core.h"

enum LastPlayStatus
{
	PVZ_BEGIN_ENUM(LastPlayStatus_),
	LastPlayStatus_None,
	LastPlayStatus_Playing,
	LastPlayStatus_Victory,
	LastPlayStatus_Defeat,
	PVZ_END_ENUM(LastPlayStatus_),
};

#endif /* defined(__PlantsVersusZombies2__LocalSaveDataEnums__) */
