//
//  TutorialDemoBarUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 4/9/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TutorialDemoBarUI__
#define __PlantsVersusZombies2__TutorialDemoBarUI__

#include "UIWidget.h"

class TutorialDemoBarUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(TutorialDemoBarUI, UIWidget, RtClass);	

	enum KeyBankSlidingState
	{
		STATE_INVALID,
		STATE_IDLE,
		STATE_SLIDING_IN,
		STATE_SLIDING_OUT,
		STATE_WAITING,
	};
	
	TutorialDemoBarUI();
	
	void Draw(Graphics* i_g) override;
	void SlideIn();
	void SlideOut();
	void SetText(const SexyString& i_label);

protected:

	OVERRIDE_STATE_UPDATE(WidgetState, Ready)

	virtual void initLoadingResourcesGroupList() override;
	
private:
	
	pvztime_t m_slideTimeStart;
	pvztime_t m_slideTimeDuration;
	KeyBankSlidingState m_slidingState;
	KeyBankSlidingState m_queuedSlidingState;
	SexyString m_text;
	
};

#endif /* defined(__PlantsVersusZombies2__TutorialDemoBarUI__) */
