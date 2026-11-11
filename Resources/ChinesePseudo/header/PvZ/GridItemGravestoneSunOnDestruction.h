//
//  GridItemGravestoneSunOnDestruction.h
//  PlantsVersusZombies2
//
//  Created by Erik Rydeman on 29/08/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __GridItemGraveStoneSunOnDestruction_H__
#define __GridItemGraveStoneSunOnDestruction_H__

#include "GridItemGravestone.h"
#include "RtObject.h"

class GridItemGravestoneSunOnDestructionPropertySheet : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemGravestoneSunOnDestructionPropertySheet, GridItemGravestonePropertySheet, RtClass);
	
	GridItemGravestoneSunOnDestructionPropertySheet()
	{
		AmountToSpawn = 0;
	}
	
	int32 AmountToSpawn;
};

class GridItemGravestoneSunOnDestruction : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemGravestoneSunOnDestruction, GridItemGravestone, RtClass);

protected:
	virtual void onKilled() override;
};


class GridItemGravestoneCoinOnDestructionPropertySheet : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemGravestoneCoinOnDestructionPropertySheet, GridItemGravestonePropertySheet, RtClass);
	
	GridItemGravestoneCoinOnDestructionPropertySheet()
	{
		AmountToSpawn = 0;
	}
	
	int32 AmountToSpawn;
};

class GridItemGravestoneCoinOnDestruction : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemGravestoneCoinOnDestruction, GridItemGravestone, RtClass);

	void		GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
	virtual void onKilled() override;
};

namespace Message
{
	void OnGridItemGravestoneCoinOnDestructionKilled(class GridItemGravestoneCoinOnDestruction* i_coinStone);
}


#endif
