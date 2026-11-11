//
//  GridItemPlantTarget.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/6/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemPlantTarget_h
#define PlantsVersusZombies2_GridItemPlantTarget_h

#include "GridItemBoardEntityConditionTarget.h"

namespace Message
{
    void GridItemPlantConditionTargetKilled(GridItem* i_target);
}

class GridItemPlantConditionTarget : public GridItemBoardEntityConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemPlantConditionTarget, GridItemBoardEntityConditionTarget, RtClass);

	void SetConditionToRemoveOnDeath(PlantConditions i_condition) { m_conditionToRemoveOnDeath = i_condition; }
	
	void MoveOverTimeTo(const Sexy::Point& i_gridLocation, pvztime_t i_duration) override;
	
protected:
	virtual void onGridItemInitialize() override;
	virtual void onKilled() override;
	
	void updatePosition() override; 
	
private:
	PlantConditions m_conditionToRemoveOnDeath = PCONDITION_Invalid;
};

#endif
