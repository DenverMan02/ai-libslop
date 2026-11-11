#ifndef ANDROIDPURCHASEDRIVER_H_INCLUDED
#define ANDROIDPURCHASEDRIVER_H_INCLUDED

#include "IPurchaseDriver.h"

namespace Sexy {
	class IPurchaseAdapter;

	struct RedeemInfo
	{
		RedeemInfo()
		{
			payCode = "";
			orderNumber = "";
		}
		std::string payCode;
		std::string orderNumber;
	};

	class AndroidPurchaseDriver : public IPurchaseDriver 	{
	public:
		AndroidPurchaseDriver();
		virtual ~AndroidPurchaseDriver();

		virtual void SetPaymentMonitor( IPaymentMonitor* monitor );
		virtual void Refresh(  const StructuredData* productIds, RefreshCallback callback );
		virtual bool CanMakePayments();
		virtual bool HasCatalogData();
		virtual bool GetProduct( const std::string& productId, Product* product );
		virtual bool ProductTypeIsSupported( ProductType prodType );
		virtual void RequestPayment( const std::string& productId, const std::string& orderNumber );
		virtual void RestorePurchases( RestoreCallback callback );
		virtual void ConfirmDelivery( const std::string& receiptId );
		virtual bool HasUnconfirmedPayments();
		void StartItemPurchase();
		void StartRecharge();
		void setParam();
		void OnPaymentComplete( const std::string& productId);
		void OnPaymentComplete( const std::string& receiptId, const std::string& receipt, const std::string& productId );
		void OnPaymentIncomplete( const std::string& productId, const IPurchaseDriver::CauseForIncompletion& cause );

		void SetPurchaseAdapter(IPurchaseAdapter *purchaseAdapter);
		IPurchaseAdapter* GetPurchaseAdapter();
		void Init();
		void OnResume();
		bool ExitGame();
		bool LaunchMoreGamesWebpage();
		int GetTodayRechargeMax();
		int GetMonthRechargeMax();
		std::string GetPurchasePlatform();
		bool NeedShowDialog();
		SexyString	GetAboutContentStringId();

		void RequestValidationPayment(const std::string& productId, const std::string& i_orderId, const std::string& i_userId);
		bool NeedPurchaseWhite();
		void QueryOrder(const std::string& productId);
		bool NeedShowChannelActivity();
		std::string GetChannelID();
		std::string GetChannelUpdateUrl();
		std::string GetUniqueID();
		std::string GetUniqueCharacterID();
		virtual void CheckRedeemOrders();
		virtual int GetRedeemOrders(std::map<std::string, RedeemInfo>& validOrders);
		virtual void ShowGameCommunity();
		std::string GetDeviceID();
		std::string GetSignature();
		void Consume(const std::string& i_payCode, const std::string& i_orderNumber);
		virtual struct ProductInfo GetProductInfo(const std::string& productId);
		void CheckSpecialRedeem();
		void CheckGameCenterStatus();
		std::string GetGameCenterUrl();
	private:

		IPaymentMonitor* mPaymentMonitor;
		IPurchaseAdapter *mPurchaseAdapter;
		std::string mTokenUrl;
		RefreshCallback mRefreshCallback;
		RestoreCallback mRestoreCallback;
	};

}

#endif
