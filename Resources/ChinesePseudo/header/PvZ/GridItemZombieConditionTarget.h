//
//  GridItemPlantTarget.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/6/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemZombieTarget_h
#define PlantsVersusZombies2_GridItemZombieTarget_h

#include <string>

#include "GridItemPlantConditionTarget.h"
#include "GridItemAnimation.h"
#include "RtDb.h"
#include "RtObject.h"
#include "TimeMgr.h"

namespace Sexy {
class Graphics;
class SexyVector2;
}  // namespace Sexy

class GridItemZombieConditionTarget : public GridItemBoardEntityConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemZombieConditionTarget, GridItemBoardEntityConditionTarget, RtClass);
	
	void SetConditionToRemoveOnDeath(ZombieConditions i_condition) { m_conditionToRemoveOnDeath = i_condition; }
	
	void MoveOverTimeTo(const Sexy::Point& i_gridLocation, pvztime_t i_duration) override;
	
protected:
	void onDestroy() override;
	void onGridItemInitialize() override;
	void onKilled() override;
	void updatePosition() override;
	void onUpdate() override;
	
	bool ShouldClipWithWater() const override;

private:
	void updateGroundEffect();

	ZombieConditions m_conditionToRemoveOnDeath = ZCONDITION_Invalid;
	EntityComponent_GroundEffect	m_groundEffect;
};

#endif
