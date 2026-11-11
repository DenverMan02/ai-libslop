/*
 * WorldMap_VivoGameCenterButton.h
 *
 *  Created on: 2020-8-24
 *      Author: Administrator
 */

#ifndef WORLDMAP_VIVOGAMECENTERBUTTON_H_
#define WORLDMAP_VIVOGAMECENTERBUTTON_H_

#include "core.h"
#include "RtObject.h"
#include "UIEasyButtonWidget.h"
#include "NetworkData.h"

class NetworkVivoGachaList : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkVivoGachaList, INetworkData, RtClass);

public:
	std::vector<GiftItem> GachaList;
	int LeftDraw;
};

class WorldMap_VivoGameCenterButton : public UIEasyButtonWidget
{

public:
	RT_CLASS_DEFINE(WorldMap_VivoGameCenterButton, UIWidget, RtClass);

	WorldMap_VivoGameCenterButton();
	virtual ~WorldMap_VivoGameCenterButton();

	void CheckActivated();

private:
	void onWorldLoaded();
	void onCheckGameCenterFinished(bool i_success);
	void onGetGameCenterUrlFinished(const std::string& i_url);
	void onButtonClicked();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void initGachaUI(const std::vector<GiftItem>& i_list, int i_drawTime);

	bool m_hasLogin;
	std::string m_url;
};


#endif /* WORLDMAP_VIVOGAMECENTERBUTTON_H_ */
