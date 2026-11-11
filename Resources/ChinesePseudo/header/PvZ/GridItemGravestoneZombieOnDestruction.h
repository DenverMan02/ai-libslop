//
//  GridItemGravestoneZombieOnDestruction.h
//  PlantsVersusZombies2
//
//  Created by Erik Rydeman on 29/08/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __GridItemGraveStoneZombieOnDestruction_H__
#define __GridItemGraveStoneZombieOnDestruction_H__

#include "GridItemGravestone.h"
#include "RtObject.h"

class GridItemGravestoneZombieOnDestruction : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemGravestoneZombieOnDestruction, GridItemGravestone, RtClass);

protected:
	virtual void onKilled() override;
};


#endif
