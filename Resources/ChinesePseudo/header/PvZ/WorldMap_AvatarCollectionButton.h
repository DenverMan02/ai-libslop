/*
 * WorldMap_AvatarCollectionButton.h
 *
 *  Created on: Jun 3, 2014
 *      Author: lijie
 */

#ifndef WORLDMAP_AVATARCOLLECTIONBUTTON_H_
#define WORLDMAP_AVATARCOLLECTIONBUTTON_H_

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_AvatarCollectionButton : public UIWidget
{

public:
	RT_CLASS_DEFINE(WorldMap_AvatarCollectionButton, UIWidget, RtClass);

	WorldMap_AvatarCollectionButton();
	virtual ~WorldMap_AvatarCollectionButton();

	// Public Interface (Inheritable)

	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;

protected:

	// Protected Interface (Inheritable)

	virtual void			initLoadingResourcesGroupList() override;

private:

	// Private Interface (Core)

	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
};


#endif /* WORLDMAP_AVATARCOLLECTIONBUTTON_H_ */
