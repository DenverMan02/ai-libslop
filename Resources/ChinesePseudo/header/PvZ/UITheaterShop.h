#ifndef UITHEATERSHOP_H
#define UITHEATERSHOP_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "ActiveSummery.h"
#include "UIWidgetAnim.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "EASquared.h"

#pragma mark - UITheaterDiceShopItem

class UITheaterDiceShopItem : public Sexy::Widget
{
public:
    UITheaterDiceShopItem(Sexy::ButtonListener* i_listener);
    virtual ~UITheaterDiceShopItem();

    virtual void Draw(Sexy::Graphics* i_g) override;

    void SetIndex(int i_index);

private:
    int m_index;
    Sexy::ButtonListener* m_listener;
};

#pragma mark - UITheaterDiceShop

class UITheaterDiceShop : public UISingletonDialog<UITheaterDiceShop>, public Sexy::ScrollWidgetListener
{
public:
    UITheaterDiceShop();
    virtual ~UITheaterDiceShop();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UITheaterDiceShop"; }
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void                            ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void                                    OnNotifyBillingReward(bool i_success, const S2C_BillingReward* pData);
};


#pragma mark - TheaterShopData

struct TheaterShopItemData
{
    int ItemId;
    int Amount;
    bool BuyFinish;
    int Currency;
};

class TheaterShopData : public INetworkData
{
public:
    RT_CLASS_DEFINE(TheaterShopData, INetworkData, RtClass);

    std::vector<TheaterShopItemData> ItemLists;
};

#pragma mark - UITheaterShop

class UITheaterShop : public UISingletonDialog<UITheaterShop>
{
public:
    UITheaterShop();
    virtual ~UITheaterShop();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UITheaterShop"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;

    void                                    WidgetTouchCallback(const class CommonRewardItemData& i_data);
    void                                    OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void                                    onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);

    void                                    onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    void init();
    void initWidgets(const TheaterShopData& i_data);
    bool IsAdvertisementEnable();
    void updateTimer();
    void refreshMaterial();
    void refreshShop(int i_id);
    void ConfirmBuy(UIMessageBox* box, int buttonID);

    bool m_canAdsRefresh;
    std::vector<class CommonRewardItemWidget*> m_vecWidget;
};

namespace Message
{
    void RichmanDiceShopBuyFinish(int number);
};

#endif