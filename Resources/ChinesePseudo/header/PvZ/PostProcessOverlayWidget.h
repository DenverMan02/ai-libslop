//
//  PostProcessOverlayWidget.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PostProcessOverlayWidget_h
#define PlantsVersusZombies2_PostProcessOverlayWidget_h

#include "core.h"
#include "SexyAppFramework/Widget.h"

enum PostProcessType
{
	PVZ_BEGIN_ENUM(POSTPROCESS_),
	POSTPROCESS_NONE,
	POSTPROCESS_FLASHBACK_INTRO,
	POSTPROCESS_FLASHBACK_OUTRO,
	POSTPROCESS_GRAYSCALE,
	PVZ_END_ENUM(POSTPROCESS_)
};

struct PostProcessItem
{
	PostProcessType		TypeToUse;
	pvztime_t			StartTime;
	pvztime_t			Duration;
	Color				StartColor;
	Color				EndColor;
};

class PostProcessOverlayWidget : public Widget
{
public:
	PostProcessOverlayWidget();
	~PostProcessOverlayWidget();
	
	// Public access
	void							ClearAll();
	void							AddFlashbackIntro(pvztime_t i_duration, Color i_startColor, Color i_endColor);
	void							AddFlashbackOutro(pvztime_t i_duration, Color i_startColor, Color i_endColor);
	
	// Inherited interface
	virtual void					Draw(Graphics* i_g);
	virtual void					Update();

private:
	
	void							startPostProcessing();
	void							endPostProcessing();
	
	std::vector<PostProcessItem>	m_postProcessItems;
	DeviceImage*					m_srcScreenImage;
};


#endif
