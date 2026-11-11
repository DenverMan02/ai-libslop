//
//  GridItemSnakeBlock.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-1-7.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemSnakeBlock__
#define __PlantsVersusZombies2__GridItemSnakeBlock__

#include "GridItem.h"

class GridItemSnakeBlock : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemSnakeBlock, GridItem, RtClass);
    
    Sexy::Rect calcCollisionRect() override;
    
	GridItemSnakeBlock() {}
	virtual ~GridItemSnakeBlock() {}
    
    void SetGridLocation(Sexy::Point i_gridLocation, const bool i_recalculatePosition = true) override;
	
protected:
    void onGridItemInitialize() override;
    void onDraw(Sexy::Graphics* i_g) override;
    
    void onAnimDone(StandaloneEffect* i_effect);
    
    int CalcRenderOrder() const override;
    
private:
    bool    m_bAppear = false;
};

#endif /* defined(__PlantsVersusZombies2__GridItemSnakeBlock__) */
