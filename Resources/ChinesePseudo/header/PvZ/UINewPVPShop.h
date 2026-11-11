#ifndef UINEWPVPSHOP_H
#define UINEWPVPSHOP_H

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
#include "DNodeWidget.h"
#include "NewPVPGame.h"
#include "SeedPacketUtils.h"
#include "UIChestAward.h"


struct Network_NewPVPShopItemData
{
	int   	m_iObjId = 0;
	int   	m_iQuantity = 0;
	int   	m_iPrice = 0;
    int 	m_iMaxBuyTimes = 0;
    int 	m_iBoughtTimes = 0;

	int 	m_iChestID = 0; // 0 = not chest,  1, 2 = chest_1, chest_2

    std::vector<int>			m_vChestRewardIds;		// all possible item id
    std::vector<int>			m_vChestRewardNums;	// [5]:  {legend card num, rare card num, normal card num, purple gold coin num, gem num}
};

class Network_NewPVPShopData : public INetworkData
{
    RT_CLASS_DEFINE(Network_NewPVPShopData, INetworkData, RtClass);

    int                           			m_leftCoin;
    std::vector<Network_NewPVPShopItemData> m_shopDataList;
};

class UINewPVPRewardItemNode : public DButton
{
public:
	UINewPVPRewardItemNode(int i_itemId, int i_quantity = -1);
};

///
/// NewPVPShopButton
///
class NewPVPShopButton : public PVZ2UIButton, public ButtonListener
{
public:
    typedef Delegate0 NewPVPShopCallback;
    NewPVPShopButton(int buttonID);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void SetCurrencyImage(Image* img) { _currencyImage = img; }
    void SetItemAmount(int amount);
    void SetItemAmountStr(SexyString i_str);
    void SetClickCallback(NewPVPShopCallback callback){ _callback = callback; }
    void SetAmountStrRect(Rect i_rect) { _amountStrRect = i_rect; }
    void SetChestIndex(int i_chestID) { _chestID = i_chestID; }

protected:
    void BuyConfirm(class UIMessageBox* box, int buttonID);

    Rect _currencyImgRect;// the rect render currency img
    Rect _amountStrRect;// the rect render amount str.
    Image* _currencyImage;// item currenty image
    SexyString _amountStr;// item amount str
    int _chestID;

    NewPVPShopCallback _callback;// click callback
};



// shop content
class NewPVPShopCommonWidget : public CommonRewardItemWidget
{
public:
	NewPVPShopCommonWidget(int index);
	virtual ~NewPVPShopCommonWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void LoadData(const CommonRewardItemData& i_data) override;// this func should called after resize and setoffset, because ui and button will init by some value

    void SetItemStatus(int status) { _itemStatus = status; }
    void SetLockDescriptionIndex(int index);
    void SetOffsetY(int offset) { _offsetY = offset; }
    void SetButtonVisible(bool visible) {
        if (_button) {
            _button->SetVisible(visible);
        }
    }

    void SetBuyTimes(int i_boughtTimes, int i_maxBuyTimes);

protected:
    void init() override;
    void ClickCallback();

protected:
    int _index;// item index in bonuslist
	int _itemStatus;// Network_NewPVPShopItemData.BtnStatus
    int _lockDescriptionIndex;// the index of the
	SexyString _lockDescription;//it's item locked description
    bool _drawAmount;// chekc if should draw item amount
    SexyString _amountString;// item amount string
    int _offsetY;// control all ui y offset
    NewPVPShopButton* _button;// if this widget can buy, then show this button

    bool _drawBuyLimit;
    int _maxBuyTimes;
    int _boughtTimes;
};

// shop chest widget
class NewPVPShopChestWidget : public NewPVPShopCommonWidget
{
public:
	NewPVPShopChestWidget(int index);
	virtual ~NewPVPShopChestWidget();

	void setChestInfo(int i_chestIndex, std::vector<int> i_chestRewardIds, std::vector<int> i_chestRewardNums);
	void Draw(Sexy::Graphics* i_g) override;

protected:
	void init() override;

private:
	void showPrizePool(const CommonRewardItemData&);
	void onBuytBtnClicked();

	int 						m_chestId = 0;
	std::vector<S2C_BonusInfo> 	m_chestBL;
	std::vector<int>			m_chestRewardIds;
	std::vector<int>			m_chestRewardNums;
};

