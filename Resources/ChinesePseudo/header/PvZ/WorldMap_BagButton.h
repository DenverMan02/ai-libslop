/*
 * WorldMap_BagButton.h
 *
 *  Created on: 2021-2-22
 *      Author: zhousen
 */

#ifndef WORLDMAP_BAGBUTTON_H_
#define WORLDMAP_BAGBUTTON_H_

#include "UIEasyButtonWidget.h"

class WorldMap_BagButton : public UIEasyButtonWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_BagButton, UIEasyButtonWidget, RtClass);

	WorldMap_BagButton();
	virtual ~WorldMap_BagButton();
	
protected:
    virtual void onLoadComplete() override;

private:
};

#endif /* WORLDMAP_BAGBUTTON_H_ */
