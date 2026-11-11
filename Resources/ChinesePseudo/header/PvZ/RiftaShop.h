#ifndef RIFTASHOP_H
#define RIFTASHOP_H

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

struct RiftaShopItemData
{
    int32   m_iObjId;
    int32   m_iQuantity;
    int32   m_iPrice;
    int32   m_iState;// 0 = can buy, 1 = has bought
    bool    m_bIsUnLock;
    int     m_nLockIndex;// this is for locked item's description
};

class RiftaShopData : public INetworkData
{
public:
    RT_CLASS_DEFINE(RiftaShopData, INetworkData, RtClass);

    std::vector<int>                m_vecRefreshCost;// times refresh cost
    std::vector<RiftaShopItemData> m_shopDataList;
    int32                           m_leftZMatchCoin;
    int                             m_alreadyRefrashTimes;
    int								m_adTimes;
};

/// 
/// riftshopbutton
///
class RiftaShopButton : public PVZ2UIButton, public ButtonListener
{
public:
    typedef Delegate0 RiftaShopCallback;
    RiftaShopButton(int buttonID);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void SetCurrencyImage(Image* img) { _currencyImage = img; }
    void SetItemAmount(int amount);
    void SetClickCallback(RiftaShopCallback callback){ _callback = callback; }

protected:
    void BuyConfirm(class UIMessageBox* box, int buttonID);

    Rect _currencyImgRect;// the rect render currency img
    Rect _amountStrRect;// the rect render amount str.
    Image* _currencyImage;// item currenty image
    SexyString _amountStr;// item amount str

    RiftaShopCallback _callback;// click callback
};



// shop content
class RiftaShopCommonWidget : public CommonRewardItemWidget
{
public:
	RiftaShopCommonWidget(int index);
	virtual ~RiftaShopCommonWidget();

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

protected:
    void init() override;
    void ClickCallback();

protected:
    int _index;// item index in bonuslist
	int _itemStatus;// RiftaShopItemData.BtnStatus
    int _lockDescriptionIndex;// the index of the 
	SexyString _lockDescription;//it's item locked description
    bool _drawAmount;// chekc if should draw item amount
    SexyString _amountString;// item amount string
    int _offsetY;// control all ui y offset
    RiftaShopButton* _button;// if this widget can buy, then show this button
};

class RiftaShop : public UISingletonDialog<RiftaShop>, public Sexy::ScrollWidgetListener
{
public:
    RiftaShop();
    virtual ~RiftaShop();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UIRiftaShop"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;

    void                                    WidgetTouchCallback(const class CommonRewardItemData& i_data);
    void                                    OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void                                    onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);


    void UpdateShopUI(const RiftaShopData& i_data) { initWidgets(i_data); refreshMaterial(); }

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

private:
    void initWidgets(const RiftaShopData& i_data);
    bool IsAdvertisementEnable();
    void updateTimer();
    void refreshMaterial();
    void refreshShop(int i_id);
    void ConfirmBuy(UIMessageBox* box, int buttonID);
    void ConfirmWatchADOrBuy(UIMessageBox* box, int buttonID);
    void onADFinished(int i_type);

    bool m_canAdsRefresh;
    std::vector<class RiftaShopCommonWidget*> m_vecWidget;
};

class RiftShopMgr : public LazySingleton<RiftShopMgr>
{
public:
	RiftShopMgr();
	virtual ~RiftShopMgr();

    void loadData(const RiftaShopData& shopData);
    const RiftaShopData& getRiftShopData() const;

    int getRefreshShopCost();
    int getRefreshShopTimes();

private:
    RiftaShopData m_shopData;// rift shop data
    int m_nCurBuyCost;
    int m_nZMatchTicket;// rift coins number
};

#endif
