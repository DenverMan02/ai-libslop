
#pragma once
#include "IPurchaseDriver.h"
#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"
#include "drivers/app/android/AndroidAppDriver.h"

namespace Sexy
{
	class GooglePlayPurchaseDriver
		: public IPurchaseDriver
		, public JavaBound< GooglePlayPurchaseDriver >
	{
	public:
		
		static IPurchaseDriver* CreatePurchaseDriver( const std::string publicKey );
		
		GooglePlayPurchaseDriver( const std::string &publicKey );
		~GooglePlayPurchaseDriver();

		void SetPaymentMonitor( IPaymentMonitor* monitor );
		void Refresh(  const StructuredData* productIds, RefreshCallback callback );
		bool CanMakePayments();
		bool HasCatalogData();
		bool GetProduct( const std::string& productId, Product* product );
		bool ProductTypeIsSupported( ProductType prodType );
		void RequestPayment( const std::string& productId, const std::string& orderNumber );
		void RestorePurchases( RestoreCallback callback );
		void ConfirmDelivery( const std::string& receiptId );
		bool HasUnconfirmedPayments();

	private:
		void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
		static JavaMethod<void>     JavaRefresh;
		static JavaMethod<void>     JavaClose;
		static JavaMethod<jboolean> JavaCanMakePayments;
		static JavaMethod<jboolean> JavaProductTypeIsSupported;
		static JavaMethod<void>     JavaRequestPayment;
		static JavaMethod<void>     JavaConfirmDelivery;
		static JavaMethod<jboolean> JavaHasUnconfirmedPayments;
        static JavaClass            JavaStringClass;
        static JavaClass            JavaSkuDetailsClass;
        static JavaMethod<jstring>  JavaGetSku;
        static JavaMethod<jstring>  JavaGetPrice;
        static JavaMethod<jstring>  JavaGetTitle;
        static JavaMethod<jstring>  JavaGetDescription;

		void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );
		static void DidRefreshHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jobjectArray skus );
		static void PaymentCompleteHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jstring receiptId, jstring receipt );
		static void PaymentIncompleteHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jstring productId, jint cause );

		void OnDidRefresh( const jobjectArray &skus );
		void OnPaymentComplete( const std::string& receiptId, const std::string& receipt );
		void OnPaymentIncomplete( const std::string& productId, const CauseForIncompletion& cause );
        
		IPaymentMonitor* mPaymentMonitor;
		RefreshCallback mRefreshCallback;
        
        std::map< std::string, IPurchaseDriver::Product > mProducts;
	};
	
}

