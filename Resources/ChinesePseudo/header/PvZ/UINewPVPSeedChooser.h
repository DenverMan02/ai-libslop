/*
 * 	UINewPVPSeedChooser.h
 */

#ifndef __UINEWPVP_SEEDCHOOSER_H__
#define __UINEWPVP_SEEDCHOOSER_H__


#include "MagentoService.h"
#include "PlantType.h"
#include "PVZTypes.h"
#include "PVZ2UIButton.h"
#include "UIEditor/UISingletonDialog.h"
#include "UIRewardFrame.h"
#include "NewPVPDataPackets.h"

namespace Message
{
	void NotifyChooserItemClicked(class UINewPVPSeedChooserItem* i_item);
};

enum UINewPVPSeedChooserID
{
	Button_BackMenu = 100,
	Button_StartMatching = 101,
	Button_DisableMap = 102,
	Button_SelectionReset = 103,
	Button_ChoosePlant = 104,
};


enum NewPVPSeedChooserItemState
{
	IS_InChooser,
	IS_Moving,
	IS_InBank,
	IS_Blacklisted,
	IS_Purchasable,
	IS_Empty,
    Is_NotEnough,
    IS_Selected,
};

enum ItemButtonState
{
	ItemButtonState_Invalid,
	ItemButtonState_Ready,
	ItemButtonState_Selected,
	ItemButtonState_Blacklisted,
};

class UINewPVPSeedChooserItem : public PVZ2UIButton, public ButtonListener
{
public:

	UINewPVPSeedChooserItem(int i_id);
	virtual ~UINewPVPSeedChooserItem();

	// ButtonListener
    void ButtonPress(int i_id) override;
	virtual void ButtonDepress(int i_id) override;

	void Draw(Graphics* g) override;
	void SetState(ItemButtonState i_state);
	void SetCost(int i_cost) { m_cost = i_cost; }
	void SetHasSelected(bool i_flg) { m_hasBeenSelected = i_flg; }
	void SetChooser(class UINewPVPSeedChooser* i_chooser) { m_chooser = i_chooser; }
	void SetPressed(bool i_flg) { m_isPressed = i_flg; }

	ItemButtonState GetState() { return m_state; }
	int GetID() { return mId; }

	ItemButtonState 			m_state = ItemButtonState_Invalid;
	int							m_cost = 0;

	PlantTypePtr	m_plantType;
	bool			m_hasBeenSelected = false;
	bool 			m_isPressed = false;

	class UINewPVPSeedChooser* m_chooser = nullptr;
};


struct ChooserItemData
{
	SexyVector2			Position;
	pvztime_t			MovingStartTime;
	pvztime_t			MovingEndTime;
	SexyVector2			MovePositionStart;
	SexyVector2			MovePositionEnd;
	int					ItemID = -1;
	int					ItemIndexInBank = -1;
	UINewPVPSeedChooserItem*			AttachedItem = nullptr;
	NewPVPSeedChooserItemState			ItemState = IS_InChooser;
	bool								IsImitaterPacket;
	MagentoProductPropsPtr ProductProps;
};

//typedef std::vector<ChooserItemData>	ChooserPacketVector;
typedef std::vector<PlantTypePtr>		PlantTypeVector;



class UINewPVPSeedChooserMapItem : public Sexy::Widget, public ButtonListener
{
public:
	UINewPVPSeedChooserMapItem() {}
	~UINewPVPSeedChooserMapItem() {}

	void Draw(Graphics* i_g) override;
	void ButtonDepress(int i_id) override;

	void init(std::string i_worldName, std::function<void(std::string, bool)> i_setStateFunc, bool i_isDisabled = false);
	void resetButtonState();

private:
	std::string 							m_worldName = "";
	bool									m_isDisabled = false;
	std::function<void(std::string, bool)> 	m_setStateFunc = nullptr;

	PVZ2UIButton* 							m_button = nullptr;
};

class UINewPVPSeedChooser : public UISingletonDialog<UINewPVPSeedChooser>, public Sexy::ScrollWidgetListener
{
public:
	UINewPVPSeedChooser();
	virtual ~UINewPVPSeedChooser();

	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UINewPVPSeedChooser"; }
	virtual void				Draw(Graphics* i_g) override;
	virtual void				DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g);
	virtual void				Update() override;

	void UpdateUI();

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void onItemClicked(UINewPVPSeedChooserItem* i_item);
	void selectPlant(int i_id);

	std::vector<int> GetSelectedPlants();
	std::vector<std::string> GetDisabledMaps() { return m_disabledMaps; }