class UINewPVPShopChestDetail : public DNodeWidget
{
public:
	UINewPVPShopChestDetail();
	~UINewPVPShopChestDetail();

	static UINewPVPShopChestDetail* create(bool focus = true);

	void Draw(Sexy::Graphics* i_g) override;

	void Initialize() override;
	void UserInit() override;

	void Init(std::vector<S2C_BonusInfo>& i_bounsList);
	void Init(std::vector<int>& i_ids, std::vector<int>& i_nums);

	void updatePlantsShow();
	void updateInfo();
	void updateItems();

	void useTestDataIfNecessary();

private:
    bool   m_bIsPlantMode = true;
    bool   m_bIsInfoMode = false;

    std::vector<S2C_BonusInfo> m_bonusInfo;
	std::vector<int>			m_detailIds;
	std::vector<int>			m_detailNums;

    static UINewPVPShopChestDetail* s_pWidgetHandler;
};

class DUINewPVPItemNode : public DTransformNode
{
public:
	DUINewPVPItemNode()
	{
		m_noCast = true;
	}
};

class UINewPVPRedPacketResult:public UIRedPacketResult
{
public:
    static UINewPVPRedPacketResult* create(const std::map<int,int>& reward,const std::vector<int>& list,bool focus = true);

    virtual ~UINewPVPRedPacketResult() {}

    virtual void UserInit() override;
};

class UINewPVPChestAward: public DNodeWidget
{
public:
    static UINewPVPChestAward* create(const std::vector<ChestAwardContent>& rewards, std::string effectName = "effects/ChestHardLevel_Chest");

    UINewPVPChestAward(const std::vector<ChestAwardContent>& rewards, std::string effectName = "effects/ChestHardLevel_Chest");
    virtual ~UINewPVPChestAward();

    virtual void Initialize() override;
    void setChestEffect(const std::string& i_effect) { m_chestEffect = i_effect; }
    void setEndCallBack(const std::function<void(DTransformNode*)>& i_callBack) { m_endCallFunc = i_callBack; };
    void setChestPositionOffset(DVec2 i_offset) { m_pChest->setPosition(getWinSize() * 0.5f + i_offset); }

private:
    DAnimNode*                  				m_pChest;
	std::vector<ChestAwardContent>          	m_rewards;
	bool										m_bBoxIsOpen;
    std::string                                 m_chestEffect;
    std::function<void(DTransformNode*)>        m_endCallFunc;
	static UINewPVPChestAward* 					s_pWidgetHandler;
};

class UINewPVPShop : public UISingletonDialog<UINewPVPShop>, public Sexy::ScrollWidgetListener
{
public:
    UINewPVPShop();
    virtual ~UINewPVPShop();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UINewPVPShop"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;

    void                                    OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);

    void UpdateShopUI(const Network_NewPVPShopData& i_data) { initWidgets(i_data); refreshMaterial(); }

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void onNotifyBuyChest(int i_itemIndex, std::vector<S2C_BonusInfo>& i_bonus);
	void costOnceBuyLimit(int i_index);

	int getChestIdFromItemIndex(int i_index);

private:
    void initWidgets(const Network_NewPVPShopData& i_data);
    void updateTimer();
    void refreshMaterial();
    void ConfirmBuy(UIMessageBox* box, int buttonID);

    void showDescriptionWidget();
    void closeDescriptionWidget();

    void refreshShop();
    int getGoodsPriceByIndex(int i_index);

    std::vector<class NewPVPShopCommonWidget*> m_vecWidget;

    class ActivityDescriptionUI* m_descriptionUI;

    bool m_resetTimes = false;
};

class NewPVPShopMgr : public LazySingleton<NewPVPShopMgr>
{
public:
	NewPVPShopMgr();
	virtual ~NewPVPShopMgr();

    void loadData(const Network_NewPVPShopData& shopData);
    const Network_NewPVPShopData& getShopData() const;

    bool m_isOpen = true;
private:
    Network_NewPVPShopData m_shopData;// shop data
};

namespace Message
{
    void NewPVPShopBuyChest(int i_chestIndex, std::vector<S2C_BonusInfo>& i_bonus);
};

#endif
