/*
 * UISecretAreaReward.h
 *
 *  Created on: 2022-3-21
 *      Author: Bob
 */

#ifndef UISECRETAREAREWARD_H_
#define UISECRETAREAREWARD_H_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "PVZ2UnchartedModeNetworkMgr.h"
#include "PVZ2UnchartedModeUtils.h"

namespace Message
{
	void SecretAreaRewardClose();
}

class UISecretAreaRewardScrollPanel : public UISingletonDialog<UISecretAreaRewardScrollPanel>
{
public:
	UISecretAreaRewardScrollPanel();
	virtual ~UISecretAreaRewardScrollPanel();
	void UpdateUI(PVZ2UIScrollingWidget* i_scrollWidget);

	virtual std::string GetLayoutName() override { return "UISecretAreaRewardScrollPanel"; }
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;



private:
	class NewerPresentButton* AddButton(Widget* i_parent, int i_id, const std::string & normalImgPath, const std::string & downImgPath,
			int x, int y, int width, int height, Sexy::ButtonListener* i_listener);
	class NewerPresentImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y, int width, int height);
	class NewerPresentImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y);
	class NewerPresentText* AddText(Widget* i_parent, const SexyString& i_text, int x, int y, int width, int height);


	int num = 7;//奖励总数
	int currentUnlockNum = 1;//当前已解锁个数
	float starNum = 7;//星星数
	float allStarNum = 21;//星星最大值
	std::vector<UnchartedModeStarRewardData> StarRewardInfo;
//	bool test = true;

};

class UISecretAreaReward : public UISingletonDialog<UISecretAreaReward>, public Sexy::ScrollWidgetListener
{
public:
	UISecretAreaReward();
	virtual ~UISecretAreaReward();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UISecretAreaReward"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void UpdateUI();
	void SetCurrent_num(int index) {Current_num = index;}
	int Current_num ; //当前传输的编号
private:
	void RefreshProgressBar();
	class PVZ2UIScrollingWidget* m_defaultScollingWdget;
	class UISecretAreaRewardScrollPanel* m_defaultPanel;
	int num = 7;//奖励总数
	int currentUnlockNum = 1;//当前已解锁个数
	float starNum = 7;//星星数
	float allStarNum = 21;//星星最大值
};

struct NetworkSecretAreaRewardContent
{
    int         m_count;
    int			m_objectId;

    NetworkSecretAreaRewardContent()
    {
        m_count = 0;
        m_objectId = 0;
    }
};

class NetworkSecretAreaReward : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkSecretAreaReward, Sexy::RtObject, Sexy::RtClass);

public:
	std::vector<std::vector<NetworkSecretAreaRewardContent>> m_contents;
	std::vector<int> m_purchasedPresent;
	std::vector<int> m_orgPrices;
};

struct SecretAreaRewardDetail
{
	SecretAreaRewardDetail()
	{
//		BonusContent;
	}

	std::vector<S2C_BonusInfo> BonusContent;
};

//class UnchartedModeEndOfPlayData : public INetworkData
//{
//public:
//	RT_CLASS_DEFINE(UnchartedModeEndOfPlayData, INetworkData, RtClass);
//
//public:
//	std::vector<S2C_BonusInfo> BonusList;
//	std::vector<S2C_BonusInfo> ExtraBonusList;
//};

//class New_S2C_BuySecretAreaReward : public INetworkData
//{
//public:
//    RT_CLASS_DEFINE(New_S2C_BuySecretAreaReward, INetworkData, RtClass);
//
//    std::vector<S2C_BonusInfo> BonusList;
//};

class SecretAreaRewardMgr : public LazySingleton <SecretAreaRewardMgr>
{
public:
	SecretAreaRewardMgr();
    ~SecretAreaRewardMgr();
//    void OnExchangeFinish(bool success,const std::vector<S2C_BonusInfo>* i_BonusContent);
    void OnExchangeFinish(bool success,const New_S2C_BuySecretAreaReward* pData);
    bool Load();
    void Init();
    void RequestNetwork();
    void SyncActivityData(const NetworkSecretAreaReward& i_data);

private:
    void onResultClosed();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    SecretAreaRewardDetail BonusContents;
    int m_currentPurchasedIndex;
    bool m_requested;
    bool m_resultCreated;
};

