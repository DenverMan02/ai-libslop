/*
 * DangerRoomSpecialOfferExtra.h
 *
 *  Created on: 2020-10-30
 *      Author: zhousen
 */

#ifndef DANGERROOMSPECIALOFFEREXTRA_H_
#define DANGERROOMSPECIALOFFEREXTRA_H_

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

///
/// btn index
///
enum {
    DANGERROOM_SPECIAL_OFFER_EXTRA_BUTTON_CLOSE = 1000,
    DANGERROOM_SPECIAL_OFFER_EXTRA_BUTTON_START = 100,// use this + N for item button click
};

// btn status
enum {
    BTN_STATUS_CANT_BUY = 0,
    BTN_STATUS_CAN_BUY = 1,
    BTN_STATUS_HAS_BOUGHT = 2,
};

///
/// activity data
///
struct DangerRoomSpecialOfferExtraItemData {
    DangerRoomSpecialOfferExtraItemData() { 
        BonusList.clear();
        ButtonStatus = 1;
        DescIndex = 1;
        OrigPrice = 100;
        CurPrice = 10;
        Discount = 1;
        Payment = "";
        Index = 0;
    }

    std::vector<S2C_BonusInfo> BonusList;// bonus data
    int ButtonStatus;// 0 = can't buy, 1 = can buy, 2 = has got
    int DescIndex;// the desction string index
    int OrigPrice;// original price
    int CurPrice;// current price
    int Discount;// discount id
    std::string Payment;// payment str
    int Index;// data index 
};

class DangerRoomSpecialOfferExtraData : public INetworkData {
public:
    RT_CLASS_DEFINE(DangerRoomSpecialOfferExtraData, INetworkData, RtClass);
    DangerRoomSpecialOfferExtraData() { 
        ItemDataList.clear();
    }

    std::vector<DangerRoomSpecialOfferExtraItemData> ItemDataList;
};

///
/// btn class
///
class DangerRoomSpecialOfferExtraButton : public PVZ2UIButton, public ButtonListener {
// TODO: price1 , arrow, price2, discount
public:
    DangerRoomSpecialOfferExtraButton(int i_id)
    : PVZ2UIButton(i_id, this, _S(""))
    {
        _origPriceStr = _S("");
        _curPriceStr = _S("");
        _discountImg = nullptr;
        _buttonIndex = i_id;
        _index = 0;
    };
    ~DangerRoomSpecialOfferExtraButton();

    virtual void Draw(Sexy::Graphics* i_g) override; 
    virtual void ButtonDepress(int i_id) override;
    
    void InitView(int index);

protected:
    Rect _origPriceRect;
    SexyString _origPriceStr;

    Rect _curPriceRect;
    SexyString _curPriceStr;

    Rect _arrowRect;

    Image* _discountImg;
    Rect _discountRect;

    int _buttonIndex;// button index
    int _index;// real index in the original data list from server
};

///
/// item ui class
///
class DangerRoomSpecialOfferExtraItemWidget :  public Widget, Sexy::ButtonListener {
public:
    DangerRoomSpecialOfferExtraItemWidget(class DangerRoomSpecialOfferExtraUI* parent);
    virtual ~DangerRoomSpecialOfferExtraItemWidget();

    virtual void DrawAll(ModalFlags* theFlags, Graphics* g) override;
    
    void InitView(int index, DangerRoomSpecialOfferExtraItemData data);
    void UpdateUI(DangerRoomSpecialOfferExtraItemData data);

protected:
    int _index;

    Rect _plusIconRect;
    Image* _plusImg;

    Rect _itemDescRect;
    SexyString _itemDescStr;

    Rect _hasBoughtRect;
    Image* _hasBoughtImg;
};

/// 
/// main ui class
///
class DangerRoomSpecialOfferExtraUI : public UISingletonDialog<DangerRoomSpecialOfferExtraUI>,public Sexy::ScrollWidgetListener {
public:
    DangerRoomSpecialOfferExtraUI();
    ~DangerRoomSpecialOfferExtraUI();

	virtual bool	     OnCreate() override;
    virtual std::string  GetLayoutName() override { return "DangerRoomSpecialOfferExtra"; }
	virtual void		 ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void UpdateUI(const DangerRoomSpecialOfferExtraData& i_data);
    void InitView();
    // void RequestNetwork();

protected:
    // void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void InitScrollView(const DangerRoomSpecialOfferExtraData& i_data);

protected:
    std::vector<DangerRoomSpecialOfferExtraItemWidget*> _itemList;
};

///
/// datamanager
///
class DangerRoomSpecialOfferExtraManager : public LazySingleton<DangerRoomSpecialOfferExtraManager>{
public:
    DangerRoomSpecialOfferExtraManager();
    ~DangerRoomSpecialOfferExtraManager();

    void LoadData(const DangerRoomSpecialOfferExtraData& data);
    DangerRoomSpecialOfferExtraData& GetData();
    DangerRoomSpecialOfferExtraItemData& GetItemData(int index);
    void FillAndSortData(DangerRoomSpecialOfferExtraData& data);
    void FillData(DangerRoomSpecialOfferExtraData& data);// fill index in data
    void SortData(DangerRoomSpecialOfferExtraData& data);// sort as got status
    void RequestNetwork();
    void NotifyPurchased(std::string item);
    void NotifyPurchased(std::vector<PaymentBundleInfo> bonusList, std::string sku);// this is used in ios v219

protected:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void TestInitData();

protected:
    DangerRoomSpecialOfferExtraData _data;
};


#endif /* DANGERROOMSPECIALOFFEREXTRA_H_ */
