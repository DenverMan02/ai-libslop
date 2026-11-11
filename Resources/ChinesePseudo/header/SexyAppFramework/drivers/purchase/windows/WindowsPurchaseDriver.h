#ifndef WINDOWS_PURCHASEDRIVER_H_INCLUDED
#define WINDOWS_PURCHASEDRIVER_H_INCLUDED

#include "IPurchaseDriver.h"

namespace Sexy 
{
	class WindowsPurchaseDriver : public IPurchaseDriver 	
	{
	public:
		WindowsPurchaseDriver();
		virtual ~WindowsPurchaseDriver();

		virtual void SetPaymentMonitor( IPaymentMonitor* monitor );
		virtual void Refresh(  const StructuredData* productIds, RefreshCallback callback );
		virtual bool CanMakePayments();
		virtual bool HasCatalogData();
		virtual bool GetProduct( const std::string& productId, Product* product );
		virtual bool ProductTypeIsSupported( ProductType prodType );
		virtual void RequestPayment( const std::string& productId );
		virtual void RestorePurchases( RestoreCallback callback );
		virtual void ConfirmDelivery( const std::string& receiptId );
		virtual bool HasUnconfirmedPayments();
	protected:
		IPaymentMonitor* mPaymentMonitor;
		std::string mTokenUrl;
		RefreshCallback mRefreshCallback;
		RestoreCallback mRestoreCallback;
	};

}

#endif
