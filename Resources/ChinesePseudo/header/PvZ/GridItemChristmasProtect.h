//
//  GridItemChristmasProtect.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-3.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemChristmasProtect__
#define __PlantsVersusZombies2__GridItemChristmasProtect__

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

class GridItemChristmasProtect : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemChristmasProtect, GridItemAnimation, RtClass);
	
	int CalcRenderOrder() const override;
    
    void TakeStealed();
    int  GetStealedNum() const;
	
protected:
	void registerForEvents() override;
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onPlaceOnBoard() override;
    void onDestroy() override;
    
    void onTakeDamage(const DamageInfo& i_damage) override;
    
private:
	
    int m_stealedNum = 0;
};

namespace Message
{
	void StealChristmasProtect();
    void ChristmasProtectDestroy();
}

#endif /* defined(__PlantsVersusZombies2__GridItemChristmasProtect__) */
