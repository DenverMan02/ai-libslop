
#pragma once
#include "IPurchaseDriver.h"


namespace Sexy
{
	class AndroidNullPurchaseDriver : public IPurchaseDriver
	{
	public:
		static IPurchaseDriver* CreatePurchaseDriver( const std::string publicKey );

		void SetPaymentMonitor( IPaymentMonitor* monitor );
		void Refresh( const StructuredData* productIds, RefreshCallback callback );
		bool CanMakePayments();
		bool HasCatalogData();
		bool GetProduct( const std::string& productId, Product* product );
		bool ProductTypeIsSupported( ProductType prodType );
		void RequestPayment( const std::string& productId, const std::string& orderNumber );
		void RestorePurchases( RestoreCallback callback );
		void ConfirmDelivery( const std::string& receiptId );
		bool HasUnconfirmedPayments();

		AndroidNullPurchaseDriver();
		~AndroidNullPurchaseDriver();
    };		
}
