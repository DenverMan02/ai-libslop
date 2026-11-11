//
//  WorldMap_WorldKeyBank.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/7/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_WorldKeyBank__
#define __PlantsVersusZombies2__WorldMap_WorldKeyBank__

#include "RtObject.h"
#include "UIWidget.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class WorldMap_WorldKeyBank : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_WorldKeyBank, UIWidget, RtClass);
	
	virtual void			Draw(Graphics* i_g) override;
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_WorldKeyBank__) */
