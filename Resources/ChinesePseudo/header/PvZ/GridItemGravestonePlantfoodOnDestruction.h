//
//  GridItemGravestonePlantfoodOnDestruction.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 9/10/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __GRIDITEMGRAVESTONEPLANTFOODONDESTRUCTION_H__
#define __GRIDITEMGRAVESTONEPLANTFOODONDESTRUCTION_H__

#include "GridItemGravestone.h"
#include "RtObject.h"

class GridItemGravestonePlantfoodOnDestruction : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemGravestonePlantfoodOnDestruction, GridItemGravestone, RtClass);

protected:
	virtual void onKilled() override;
};


#endif
