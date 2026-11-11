//
//  PurchaseBroker.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PurchaseBroker__
#define __PlantsVersusZombies2__PurchaseBroker__

#include <string>
#include <map>
#include "SexyAppFramework/IPurchaseDriver.h"
#include "SexyAppFramework/RtDelegate.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include "PVZ2UIDialog.h"
#include "RvsChecker.h"
#include "PlayerInfo.h"

enum BundleInfoType
{
	Bundle_PlantSpecialOffer,
	Bundle_DangerRoomSpecialOffer,
	Bundle_RedPacket,
	Bundle_NewerPresent
};

struct CartInstanceInfo
{
	CartInstanceInfo()
	{
		IsCartActive = false;
	}
	
	std::string CartInstanceID;
	std::string CartEntrySource;
	std::string CartType;
	std::string CartSubType;
	bool		WasAnyPurchaseAttempted;
	bool		WasLastPurchaseSuccessful;
	bool		IsCartActive;
};

struct PaymentInfo
{
	PaymentInfo()
	{
		m_requestedSku = "";
		m_orderNumber = "";
	}

	std::string m_requestedSku;
	std::string m_orderNumber;
};

enum PurchaseState
{
	PURCHASESTATE_None,
    PURCHASESTATE_NeedToCheckRvs,
    PURCHASESTATE_CheckRvs,
	PURCHASESTATE_NeedToSendPurchase,
	PURCHASESTATE_WaitingForResponse,
	PURCHASESTATE_WaitingForValidate,
	PURCHASESTATE_CompleteValidate
};
//PVZ2_CHINESE_START
#ifdef HOST_ANDROID
	#include "SexyAppFramework/drivers/purchase/android/IPurchaseAdapter.h"

enum PurchaseChannel
{
	PURCHASE_NULL = 0,
	PURCHASE_CHINAMOBILE,
	PURCHASE_CHINAMOBILE_MM,
	PURCHASE_ALIPAY
};

/* Configuration for purchase platform
		ProvinceNull = 0,
		ProvinceBeijing = 10,
		ProvinceShanghai = 21,
		ProvinceTianjin = 22,
		ProvinceChongqing = 23,
		ProvinceHebei = 311,
		ProvinceZhejiang = 571,
		ProvinceLiaoning = 24,
		ProvinceHubei = 27,
		ProvinceJiangsu = 25,
		ProvinceJiangxi = 791,
		ProvinceShanxi = 351,
		ProvinceGansu = 931,
		ProvinceShandong = 531,
		ProvinceHeilongjiang = 451,
		ProvinceFujian = 591,
		ProvinceGuangdong = 20,
		ProvinceSichuan = 28,
		ProvinceHunan = 731,
		ProvinceHenan = 371,
		ProvinceYunnan = 871,
		ProvinceAnhui = 551,
		ProvinceJilin = 431,
		ProvinceGuangxi = 771,
		ProvinceGuizhou = 851,
		ProvinceShaanxi = 29,
		ProvinceQinghai = 971,
		ProvinceHainan = 898,
		ProvinceXizang = 891,
		ProvinceInnerMongolia = 471,
		ProvinceSinkiang = 991,
		ProvinceNingxia = 951",
 */
static int simSNProvinceMaps[] = {0, 10, 22, 311, 351, 471, 24, 431, 451, 21, 25, 571, 551, 591
		, 791, 531, 371, 27, 731, 20, 771, 898, 28, 851, 871, 891, 29, 931, 971, 951, 991, 23};

class PurchaseConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(PurchaseConfig, Sexy::RtObject, Sexy::RtClass);

	std::vector<int> MMPurchases;
	std::vector<int> AlipayPurchases;
	std::vector<int> NonePurchases;
	std::vector<int> ChinaMobilePurchases;
	std::string ErrorProvincePurchase;
	bool	 ShowPurchaseConfirm;

	PurchaseChannel GetPurchaseChannel(int i_province);
};
#endif

