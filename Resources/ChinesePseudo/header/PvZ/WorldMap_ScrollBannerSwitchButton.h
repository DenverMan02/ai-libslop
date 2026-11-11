/*
 * WorldMap_ScrollBannerSwitchButton.h
 *
 *  Created on: 2021-6-17
 *      Author: zhousen
 */

#ifndef WORLDMAP_SCROLLBANNERSWITCHBUTTON_H_
#define WORLDMAP_SCROLLBANNERSWITCHBUTTON_H_

#include "UIEasyButtonWidget.h"

namespace Message
{
	void ShowScrollBannerSwitch();
}

//
// WorldMap_ScrollBannerSwitchButton
//
class WorldMap_ScrollBannerSwitchButton : public UIEasyButtonWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_ScrollBannerSwitchButton, UIEasyButtonWidget, RtClass);

	WorldMap_ScrollBannerSwitchButton();
	virtual ~WorldMap_ScrollBannerSwitchButton();

    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    bool checkVisiable();

protected:
	void UpdateSwitchButton(bool show);
	void ShowScrollBannerSwitch();
	void onLoadComplete() override;

private:
	bool _isShowing;// show scroll banner
};


#endif /* WORLDMAP_SCROLLBANNERSWITCHBUTTON_H_ */
