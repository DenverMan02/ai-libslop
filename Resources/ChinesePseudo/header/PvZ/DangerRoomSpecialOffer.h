/*
 * DangerRoomSpecialOffer.h
 *
 *  Created on: 2020-1-4
 *      Author: Administrator
 */

#ifndef DANGERROOMSPECIALOFFER_H_
#define DANGERROOMSPECIALOFFER_H_

#include "NetworkData.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"

namespace Message
{
	void NotifyPurchasedDangerRoomSpecialOffer();
}

class NetworkDangerRoomSpecialOfferInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkDangerRoomSpecialOfferInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<class DangerRoomSpecialOfferConfig> m_infos;
};

struct DangerRoomSpecialOfferInfo
{
	DangerRoomSpecialOfferInfo()
	{
		PlantId = 0;
		PlantLevel = 1;
		EndTime = 0;
		GemNum = 0;
		BundleId = 0;
		OrgPrice = 0;
	}

	int PlantId;
	int PlantLevel;
	time_t EndTime;
	int GemNum;
	int BundleId;
	int OrgPrice;
};

struct DangerRoomBuyOfferInfo
{
	DangerRoomBuyOfferInfo()
	{
		ObjectId = 0;
		Amount = 0;
	}
	int ObjectId;
	int Amount;
};

class NetworkDangerRoomOfferInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkDangerRoomOfferInfo, Sexy::RtObject, Sexy::RtClass);

public:
    int plantId;
    int gemNum;
};

class NetworkDangerRoomBuyOfferInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkDangerRoomBuyOfferInfo, INetworkData, RtClass);

public:
	std::vector<DangerRoomBuyOfferInfo> itemInfos;
};

class DangerRoomSpecialOfferUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	DangerRoomSpecialOfferUI();
    ~DangerRoomSpecialOfferUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void 	DrawOverlay(Sexy::Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView();
	void InitTestData();
	ImagePtr GetImgPtrFromObjectId(int i_objectId);

	void RefreshActivity();
	void SyncActivityData(int i_bundleId, int i_plantId, int i_plantLevel, time_t i_endTime, int i_gemNum, int i_orgPrice);

	static void RequestNetwork();
	static void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	static void onMsgErrorRequest(int erroId, const std::string& i_reqID);
	static void setUnactive();
	static bool isActive(){return s_isActive;}

private:
	// main board
	Rect m_dialogRect;
	// plant detail & avatar detail
	Image* m_plantImg;
	Rect m_plantImgRect;
	// left time
	Rect m_leftTimeRect;
	// network detail
	DangerRoomSpecialOfferInfo m_info;
	// purchase button
	PVZ2UIButton* m_purchaseBtn;
	Rect m_crossRect;
	// main bg
	Image* m_mainBg;
	Rect m_mainBgRect;
	// banner
	Image* m_bannerImg;
	Rect m_bannerRect;
	// title
	Image* m_titleImg;
	Rect m_titleRect;
	// title text
	Rect m_titleTextRect;
	// gray bg
	Image* m_grayBg;
	Rect m_grayBgRect;
	// label
	Image* m_labelImg;
	Rect m_labelRect;
	// label text
	SexyString m_labelName;
	Rect m_labelTextRect;
	// bundle img
	Image* m_bundleImg;
	Rect m_bundleRect;
	// level img
	Image* m_levelImg;
	Rect m_levelRect;

	// bundle text
	SexyString m_bundleName;
	Rect m_bundleTextRect;

	SexyString m_gemText;
	Rect m_gemTextRect;
	bool m_hasPurchased;

	static bool s_isActive;
};

class DangerRoomOfferMgr : public LazySingleton <DangerRoomOfferMgr>
{
public:
	DangerRoomOfferMgr();
    ~DangerRoomOfferMgr();

    void BuyOffer(const std::string& i_sku, const DangerRoomSpecialOfferInfo& i_info);
    void requestBuyOffer(const std::string& i_sku, bool i_restore);

    int GetTargetBundlePrice(int i_bundleId);
    std::string GetTargetBundleSku(int i_bundleId);

    void SetIsPopBehavior(bool i_pop) { m_isPopBehavior = i_pop; }
    bool GetIsPopBehavior() { return m_isPopBehavior; }

    bool IsUIActive();

private:
    void onNotifyBundlePurchased(int i_type, const std::vector<PaymentBundleInfo>& i_infos);

    DangerRoomSpecialOfferInfo m_info;
    bool m_isPopBehavior;
};


#endif /* DANGERROOMSPECIALOFFER_H_ */
