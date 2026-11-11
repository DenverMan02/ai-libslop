//
//  WorldMap_TWLoginRewardButton.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16-09-08.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef WORLDMAP_TWLOGINREWARDBUTTON_H_
#define WORLDMAP_TWLOGINREWARDBUTTON_H_

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class WorldMap_TWLoginRewardButton : public UIWidget
{

public:
	RT_CLASS_DEFINE(WorldMap_TWLoginRewardButton, UIWidget, RtClass);

	WorldMap_TWLoginRewardButton();
	virtual ~WorldMap_TWLoginRewardButton();

	// Public Interface (Inheritable)
    void                    OnWorldMapWorldLoaded();
    void                    OnUniverseMapOpened();

	virtual void		Draw(Graphics* i_g) override;
	virtual void		OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void		OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void		OnMouseMove(const int i_mouseX, const int i_mouseY) override;

    static void ShowSignUI();
protected:

	OVERRIDE_STATE_ONENTER(WidgetState, Initializing)

	// Protected Interface (Inheritable)

	virtual void		initLoadingResourcesGroupList() override;

	virtual void		onUpdate() override;

private:
	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

    bool ShowTheNotice();
};


#endif /* WORLDMAP_LOGINREWARDBUTTON_H_ */
