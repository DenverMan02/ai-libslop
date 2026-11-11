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

class GridItemCoal : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemCoal, GridItemAnimation, RtClass);
	
protected:
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	void onGridItemInitialize() override;

	void onUpdate() override;

	void onDisappeared(const std::string& animName);

private:
	float m_disappearTime;
};

class GridItemCoalProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemCoalProps, GridItemAnimationProps, RtClass);
	GridItemCoalProps(){}
	float DisappearTime;
};

#endif /* defined(__PlantsVersusZombies2__GridItemCrater__) */
