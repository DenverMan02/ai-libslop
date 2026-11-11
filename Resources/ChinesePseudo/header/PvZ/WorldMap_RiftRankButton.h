/*
 * WorldMap_RiftRankButton.h
 *
 *  Created on: 2020-5-28
 *      Author: Administrator
 */

#ifndef WORLDMAP_RIFTRANKBUTTON_H_
#define WORLDMAP_RIFTRANKBUTTON_H_

#include "UIWidgetSheet.h"
#include "UIButtonWidget.h"

class WorldMap_RiftRankButton : public UIButtonWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_RiftRankButton, UIButtonWidget, RtClass);

	WorldMap_RiftRankButton();
	virtual ~WorldMap_RiftRankButton();
	void Draw(Graphics* i_g) override;

	void GetLegendReward(int i_index);

protected:
	void performButtonAction() override;
	void initLoadingResourcesGroupList() override;

private:
	void onRiftNetworkResponse(int i_context, int i_status);
	void onSuccessResponse();
	void CheckMark();

	bool m_showMark;
	bool m_thisRequest;
	std::vector<int> m_exceptIndex;
};


#endif /* WORLDMAP_RIFTRANKBUTTON_H_ */
