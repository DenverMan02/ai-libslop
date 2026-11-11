/*
 * CustomLevelShop.h
 *
 *  Created on: 2021-7-29
 *      Author: zhousen
 */

#ifndef CUSTOMLEVELSHOP_H_
#define CUSTOMLEVELSHOP_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
//#include "CustomLevelMainMenu.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "CustomLevelConfig.h"

struct CustomLevelShopItemDData
{
	CustomLevelShopItemDData() {
		m_iObjId = 0;
		m_iQuantity = 0;
		m_iPrice = 0;
		m_iBuyTimes = 0;
		m_iBuyTImesMax = 0;
		m_currencyType = 4013;
		m_iState = 0;
		m_bIsUnLock = false;
		m_nLockIndex = 0;
	}
    int32   m_iObjId;
    int32   m_iQuantity;
    int32   m_iPrice;
    int32   m_iBuyTimes;
    int32 	m_iBuyTImesMax;
    int32	m_currencyType;
    // maybe useful
    int32   m_iState;// 0 = can buy, 1 = has bought
    bool    m_bIsUnLock;
    int     m_nLockIndex;// this is for locked item's description
};

class CustomLevelShopData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CustomLevelShopData, INetworkData, RtClass);

    std::vector<std::string> GetConstraintValue(const std::string& i_key) const;
    float GetConstraintValue(const std::string& i_key, float i_default) const;

    std::vector<CustomLevelShopItemDData> m_shopDataList;
    int32                           m_leftZMatchCoin;
    int32							m_leftCoinHard;
    ConstraintConfig 				m_constraintConfigs;
    std::vector<S2C_BonusInfo>		m_bonusList;
};

class CustomLevelShopButton : public PVZ2UIButton, public ButtonListener
{
public:
    typedef Delegate0 CustomLevelShopCallback;
    CustomLevelShopButton(int buttonID);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void SetCurrencyImage(Image* img) { _currencyImage = img; }
    void SetItemAmount(int amount);
    void SetClickCallback(CustomLevelShopCallback callback){ _callback = callback; }

protected:
    void BuyConfirm(class UIMessageBox* box, int buttonID);

protected:
    Rect _currencyImgRect;// the rect render currency img
    Rect _amountStrRect;// the rect render amount str.
    Image* _currencyImage;// item currenty image
    SexyString _amountStr;// item amount str

    CustomLevelShopCallback _callback;// click callback
};

class CustomLevelShopCommonWidget : public CommonRewardItemWidget
{
public:
	CustomLevelShopCommonWidget(int index);
	virtual ~CustomLevelShopCommonWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void LoadData(const CommonRewardItemData& i_data) override;// this func should called after resize and setoffset, because ui and button will init by some value
    void TouchEnded(const Sexy::Touch& i_touch) override;

    void SetItemStatus(int status) { _itemStatus = status; }
    void SetLockDescriptionIndex(int index);
    void SetOffsetY(int offset) { _offsetY = offset; }
    void SetButtonVisible(bool visible) {
        if (_button) {
            _button->SetVisible(visible);
        }
    }
    void SetBuyTimes(int times, int maxTimes);
    bool CheckShopItem(const S2C_ShopItemPurchaseInfo* data);
    void UpdateShopCommonWidget(const S2C_ShopItemPurchaseInfo* data);
    bool  is_expect;

protected:
    void init() override;
    void ClickCallback();

protected:
    SexyString _buyTimeStr;
    int _buyTimes;
    int _buyTimesMax;
    int _index;// item index in bonuslist
	int _itemStatus;// RiftaShopItemData.BtnStatus
    int _lockDescriptionIndex;// the index of the
	SexyString _lockDescription;//it's item locked description
    bool _drawAmount;// chekc if should draw item amount
    SexyString _amountString;// item amount string
    int _offsetY;// control all ui y offset
    CustomLevelShopButton* _button;// if this widget can buy, then show this button
};

class CustomLevelShop : public UISingletonDialog<CustomLevelShop>, public Sexy::ScrollWidgetListener
{
public:
	CustomLevelShop();
    virtual ~CustomLevelShop();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "CustomLevelShop"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;

    void                                    WidgetTouchCallback(const class CommonRewardItemData& i_data);
    void                                    OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);


    void UpdateShopUI(const CustomLevelShopData& i_data) { initWidgets(i_data); refreshMaterial(); }

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

private:
    void initWidgets(const CustomLevelShopData& i_data);
    bool IsAdvertisementEnable();
    void updateTimer();
    void refreshMaterial();
    void refreshShop(int i_id);
    void ConfirmBuy(UIMessageBox* box, int buttonID);
    void ShowTipsUI();

    bool m_canAdsRefresh;
    std::vector<class CustomLevelShopCommonWidget*> m_vecWidget;
};

class CustomLevelShopMgr : public LazySingleton<CustomLevelShopMgr>
{
public:
	CustomLevelShopMgr();
	virtual ~CustomLevelShopMgr();

    void loadData(const CustomLevelShopData& shopData);
    const CustomLevelShopData& getShopData() const;
    int GetCointDeltaCount(int coin_id);

    int getRefreshShopCost();
    int getRefreshShopTimes();

private:
    CustomLevelShopData m_shopData;// shop data
    int m_nCurBuyCost;
    int m_nZMatchTicket;// coins number
    int m_nTicketHard;// coins number for hardmode
};

#endif /* CustomLevelShop_H_ */