#ifdef HOST_ANDROID
static const PlatformType MONTHLYVIPCARD_CHANNEL_ID[] = {
	PLATFORM_CHINA_TELECOM_HD,
	PLATFORM_360_HD,
	PLATFORM_BUBUGAO_HD,
	PLATFORM_HUAWEI_HD,
	PLATFORM_OPPO_HD,
	PLATFORM_XIAOMI_HD,
	PLATFORM_ANZHI_HD,
	PLATFORM_UC_HD,
	PLATFORM_WANDOULABS_HD,
	PLATFORM_LESHI_HD,
	PLATFORM_LENOVO_HD,
	PLATFORM_4399_HD,
	PLATFORM_91_HD,
	PLATFORM_BAIDU_DUOKU_HD,
	PLATFORM_JINLI_HD,
	PLATFORM_POPCAP_HD,
	PLATFORM_SHOUGOU_HD,
	PLATFORM_DANGLE_HD,
	PLATFORM_YINGYONGHUI_HD,
	PLATFORM_MEIZU_HD,
	PLATFORM_YOUYI_HD,
	PLATFORM_MAOPAOTANG_HD,
	PLATFORM_TIANYIDA_HD,
	PLATFORM_TIANTIAN_HD,
	PLATFORM_CHUIZI_HD,
	PLATFORM_KUPAI_HD,
	PLATFORM_SHQC_HD
};

#endif

class PurchaseBroker : public Sexy::IPaymentMonitor
#ifdef HOST_IPHONEOS
      , public Sexy::NetworkServiceListener
#endif
//PVZ2_CHINESE_END
{
 public:
	enum ValidationResult
	{
		RESULT_PENDING = 0,
		RESULT_SUCCESS = 1,
		RESULT_COMPLETED_ORDER = 2
	};

	PurchaseBroker();
	virtual ~PurchaseBroker();
#ifdef HOST_IPHONEOS
    void ShowRestoreProduct();
    bool CheckUnfinishedPurchase();
    bool CheckRestorePurchase();
    void GetBackPurchase();
    void HandleRestoredPurchase();
	void Refresh();
	void onPurchaseRefreshComplete(Sexy::IPurchaseDriver* purchase_driver, bool bSuccess);
    void Init();
    bool IsRecieptUsed() { return m_recieptUsed; }
    void SetRecieptUsed(bool i_used) { m_recieptUsed = i_used; }
#endif

	void RequestPayment(const std::string& product_id, int objectId = 0);
	void ConfirmDelivery(const std::string&);
	void SetObjectId(int i_id) { m_objectId = i_id; }

#ifdef HOST_ANDROID
    void Init();
    void InitIMSIData();
    int GetSimProvince();
    PurchaseChannel GetPurchaseChannel();
    IPurchaseAdapter* GetPurchaseAdapter(PurchaseChannel i_purchaseChannel);
    void ResetPurchaseAdapter();
    void LaunchSave();
	Sexy::IPurchaseAdapter* CreatePurchaseAdapter();
	void OnAppResumeFocus();
	bool ExitGame();
	bool LaunchMoreGamesWebpage();
	std::string GetPurchasePlatform();

	PurchaseChannel m_purchaseChannel;
	bool m_bChinaMobilePurchase;
	bool m_bChinaMobileMMPurchase;
	bool m_bTWPurchase;
	std::map<int, int> m_provinces;
	SexyString  GetAboutContentStringId();

	void DoOfflinePayment(const std::string& i_userId);
	void DoValidationPayment(const std::string& i_orderId, const std::string& i_userId);
	bool IsInPurchase() { return m_purchaseState == PURCHASESTATE_WaitingForResponse; }
	void OnNotifyPurchaseResult(bool i_success, const std::string& i_skuId, int i_errorCode);
	void LostPurchaseSuccessed(std::string sku_id);
	void onLostPurchaseDialogButtonPressed();
    
    bool NeedPurchaseWhite();
    bool NeedShowChannelActivity();
    std::string GetChannelID();
    std::string GetUniqueID();
    std::string GetUniqueCharacterID();
	std::string GetChannelUpdateUrl();
	std::string GetDeviceID();
	std::string GetSignature();
    void QueryOrder(const std::string& product_id);

    void CheckRedeemOrders();

    int GetRedeemOrders(std::map<std::string, RedeemInfo>& validOrders);

    void ShowGameCommunity();

    void CheckGameCenterStatus();
    std::string GetGameCenterUrl();

    void Consume(const std::string& i_payCode, const std::string& i_orderNumber);

    void CheckSpecialRedeem();

    ProductInfo GetProductInfo(const std::string& productId);

    void requestLostPayment();

#endif
    void ShowAuthIDDialog();

    void PurchaseSuccessed(std::string orderNumber, std::string sku_id, const std::vector<struct PaymentBundleInfo>& i_bundleInfos, bool i_lostPurchase = false);

	//IPaymentMonitor
	//PVZ2_CHINESE_START
	virtual void PurchaseDriverPaymentIncomplete(IPurchaseDriver* merch, const std::string& productId, IPurchaseDriver::CauseForIncompletion);
	//PVZ2_CHINESE_END
	virtual void PurchaseDriverPaymentComplete(Sexy::IPurchaseDriver* merch, const std::string& productId);
	virtual void PurchaseDriverPaymentComplete( IPurchaseDriver* merch, const std::string& receiptId, const std::string& receipt, const std::string& productId );
    virtual void PurchaseDriverPaymentDeferred( IPurchaseDriver* merch, const std::string& productId );
    

#ifdef HOST_IPHONEOS
	//NetworkServiceListener
	virtual void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) {}
	virtual void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context ) {}
	virtual void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
