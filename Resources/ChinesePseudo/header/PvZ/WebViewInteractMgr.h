/*
 * WebViewInteractMgr.h
 *
 *  Created on: 2018-10-8
 *      Author: Administrator
 */

#ifndef WEBVIEWINTERACTMGR_H_
#define WEBVIEWINTERACTMGR_H_

#include "Singleton.h"
#include "LawnAppEnums.h"
#include "NetworkData.h"
#include "EASquared.h"

class NetworkWebCallSettlement : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkWebCallSettlement, INetworkData, RtClass);

public:
    int PlayCount;
};

struct LotteryInfo
{
	LotteryInfo()
	{
		Id = 0;
		Quantity = 0;
	}
	int Id;
	int Quantity;
};

class NetworkWebCallLottery : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkWebCallLottery, INetworkData, RtClass);

public:
    LotteryInfo Info;
    int Index;
};

class NetworkWebCallScoreStoreInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkWebCallScoreStoreInfo, INetworkData, RtClass);

public:
    std::string StoreInfo;
};

class NetworkWebCallScoreStoreBuy : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkWebCallScoreStoreBuy, INetworkData, RtClass);

public:
    int Id;
    int ConsumeScore;
    int PreviousScore;
};

class NetworkWebCallAddPlayCount : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkWebCallAddPlayCount, INetworkData, RtClass);

public:
    int PlayCount;
};

class WebInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(WebInfo, Sexy::RtObject, Sexy::RtClass);

public:
    int totalScore;
    int plantId;
    int zombieId;
    int playCount;
    std::string rewardInfo;
    int buyTimes;
    int tutorial;
};

class WebViewInteractMgr : public LazySingleton <WebViewInteractMgr>
{
public:
	WebViewInteractMgr();
    ~WebViewInteractMgr();

    void RequestNetwork();
    void RefreshActivity();

    void CallSettlement(std::string i_key, int i_score, int i_houseId, int i_tombStoneId);
    void CallLottery(std::string i_key);
    void CallScoreStoreInfo(std::string i_key);
    void CallScoreStoreBuy(std::string i_key, int i_id);
    void CallConsumeCash(std::string i_key, int i_num, int i_id);
    void CallCloseWebView();
    void CallOpenAd();
    void CallAddPlayCount();
    void CallAddPlayTimes(std::string i_key, int i_num, int i_id);

    void UpdateConsumeCashLog(int i_num, int i_id);
    void UpdateScoreStoreBuyLog(int i_id, int i_consumeScore, int i_previousScore);
    void UpdateSettlementLog(int i_score);
    void UpdateLotteryLog(int i_id, int i_quantity);
    void UpdateAddPlayTimesLog(int i_num);
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    std::string CreateRequestURL(const WebInfo& i_data);
    void onWatchedAD(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    void TryShowWebView();
    void RequestAddPlayTimes(int i_num);
    //void SyncActivityData(const WebInfo& i_data);

    std::string m_key;
    WebInfo m_data;
    bool m_requested;
    int m_totalScore;
    int m_accScore;
    int m_consumeNum;

//private:
//    void SyncActivityData(const GemOfferInfo& i_data);
};

#endif /* WEBVIEWINTERACTMGR_H_ */
