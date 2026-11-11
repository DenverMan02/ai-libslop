//
//  StartGameButton.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 3/6/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StartGameButton__
#define __PlantsVersusZombies2__StartGameButton__

#include "UIWidget.h"

class StartGameButton : public UIWidget, public ButtonListener
{
public:
	RT_CLASS_DEFINE(StartGameButton, UIWidget, RtClass) {}

	StartGameButton();
	~StartGameButton();

	virtual void Draw(Graphics* i_g) override;

	void SetLabel(const SexyString& i_label);

protected:
	
	virtual void initLoadingResourcesGroupList() override;

	OVERRIDE_STATE_ONENTER(WidgetState, Initializing);

private:
	bool handleTouch(const Sexy::Touch& i_touch);
	void startTouch(Sexy::TouchID i_touchIdent);
	void cancelTouch();

	class StretchableNewLawnButton* m_startGameButton;
	Sexy::TouchID m_touchIdent;
};

namespace Message
{
	void StartGameButtonPressed();
}

#endif /* defined(__PlantsVersusZombies2__StartGameButton__) */