#endif
	Sexy::IPurchaseDriver* m_purchaseDriver;

	void Update();
    void UpdateDialog();
    void ClearTempPurchaseInfo();
    PurchaseInfo GetTempPurchaseInfo();
    bool HandlePurchaseNow(PurchaseInfo purchaseinfo);
    void DelayRestorePurchase(PurchaseInfo purchaseinfo);
    bool HasTmpPurchase();

	void StartNewCartInstance(const std::string& i_entrySource, const std::string& i_type, const std::string& i_subType);
	void EndCartInstance();
	const CartInstanceInfo& GetCartInfo() { return m_cartInstanceInfo; }
	
	void NDREChargeReward(int price, std::string sku_id);
private:
    void SetRechargeBundleObjectID(int objectID);
    int GetRechargeBundleObjectID();
    
    void SetArtifactPresentBundleObjectID(int objectID);
    int GetArtifactPresentBundleObjectID();

	void onDialogButtonPressed();
	void onPurchaseConfirm(class MagentoProductProps* purchaseProps, const std::string& orderNumber);
    void onValidateChargeFinish(bool i_success);
    void onNotifyAuthPaymentResult(bool i_success);
    void makePayment();
    void createPayment(MagentoProductProps* purchaseProps);
    void validatePayment(const std::string& i_productId, const std::string& i_orderNumber);
    void syncPayment(const std::string& i_productId, const std::string& i_orderNumber, const std::string& i_objectType, bool i_lostPurchase);
    void onNotifyPurchaseValidation(const std::string& i_orderNumber, const std::string& i_skuId, const std::vector<struct PaymentBundleInfo>& i_bundleInfos,
    		int i_status);
    void OnNotifyPurchaseResult(int i_result, const std::string& i_orderNumber, const std::string& i_skuId, const std::vector<struct PaymentBundleInfo>& i_bundleInfos);
    void onNotifyLostPurchase(const std::vector<struct NetworkPaymentInfo>& i_infos);
    void onSyncPayment(const std::string& i_orderNumber, const std::string& i_skuId, bool i_lostPurchase, std::vector<S2C_BonusInfo> bonuslist);
    bool validateTimeout();
    bool validateRetry();
    void onMsgError(int erroId, const std::string& requestID);
    void PurchaseFailed();
    void showLostPurchaseDialog(const std::string& i_skuId);

	CartInstanceInfo m_cartInstanceInfo;
	PurchaseState m_purchaseState;
	PaymentInfo m_paymentInfo;
	
#ifdef HOST_IPHONEOS
//PVZ2_CHINESE_BEGIN
    // added by weiqi.zhong
    std::string m_receipt;
    RvsChecker m_rvsChecker;
    bool m_bConnected;
    bool m_bRefresh;
    int m_retries;
    bool m_recieptUsed;

    pvztime_t m_WatingRestoreReceipt;
//PVZ2_CHINESE_END
#endif
    int m_watingTimes;
    std::string m_lostProductId;
//    int m_objectId;
    bool m_bGetLostProduct;
	PlayerInfo* m_playerInfo;
	bool m_bShowDialog;
	bool m_bNeedShowDialog;
    
    bool m_HasTempPurchaseInfo;
    PurchaseInfo m_tempPurchaseInfo;
    pvztime_t m_waitingResultTime;
    pvztime_t m_waitingCD;
    bool m_sendingRequest;
    int m_objectId;
};

namespace Message
{
	void PurchaseDialogClosed();
	void NotifyBundlePurchased(int i_type, const std::vector<struct PaymentBundleInfo>& i_infos);
}

#endif /* defined(__PlantsVersusZombies2__PurchaseBroker__) */
