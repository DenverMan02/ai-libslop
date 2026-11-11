/*
 * UICardGameReward.h
 *
 *  Created on: 2022-7-12
 *      Author: admin
 */

#ifndef UICARDGAMEREWARD_H_
#define UICARDGAMEREWARD_H_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "CardGameNetworkMgr.h"
#include "CardGameUtils.h"

class UICardGameRewardScrollPanel : public UISingletonDialog<UICardGameRewardScrollPanel>
{
public:
	UICardGameRewardScrollPanel();
	virtual ~UICardGameRewardScrollPanel();
	void UpdateUI(PVZ2UIScrollingWidget* i_scrollWidget);

	virtual std::string GetLayoutName() override { return "UICardGameRewardScrollPanel"; }
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
	std::vector<CardGameStarRewardData> StarRewardInfo;
//	bool test = true;

};

class UICardGameReward : public UISingletonDialog<UICardGameReward>, public Sexy::ScrollWidgetListener
{
public:
	UICardGameReward();
	virtual ~UICardGameReward();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UICardGameReward"; }
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
	class UICardGameRewardScrollPanel* m_defaultPanel;
	int num = 7;//奖励总数
	int currentUnlockNum = 1;//当前已解锁个数
	float starNum = 7;//星星数
	float allStarNum = 21;//星星最大值
};

struct NetworkCardGameRewardContent
{
    int         m_count;
    int			m_objectId;

    NetworkCardGameRewardContent()
    {
        m_count = 0;
        m_objectId = 0;
    }
};

class NetworkCardGameReward : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkCardGameReward, Sexy::RtObject, Sexy::RtClass);

public:
	std::vector<std::vector<NetworkCardGameRewardContent>> m_contents;
	std::vector<int> m_purchasedPresent;
	std::vector<int> m_orgPrices;
};

struct CardGameRewardDetail
{
	CardGameRewardDetail()
	{
//		BonusContent;
	}

	std::vector<S2C_BonusInfo> BonusContent;
};

class New_S2C_BuyCardGameReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_BuyCardGameReward, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> BonusList;
};

class CardGameRewardMgr : public LazySingleton <CardGameRewardMgr>
{
public:
	CardGameRewardMgr();
    ~CardGameRewardMgr();
//    void OnExchangeFinish(bool success,const std::vector<S2C_BonusInfo>* i_BonusContent);
    void OnExchangeFinish(bool success,const New_S2C_BuyCardGameReward* pData);
    bool Load();
    void Init();
    void RequestNetwork();
    void SyncActivityData(const NetworkCardGameReward& i_data);
    void RequestCardGameReward(const std::string& world, int index);

private:
    void onResultClosed();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    CardGameRewardDetail BonusContents;
    int m_currentPurchasedIndex;
    bool m_requested;
    bool m_resultCreated;
};

namespace Message
{
	void CardGameRewardClose();
	void NotifyCardGameRewardDetails(bool success,const New_S2C_BuyCardGameReward* pData);
}

#endif /* UICARDGAMEREWARD_H_ */
