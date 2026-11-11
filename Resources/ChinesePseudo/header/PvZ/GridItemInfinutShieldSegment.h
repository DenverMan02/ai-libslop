//
//  GridItemInfinutShieldSegment.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/15/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemInfinutShieldSegment_h
#define PlantsVersusZombies2_GridItemInfinutShieldSegment_h

#include "GridItemLinkedPlantShield.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class GridItemInfinutShieldSegment : public GridItemLinkedPlantShield
{
public:
	RT_CLASS_DEFINE(GridItemInfinutShieldSegment, GridItemLinkedPlantShield, RtClass);

	void AddToRenderQueue(class RenderQueue* i_queue) override;
	void Heal() override;
	
protected:

	void drawBackgroundShieldSegment(Sexy::Graphics* i_graphics);
    virtual void onTakeDamage(const DamageInfo& i_damage) override;
	void onGridItemInitialize() override;

private:
	void updateDamageState();
	
	int m_currentDamageState = 0;
};

#endif
