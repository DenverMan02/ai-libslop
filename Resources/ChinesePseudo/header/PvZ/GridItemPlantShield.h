//
//  GridItemPlantShield.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemPlantShield_h
#define PlantsVersusZombies2_GridItemPlantShield_h

#include "GridItemBreakableTarget.h"
#include "RtDb.h"
#include "RtObject.h"

class GridItemPlantShield : public GridItemBreakableTarget
{
public:
	RT_CLASS_DEFINE(GridItemPlantShield, GridItemBreakableTarget, RtClass);

	void SetOwner(RtWeakPtr<GameObject>& i_newOwner) { m_owner = i_newOwner; }
	bool IsOwnedBy(RtWeakPtr<GameObject>& i_owner) { return m_owner == i_owner; }
	bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override { return true; }

	int CalcRenderOrder() const override { return CalcRenderOrderFromPosition(m_position); }
	
	void SetDamageFlash(float i_duration) override {}

protected:
	void onGridItemInitialize() override;
	void onDraw(class Sexy::Graphics* i_g) override;

	void drawShield(Sexy::Graphics* i_g, const SexyVector2& i_boardSpaceOffset);
	
	SexyVector2	getRenderOffset() override;

private:
	RtWeakPtr<GameObject> m_owner;
	
	SexyVector2 m_boardSpaceDrawOffset;
};

#endif
