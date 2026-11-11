
#pragma once
#include "Common.h"
#include "RtDelegate.h"
#include <string>
#include <vector>
#include <map>

namespace Sexy
{
	class StructuredData;
	class IPaymentMonitor;
	
	class IPurchaseDriver
	{
	public:

        /**
         * Create the purchase driver. publicKet is your application's public key on Google Play,
         * and is ignored on iOS.
         */
		static IPurchaseDriver* CreatePurchaseDriver( const std::string publicKey = "");
		
		enum ProductType
		{
			Consumable,
			Restorable,
			Subscription,
		};
		
		enum CauseForIncompletion
		{
			Error,
			Canceled,
			AlreadyPaid,
			//PVZ2_CHINESE_START
            NoProductFound,
			//PVZ2_CHINESE_END
			UserNotAuthorized,
            ServiceUnavailable,
#ifdef HOST_IPHONEOS
            RecieptUsed,
#endif
            Pending,                // there is already a purchase pending on the given item, so you can't buy another one
            ValidateServerUnavailable,
            ValidateServerError,
            ValidateCheat,
            //PVZ2_CHINESE_START
            //for ios purchase
            TransactionStateFailedError,
            TransactionStatePurchasedError,
            TransactionStateRestoredError,
            //PVZ2_CHINESE_END
		};
		
		struct Product
		{
			std::string productIdentifier;
			SexyString localizedDescription;
			SexyString localizedTitle;
			SexyString localizedPrice;
		};
		
		//PVZ2_CHINESE_START
		typedef Delegate2<IPurchaseDriver*, bool> RefreshCallback;
		//PVZ2_CHINESE_END
		typedef Delegate2<IPurchaseDriver*,bool> RestoreCallback;
		
		virtual ~IPurchaseDriver() {}
		
		/**
		 *
		 */
		virtual void SetPaymentMonitor( IPaymentMonitor* monitor ) = 0;
		
		/**
		 * Check availability of service, update products, etc.
		 * Will result in a call to IPurchaseListener::PaymentServiceAvailable.
		 */
		virtual void Refresh( const StructuredData* productIds, RefreshCallback callback ) = 0;
		
		/**
		 * Returns true if a payment system is available and enabled for the user.
		 * Value is not meaningful until after Refresh() has been called and the listener
		 * has received a PaymentServiceAvailable callback.
		 */
		virtual bool CanMakePayments() = 0;
		
		/**
		 * Returns true if the payment system has supplied catalog data.
		 * If it has, then it can be accessed with GetCatalogData.
		 */
		virtual bool HasCatalogData() = 0;
		
		/**
		 * Get a copy of the product information for the specified product id.
		 * @return true if the product was found in the catalog.
		 */
		virtual bool GetProduct( const std::string& productId, Product* product ) = 0;
		
		/**
		 * Returns true if the specified product type is supported by the payment system.
		 * Value is not meaningful until after Refresh() has been called and the listener
		 * has received a PurchaseManagerDidRefresh() callback.
		 */
		virtual bool ProductTypeIsSupported( ProductType prodType ) = 0;
		
		/**
		 * Initiate the purchase of a product.  If there are no errors,
		 * the listener will receive a PurchaseManagerPaymentComplete() callback.
		 * After verification of the receipt, call ConfirmDelivery() to tell the
		 * payment service that the product has been delivered.
		 */
		virtual void RequestPayment( const std::string& productId, const std::string& orderNumber ) = 0;
		
		/**
		 *
		 */
		virtual void RestorePurchases( RestoreCallback callback ) = 0;
		
		/**
		 * Tells the driver that the specified receipt has been verified.
		 */
		virtual void ConfirmDelivery( const std::string& receiptId ) = 0;
		
		virtual bool HasUnconfirmedPayments() = 0;
		
		virtual void QueryOrder( const std::string& productId ) = 0;

	};
	
	class IPaymentMonitor
	{
	public:
		virtual void PurchaseDriverPaymentComplete( IPurchaseDriver* merch, const std::string& receiptId, const std::string& receipt, const std::string& productId ) = 0;
		virtual void PurchaseDriverPaymentIncomplete( IPurchaseDriver* merch, const std::string& productId, IPurchaseDriver::CauseForIncompletion ) = 0;
		virtual void PurchaseDriverPaymentComplete( IPurchaseDriver* merch, const std::string& productId ) = 0;
        virtual void PurchaseDriverPaymentDeferred( IPurchaseDriver* merch, const std::string& productId ) = 0;
	};
	
}

