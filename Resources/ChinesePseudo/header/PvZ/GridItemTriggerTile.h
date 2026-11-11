//
//  GridItemTriggerTile.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/20/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemTriggerTile__
#define __PlantsVersusZombies2__GridItemTriggerTile__

#include "GridItemAnimation.h"

class GridItemTriggerTileProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemTriggerTileProps, GridItemAnimationProps, RtClass);
	
	GridItemTriggerTileProps()
	: JSONTriggeringEntityTypes { ENTITYTYPE_None }
    , TimeBetweenTriggersInSeconds(0)
	{
	}
	
	std::vector<BoardEntityTypeFlag>	JSONTriggeringEntityTypes;
	Rect								TriggerRect;
	pvztime_t							TimeBetweenTriggersInSeconds;
};

class GridItemTriggerTile : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemTriggerTile, GridItemAnimation, RtClass);
	
	virtual bool CanTriggerTile();
	virtual void ManuallyTriggerTile();
	
#ifndef WANTS_CHEATS_DISABLED
	void DrawCollisionInfo(Graphics* i_g) override;
#endif
	
protected:
	virtual std::vector<BoardEntity*> findTargets() const;
	virtual Sexy::Rect calculateTriggerRect() const;
	virtual void handleTargetCollisions(const std::vector<BoardEntity*>& i_entities) {}
	
	BoardEntityTypeFlag getTriggeringEntityTypes() const;
	bool isThereValidTriggeringEntity(const std::vector<BoardEntity*>& i_entities) const;
	bool isTimeForNextTrigger() const;
	void resetTriggerTime();
	
	void onGridItemInitialize() override;
	void onUpdate() override;
	
private:
	pvztime_t m_nextTriggerTime = PVZ_EOT();
};

#endif /* defined(__PlantsVersusZombies2__GridItemTriggerTile__) */
