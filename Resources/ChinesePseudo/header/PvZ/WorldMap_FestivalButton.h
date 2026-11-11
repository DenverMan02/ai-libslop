/*
 * WorldMap_FestivalButton.h
 *
 *  Created on: 2021-3-31
 *      Author: zhousen
 */

#ifndef WORLDMAP_FESTIVALBUTTON_H_
#define WORLDMAP_FESTIVALBUTTON_H_


#include "UIEasyButtonWidget.h"
#include "GameDefine.h"

class WorldMap_FestivalButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_FestivalButton, UIEasyButtonWidget, RtClass);

    WorldMap_FestivalButton();
    virtual ~WorldMap_FestivalButton();

    virtual bool CheckActivated();
    virtual void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

protected:
    virtual void onWorldLoaded();
    virtual void onButtonClicked();
};


#endif /* WORLDMAP_FESTIVALBUTTON_H_ */
