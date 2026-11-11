
#pragma once
#include "IPurchaseDriver.h"
#include "Common.h"
#include "RtDelegate.h"
#import <StoreKit/StoreKit.h>
using namespace Sexy;

namespace Sexy
{
	class IOSPurchaseDriver;
}

@interface ProductsRequestDelegate : NSObject<SKProductsRequestDelegate>
{
	IOSPurchaseDriver* driver;
}
@property (assign) IOSPurchaseDriver* driver;
@end

@interface TransactionObserver : NSObject< SKPaymentTransactionObserver >
{
	IOSPurchaseDriver* driver;
}
@property (assign) IOSPurchaseDriver* driver;
@end

namespace Sexy
{
	
	class IOSPurchaseDriver : public IPurchaseDriver
	{
	public:
		
		IOSPurchaseDriver();
		~IOSPurchaseDriver();

		void SetPaymentMonitor( IPaymentMonitor* monitor );
		void Refresh( const StructuredData* productIds, RefreshCallback callback );
		bool CanMakePayments() ;
		bool HasCatalogData();
		bool GetProduct( const std::string& productId, Product* product );
		bool ProductTypeIsSupported( ProductType prodType );
		void RequestPayment( const std::string& productId );
		void RestorePurchases( RestoreCallback callback );
		void ConfirmDelivery( const std::string& receiptId );
		bool HasUnconfirmedPayments();
		
		void ProductsRequestDidReceiveResponse( SKProductsResponse* response );
		void RequestDidFailWithError( NSError* error );
		void PaymentQueueUpdatedTransactions( SKPaymentQueue* queue, NSArray* transactions );
		void PaymentQueueRemovedTransactions( SKPaymentQueue* queue, NSArray* transactions );
		void PaymentQueueRestoreCompletedTransactionsFailedWithError( SKPaymentQueue* queue, NSError* error );
		void PaymentQueueRestoreCompletedTransactionsFinished( SKPaymentQueue* queue );
		
		//PVZ2_CHINESE_START
		void ProcessSuccessfulTransaction( NSString* transactionIdentifier, NSData* transactionReceipt, NSString *productIdentifier , bool needTransactionID = false);
		//PVZ2_CHINESE_END
		
	protected:
		
		void SetShadowTransaction( SKPaymentTransaction* transaction );
		void RemoveShadowTransaction( SKPaymentTransaction* transaction );
		bool TransactionAndItsReceiptValid( SKPaymentTransaction* transaction );
		bool CheckReceiptSecurity( NSData* purchaseInfoData, NSString* signatureString, CFDateRef purchaseDate );
		bool TransactionDetailsMatchPurchaseInfo( SKPaymentTransaction* transaction, NSDictionary* purchaseInfoDict );
		
		NSArray* mProducts;
		SKProductsRequest* mProductsRequest;
		ProductsRequestDelegate* mProductsRequestDelegate;
		TransactionObserver* mTransactionObserver;
		NSMutableDictionary* mShadowQueue;
		IPaymentMonitor* mPaymentMonitor;
		RefreshCallback mRefreshCallback;
		RestoreCallback mRestoreCallback;
		NSMutableDictionary* mPurchaseInfoCache;
    };		
}
