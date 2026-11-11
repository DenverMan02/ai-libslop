#ifndef ANDROIDHTTPTRANSACTION_H_INCLUDED
#define ANDROIDSHTTPTRANSACTION_H_INCLUDED
#pragma once
#include "IHttpDriver.h"
#include "Common.h"
#include "drivers/app/android/AndroidAppDriver.h"
#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"

#include <queue>

namespace Sexy
{
	class AndroidHttpDriver;

	class AndroidHttpTransaction
		: public IHttpTransaction
		, public JavaBound< AndroidHttpTransaction >
	{
	public:

		AndroidHttpTransaction( const std::string& method, const std::string& url , uint32 responseBufferSize );

		void SetListener( IHttpListener* listener );
		void SetUserData( void* userData );
		void SetRequestHeader( const std::string& name, const std::string& value );
		void SetRequestBody( const void* data, size_t length );
		void SetResponseBuffer( void* buffer, size_t bufferSize );
		void SetTimeout( int seconds );
   		void SetSlackCertificateValidation( bool slack );
   		void SetBasicAuth( const std::string& username, const std::string& password );

		void Start();
		void Release();
		void Update();

   		std::string GetRequestUrl();
		void* GetUserData();
		int GetStatusCode();
		std::string GetStatusLine();
		int GetResponseLength();
		std::string GetResponseHeader( const std::string& key );

		std::string GetSerializedRequest();
		std::string GetErrorMessage();

	protected:

		void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
		static JavaMethod<void> JavaSetRequestHeader;
		static JavaMethod<void> JavaSetRequestBody;
		static JavaMethod<void> JavaSetTimeout;
		static JavaMethod<void> JavaStart;
		static JavaMethod<jint> JavaGetStatusCode;
		static JavaMethod<jstring> JavaGetStatusLine;
		static JavaMethod<jint> JavaGetResponseLength;
		static JavaMethod<jstring> JavaGetResponseHeader;
		static JavaMethod<void> JavaRelease;

		void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );
		static void OnReceivedResponseHook( JNIEnv* env, jobject javaObject, jlong nativeTransaction );
		static void OnReceivedDataHook( JNIEnv* env, jobject javaObject, jlong nativeTransaction, jbyteArray data, jint dataSize );
		static void OnTransactionCompleteHook( JNIEnv* env, jobject javaObject, jlong nativeTransaction );
		static void OnTransactionErrorHook( JNIEnv* env, jobject javaObject, jlong nativeTransaction );
		static void OnTransactionCleanupHook( JNIEnv* env, jobject javaObject, jlong nativeTransaction );

		~AndroidHttpTransaction();

		IHttpListener* mListener;
		void* mUserData;
		int mTransactionNum;

		struct ReceivedDataCallback
			: public DelegateClosure< ReceivedDataCallback, AndroidAppDriver::Callback >
		{
			AndroidHttpTransaction* transaction;
			char* data;
			size_t dataSize;

			void Func()
			{
				transaction->OnReceivedData( data, dataSize );
				transaction->ReleaseReceivedDataCallback( this );
			}
		};

		ReceivedDataCallback* CreateReceivedDataCallback( size_t dataSize );
		void ReleaseReceivedDataCallback( ReceivedDataCallback* callback );

		void OnReceivedResponse();
		void OnReceivedData( void* data, size_t dataSize );
		void OnTransactionComplete();
		void OnTransactionError();
		void OnTransactionCleanup();
	};
}

#endif

