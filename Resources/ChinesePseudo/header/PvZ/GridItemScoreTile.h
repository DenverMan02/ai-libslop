//
//  GridItemScoreTile
//  PlantsVersusZombies2
//
//  Created by Emery, Jason on 7/13/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemScoreTile__
#define __PlantsVersusZombies2__GridItemScoreTile__

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

class GridItemScoreTile : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemScoreTile, GridItemAnimation, RtClass);
	
	float GetBonusModifier();
	void ShowBonusEffect();
	
protected:
	void onGridItemInitialize() override;

	int CalcRenderOrder() const override;
	
	bool BlocksGravestoneSpawning() override { return false; }
	
};


class GridItemScoreTileProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemScoreTileProps, GridItemAnimationProps, RtClass);
	
	GridItemScoreTileProps()
	{
		ScoreMultiplier = 2;
	}
	
	float ScoreMultiplier;
};

#endif /* defined(__PlantsVersusZombies2__GridItemScoreTile__) */
