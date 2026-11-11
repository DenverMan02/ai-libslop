//
//  EffectObject_StretchedScrollingImage.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 6/9/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectObject_StretchedScrollingImage__
#define __PlantsVersusZombies2__EffectObject_StretchedScrollingImage__

#include "TimeLine.h"
#include "EffectObject.h"

namespace Sexy {
	class Graphics;
}

class EffectObject_StretchedScrollingImageProps : public EffectObjectPropertySheet
{
public:
	RT_CLASS_DEFINE(EffectObject_StretchedScrollingImageProps, EffectObjectPropertySheet, RtClass);
	
	EffectObject_StretchedScrollingImageProps()
	{
		ColorizeColor = Color::White;
		DurationInSecondsToScroll = 5.0f;
		DistanceToScroll = 0.0f;
		Scale = 1.0f;
	}
	
	Color		ColorizeColor;
	pvztime_t	DurationInSecondsToScroll;
	float		DistanceToScroll;
	float		Scale;
};

class EffectObject_StretchedScrollingImage : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_StretchedScrollingImage, EffectObject, RtClass);

protected:
	void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void onUpdate() override;
	
private:
	CurveCollection_Float m_movementCurves;
};

#endif /* defined(__PlantsVersusZombies2__EffectObject_StretchedScrollingImage__) */
