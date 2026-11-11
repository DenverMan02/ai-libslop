/*
 * WorldMap_LoginRewardButton.h
 *
 *  Created on: 2013-10-28
 *      Author: zhaobk
 */

#ifndef WORLDMAP_LOGINREWARDBUTTON_H_
#define WORLDMAP_LOGINREWARDBUTTON_H_

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_LoginRewardButton : public UIWidget
{

public:
	RT_CLASS_DEFINE(WorldMap_LoginRewardButton, UIWidget, RtClass);

	WorldMap_LoginRewardButton();
	virtual ~WorldMap_LoginRewardButton();

	// Public Interface (Inheritable)

	virtual void		Draw(Graphics* i_g) override;
	virtual void		OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void		OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void		OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    static bool SignToday();
    static void ShowSignUI();
protected:

	OVERRIDE_STATE_ONENTER(WidgetState, Initializing)

	// Protected Interface (Inheritable)

	virtual void		initLoadingResourcesGroupList() override;

	virtual void		onUpdate() override;

	void onDailyRewardError();

private:

	// Private Interface (Core)

	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

	// Private Members (serialized)

	// Private Members (not serialized)

	static bool s_SyncFinish;
};


#endif /* WORLDMAP_LOGINREWARDBUTTON_H_ */
