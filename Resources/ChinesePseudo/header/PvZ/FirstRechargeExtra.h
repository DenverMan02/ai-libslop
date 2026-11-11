/*
 * FirstRechargeExtra.h
 *
 *  Created on: 2020-7-29
 *      Author: zhousen
 */

#ifndef FIRSTRECHARGEEXTRA_H_
#define FIRSTRECHARGEEXTRA_H_

// this is for new first recharge ui

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

namespace Message
{
	void FirstRechargeButtonSelect(int index);
}

// bonus state
enum {
    FIRST_RECHARGE_NORECHARGE,// has not recharge above 2 yuan yet
    FIRST_RECHARGE_HAS_GOT,// has got current day bonus
    FIRST_RECHARGE_CAN_GOT,// can got current day bonus
};

// button id
enum {
    FIRST_RECHARGE_BUTTON_CLOSE = 1000,
    FIRST_RECHARGE_BUTTON_GOTO_RECHARGE = 1001,
    FIRST_RECHARGE_BUTTON_GET_BONUS = 1002,
    FIRST_RECHARGE_BUTTON_GOTO_RECHARGE_START = 1100,
    FIRST_RECHARGE_BUTTON_GET_BONUS_START = 1200,
    FIRST_RECHARGE_BUTTON_TAB_BUTTON_START = 1300,
    FIRST_RECHARGE_BUTTON_TAB_BUTTON_1 = FIRST_RECHARGE_BUTTON_TAB_BUTTON_START,
    FIRST_RECHARGE_BUTTON_TAB_BUTTON_2,
    FIRST_RECHARGE_BUTTON_TAB_BUTTON_3,
};

// bonus type 
enum {
    FIRST_RECHARGE_BONUS_TYPE_NORMAL,
    FIRST_RECHARGE_BONUS_TYPE_CHOOSE,
};

// tab index
enum {
	FIRST_RECHARGE_TAB_ONE = 1,
	FIRST_RECHARGE_TAB_TWO,
	FIRST_RECHARGE_TAB_THREE,
};

struct FirstRechargeExtraBonusData
{
    FirstRechargeExtraBonusData() {
        m_type = 0;
        m_bonuslist.clear();
    }

    ~FirstRechargeExtraBonusData() {
    	m_type = 0;
    	m_bonuslist.clear();
    }

    int m_type;// 1 = choose one in three, 0 = normal once bonus
    std::vector<S2C_BonusInfo> m_bonuslist;// if type == 1 , the data should create ui, if type == 0, the data is no use.
};

// server data struct
class FirstRechargeExtraNetworkData : public INetworkData
{
public:
    RT_CLASS_DEFINE(FirstRechargeExtraNetworkData, INetworkData, RtClass);

    FirstRechargeExtraNetworkData() { 
    }

    bool IsPopUp() {
    	for(int i = 0; i < m_hasgotStatusList.size(); ++i) {
    		if (!m_hasgotStatusList[i] && m_currentIndexList[i] > 0) {
    			return true;
    		}
    	}
    	return false;
    }

    bool IsNoRecharge() {
    	bool noRecharge = true;
    	for(int i = 0; i < m_currentIndexList.size(); ++i) {
    		if (m_currentIndexList[i] != 0) {
    			noRecharge = false;
    			break;
    		}
    	}
    	return noRecharge;
    }

    std::vector<int> m_hasgotStatusList;// true : show tips, false : check m_currentindex
    std::vector<int> m_currentIndexList;// index = 0 means no recharge, index = 1, 2, 3 means can get current bonus
    std::vector<std::vector<FirstRechargeExtraBonusData> > m_bonuslistList;// all day bonus data
};

/// 
/// FirstRechargeExtraManager
///
class FirstRechargeExtraManager : public LazySingleton<FirstRechargeExtraManager>
{
public:
    FirstRechargeExtraManager();
    ~FirstRechargeExtraManager();

