/*
 * SecretGachaMgr.h
 *
 *  Created on: 2020-3-17
 *      Author: Administrator
 */

#ifndef SECRETGACHAMGR_H_
#define SECRETGACHAMGR_H_

#include "Singleton.h"
#include "LawnAppEnums.h"
#include "NetworkData.h"
#include "DNode/DNodeWidget.h"

namespace Message
{
	void NotifySecretGachaChangePlant(int i_selectId);
}

class UISecretGachaDetail:public DNodeWidget
{
public:
    static UISecretGachaDetail* create(const std::vector<int>& i_plantList, const std::vector<int>& i_pieceList, bool focus = true);

    UISecretGachaDetail();
    virtual ~UISecretGachaDetail();

    virtual void Initialize() override;

    virtual void UserInit() override;

	void updateInfo();
	void updateItems(const std::vector<int>& list);

public:
    static UISecretGachaDetail* s_pWidgetHandler;
    std::vector<int>            m_plantslist;
	std::vector<int>            m_pieceslist;
};

class UISecretGachaChangePlant:public DNodeWidget
{
public:
    static UISecretGachaChangePlant* create(int i_selectId, const std::vector<int>& list,bool focus = true);

    UISecretGachaChangePlant();
    virtual ~UISecretGachaChangePlant();

    virtual void Initialize() override;

    virtual void UserInit() override;

    void updateSelectBox(int i_selectId);

    void ChangeReward(int i_selectId);

public:
    static UISecretGachaChangePlant* s_pWidgetHandler;
    std::vector<int>          m_list;
    int m_selectId;
};

class UISecretGacha:public DNodeWidget
{
public:
    static UISecretGacha* create(const Rect& rect);
    static UISecretGacha* get();

    UISecretGacha();
    virtual ~UISecretGacha();

    virtual void Initialize() override;
    virtual void UserInit() override;

    void  removeFromParent();

    void Update() override;

private:
    void DoConfirmDialog(float i_cost, bool i_drawTicket);
    void ConfirmBuyGacha();
    bool canGacha(bool i_singleDraw);
    bool gachaAgain();
    void CancelBuy();
    void createIcons(bool i_main);
    void createBtns(bool i_singleDraw);
    void refreshBtns(bool i_singleDraw);
    void refreshTicket();
    void updateBtnState(bool i_singleDraw, bool i_ticket);
    void syncActivity();
    void showOverview();
    void onNotifySecretGachaChangePlant(int i_selectId);
    void getLists(std::vector<int>& i_mainList, std::vector<int>& i_subList);

    static UISecretGacha* s_pWidgetHandler;
    time_t m_expireTime;
    int m_cost;
    int m_actId;
    int m_tempCost;
    int m_tempActId;
};

struct SecretGachaItem
{
	SecretGachaItem(int i_id, int i_quantity)
	{
		ObjectId = i_id;
		Amount = i_quantity;
	}

	SecretGachaItem()
	{
		ObjectId = 0;
		Amount = 0;
	}
	int ObjectId;
	int Amount;
};

class NetworkSecretGachaInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkSecretGachaInfo, Sexy::RtObject, Sexy::RtClass);

public:
    int mainObjectId;
    std::vector<SecretGachaItem> subObjectIds;
    int drawPrice;
    int multiDrawPrice;
    std::vector<int> mainObjectIds;
    int expireTime;
    bool isMonthlyCard;
};

class NetworkChangeSecretGachaInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkChangeSecretGachaInfo, INetworkData, RtClass);

public:
	int selectId;
};

class SecretGachaMgr : public LazySingleton <SecretGachaMgr>
{
public:
	SecretGachaMgr();
    ~SecretGachaMgr();

    void CreateMainUI(const Rect &i_rect, Widget* i_parent);
    void RemoveMainUI();

    bool NeedInit();
    void RequestGachaInit();
    bool GetDelayDialog() { return m_delayDialog; }
	void SetDelayDialog(bool i_delay) { m_delayDialog = i_delay; }
	void PopDelayDialog();
	void Update();
	const NetworkSecretGachaInfo& GetGachaInfo() { return m_info; }
	void SetSelectId(int i_selectId);
	std::string GetScreenType();
	bool IsUIActive();

private:
	bool m_delayDialog;
	NetworkSecretGachaInfo m_info;
	pvztime_t m_requestTime;

    void RefreshActivity();
    void SyncActivityData(const NetworkSecretGachaInfo& i_data);
    void OnNetworkError(int erroId, const std::string& i_reqID);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    void InitTestData();
};


#endif /* SECRETGACHAMGR_H_ */
