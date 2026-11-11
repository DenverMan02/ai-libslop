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

class GridItemCoalCart: public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemCoalCart, GridItemAnimation, RtClass);

protected:
	void onKilled() override;
};

class GridItemCoalCartProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemCoalCartProps, GridItemAnimationProps, RtClass);
	GridItemCoalCartProps(){}

	std::string BreakEffect;
	SexyVector2 BreakEffectOffset;
	std::string BreakSound;
};

class GridItemAnimRig_CoalCart: public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemAnimRig_CoalCart, PlantAnimRig, RtClass);

	void SetCoalCartDamageLayer(bool damaged);
	void PlayCrashAnim(AnimStoppedDelegate i_onAnimStopped);
};

#endif /* defined(__PlantsVersusZombies2__GridItemCrater__) */
