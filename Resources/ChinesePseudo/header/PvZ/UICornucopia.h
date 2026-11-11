/*
 * UICornucopia.h
 *
 *  Created on: 2023-3-21
 *      Author: zhousen
 */

#ifndef UICORNUCOPIA_H_
#define UICORNUCOPIA_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "UIListener.h"
#include "RepeatUIComponent.h"
#include "NameMapperEnum.h"

class TouchWidget;

namespace Message
{
	void CornucopiaBubbleGenerate();
    void NewTreasureBuyPrivilege();//新宝藏购买特权
    void NewTreasureBuyBundle(int i_index);//新宝藏购买包
}

//////////////////////////////////////////////
/// Cornucopia Data
//////////////////////////////////////////////
struct CornucopiaShopItemData
{
	CornucopiaShopItemData() {
		m_iObjId = 0;
		m_iQuantity = 0;
		m_iPrice = 0;
		m_iBuyTimes = 0;
		m_iBuyTImesMax = 0;
		m_currencyType = id_mat_cornucopia_emblem;
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

// this should be moved to v303 main data.
class CornucopiaData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CornucopiaData, INetworkData, RtClass);

    CornucopiaData() {
    	m_currentActivityID = 0;
    	m_isSettle = false;
    	m_resourceID = 0;
    	m_isGetReward = false;
    	m_presentList.clear();
    	m_presentLeftCountList.clear();
    	m_tickets = 0;
    	m_emblems = 0;
    	m_playerGachaCount = 0;
    	m_isOnLeaderboard = true;
    	m_maxExp = 0;
    	m_currentExp = 0;
    	m_level = 0;
    	m_rank = 0;
    	m_shopDataList.clear();
    	m_serverTotalGem = 100;
    	m_bubbleHarvestList.clear();
    	m_bubbleStandbyIndex = 0;
    	m_bubbleStandbyCountdownTime = 0;
    	m_bubbleTimeList.clear();
    	m_bubbleRealTimeList.clear();
    	m_rewardPreviewList.clear();
    	m_rankReward = 0;
    	m_activityExpireTime = 0;
    }

    int m_currentActivityID;// current period activity round.
    bool m_isSettle;// check if in settle.
    int m_resourceID;// for difficulty version.
    std::map<std::string, int> m_taskInfos;// for tasks
    bool m_isGetReward;// check is get reward
    std::vector<std::vector<S2C_BonusInfo>> m_presentList;// present list
    std::vector<int> m_presentLeftCountList;// present buy left count list
    int m_tickets;// for gacha
    int m_emblems;// for shop buy items
    int m_playerGachaCount;// how many times player has gacha
    bool m_isOnLeaderboard;// check is on leaderboarder
    int m_maxExp;// max exp
    int m_currentExp;// current exp
    int m_level;// level
    int m_rank;// rank (only used when is on leaderboarder)
    std::vector<CornucopiaShopItemData> m_shopDataList;// shop list
    int m_serverTotalGem;// server total progress
    std::vector<struct CornucopiaBubbleHarvestData> m_bubbleHarvestList;// bubble harvest list
    int m_bubbleStandbyIndex;// the index of standby bubble
    time_t m_bubbleStandbyCountdownTime;// the standby countdown time.
    std::vector<std::string> m_bubbleTimeList;// bubble count down time list for different level
    std::vector<int> m_bubbleRealTimeList;// each level countdown time (seconds.)
    std::vector<int> m_rewardPreviewList;// reward preview list
    int m_rankReward;// rank reward gems.
    int m_activityExpireTime;// activity expire time.
};

class CornucopiaGachaData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CornucopiaGachaData, INetworkData, RtClass);

    CornucopiaGachaData() {
    	m_bonusList.clear();
    	m_tickets = 0;
    	m_emblems = 0;
    	m_playerTotalGachaCount = 0;
    	m_serverTotalGems = 0;
    }

    std::vector<S2C_BonusInfo> m_bonusList;
    int m_tickets;
    int m_emblems;
    int m_playerTotalGachaCount;
    int m_serverTotalGems;
};

struct CornucopiaBubbleHarvestData
{
	CornucopiaBubbleHarvestData() {
		m_objectId = 0;
		m_quantity = 0;
		m_key = 0;
	}

	int m_objectId;
	int m_quantity;
	int m_key;// which slot is harvest bubble
};

class CornucopiaBubbleRewardData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CornucopiaBubbleRewardData, INetworkData, RtClass);

    CornucopiaBubbleRewardData() {
    	m_bonusList.clear();
    	m_bubbleHarvestList.clear();
    	m_bubbleStandbyIndex = 0;
    	m_bubbleStandbyCountdownTime = 0;
    	m_tickets = 0;
    }

    std::vector<S2C_BonusInfo> m_bonusList;
    std::vector<CornucopiaBubbleHarvestData> m_bubbleHarvestList;
    int m_bubbleStandbyIndex;// which slot should show countdown.
    time_t m_bubbleStandbyCountdownTime;
    int m_tickets;
};

