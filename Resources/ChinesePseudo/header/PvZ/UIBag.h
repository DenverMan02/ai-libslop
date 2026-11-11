/*
 * UIBag.h
 *
 *  Created on: 2021-1-28
 *      Author: zhousen
 */

#ifndef UIBAG_H_
#define UIBAG_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "ActiveSummery.h"
#include "UIWidgetAnim.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "EASquared.h"
#include "UIUtil.h"
#include "UIRewardFrame.h"
#include "UIBagItemBox.h"

/// button id
enum {
	UI_BAG_BUTTON_CLOSE = 1000,
};

///
/// enum bag item type
///
enum BAG_ITEM_TYPE
{
	BAG_ITEM_INVALID = -1,
	BAG_ITEM_PLANT,
	BAG_ITEM_AVATAR,
	BAG_ITEM_ACCESSORY,
	BAG_ITEM_MATERIAL,
	BAG_ITEM_MAX,
};

///
/// base item button
///
class BagItemButtonBase : public UIRewardFrame, public ButtonListener
{
public:
	BagItemButtonBase(int itemID, RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);

	virtual void ButtonDepress(int i_id) override;
	
	static BagItemButtonBase* CreateBagItem(int objectId, int num, bool hasFrame);// bag item factory fucntion
	
	void CreateButton();

protected:
	virtual void ButtonCallback(class UIBagItemBox* pBox, int buttonID);

protected:
	int _itemID;// item id
	int _count;// item count
    class PVZ2UIButton* _obtainBtn;
};

///
/// plant piece button
///
 class PlantPieceButton : public BagItemButtonBase
 {
 public:
	 PlantPieceButton(int itemID, RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual void ButtonDepress(int i_id) override;
	
protected:
	void ButtonCallback(class UIBagItemBox* pBox, int buttonID) override;
 };

 ///
 /// avatar piece button
 ///
 class AvatarPieceButton : public BagItemButtonBase
 {
 public:
	 AvatarPieceButton(int itemID, RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual void ButtonDepress(int i_id) override;
	
protected:
	void ButtonCallback(class UIBagItemBox* pBox, int buttonID) override;
};

 ///
 /// accessory piece button
 ///
class AccessoryPieceButton : public BagItemButtonBase
{
public:
	AccessoryPieceButton(int itemID, RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual void ButtonDepress(int i_id) override;

protected:
	void ButtonCallback(class UIBagItemBox* pBox, int buttonID) override;
};

///
/// material item button
///
class MaterialItemButton : public BagItemButtonBase
{
public:
	MaterialItemButton(int itemID, RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual void ButtonDepress(int i_id) override;

protected:
	void ButtonCallback(class UIBagItemBox* pBox, int buttonID) override;
    void ShowActivityNotOpen();
	void GoToMaterialUI(int activityID);
private:
	void OnExchangeGeneralPlantChips(int i_material, int i_number);
	void ExchangeMaterial(int i_material, int i_number);
};

///
/// trial card item button
///
class TrialCardItemButton : public BagItemButtonBase
{
public:
	TrialCardItemButton(int itemID, RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual void ButtonDepress(int i_id) override;

protected:
	void ButtonCallback(class UIBagItemBox* pBox, int buttonID) override;
	void Exchange(class UIMessageBox* pBox, int buttonID);
};


///
/// bag item data
///
struct BagItemData
{
	int itemID = 0;
	int itemCount = 0;

	BagItemData(int id, int count) {
		itemID = id;
		itemCount = count;
	}
};

///
/// ui bag
///
class UIBag : public UISingletonDialog<UIBag>, public Sexy::ScrollWidgetListener, public UI::TabControlListener
{
public:
	enum{
		TAB_PLANT = 1,
		TAB_AVATAR,
		TAB_ACCESSORY,
		TAB_MATERIAL,
	};

	UIBag();
	virtual ~UIBag();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIBag"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
    virtual void TabSelectionChanged(int tabID) override;
	
	static int FindMaterialActivity(int item);

	void RefreshTab(BAG_ITEM_TYPE type);

protected:
	void InitView();
	void CreateBagItems(BAG_ITEM_TYPE type, Sexy::Widget* parent);// create piece list under parent widget
	int CalcItemCatagoryCount(BAG_ITEM_TYPE type);
	std::vector<BagItemData> GetItemIDs(BAG_ITEM_TYPE type);
	void AttachItem(BAG_ITEM_TYPE type, BagItemButtonBase* item);
	void SortItemIDsForRare(BAG_ITEM_TYPE type, std::vector<BagItemData>& itemList);
	static void InitMaterialActivityMap();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onStartMission(const std::string& wldName,const std::string& missionName,int istars);

protected:
	std::vector<BagItemButtonBase*> _plantPieceList;
	std::vector<BagItemButtonBase*> _avatarPieceList;
	std::vector<BagItemButtonBase*> _accessoryPieceList;
	std::vector<BagItemButtonBase*> _materialItemList;

	static std::map<int, int> _materialActivityMap;// key = material id, value = activity id

	bool _initItemsFlag[4];// the flag of init items, index = 0-plant 1-avatar 2-accessory 3-material
};


#endif /* UIBAG_H_ */
