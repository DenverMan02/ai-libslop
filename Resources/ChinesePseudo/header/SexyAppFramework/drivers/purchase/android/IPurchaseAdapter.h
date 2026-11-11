#ifndef PAYADAPTER_H_INCLUDED
#define PAYADAPTER_H_INCLUDED

#include "Common.h"
#include "AndroidPurchaseDriver.h"
#include "drivers/app/android/JavaBound.h"
#include "drivers/app/android/AndroidAppDriver.h"
#include <list>

namespace Sexy
{
	struct ProductInfo {
		ProductInfo()
		{
			productIdentifier = "";
			productCode = "";
		}
		std::string productIdentifier;
		std::string productCode;
		std::string productName;
		int productPrice;
		int productCount;
	};

	class IPurchaseAdapter {
	public:
		enum ResultCode {
			BILLING_RESULT_SUCCESS = 0,
			BILLING_RESULT_FAILED,
			BILLING_RESULT_CANCELED,
			BILLING_RESULT_ALREADY_PAID
		};

		IPurchaseAdapter();
		virtual ~IPurchaseAdapter();
		// check system or network if can pay
		virtual bool CanPay() = 0;

		// Initialize sdk or some configure
		virtual void Initialize();
		virtual void Destory();
		virtual void OnResume();

		virtual bool ExitGame();
		virtual bool LaunchMoreGamesWebpage();
		virtual std::string GetPurchasePlatform() = 0;
		virtual bool NeedShowDialog();
		virtual SexyString GetAboutContentStringId() = 0;
		virtual int GetTodayRechargeMax() = 0;
		virtual int GetMonthRechargeMax() = 0;
		
		virtual ProductInfo GetProductInfo(const std::string& productId);
		// request pay for product
		virtual void RequestPay(const std::string& productId, const std::string& orderNumber);
		virtual void QueryOrder(const std::string& productId);

		virtual void RequestLaunchSave();
		virtual void SetPayParam();
		virtual void SetPurchaseDriver( AndroidPurchaseDriver* purchaseDriver );

		virtual void OnPaymentComplete( const std::string& receipt );
		virtual void OnPaymentIncomplete( const IPurchaseDriver::CauseForIncompletion& cause );

		// add for TW validation payment
		virtual void RequestValidationPayment(const std::string& productId, const std::string& i_orderId, const std::string& i_userId) {}

		virtual bool NeedPurchaseWhite() {return true;}

		virtual bool NeedShowChannelActivity() {return false;}

		virtual std::string GetChannelID() { return ""; }
		virtual std::string GetChannelUpdateUrl() { return ""; }
		virtual std::string GetUniqueID() {return ""; }
		virtual std::string GetUniqueCharacterID() {return ""; }
		virtual void CheckRedeemOrders() {}

		virtual int GetRedeemOrders(std::map<std::string, RedeemInfo>& validOrders) { return 0; }

		virtual void ShowGameCommunity() {}

		virtual std::string GetDeviceID() { return ""; }

		virtual std::string GetSignature() { return ""; }

		virtual void Consume(const std::string& i_payCode, const std::string& i_orderNumber) {}

		virtual void CheckSpecialRedeem() {}

		virtual void CheckGameCenterStatus() {}

		virtual std::string GetGameCenterUrl() { return ""; }


	protected:
		AndroidPurchaseDriver *mPurchaseDriver;
		std::string mProductId;

	};

}
#endif
