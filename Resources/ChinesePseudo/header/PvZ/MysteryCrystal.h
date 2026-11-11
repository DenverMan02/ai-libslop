/*
 * MysteryCrystal.h
 *
 *  Created on: 2020-7-27
 *      Author: Administrator
 */

#ifndef MYSTERYCRYSTAL_H_
#define MYSTERYCRYSTAL_H_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "DNode/DNodeWidget.h"

struct StoreData
{
	StoreData()
	{
		m_objectId = 0;
		m_price = 0;
	}

	int m_objectId;
	int m_price;
};

class NetworkGetMysteryStore : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkGetMysteryStore, INetworkData, RtClass);

public:
	std::vector<std::vector<StoreData>> StoreInfos;
	std::vector<int> PurchasedInfos;
	int GainedMaterials;
	int GainedLimit;
};

class MysteryCrystalMgr : public LazySingleton <MysteryCrystalMgr>
{
public:
	MysteryCrystalMgr();
    ~MysteryCrystalMgr();

    void TryAwards();

    void RequestGetStore();
    void Init(bool i_openUI = true);

    const std::vector<StoreData>& GetPlantList(int i_type);
    const std::vector<int>& GetPurchasedList();
    int GetWeeklyGainedLimit();
    int GetCurrentGained();
    void AddToCurrentGained(int i_amount);
    int GetDropAmount(bool i_hard);
    bool CanAwards(int i_amount);
    int GetRealDropAmount(int i_initAmt);

private:
    bool CanAwards();

    void initTestData();
    bool loadTest();
    bool Load();
    void requestTryAward(const std::vector<NetworkItemInfo>& i_infos);

    NetworkGetMysteryStore m_info;
};

class UIMysteryStore:public DNodeWidget
{
public:
    static UIMysteryStore* create(bool focus = true);

    UIMysteryStore();
    virtual ~UIMysteryStore();

    virtual void Initialize() override;

    virtual void UserInit() override;

    static UIMysteryStore* s_pWidgetHandler;

    void Update() override;

private:
    void updatePlantsShow(int i_mode);
	void updateItems(const std::vector<StoreData>& list);
	void updatePlantList(int i_mode);
	void updateSelectBox(const std::vector<int>& list);
	void UpdateTime();

	std::string getContentBgImg(int i_rare);
	void tryBuyItem(int i_itemId, int i_price);
	void showShopConfirm(int i_itemId);
	void showMaterialShopConfirm();
	void showOverview();
	void onConfirmBuy();
	void onConfirmToStore();
	void onShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);
	void onItemPurchased(int i_itemId);
	void onPaySuccess();
	void OnNotifyFreeItemGot(const std::string& i_type);
    void onADFinished(int i_type);

	void SyncRefreshTime();
	void SyncMaterial();
	void SyncPurchasedList();

    std::vector<StoreData> m_plantList;
    std::vector<int> m_purchasedPlantList;
    int m_itemId;
    int m_mode;
    time_t m_refreshTime;
};

#endif /* MYSTERYCRYSTAL_H_ */
