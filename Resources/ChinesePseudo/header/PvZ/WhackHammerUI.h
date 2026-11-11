//
//  WhackHammerUI.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 1/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//
//  UI for the Whack-A-Zombie hammer tool.

#ifndef __WHACKUI_H__
#define __WHACKUI_H__

#include "RtObject.h"
#include "StateMachine.h"
#include "UIWidget.h"

namespace Sexy {
class Graphics;
struct Touch;
}  // namespace Sexy

class WhackHammerUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(WhackHammerUI, UIWidget, RtClass);
	
	WhackHammerUI();
	virtual ~WhackHammerUI();
	
	// Public Interface (Inheritable)
	
	virtual void	Draw(Graphics* i_g) override;

protected:
	
	// Protected Interface (Inheritable)

	void 			onGameplayEnded();
	virtual void	onUpdate() override;

	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	
private:	
	
	// Private Interface
	
	// Private Members (serialized)
	bool 					m_levelEnded;
	
	// Private Members (not serialized)
};

#endif
