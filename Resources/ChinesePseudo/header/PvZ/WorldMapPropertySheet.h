//
//  WorldMapPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMapPropertySheet__
#define __PlantsVersusZombies2__WorldMapPropertySheet__

#include "PropertySheetBase.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"

class WorldMapPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(WorldMapPropertySheet, PropertySheetBase, RtClass);

	WorldMapPropertySheet()
	{
		// Not editable
		ParallaxSpeedLayer0 = 1.0f;
		
		// Editable
		ParallaxSpeedLayerForeground4 = 1.4f;
		ParallaxSpeedLayerForeground3 = 1.3f;
		ParallaxSpeedLayerForeground2 = 1.2f;
		ParallaxSpeedLayerForeground1 = 1.1f;
		ParallaxSpeedLayer1 = 0.9f;
		ParallaxSpeedLayer2 = 0.8f;
		ParallaxSpeedLayer3 = 0.7f;
		ParallaxSpeedLayer4 = 0.6f;
		ParallaxSpeedLayer5 = 0.5f;
		ParallaxSpeedLayer6 = 0.4f;
		ParallaxSpeedLayer7 = 0.3f;
		ParallaxSpeedLayer8 = 0.2f;
		ParallaxSpeedLayer9 = 0.1f;
		ParallaxSpeedLayer10 = 0.0f;
		PathUnlockSpeed = 400.0f;
		SnapGrid = SexyVector2(62.35f, 32.9f);
		
		// World map uses 600 height in world pixels
		// iphone is centered, assumed 500 height in world pixels, taken from 600 * (640/768) = 500
		// ---------
		// 74 padding from hud
		// 50 cropped pixels from iphone	(74 + 50 = 124)
		// content (centered on screen)
		// 50 cropped pixels from iphone	(600 - (90 + 50) = 600 - 140 = 460)
		// 90 padding from hud
		// ---------

		EditorSafeZoneYStart = 124;
		EditorSafeZoneYEnd = 460;
	}
	
	float 			ParallaxSpeedLayerForeground4;
	float 			ParallaxSpeedLayerForeground3;
	float			ParallaxSpeedLayerForeground2;
	float 			ParallaxSpeedLayerForeground1;
	float			ParallaxSpeedLayer0;
	float			ParallaxSpeedLayer1;
	float			ParallaxSpeedLayer2;
	float			ParallaxSpeedLayer3;
	float			ParallaxSpeedLayer4;
	float			ParallaxSpeedLayer5;
	float			ParallaxSpeedLayer6;
	float			ParallaxSpeedLayer7;
	float			ParallaxSpeedLayer8;
	float			ParallaxSpeedLayer9;
	float			ParallaxSpeedLayer10;

	float			PathUnlockSpeed;
	SexyVector2		SnapGrid;
	float			EditorSafeZoneYStart;
	float			EditorSafeZoneYEnd;
	
};

#endif /* defined(__PlantsVersusZombies2__WorldMapPropertySheet__) */
