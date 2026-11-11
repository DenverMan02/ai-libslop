//
//  GridItemCrater.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 6/24/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemCrater__
#define __PlantsVersusZombies2__GridItemCrater__

#include "RtDb.h"
#include "RtObject.h"
#include "GridItemAnimation.h"
#include "Timer.h"

class GridItemCrater : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemCrater, GridItemAnimation, RtClass);
	
protected:
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	void onGridItemInitialize() override;
};

class GridItemCraterTimed : public GridItemCrater
{
public:
	RT_CLASS_DEFINE(GridItemCraterTimed, GridItemCrater, RtClass);
	
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	
private:
	PvZ2::Utilities::Timer m_timer;
	
	void onTimeout();
};

class GridItemCraterProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemCraterProps, GridItemAnimationProps, RtClass);
	GridItemCraterProps(){}
};

class GridItemCraterTimedProps : public GridItemCraterProps
{
public:
	RT_CLASS_DEFINE(GridItemCraterTimedProps, GridItemCraterProps, RtClass);
	
	float Lifetime;
};

#endif /* defined(__PlantsVersusZombies2__GridItemCrater__) */