    void TestData();
    void LoadData(const FirstRechargeExtraNetworkData& data, bool openUI);
    FirstRechargeExtraNetworkData& GetData();

    void SetOpenUI(bool shouldOpen);
    int GetCurrentIndex(int index);
    bool IsBonusReadyGot(int index);
    int IsBonusReadyGot();
    int FindFirstLockTab();
    bool IsNoRecharge();
    bool IsValid(int index);
    std::vector<FirstRechargeExtraBonusData> GetBonusList(int index);
    void RequestNetwork();
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    FirstRechargeExtraNetworkData m_data;
    bool m_shouldOpenUI;
};

///
/// FirstRechargeExtraDayWidget
///
class FirstRechargeExtraDayWidget : public Widget
{
public:
    FirstRechargeExtraDayWidget(int index, int tab);
    virtual ~FirstRechargeExtraDayWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;

    void SetHasGot(bool hasGot);
    void SetFrameEnable(bool hasFrame);
    void StartHasGotEffect();

private:
    Image* m_hasGotImage;// has got image
    Image* m_widget;// main pic
    Image* m_frameImage;// frame image

    bool m_frameEnable;// if show frame
    bool m_hasgotEnable;//if show has got

    int m_index;// the index day
    int m_tabIndex;// the tab index

    SexyString m_hasGotStr;// has got str
};

///
/// FirstRechargeTabButton
///
class FirstRechargeTabButton : public PVZ2UIButton, public ButtonListener
{
public:
	FirstRechargeTabButton(int buttonID);
	virtual ~FirstRechargeTabButton();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void SetSelected(bool select) { m_selected = select; }
    bool IsSelected() const { return m_selected; }
    void SetHasGot(bool got) { m_hasGot = got; }
    bool IsHasGot() const { return m_hasGot; }

protected:
    int m_buttonID;
    int m_index;// challenge index
    bool m_selected;// is selected.
    bool m_hasGot;
    Image* m_bgPress;
    Image* m_bgUnpress;
    SexyString m_hasGotStr;
};

///
/// FirstRechargeExtraUI
///
class FirstRechargeExtraUI : public UISingletonDialog<FirstRechargeExtraUI>
{
public:
    FirstRechargeExtraUI();
    ~FirstRechargeExtraUI();

	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UIFirstRechargeExtraNew"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							ButtonDepress(int i_id) override;

    void UpdateUI(const FirstRechargeExtraNetworkData& i_data);
    void InitView();

private:
    void UpdateBonusWidgets(const FirstRechargeExtraNetworkData& data);
    void UpdateBottomWidgets(bool hasgot, int currentIndex, int tab);// update bottom widgets (eg. hasgotText, rechargeBtn, gotBonusBtn)
    void ShowChooseBonus(std::vector<S2C_BonusInfo> bonuslist);
    void GotBonus(int index, int tab);
    void RequestNetwork(int index, std::vector<S2C_BonusInfo> bonuslist, int tab, int day);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void ClickTabButton(int index);

    std::vector<class FirstRechargeExtraDayWidget*> m_bonusWidgets;
    std::vector<std::vector<class FirstRechargeExtraDayWidget*>> m_bonusWidgetsList;

    Sexy::Widget* m_hasgotTextWidget;// has got text
    Sexy::Widget* m_rechargeBtn;// recharge btn
    Sexy::Widget* m_gotBonusBtn;// got bonus btn

    std::vector<Sexy::Widget*> m_hasgotTextWidgetList;
    std::vector<Sexy::Widget*> m_rechargeBtnList;
    std::vector<Sexy::Widget*> m_gotBonusBtnList;
    std::vector<Sexy::Widget*> m_containerList;
    std::vector<FirstRechargeTabButton*> m_buttonList;

    int m_currentTab;
};

class S2C_FirstRechargeExtraBonusData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_FirstRechargeExtraBonusData, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> m_bonuslist;
};

#endif /* FIRSTRECHARGEEXTRA_H_ */
