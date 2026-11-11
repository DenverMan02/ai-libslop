//
//  WorldMap_ScrollBarSpeaker.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 14/1/17.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_ScrollBarSpeaker_h
#define PlantsVersusZombies2_WorldMap_ScrollBarSpeaker_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "SexyString.h"

class WorldMap_ScrollBarSpeaker : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_ScrollBarSpeaker, UIWidget, RtClass);

	WorldMap_ScrollBarSpeaker();
	virtual ~WorldMap_ScrollBarSpeaker();

	virtual void			Draw(Graphics* i_g) override;

	void Reset();
	void ScrollText(const SexyString& i_textToScroll, const Sexy::Color& i_color, int i_displayCount, float i_scrollSpeed, float i_durationToDelay);

protected:
	virtual void			initLoadingResourcesGroupList() override;
	virtual void			onUpdate() override;

private:
	void 					restartScrollingText();
	bool 					doesCurScrollEnd() const;

 	int 					m_displayInfoCount;
 	float					m_textX;
 	float 					m_scrollSpeed;
 	float					m_timeToDisplay;
 	SexyString 				m_textToScroll;
 	Sexy::Color				m_color;
 	bool 					m_startScrollingText;
 	int 					m_textLength;
};


#endif
