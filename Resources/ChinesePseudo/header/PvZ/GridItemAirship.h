//
//  GridItemAirship.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-6-15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemAirship__
#define __PlantsVersusZombies2__GridItemAirship__

#include "GridItem.h"

class GridItemAirship : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemAirship, GridItem, RtClass);
    
    Sexy::Rect calcCollisionRect() override;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    
    void TakeDamage(const DamageInfo& i_damage) override;
    
	GridItemAirship()            {}
	virtual ~GridItemAirship()   {}
	
protected:
    void onGridItemInitialize()         override;
    void onDraw(Sexy::Graphics* i_g)    override;
    
private:
    
};

#endif /* defined(__PlantsVersusZombies2__GridItemAirship__) */
