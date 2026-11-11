/*
 * WorldMap_RiftStoreButton.h
 *
 *  Created on: 2020-5-28
 *      Author: Administrator
 */

#ifndef WORLDMAP_RIFTSTOREBUTTON_H_
#define WORLDMAP_RIFTSTOREBUTTON_H_

#include "UIWidgetSheet.h"
#include "UIButtonWidget.h"

class WorldMap_RiftStoreButton : public UIButtonWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_RiftStoreButton, UIButtonWidget, RtClass);

	WorldMap_RiftStoreButton();

protected:
	void performButtonAction() override;
	void initLoadingResourcesGroupList() override;
};


#endif /* WORLDMAP_RIFTSTOREBUTTON_H_ */
