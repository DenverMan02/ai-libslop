//
//  ProjectileEnums.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/24/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PROJECTILEENUMS_H__
#define __PROJECTILEENUMS_H__

#include "Precompile.h"
#include "Core.h"

enum ProjectilePropertyFlag
{
	PVZ_BEGIN_FLAG_ENUM(PROJECTILE_FLAG_),
	PVZ_FLAG(PROJECTILE_FLAG_PAUSED),	// If this flag is set, this projectile will not move and will
										// not check for collisions. Animations will still update.
    PVZ_FLAG(PROJECTILE_FLAG_HIDDEN),	// Do not draw this projectile (or its shadow)
	PVZ_FLAG(PROJECTILE_FLAG_HIDESHADOW),
    PVZ_FLAG(PROJECTILE_FLAG_FORCEIMPACTSOUND),
	PVZ_FLAG(PROJECTILE_FLAG_FOLLOWSGROUND),	// Snaps to the ground Z position (tide)
	PVZ_END_FLAG_ENUM(PROJECTILE_FLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ProjectilePropertyFlag);

#endif // __PROJECTILEENUMS_H__
