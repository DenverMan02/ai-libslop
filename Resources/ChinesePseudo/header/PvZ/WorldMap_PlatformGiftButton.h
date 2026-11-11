/*
 * WorldMap_PlatformGiftButton.h
 *
 *  Created on: 2019-3-29
 *      Author: zhousen
 */

#ifndef WORLDMAP_PLATFORMGIFTBUTTON_H_
#define WORLDMAP_PLATFORMGIFTBUTTON_H_

class WorldMap_PlatformGiftButton : public UIWidget
{
public:
// this should be relfection, to put the button into worldmap
	RT_CLASS_DEFINE(WorldMap_PlatformGiftButton, UIWidget, RtClass);
	
	WorldMap_PlatformGiftButton();
	virtual ~WorldMap_PlatformGiftButton();

	virtual void Draw(Graphics* g) override;
	virtual void OnMouseUp(const int x, const int y) override;
	virtual void OnMouseDown(const int x, const int y) override;

	static void SetButtonEnable(bool enable);

	void OnNotifyRefresh(bool i_success, const std::set<int>& changeList);

private:
	static bool _canGetGift;// if will show this button
	std::vector<GiftItem> _itemList;// bonus list
	int _leftDays;// the activity will last how many days
};


#endif /* WORLDMAP_PLATFORMGIFTBUTTON_H_ */