// UI Uncharted Festival Reward Purchase
class UIUnchartedFestivalRewardPurchase : public UISingletonDialog<UIUnchartedFestivalRewardPurchase>
{
public:
	enum {
		FESTIVAL_REWARD_PURCHASE_CLOSE_BTN = 1000,
		FESTIVAL_REWARD_PURCHASE_BUY_BTN = 1001,
	};
	UIUnchartedFestivalRewardPurchase();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIUnchartedFestivalRewardPurchase"; }
	virtual void                ButtonDepress(int i_id) override;
};

class UIUnchartedFestivalReward : public UISingletonDialog<UIUnchartedFestivalReward>,  public Sexy::ScrollWidgetListener
{
public:
	enum {
		FESTIVAL_REWARD_CLOSE_BTN = 1000,
		FESTIVAL_REWARD_GET_ALL_BTN = 1001,
		FESTIVAL_REWARD_ACTIVATE_BTN = 1002,
		FESTIVAL_REWARD_GET_BTN,
	};

	UIUnchartedFestivalReward();
	~UIUnchartedFestivalReward();

	virtual bool                OnCreate() override;
	virtual void				Update() override;
	virtual std::string         GetLayoutName() override { return "UIUnchartedFestivalReward"; }
	virtual void                ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void UpdateFestivalRewardItemData();

private:
	void InitView();
	void UpdateCountDown();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

	void GetAllRewards();
    bool AllRewardsGot();
	void ShowGetAllRewardsConfirmDialog();
	void DetermineSelect(UIMessageBox* box, int buttonID);
	void UpdateCurrentReward();
    void FillPreview(Widget* i_widget, UnchartedModeFestivalRewardData& i_data, bool isNormal);

private:
	UIWidgetText* m_timeCountDownText;
	PVZ2UIButton* m_getAllRewardsBtn;
	PVZ2UIButton* m_activateBtn;
	UIWidgetImage* m_noticeImage;

	UIWidgetText* m_normalRewardText;
	UIWidgetText* m_advanceRewardText;
	Widget* m_normalRewardFrameParent;
	Widget* m_advanceRewardFrameParent;

    class PVZ2UIScrollingWidget* m_scrollWidget;
    std::vector<class UnchartedFestivalRewardItemWidget*> m_normalRewardList;
    std::vector<class UnchartedFestivalRewardItemWidget*> m_advanceRewardList;

    std::vector<UnchartedModeFestivalRewardData> m_data;

    std::vector<std::pair<int, int>> m_stepScrollOffset;
    int m_lastPreviewIndex;
};

// UnchartedFestivalRewardItemWidget
class UnchartedFestivalRewardItemWidget : public Widget, public Sexy::ButtonListener
{
public:
	UnchartedFestivalRewardItemWidget();
    virtual ~UnchartedFestivalRewardItemWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;

    void InitData(const UnchartedModeFestivalRewardData& i_data, int i_index, bool i_isNormal);
    void UpdateData(const UnchartedModeFestivalRewardData& i_data);
    void SetAwarded();

private:
    void SelectAndRequest();
    void DetermineSelect(class UIMessageBox* box, int buttonID);
    void RequestReward(int i_boxIndex = -1);// -1 = get all.

    int m_index;
    bool m_isNormal;
    bool m_awarded;
    int m_canGot;
    Image* m_starImage;
    SexyString m_starNumberStr;
    UnchartedModeFestivalRewardData m_data;
    class UIRewardFrameSelect* m_rewardFrame;
    PVZ2UIButton* m_receiveBtn;
    Rect m_rewardFrameRect;
};

// network data
class UnchartedFestivalRewardNetworkData : public INetworkData
{
public:
	RT_CLASS_DEFINE(UnchartedFestivalRewardNetworkData, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> RewardList;
};

#endif /* UISECRETAREAREWARD_H_ */
