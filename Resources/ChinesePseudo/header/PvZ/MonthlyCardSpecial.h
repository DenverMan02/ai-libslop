/*
 * MonthlyCardSpecial.h
 *
 *  Created on: 2020-9-7
 *      Author: zhousen
 */

#ifndef MONTHLYCARDSPECIAL_H_
#define MONTHLYCARDSPECIAL_H_

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

///
/// button enum
///
enum {
    MONTHLY_CARD_BUTTON_CLOSE = 1000,
    MONTHLY_CARD_BUTTON_GOTO_MONTHLYCARD = 1001,
    MONTHLY_CARD_BUTTON_TIPS = 1002,
    MONTHLY_CARD_ITEM_BUTTON_START = 100,// use this + N for buttonID
};

/// 
/// avtivity data
///
struct MonthlyCardSpecialItemData {
    MonthlyCardSpecialItemData() { 
        TrailDay = 1;
        // CanBuy = false;
        BuyTimes = 1;
        // Discount = 0;
    }

    int TrailDay;// N days monthly card trail
    // bool CanBuy;// if this item can be bought
    int BuyTimes;// valid buy times
    // int Discount;// 0 = free, 1 ~ 9 is discount
};

class MonthlyCardSpecialData  : public INetworkData {
public:
    RT_CLASS_DEFINE(MonthlyCardSpecialData, INetworkData, RtClass);
    MonthlyCardSpecialData() { 
        ItemDataList.clear();
    }

    std::vector<MonthlyCardSpecialItemData> ItemDataList;
};

///
/// monthly card special manager
/// 
class MonthlyCardSpecialManager : public LazySingleton<MonthlyCardSpecialManager> {
public:
    MonthlyCardSpecialManager();
    ~MonthlyCardSpecialManager();

    void LoadData(const MonthlyCardSpecialData& data);
    MonthlyCardSpecialData& GetData();

    void SetActivityEndTime(time_t time) { _activityEndTime = time; }
    time_t GetActivityEndTime() { return _activityEndTime; }

    void RequestNetwork();

protected:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void TestInitData();

protected:
    MonthlyCardSpecialData _data;
    time_t _activityEndTime;// activity end time
};

/// 
/// Item Widget
///
class MonthlyCardItemWidget : public Widget, Sexy::ButtonListener {
public:
    MonthlyCardItemWidget(class MonthlyCardSpecialUI* parent);
    virtual ~MonthlyCardItemWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* theFlags, Graphics* g) override;
    virtual void ButtonDepress(int id) override;
    
    void InitView(int index, MonthlyCardSpecialData data);
    void UpdateUI(MonthlyCardSpecialData data);

protected:
    PVZ2UIButton* _buyBtn;// buy button
    int _buttonID;// buy button id
    int _index;// item index of the buy item data list.
    MonthlyCardSpecialUI* _parentUI;// maybe no use

    SexyString _itemTitleStr;// title str
    SexyString _buyTimeStr;// buy time str
    Image* _itemOriginalPriceImage;// original price image
    Image* _itemDiscountImage;// discount image
    SexyString _originalPriceStr;// original price str
    SexyString _lineStr;// line on original price str
};

/// 
/// Main UI
///
class MonthlyCardSpecialUI : public UISingletonDialog<MonthlyCardSpecialUI> {
public:
    MonthlyCardSpecialUI();
    ~MonthlyCardSpecialUI();

	virtual bool	     OnCreate() override;
    virtual std::string  GetLayoutName() override { return "MonthlyCardSpecial"; }
	virtual void		 Draw(Sexy::Graphics* i_g) override;
	virtual void		 ButtonDepress(int i_id) override;
    virtual void         Update() override;
    
    void UpdateUI(const MonthlyCardSpecialData& i_data);
    void InitView();

protected:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void UpdateTimeCountDown();

protected:
    UIWidgetText* _countDownDateText;// activity count down date
    time_t _activityEndTime;// activity end time
    std::vector<MonthlyCardItemWidget*> _itemList;// shop content item list  
};



#endif /* MONTHLYCARDSPECIAL_H_ */
