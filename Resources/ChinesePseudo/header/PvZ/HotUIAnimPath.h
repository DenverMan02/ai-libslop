//
//  HotUIAnimPath.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 8/6/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIAnimPath__
#define __PlantsVersusZombies2__HotUIAnimPath__

#include "HotUIAnim.h"

class HotUIAnimPath : public HotUIAnim
{
public:
	RT_CLASS_DEFINE(HotUIAnimPath, HotUIAnim, RtClass);
	
	void SetStartAndEndPointsAndOffsets(HotUIWidget* i_startPoint, HotUIWidget* i_endPoint, Sexy::Point& i_startOffset, Sexy::Point& i_endOffset);
	
protected:
	void	onLayoutFinalized() override;
		
private:
	HotUIWidgetPtr m_startWidget;
	HotUIWidgetPtr m_endWidget;
	
	Sexy::Point m_startOffset;
	Sexy::Point m_endOffset;
};

class HotUIAnimPathProperties : public HotUIAnimProperties
{
public:
	RT_CLASS_DEFINE(HotUIAnimPathProperties, HotUIAnimProperties, RtClass);
	
	RtClass* GetWidgetClass() const override
	{
		return HotUIAnimPath::StaticGetClass();
	}
};
#endif /* defined(__PlantsVersusZombies2__HotUIAnimPath__) */
