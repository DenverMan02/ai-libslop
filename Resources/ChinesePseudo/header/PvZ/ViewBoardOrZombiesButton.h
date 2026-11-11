//
//  ViewBoardOrZombiesButton.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 3/5/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ViewBoardOrZombiesButton__
#define __PlantsVersusZombies2__ViewBoardOrZombiesButton__

#include "UIWidget.h"
#include "PopAnimRig.h"

class ViewBoardOrZombiesButton : public UIWidget
{
public:
	RT_CLASS_DEFINE(ViewBoardOrZombiesButton, UIWidget, RtClass);

	ViewBoardOrZombiesButton();
	~ViewBoardOrZombiesButton();

	virtual void	Draw(Graphics* i_g) override;

protected:

	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	OVERRIDE_STATE_UPDATE(WidgetState, Pressed);
	
	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;
	

private:
	bool			handleTouch(const Sexy::Touch& i_touch);
	void			cancelTouch();

	void			onEyeMoveAnimFinished(const std::string& i_animLabel);
	
	// Private Members (serialized)
	PopAnimRigPtr	m_animRig;
	pvztime_t		m_timeTillNextEyeMotion;
	uint8			m_eyeIdleIndex;
	bool			m_screenIsScrolled;
	
	// Private Members (not serialized)
	Sexy::TouchID	m_touchIdent;
};

namespace Message
{
	void ViewBoardOrZombiesButtonPressed();
}

#endif /* defined(__PlantsVersusZombies2__ViewBoardOrZombiesButton__) */