//	void SetPlantBlacklist(std::vector<std::string> i_blacklist) { m_plantBlacklist = i_blacklist; }

	void setItemPreview(int i_id);


private:

	void rebuildValidPlantTypeList();
	void deleteChooserPackets();
	void initSelectedPlantMap();

	void addItemToChooser(int i_id);
	bool isBlacklisted(const std::string& i_seedName);

	void selectItem(int i_id) {}
	void unSelectItem(int i_id) {}

	void addItemToBank(int i_id, int i_index = -1);

	void onItemClicked(int i_id);

	void updateItems();

	int getItemDataIndexInChooser(int i_id);
	int getItemDataIndexInBank(int i_id);

	SexyVector2 calcItemPositionInBank(int i_index);
	int getMinAvailableIndexInBank();

	bool hasBeenSelected(int i_id);

	void updateBank();

	bool isBankFull();

	void checkPreviousSelected();
	bool IsItemSelected(int i_id);
	void clearBankItems();

	void setItemState(int i_id, NewPVPSeedChooserItemState i_newState);


	void selectPlant(int i_index, int i_id);
	void unSelectPlant(int i_index);

	void updateItemsMoving();


	// disable map
	void rebuildValidMapList();

	std::map<std::string, bool> m_mapState;


	PVZ2UIScrollingWidget* m_candidateScrollingWidget = nullptr;
	PVZ2UIButton* m_choosePlantButton = nullptr;
	PVZ2UIButton* m_disableMapButton = nullptr;
	Widget* m_chooser = nullptr;
	Widget* m_bank = nullptr;
	Widget* m_preview = nullptr;
	Widget* m_displayMapPlane = nullptr;

	Sexy::Widget* m_choosePlantView = nullptr;
	Sexy::Widget* m_disabledMapView = nullptr;

	std::vector<ChooserItemData>			m_chooserItems;
	std::vector<ChooserItemData>			m_bankItems;

	class PVZ2UISeedChooserPreviewDisplay* m_seedInfoWidget = nullptr;

	int 						m_previewItemID = -1;

	std::vector<int> 			m_selectedPlants;
	std::vector<std::string>	m_disabledMaps;

	std::map<int, int>			m_selectedPlantsMap;
};

struct NewPVPDuanRewardsData
{
	NewPVPDuanRewardsData() {}

	NewPVPDuanRewardsData(int i_sIndex, std::vector<S2C_BonusInfo> i_rewards, int i_rand = 0, int i_obt = 0, int i_unLocked = 0)
	{
		Index = i_sIndex;
		Rewards = i_rewards;
		Random = i_rand;
		Obtained = i_obt;
		Unlocked = i_unLocked;
	}

	int Obtained = 0;
	int Unlocked = 0;
	int Random = 0;		// 0: single, reward 1: random box1, 2: random box2
	int Index = -1;		// Server index

	std::vector<S2C_BonusInfo> Rewards;
};

struct NewPVPSmallDuan
{
	NewPVPSmallDuan() {}

	NewPVPSmallDuan(int i_bNum, int i_sNum, int i_sReq, NewPVPDuanRewardsData i_rewardsInfo)
	{
		BigDuanNum = i_bNum;
		SmallDuanNum = i_sNum;
		StarNumRequired = i_sReq;
		RewardsInfo = i_rewardsInfo;
	}

	int BigDuanNum = 1;
	int SmallDuanNum = 1;
	int StarNumRequired = 3;

	NewPVPDuanRewardsData RewardsInfo;
};

class S2C_DuanRewards : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_DuanRewards, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> billList;
};

class UINewPVPDuanItemRewardFrame : public UIRewardFrame
{
public:
    static UINewPVPDuanItemRewardFrame* CreateUIRewardFrame(int objectId, int num, bool hasFrame);
    static UINewPVPDuanItemRewardFrame* CreateUIRewardFrame(UINewPVPDuanItemRewardFrame* i_copy);

    static UINewPVPDuanItemRewardFrame* CreateUIRewardsFrame(NewPVPDuanRewardsData i_rewards);

