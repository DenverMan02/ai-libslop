//
//  PauseButton.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/17/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PAUSEBUTTON_H__
#define __PAUSEBUTTON_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"

class PauseButton : public UIWidget
{
public:
	RT_CLASS_DEFINE(PauseButton, UIWidget, RtClass);
	
	PauseButton();
	virtual ~PauseButton();
	
	// Public Interface (Inheritable)
	
	virtual void	Draw(Graphics* i_g) override;
	virtual void	OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	//PVZ2_CHINESE_START
    virtual const Sexy::Rect GetHitRect() override;
	//PVZ2_CHINESE_END

protected:
	
	// Protected Interface (Inheritable)

	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;
	
	// Protected Interface (Core)

	void			onGamePaused();
	void			onGameUnpaused();
	void 			onGameplayEnded();
	
private:	
	
	// Private Members (not serialized)
	bool			m_gameIsPaused;
};

namespace Message
{
	void PauseButtonPressed();
}

#endif //__PAUSEBUTTON_H__