struct CornucopiaPresentData
{
	std::vector<S2C_BonusInfo> m_bonusList;

    CornucopiaPresentData() {
    	m_bonusList.clear();
    }
};

struct CornucopiaRankData
{
    int Rank = 0;
    std::string Name;
    int HeadShotID = 0;
    int GachaCount = 0;
};

class CornucopiaLeaderBoardData : public INetworkData
{
public:
    RT_CLASS_DEFINE(CornucopiaLeaderBoardData, INetworkData, RtClass);

    CornucopiaLeaderBoardData() {
    	m_rankList.clear();
    }

    std::vector<CornucopiaRankData> m_rankList;
};

/////

//////////////////////////////////////////////
/// Task
//////////////////////////////////////////////


//////////////////////////////////////////////
/// Present Shop
//////////////////////////////////////////////
class NewTreasureWidget : public TemplateBundleWidget
{
public:
    NewTreasureWidget();
    virtual ~NewTreasureWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Init(int i_index) override;

protected:
    virtual void UpdateButtonState() override;
    virtual void DrawBundleCenter(Sexy::Graphics* i_g) override;
    virtual void OnPurchaseButtonDepress() override;

    void BuyConfirm(class UIMessageBox* box, int buttonID);
    void OnBuyExp(int i_index);
};

//////////////////////////////////////////////
/// Rank
//////////////////////////////////////////////
class CornucopiaTurnPagesItem : public Widget
{
public:
    void InitView(int i_rank, const CornucopiaRankData& i_data);
    virtual void Draw(Graphics* i_g) override;

protected:
    int m_rank;
    SexyString m_name;
    SexyString m_gachaStr;
    SexyString m_dummyStr;
    CornucopiaRankData m_data;
    bool m_isDummy;
};

class UICornucopiaTurnPagesList : public UISingletonDialog<UICornucopiaTurnPagesList>, public Sexy::ScrollWidgetListener
{
public:
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UITurnPages"; }
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitData(const std::vector<CornucopiaRankData>& i_list, int i_start);
    void ChangePage(int i_index);

public:
    int m_index;
    int m_start;
    std::vector<CornucopiaRankData> m_rankData;
};

//////////////////////////////////////////////
/// Shop
//////////////////////////////////////////////
class CornucopiaShopButton : public PVZ2UIButton, public ButtonListener
{
public:
    typedef Delegate0 CornucopiaShopCallback;
    CornucopiaShopButton(int buttonID);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void SetCurrencyImage(Image* img) { _currencyImage = img; }
    void SetItemAmount(int amount);
    void SetClickCallback(CornucopiaShopCallback callback){ _callback = callback; }

protected:
    void BuyConfirm(class UIMessageBox* box, int buttonID);

protected:
    Rect _currencyImgRect;// the rect render currency img
    Rect _amountStrRect;// the rect render amount str.
    Image* _currencyImage;// item currenty image
    SexyString _amountStr;// item amount str
    CornucopiaShopCallback _callback;// click callback
};

class CornucopiaShopCommonWidget : public CommonRewardItemWidget
{
public:
	CornucopiaShopCommonWidget(int index);
	virtual ~CornucopiaShopCommonWidget();

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

protected:
    virtual void init() override;
    virtual void ClickCallback();
    virtual void InitButton();

protected:
    SexyString _buyTimeStr;
    SexyString _nolimitBuyTimeStr;
    bool _isArtifact;
    int _buyTimes;
    int _buyTimesMax;
    int _index;// item index in bonuslist
	int _itemStatus;// RiftaShopItemData.BtnStatus
    int _lockDescriptionIndex;// the index of the
	SexyString _lockDescription;//it's item locked description
    bool _drawAmount;// chekc if should draw item amount
    SexyString _amountString;// item amount string
    int _offsetY;// control all ui y offset
    CornucopiaShopButton* _button;// if this widget can buy, then show this button
};

/////////////////////////////////////////
/// Server Total Gems Tips Button
/////////////////////////////////////////
class CornucopiaProgressTipsUI : public TouchWidget
{
public:
	CornucopiaProgressTipsUI();
    virtual ~CornucopiaProgressTipsUI();

    virtual void Draw(Sexy::Graphics* i_g) override;

protected:
	Sexy::Image* m_image;
};

/////////////////////////////////////////////
/// CornucopiaBubbleWidget
/////////////////////////////////////////////
class CornucopiaBubbleWidget : public Sexy::Widget
{
public:
	CornucopiaBubbleWidget(int index, time_t endTime = 0);
	virtual ~CornucopiaBubbleWidget();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;