    void Draw(Sexy::Graphics* i_g) override;
    void DrawObtainedImage(Sexy::Graphics* i_g);

    void SetObtainedString(std::string i_str);
    void SetSelectDescription(SexyString sexyStr);

    void SetCanReward(bool i_can);

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void TouchesCanceled() override;

    void RequestReward();
    void SetServerIndex(int i_sIndex) { m_serverIndex = i_sIndex; }

private:
    UINewPVPDuanItemRewardFrame(RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
    ~UINewPVPDuanItemRewardFrame();

    void Update() override;

private:
    int m_touchId;
    SexyString m_des;
    class StoneLotteryItemTipUI* m_tipUI;
    Image* m_obtainedImage = nullptr;
    class Effect_PopAnim* m_lightEffect = nullptr;
    int m_serverIndex = -1;
    bool m_canReward = false;
};

class UINewPVPDuanItem : public Widget
{
public:
	UINewPVPDuanItem() {}
	virtual ~UINewPVPDuanItem() {}

	virtual void Draw(Graphics* i_g) override;
	virtual void Init(NewPVPSmallDuan i_sDuan);

	void InitRewardsFrame();

	NewPVPSmallDuan m_smallDuan = {};
	UINewPVPDuanItemRewardFrame* m_rewardFrame = nullptr;
};


class UINewPVPDuanPlane : public Widget
{
public:
	UINewPVPDuanPlane() {}
	UINewPVPDuanPlane(std::vector<std::vector<NewPVPSmallDuan>> i_list, SexyVector3 i_currentDuan);
	virtual ~UINewPVPDuanPlane() {}

	virtual void Draw(Graphics* i_g) override;
	virtual void Init(std::vector<std::vector<NewPVPSmallDuan>> i_list, SexyVector3 i_currentDuan);

	int CalculateStarNumOfCurrentSmallDuan();
	int CalculateSmallDuanNumOfBigDuan(int i_bigDuan);

	bool IsFull();
	bool IsTopBigDuan(int i_bigDuan);

private:
	std::vector<std::vector<NewPVPSmallDuan>> m_duanInfos;
	std::vector<std::vector<Widget*>> m_duanItems;

	SexyVector3 m_currentDuan = SexyVector3(1, 1, 0);
};

// Duan
class UINewPVPDuan : public UISingletonDialog<UINewPVPDuan>, public Sexy::ScrollWidgetListener
{
public:

	enum ButtonID
	{
		BTN_OK,
	};

	UINewPVPDuan();
	virtual ~UINewPVPDuan();

	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UINewPVPDuan"; }

	virtual void Draw(Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g);

	virtual void Update() override;

	void SetInfoList(std::vector<Network_NewPVPSmallDuan> i_infos = {});
	void SetRewardsStatus(std::vector<int> i_status);

	void SetCurrentTotalStarNum(int i_num);
	void SetMaxTotalStarNum(int i_num);
	void SetCurrentDuan(int i_bigDuan, int i_smallDuan, int i_star);
	void SetMaxDuan(int i_bigDuan, int i_smallDuan, int i_star = 0);

	void InitScrollWidget();
	void RefreshUI();
	void RefreshRewardsLockState();

	SexyVector3 CalculateDuanNumFromStar(int i_starNum); // SexyVector3(BigDuan, SmallDuan, StarNum)
	int CalculateSmallDuanNumOfBigDuan(int i_bigDuan);

	bool IsTopBigDuan(int i_bigDuan);
	bool CanReward() { return m_canReward; }

	// ButtonListener
	virtual void ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	bool HasObtainedReward(int i_bigDuan, int i_smallDuan) { return m_duanInfos[i_bigDuan][i_smallDuan].RewardsInfo.Obtained; }

private:

	std::vector<std::vector<NewPVPSmallDuan>> m_duanInfos;
	std::vector<std::vector<Widget*>> m_duanItems;

	SexyVector3 m_currentDuan = SexyVector3(1, 1, 0);
	SexyVector3 m_maxDuan = SexyVector3(1, 1, 0);

	Widget* m_scrollPlane = nullptr;

	bool m_canReward = false;
	pvztime_t m_accumulatedTime = 0.f;



};


#endif /* __UINEWPVP_SEEDCHOOSER_H__ */
