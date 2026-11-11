//
//  GridSquareLaser.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 10/16/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridSquareLaser__
#define __PlantsVersusZombies2__GridSquareLaser__

#include <stdio.h>

#include "GridSquareCoveringFlame.h"


class Effect_PopAnim;

class GridSquareLaser : public GridSquareCoveringFlame
{
public:
	RT_CLASS_DEFINE(GridSquareLaser, GridSquareCoveringFlame, RtClass);
	
	void StartLaserEffect(Point i_gridLocation, float i_burnTime, BoardEntity* i_owner);
	const char* getPamName() override;
	void doDamage();
	
protected:
	void onUpdate() override;
	
private:
	float getDPS() override { return 0.0; }
	
};

#endif /* defined(__PlantsVersusZombies2__GridSquareLaser__) */