    int GetIndex() const { return m_index; }

protected:
    void InitView();
	void BubbleReward(int index);
	void RequestBubbleReward(int index);
	void BubbleRewardConfirm(UIMessageBox* box, int buttonID);
	SexyString CalcCountdownTime(time_t endTime);
	int CheckHarvest(std::vector<CornucopiaBubbleHarvestData> dataList);// return the index of bubbleharvestdata

protected:
    Image* m_bgImage;
    Image* m_bubbleImage;
    Image* m_countDownBgImage;
    Image* m_harvestBgImage;

    SexyString m_countDownStr;
    SexyString m_harvestStr;

    int m_touchId;
    int m_index;
    bool m_isHarvest;// if is harvest bubble
    time_t m_endTime;// only used when it is a standby bubble.
    S2C_BonusInfo m_bonus;
};

/////////////////////////////////////////////
/// CornucopiaTaskWidget
//////////////////////////////////////////////

class CornucopiaTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(CornucopiaTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;

protected:
    virtual void RequestReward() override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g);

};

/////////////////////////////////////////////
/// Cornucopia Main
//////////////////////////////////////////////
class UICornucopia : public UISingletonDialog<UICornucopia>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
	enum {
		Cornucopia_TimeLeftType_Invalid = -1,
		Cornucopia_TimeLeftType_Cornucopia,// activity expire time
		Cornucopia_TimeLeftType_Task,// task expire time
		Cornucopia_TimeLeftType_Present,// present expire time
		Cornucopia_TimeLeftType_Shop,// shop expire time
		Cornucopia_TimeLeftType_LeaderBoard,// leaderboard expire time
		Cornucopia_TimeLeftType_Max,
	};

	UICornucopia();
    virtual ~UICornucopia();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UICornucopia"; }
    virtual void                            Update() override;
	virtual void							ButtonDepress(int i_id) override;

    virtual void TabSelectionChanged(int tabID);
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitBubble();
	void RefreshTickets();
    void RefreshMaterial();
    bool IsGachaAnimationPlay() { return m_isGachaAnimationPlay; }

private:
	void UpdateTimer();
	void UpdateQuit();

	void ShowMainTips();
	void CloseMainTips();
	void ShowRewardPreview();
	void EnableGachaButtonStatus(bool status);

	void RefreshTotalGacha();
	void RefreshHarvestLimitTime();
	void RefreshPlayerLevel();
	void RefreshCornucoppiaProgress();
	void RefreshNextLevelProgress();
	void RefreshGiftDesc();
	void RefreshMask();

	void InitGachaButtons();
	void InitCornucopiaProgressTips();
	int GetServerTotalIndex(int gems);
	void GoToTaskView();
	void GoToShopView();

    void InitShopWidgets(const CornucopiaData& i_data);
    void OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void UpdateShopUI(const CornucopiaData& i_data);

    void CloseRewardDisplay();
	void GachaForItems(int count);
	void RequestGachaItems(int count);
	void GachaConfirm(UIMessageBox* box, int buttonID);

	void BubbleGenerate(int index, time_t endTime);
	void OnBubbleGenerate();
	int FindEmptySlot();
	bool IsSlotUse(int index);

	void InitGift();
	void GiftReward();
	void RequestGiftLeaderBoard(int index);
    std::vector<CornucopiaRankData> FillLeaderBoardDummyData(std::vector<CornucopiaRankData>& datalist, int maxSize);

    void InitPresent();
    void InitTasks();
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void SetExpireTimeType(int type);

private:
    class ActivityDescriptionUI* m_descriptionUI;// main tips ui.
    CornucopiaProgressTipsUI* m_cornucopiaProgressTipsUI;
    int m_gachaCount;
    std::vector<class CornucopiaShopCommonWidget*> m_vecWidget;// shop items.
    std::vector<S2C_BonusInfo> m_gachaBonusList;
    std::vector<CornucopiaBubbleWidget*> m_bubbleWidgetList;// bubble widget list
    int m_gachaType;// 1 : gacha, 0 : bubble
    int m_expireType;// show expire time type.
    time_t m_activityExpireTime;// activity expire time.
    time_t m_settleExpireTime;// for shop and leaderboard expire time.
    UIWidgetText* m_countdownTimerText;
    bool m_isGachaAnimationPlay;
    bool m_autoInitMask;
};

class CornucopiaMgr : public LazySingleton<CornucopiaMgr>
{
public:
	CornucopiaMgr();
	virtual ~CornucopiaMgr();

    void LoadData(const CornucopiaData& data);
    const CornucopiaData& GetData() const;

    void RequestNetwork();

private:
    void TestData();

private:
    CornucopiaData m_data;
};


#endif /* UICORNUCOPIA_H_ */
