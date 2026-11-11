//
//  WorldMap_Minimap.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 12/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_Minimap_h
#define PlantsVersusZombies2_WorldMap_Minimap_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_Minimap : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_Minimap, UIWidget, RtClass) {}

	WorldMap_Minimap();

	virtual void Draw(Graphics* i_g) override;
	virtual void OnMouseUp(const int i_mouseX, const int i_mouseY) override;

private:
	Rect getMinimapRect();
	void calcTransforms();

	bool m_transformsNeedUpdate;
	SimpleMatrix m_worldToMinimap;
};

#endif
