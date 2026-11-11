/*
 * RechargeDailySignActivity.h
 *
 *  Created on: 2020-4-26
 *      Author: zhousen
 */

#ifndef RECHARGEDAILYSIGNACTIVITY_H_
#define RECHARGEDAILYSIGNACTIVITY_H_

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

class RechargeDailySignActivityUI;

// Recharge DailySign Bonus Type
enum RechargeDailySignBonusType
{
    DailySignBonusInvalid = -1,
    DailySignBonusNormal,// everybody can get
    DailySignBonusAdvance,// can get one if player recharge once
    DailySignBonusMax,
};

enum RechargeDailySignBonusBtnStatus 
{
    BtnStatus_Invalid = -1,
    BtnStatus_ShowBtn,
    BtnStatus_Disable,// show btn , but can't be clicked
    BtnStatus_HideBtn,
    BtnStatus_Max,
};

struct RechargeDailySignDayReward
{
    int ObjectID;
    int Quantity;
    int BtnStatus;// 0 = not got, 1 = has got

    RechargeDailySignDayReward() { 
        ObjectID = 0;
        Quantity = 0;
        BtnStatus = 0;
    }
};

class RechargeDailySignData : public RtObject
{
public:
	RT_CLASS_DEFINE(RechargeDailySignData, RtObject, RtClass);
	RechargeDailySignData();

    // bool _isRechargeToday;
    std::vector<std::vector<RechargeDailySignDayReward>> _dayDataList;// 1~7 days, each day [0] = normal, [1] = advance.
    int _rechargeCurrency;// current recharge currency num
    int _advanceSignDayNum;// the days can get advance sign reward
    int _normalDaySignNum;// the days can get normal sign reward
    std::string _bannerImage;// server config banner name
};

// a widget contains 2 plants icon, 2 buttons, day desc
class RechargeDailySignWidget : public Widget, public Sexy::ButtonListener
{
public:
    RechargeDailySignWidget(RechargeDailySignActivityUI* parent);
    virtual ~RechargeDailySignWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int id) override;

    virtual void InitView(int index, std::vector<RechargeDailySignDayReward> list);
    virtual void UpdateUI(std::vector<RechargeDailySignDayReward> list);

protected:
    void RequestGetReward(RechargeDailySignBonusType type);

protected:
    int _index;// sign day index
    RechargeDailySignDayReward _clickData;// current get bonus data
    RechargeDailySignBonusType _clickBonusType;// current get bonus type

    // not use now
    std::vector<S2C_BonusInfo> _bonusList;
    std::vector<int> _btnStatusList;// 0 = disable, 1 = getable, 2 = got

    std::vector<RechargeDailySignDayReward> _bonusRewardList;

    PVZ2UIButton* _normalBtn;// normal sign bonus btn
    PVZ2UIButton* _advanceBtn;// advance sign bonus btn
    Sexy::Image* _hasGotImage;// all bonus got, then show this icon
    bool _hasGotImageVisible;

    int _normalBtnID;
    int _advanceBtnID;

    UIRewardFrame* _normalItemFrame;
    UIRewardFrame* _advanceItemFrame;

    SexyString _dayDesc;// the N day
    Sexy::Image* _bgImage;// bg
    Sexy::Rect _bgRect;
    Sexy::Image* _dayBgImage;// the N day background
    Sexy::Rect _dayBgRect;

    Sexy::Widget* _gift_icon;
    Sexy::Widget* _arrow;
    UIWidgetText* _dayTitle;

    RechargeDailySignActivityUI* _parentUI;// for get widgets properties
};

// for activity new panel
class RechargeDailySignWidgetNew : public RechargeDailySignWidget
{
public:
	RechargeDailySignWidgetNew(RechargeDailySignActivityUI* parent);
    virtual ~RechargeDailySignWidgetNew();

    virtual void Draw(Graphics* i_g) override;
    virtual void InitView(int index, std::vector<RechargeDailySignDayReward> list);

protected:
    Rect _dayTitleRect;
};

enum {
    RECHARGE_BTN = 1000,// jump to store
};

// main ui, contains a scroll view with RechargeDailySignWidget
class RechargeDailySignActivityUI : public UISingletonDialog<RechargeDailySignActivityUI>, public Sexy::ScrollWidgetListener
{
public:
    RechargeDailySignActivityUI();
    ~RechargeDailySignActivityUI();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override {
//    	return "RechargeDailySignActivity";
    	return "RechargeDailySignActivityNewYear";
    }
    virtual void Draw(Graphics* i_g) override;
    virtual void Update() override;
	virtual void ButtonDepress(int i_id) override;
    
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void UpdateUI(RechargeDailySignData data);
    void UpdateUI();

protected:
    void InitView();
    void UpdateTimeCountDown();
    
    void RequestNetwork();

    void RechargeBundlePurchased(int objectId);
    void OnRechargeCallback(MagentoProductProps* i_props);
    void OnGetRewardResult(bool i_success, const std::set<int>& changeList);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    std::vector<std::vector<S2C_BonusInfo>> CreateTestBonusData();
    std::vector<std::vector<int>> CreateTestBtnStatusData();

protected:
    SexyString _activityDesc;// the activity description
    SexyString _rechargeStatus;// has recharged or not
    PVZ2UIButton* _rechargeBtn;// jump to the store
    std::vector<RechargeDailySignWidget*> _itemList;// for all days ui

    time_t _activityEndTime;// activity close time
    
    Sexy::Widget* _banner;
    Sexy::Widget* _countdownUI;
    UIWidgetText* _countdownText;
    SexyString _countdownStr;
    Sexy::Widget* _scrollBg;
    Sexy::Image* _bannerImage;
};

/// get data from server before RechargeDailySignActivityUI created
class RechargeDailySignActivityManager : public LazySingleton<RechargeDailySignActivityManager>
{
public:
    RechargeDailySignActivityManager();
    ~RechargeDailySignActivityManager();

    void Init(ActiveItem item);

    std::vector<RechargeDailySignDayReward> GetDayData(int day) {
        DASSERT(day >= 0 && day < _data._dayDataList.size(), "invalid index for RechargeDailySignActivityManager::GetDayData");
        return _data._dayDataList[day];
    }

    RechargeDailySignData GetSignData() { return _data; }
    int GetDayLength() { return (int)_data._dayDataList.size(); }
    bool IsRechargeToday() { return _data._rechargeCurrency > 0; } // maybe not use
    time_t GetActivityEndTime() { return _activityEndTime; }
    std::string GetBannerImageName() { return _data._bannerImage; }
    int CurrentCanGotItemIndex();
    int CurrentAdvanceSignDayNum() { return _data._advanceSignDayNum; }
    int CurrentNormalSignDayNum() { return _data._normalDaySignNum; }
    RechargeDailySignBonusBtnStatus GetBtnStatus(int day, RechargeDailySignBonusType bonusType);// 0 = can got, 1 = disable btn, 2 = hide btn
    void RequestNetwork();

private:
    RechargeDailySignData _data;// all data for activity
    time_t _activityEndTime;// activity end time
};


#endif /* RECHARGEDAILYSIGNACTIVITY_H_ */
