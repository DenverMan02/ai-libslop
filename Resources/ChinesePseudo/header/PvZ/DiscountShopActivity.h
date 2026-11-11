/*
 * DiscountShopActivity.h
 *
 *  Created on: 2020-4-30
 *      Author: zhousen
 */

#ifndef DISCOUNTSHOPACTIVITY_H_
#define DISCOUNTSHOPACTIVITY_H_

#include "PVZDB.h"
#include "Singleton.h"
#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "MagentoService.h"
#include "PlantAdventureConfig.h"
#include "BoxOpenUI.h"
#include "PopingWidget.h"
#include "UISingletonDialog.h"
#include "EASquared.h"
#include "UIUtil.h"
#include "UIRewardFrame.h"
//#include "ActivityManager.h"
#include "UIUtil.h"

class DiscountShopActivityUI;

struct DiscountShopContentData
{
    int ObjectId;
    int Quantity;
    int CostGem;
    int Discount;
    int BtnStatus;// 0 = can buy, 1 = got
    int CurrencyID;

    DiscountShopContentData() { 
        ObjectId = 0;
        Quantity = 0;
        CostGem = 0;
        Discount = 0;
        BtnStatus = 0;
        CurrencyID = 3008;// default gem, not serialize now
    }
};

class DiscountShopData : public RtObject
{
public:
    RT_CLASS_DEFINE(DiscountShopData, RtObject, RtClass);
    DiscountShopData();

    std::vector<DiscountShopContentData> _itemList;
    int _rechargeCurrencyToday;
    std::string _bannerImage;// server config banner name
};

// shop content main panel
class DiscountShopCommonWidget : public CommonRewardItemWidget
{
public:
    DiscountShopCommonWidget();
    virtual ~DiscountShopCommonWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    void SetDiscount(int i);// discount 1 ~ 9

protected:
    Sexy::Image* _discountImage;
};

class DiscountShopCommonWidgetNew : public CommonRewardItemWidget
{
public:
	DiscountShopCommonWidgetNew();
    virtual ~DiscountShopCommonWidgetNew();

    virtual void Draw(Sexy::Graphics* i_g) override;
    void SetDiscount(int i);// discount 1 ~ 9

protected:
    void init() override;

protected:
    Sexy::Image* _discountImage;
    Sexy::Image* _mainBg;
};

// shop content item
class DiscountShopContentWidget : public Widget, public Sexy::ButtonListener
{
public:
    DiscountShopContentWidget(DiscountShopActivityUI* parent);
    virtual ~DiscountShopContentWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int id) override;

    void InitView(int index, DiscountShopContentData data);
    void UpdateUI(DiscountShopContentData data);

protected:
    void CreateTipsPanel();
    void CancelCallback();
    void RechargeCallback();
    CommonRewardItemData CreateCommonRewardItemData(DiscountShopContentData);
    
protected:
    DiscountShopCommonWidget* _itemWidget;// main ui
    PVZ2UIButton* _buyBtn;// buy button
    int _btnID;// btn id (1001, 1002, 1003)
    int _itemIndex;// item index, for V392 item param
    DiscountShopContentData _data;// shop content data
    DiscountShopActivityUI* _parentUI;// parent UI
};

///////////////////////////////////
/// DiscountShopContentWidgetNew
///////////////////////////////////
class DiscountShopContentWidgetNew : public Widget, public Sexy::ButtonListener
{
public:
	DiscountShopContentWidgetNew(DiscountShopActivityUI* parent);
    virtual ~DiscountShopContentWidgetNew();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int id) override;

    void InitView(int index, DiscountShopContentData data);
    void UpdateUI(DiscountShopContentData data);

protected:
    void CreateTipsPanel();
    void CancelCallback();
    void RechargeCallback();
    CommonRewardItemData CreateCommonRewardItemData(DiscountShopContentData);

protected:
    DiscountShopCommonWidgetNew* _itemWidget;// main ui
    PVZ2UIButton* _buyBtn;// buy button
    int _btnID;// btn id (1001, 1002, 1003)
    int _itemIndex;// item index, for V392 item param
    DiscountShopContentData _data;// shop content data
    DiscountShopActivityUI* _parentUI;// parent UI
};


enum {
    BTN_RECHARGE = 1000, // in panel recharge button
};

// discount shop activity ui
class DiscountShopActivityUI : public UISingletonDialog<DiscountShopActivityUI>
{
public:
    DiscountShopActivityUI();
    ~DiscountShopActivityUI();

    virtual bool OnCreate() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;
    virtual std::string GetLayoutName() override { return "DiscountShopActivity"; }
	virtual void ButtonDepress(int i_id) override;
    void UpdateUI(DiscountShopData data);
    void UpdateUI();

protected:
    void InitView();
    void UpdateTimeCountDown();
    
    void RequestNetwork();
    void RechargeBundlePurchased(int objectId);
    void OnRechargeCallback(MagentoProductProps* i_props);
    void OnGetRewardResult(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    SexyString _timeCountDownStr;// time countdown str
    SexyString _activityTimeCountDownStr;// activity time countdown str
    
    time_t _activityEndTime;// activity close time

    Sexy::Widget* _banner;// banner ui
    Sexy::Widget* _countdownUI;// timecountdown ui
    Sexy::Widget* _scrollBg;// item background
    Sexy::Widget* _activityCountdownUI;// activity countdown

    std::vector<DiscountShopContentWidget*> _itemList;// shop content item list
    Sexy::Image* _bannerImage;
};

/// discount shop activity manager
class DiscountShopActivityManager : public LazySingleton<DiscountShopActivityManager>
{
public:
    DiscountShopActivityManager();
    ~DiscountShopActivityManager();

    void Init(ActiveItem item);

    DiscountShopData GetShopData() { return _data; }
    DiscountShopContentData GetShopContentData(int i) {
        DASSERT(i >= 0 && i < _data._itemList.size(), "invalid index for DiscountShopActivityManager");
        return _data._itemList[i];
    }
    int GetDataLength() { return (int)_data._itemList.size(); }
    bool IsRechargeToday() { return _data._rechargeCurrencyToday > 0; }
    time_t GetActivityEndTime() { return _activityEndTime; }
    std::string GetBannerImageName() { return _data._bannerImage; }
    void RequestNetwork();

private:
    DiscountShopData _data;
    time_t _activityEndTime;// activity end time
};


#endif /* DISCOUNTSHOPACTIVITY_H_ */
